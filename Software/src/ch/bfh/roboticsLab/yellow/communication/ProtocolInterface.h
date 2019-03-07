#line 2 "ch/bfh/roboticsLab/yellow/communication/ProtocolInterface.h"
/* ProtocolInterface.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <string>

#include <ch/bfh/roboticsLab/yellow/StateMachine.h>
#include <ch/bfh/roboticsLab/yellow/communication/SerialServer.h>
#include <ch/bfh/roboticsLab/yellow/communication/yellow.pb.h>
#include <fi/kapsi/pb_encode.h>
#include <fi/kapsi/pb_decode.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
/** This namespace holds all communication-related classes. */
namespace communication {

/**
 * This interface defines methods to interact with the communication protocol.
 * The communication protocol generates binary-encoded messages and is based on the protobuf library.
 *
 * Usage:
 * @code
 * communication::ProtocolInterface protocolInterface;
 *
 * // Prepare a telemetry message
 * ch_bfh_roboticsLab_yellow_communication_Telemetry telemetry = {};
 * telemetry.state.state = getStateName(stateMachine.getState());
 * telemetry.has_state = true;
 *
 * telemetry.odometry.pose.x = stateMachine.controller.getX();
 * telemetry.odometry.pose.y = stateMachine.controller.getY();
 * telemetry.odometry.pose.alpha = stateMachine.controller.getAlpha();
 * telemetry.has_odometry = true;
 * std::string outgoing;
 * protocolInterface.reportTelemetry(telemetry, outgoing);
 * // outgoing now contains the binary-encoded byte string.
 *
 * // Decode an incoming telecommand message
 * std::string incoming;
 * ... // Fill incoming with a binary-encoded byte-string telecommand message (e.g. incoming from a client).
 * ch_bfh_roboticsLab_yellow_communication_Telecommand telecommand = protocolInterface.processTelecommand(incoming);
 * if (telecommand.has_state)
 *   printf("Received telecommand.state %d\r\n", telecommand.state.state);
 * @endcode
 *
 * @author gabriel.gruener@bfh.ch
 * @see yellow.proto
 */
class ProtocolInterface {

public:
  /** Creates a protocol interface. */
  ProtocolInterface();

  /** Destroys the object. */
  virtual ~ProtocolInterface();

  /**
   * This method processes an incoming command byte stream and returns the resulting Telecommand object.
   * @param incoming The incoming command.
   * @return The resulting Telecommand.
   * @see ch_bfh_roboticsLab_yellow_communication_Telecommand
   */
  static ch_bfh_roboticsLab_yellow_communication_Telecommand processTelecommand(const Stream& incoming);

  /**
   * Prepares a telemetry message and places it in the @c outgoing byte stream.
   * @param telemetry Reference to the telemetry data to encode in the message.
   * @param outgoing Reference to the outgoing byte stream.
   * @return Reference to @c outgoing.
   * @see ch_bfh_roboticsLab_yellow_communication_Telemetry
   */
  static Stream& reportTelemetry(const ch_bfh_roboticsLab_yellow_communication_Telemetry& telemetry, Stream& outgoing);

  /**
   * Retrieve the communication protocol state name for the given StateMachine state.
   * @param state The StateMachine state.
   * @return The correspoding communication protocol state name.
   */
  static ch_bfh_roboticsLab_yellow_communication_StateName getStateName(yellow::State::Enum state);

  /**
   * Retrieve the StateMachine state for the given communication protocol state name.
   * @param stateName The communication protocol state name.
   * @return The correspoding StateMachine state.
   */
static yellow::State::Enum getState(ch_bfh_roboticsLab_yellow_communication_StateName stateName);

private:

  /** Size of the buffer to place a full Telemetry message. */
  static constexpr uint16_t BUFFER_SIZE = 3200;
  /** Buffer to place the binary-encoded telemetry message. */
  static uint8_t buffer[BUFFER_SIZE];
};

}
}
}
}
}
