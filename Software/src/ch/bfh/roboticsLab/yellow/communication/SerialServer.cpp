#line 2 "ch/bfh/roboticsLab/yellow/communication/SerialServer.cpp"
/* SerialServer.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/communication/SerialServer.h>

#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/yellow/Console.h>


namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace communication {

namespace encoder {

SerialEncoder::SerialEncoder() :
    checksum(0) {
}

SerialEncoder::~SerialEncoder() {
}

void SerialEncoder::escapeData(const uint8_t data) {
  checksum += data;
  switch (data) {
  case START_DELIMITER:
  case ESCAPE_BYTE: {
    stream.push_back(ESCAPE_BYTE);
    stream.push_back(data ^ ESCAPE_MODIFIER);
    break;
  }
  default:
    stream.push_back(data);
    break;
  }
}

Stream& SerialEncoder::encode(const Stream& message, Stream& encodedMessage) {

  stream.clear();
  stream.push_back(START_DELIMITER);

  uint16_t size = message.size();
  escapeData((size & 0xff00) >> 8);
  escapeData((size & 0x00ff));

  checksum = 0;  // checksum does not include start delimiter and size
  for (int i = 0; i < size; ++i) {
    escapeData(message[i]);
  }

  // Add checksum
  escapeData(crc(checksum));

  encodedMessage = stream;
  return encodedMessage;
}

SerialDecoder::SerialDecoder() :
    readState(DecoderState::WAITING_FOR_HEADER), escapedByte(false), payloadSize(0), byteCounter(0) {
}

SerialDecoder::~SerialDecoder() {
}

Stream& SerialDecoder::getMessage(Stream& incoming) {
  if (readState == DecoderState::DONE)
    incoming = payload;
  return incoming;
}

void SerialDecoder::putc(int data) {

  uint8_t b = static_cast<uint8_t>(data & 0xFF);

  if (readState == DecoderState::WAITING_FOR_HEADER) {
    if (b == START_DELIMITER)
      readState = DecoderState::SIZE_1;
    return;
  }

  if (b == ESCAPE_BYTE) {
    escapedByte = true;
    return;
  }

  if (escapedByte) {
    b = (b ^ ESCAPE_MODIFIER);
    escapedByte = false;
  }

  switch (readState) {
  case DecoderState::SIZE_1:
    payloadSize = static_cast<uint32_t>(b) << 8;
    readState = DecoderState::SIZE_2;
    break;
  case DecoderState::SIZE_2:
    payloadSize += static_cast<uint32_t>(b);
    byteCounter = 0;
    readState = DecoderState::PAYLOAD;
    break;
  case DecoderState::PAYLOAD:
    payload.push_back(b);
    byteCounter++;
    if (byteCounter == payloadSize)
      readState = DecoderState::CRC_BYTE;
    break;
  case DecoderState::CRC_BYTE: {
    uint32_t checksum = 0;
    for (uint16_t i = 0; i < payload.size(); ++i)
      checksum += payload[i];
    uint8_t myCRC = crc(checksum);
    if (b != myCRC) {
      readState = DecoderState::ERROR;
    }
    readState = DecoderState::DONE;
    break;
  }
  default:
    break;
  }
}

} // namespace encoder

SerialServer& SerialServer::getInstance() {

  static SerialServer serialServer;
  return serialServer;
}

SerialServer::SerialServer() :
    serial(peripherals::wifiSerialTx, peripherals::wifiSerialRx) {

  serial.baud(38400);
  serial.format(8, SerialBase::None, 1);

  // initialize local values
  Console::getInstance().printf("Starting Serial Server...\r\n");
  serial.attach(callback(&SerialServer::getc, this), SerialBase::RxIrq);
}

SerialServer::~SerialServer() {
}

void SerialServer::getc(SerialServer* server) {
  if (server->serial.readable()) {
    int c = server->serial.getc();
    server->decoder.putc(c);
  }
}

void SerialServer::putc(const uint8_t data) {
  while (!serial.writeable())
    Thread::wait(1);
  serial.putc(static_cast<int32_t>(data));
}

void SerialServer::send(const Stream& outgoing) {
  static Stream message;
  encoder.encode(outgoing, message);
  for (uint16_t i = 0; i < message.size(); ++i)
    putc(message[i]);
}

Stream& SerialServer::receive(Stream& incoming) {
  bool block = true;
  while (block) {
    switch (decoder.getState()) {
    case encoder::DecoderState::DONE:
      decoder.getMessage(incoming);
      block = false;
      break;
    case encoder::DecoderState::ERROR:
      block = false;
      break;
    default:
      Thread::wait(1);
    }
  }
  decoder.reset();
  return incoming;
}

}
}
}
}
}
