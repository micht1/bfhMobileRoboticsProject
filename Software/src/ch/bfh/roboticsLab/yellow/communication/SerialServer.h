#line 2 "ch/bfh/roboticsLab/yellow/communication/SerialServer.h"
/* SerialServer.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <string>
#include <deque>

#include <mbed.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace communication {

/** The type to store incoming and outgoing data streams. */
typedef std::deque<uint8_t> Stream;

/** This namespace holds definitions useful to encode and decode messages. */
namespace encoder {
/** The communication message start delimiter. */
static const uint8_t START_DELIMITER = 0x7E;
/** The communication message escape byte. */
static const uint8_t ESCAPE_BYTE = 0x7D;
/** The communication message escape modifier. */
static const uint8_t ESCAPE_MODIFIER = 0x20;

/**
 * Retrieves a cyclic redundancy code (CRC) from a byte array (check)sum.
 * @return The CRC.
 */
inline uint8_t crc(const uint32_t& sum) {
  uint8_t crc = 0xFF - static_cast<uint8_t>(sum & 0xFF);
  return crc;
}

/**
 * This class encodes a byte array creating a packet that can be transfered through a serial interface.
 * @author gabriel.gruener@bfh.ch
 */
class SerialEncoder {

public:

  /** Creates a new SerialEncoder object. */
  SerialEncoder();

  virtual ~SerialEncoder();

  /**
   * Encodes the given byte-string message and puts in the byte-string @c encodedMessage.
   * @param message Message to encode.
   * @param encodedMessage Encoded message.
   * @return reference to @c encodedMessage.
   */
  Stream& encode(const Stream& message, Stream& encodedMessage);

private:
  /** String stream to build the encoded message. */
  Stream stream;

  /**
   * Pushes the given byte data into the underlying stream, escaping it
   * if necessary.
   * @param data The byte data to encode.
   */
  inline void escapeData(const uint8_t data);

  /** Encoded buffer checksum. */
  uint32_t checksum;
};

/**
 * This class defines the serial decoder states.
 * @see SerialDecoder
 */
struct DecoderState {
  /** Enumeration containing the read states. */
  enum Enum {
    /** Waiting for the header byte to arrive. */
    WAITING_FOR_HEADER,
    /** Reading first size byte. */
    SIZE_1,
    /** Reading second size byte. */
    SIZE_2,
    /** Reading payload bytes. */
    PAYLOAD,
    /** Reading CRC byte. Note Macro CRC is defined in a STM32 header */
    CRC_BYTE,
    /** CRC mismatch */
    ERROR,
    /** Done reading, message is ready. */
    DONE
  };
};

/**
 * This class decodes a byte array arriving through a serial interface and allows to retrieve the packet's payload.
 * @author gabriel.gruener@bfh.ch
 */
class SerialDecoder {

public:

  /** Creates a SerialDecoder. */
  SerialDecoder();

  virtual ~SerialDecoder();

  /**
   * Reset the decoder so it is ready to read the next message.
   */
  inline void reset() {
    readState = DecoderState::WAITING_FOR_HEADER;
    payload.clear();
  }

  /**
   * Pushes a received byte into the message, removing escaped bytes and checksum.
   * Updates #readState as the payload is parsed, arriving to the state ReadState::DONE
   * when the message is complete or ReadState::ERROR if an error occurs.
   * @param data the byte received.
   */
  void putc(int data);

  /**
   * Retrieves the current decoder state.
   */
  inline DecoderState::Enum getState() const {
    return readState;
  }

  /**
   * Retrieves an incoming message.
   * Non-blocking operation that puts the message in @c incoming, if available.
   * Otherwise, @c incoming will be returned unchanged.
   * @param incoming Reference to a string object to place the payload.
   * @return reference to @c incoming.
   */
  Stream& getMessage(Stream& incoming);

private:

  /** The read state. */
  DecoderState::Enum readState;

  /** Input buffer flag, whether we just read a escape byte. */
  bool escapedByte;
  /** Payload size. */
  uint32_t payloadSize;
  /** Payload read. */
  Stream payload;
  /** Counter of payload bytes read. */
  uint32_t byteCounter;

};

}

/**
 * This class implements a communication server using a serial interface.
 * @author gabriel.gruener@bfh.ch
 */
class SerialServer {

public:

  /**
   * Retrieve the SerialServer singleton.
   * @return The SerialServer singleton.
   */
  static SerialServer& getInstance();

  /** Delete the serial server object and release all allocated resources. */
  virtual ~SerialServer();

  /**
   * Sends the given string through the serial server by encoding it.
   * @param outgoing string (byte array) to send.
   */
  void send(const Stream& outgoing);

  /**
   * Receives a message arriving to the serial server.
   * Blocks until a message is received or an error happens.
   * If a message is successfully read, its decoded payload is put in @c incoming.
   * @param incoming Reference to an allocated string object to place the incoming message.
   * @return reference to @c incoming.
   */
  Stream& receive(Stream& incoming);

private:

  /** stack size of thread, given in [bytes] */
  static constexpr uint32_t STACK_SIZE = 4096;
  /** the period of the timer interrupt, given in [s] */
  static constexpr float PERIOD = 0.0002f;

  /** Reference to the UART hardware. */
  RawSerial serial;

  /** Serial packet encoder. */
  encoder::SerialEncoder encoder;
  /** Serial packet decoder. */
  encoder::SerialDecoder decoder;

  /** Creates a new SerialServer object that connects to the WiFi interface. */
  SerialServer();
  /** Private empty constructor to force usage of #getInstance. */
  SerialServer(SerialServer const&);
  /** Private equals operator to force usage of #getInstance. */
  void operator=(SerialServer const&);

  /** Callback function called when one byte arrives. */
  static void getc(SerialServer* server);

  /** Writes the given byte data to the underlying serial driver. */
  inline void putc(const uint8_t data);

};

}
}
}
}
}
