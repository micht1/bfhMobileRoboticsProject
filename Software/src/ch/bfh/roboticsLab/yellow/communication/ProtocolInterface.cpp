#line 2 "ch/bfh/roboticsLab/yellow/communication/ProtocolInterface.cpp"
/* ProtocolInterface.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/communication/ProtocolInterface.h>

#include <vector>

#include <ch/bfh/roboticsLab/yellow/Console.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace communication {

uint8_t ProtocolInterface::buffer[ProtocolInterface::BUFFER_SIZE];

ch_bfh_roboticsLab_yellow_communication_Telecommand ProtocolInterface::processTelecommand(const Stream& incoming) {

    ch_bfh_roboticsLab_yellow_communication_Telecommand t = { };
    // Convert the stream to an ordered structure in memory
    std::vector<uint8_t> data(incoming.begin(), incoming.end());
    pb_istream_t inputStream = pb_istream_from_buffer(data.data(), data.size());
    if (!pb_decode(&inputStream, ch_bfh_roboticsLab_yellow_communication_Telecommand_fields, &t)) {
      ::ch::bfh::roboticsLab::yellow::Console::getInstance().printf("Decoding failed: %s\r\n", PB_GET_ERROR(&inputStream));
    }
    return t;
}

Stream& ProtocolInterface::reportTelemetry(const ch_bfh_roboticsLab_yellow_communication_Telemetry& t, Stream& outgoing) {

// Comment/uncomment to report binary-encoded buffer size
//#define YELLOW_PROTOCOL_INTERFACE_CHECK_SIZE
#ifdef YELLOW_PROTOCOL_INTERFACE_CHECK_SIZE
  pb_ostream_t sizestream = { 0 };
  pb_encode(&sizestream, ch_bfh_roboticsLab_yellow_communication_Telemetry_fields, &t);
  ::ch::bfh::roboticsLab::yellow::Console::getInstance()->printf("Encoded size of telemetry is %d\r\n", sizestream.bytes_written);
#endif

  // The pb output stream to perform the protocol binary encoding.
  pb_ostream_t outputStream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool status = pb_encode(&outputStream, ch_bfh_roboticsLab_yellow_communication_Telemetry_fields, &t);
  if (!status) {
    ::ch::bfh::roboticsLab::yellow::Console::getInstance().printf("Encoding failed: %s\r\n", PB_GET_ERROR(&outputStream));
  } else {
    outgoing.clear();
    size_t message_length = outputStream.bytes_written;
    for (size_t i=0; i< message_length; ++i)
      outgoing.push_back(buffer[i]);
  }
  return outgoing;
}

ch_bfh_roboticsLab_yellow_communication_StateName ProtocolInterface::getStateName(State::Enum state) {
  ch_bfh_roboticsLab_yellow_communication_StateName stateName = ch_bfh_roboticsLab_yellow_communication_StateName_OFF;
  switch (state) {
  case yellow::State::OFF:
  case yellow::State::SWITCH_ON:
  case yellow::State::SWITCH_OFF:
  case yellow::State::ON:
    stateName = ch_bfh_roboticsLab_yellow_communication_StateName_OFF;
    break;
  case yellow::State::MANUAL:
    stateName = ch_bfh_roboticsLab_yellow_communication_StateName_MANUAL;
    break;
  case yellow::State::AUTO_REACTIVE:
    stateName = ch_bfh_roboticsLab_yellow_communication_StateName_AUTO_REACTIVE;
    break;
  case yellow::State::AUTO_POSITION:
    stateName = ch_bfh_roboticsLab_yellow_communication_StateName_AUTO_POSITION;
    break;
  }
  return stateName;
}

yellow::State::Enum ProtocolInterface::getState(ch_bfh_roboticsLab_yellow_communication_StateName stateName) {
  yellow::State::Enum state = State::OFF;
  switch (stateName) {
  case ch_bfh_roboticsLab_yellow_communication_StateName_OFF:
    state = State::OFF;
    break;
  case ch_bfh_roboticsLab_yellow_communication_StateName_MANUAL:
    state = State::MANUAL;
    break;
  case ch_bfh_roboticsLab_yellow_communication_StateName_AUTO_REACTIVE:
    state = State::AUTO_REACTIVE;
    break;
  case ch_bfh_roboticsLab_yellow_communication_StateName_AUTO_POSITION:
    state = State::AUTO_POSITION;
    break;
  }
  return state;
}

}
}
}
}
}

