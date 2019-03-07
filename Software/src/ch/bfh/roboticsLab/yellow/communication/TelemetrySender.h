#line 2 "ch/bfh/roboticsLab/yellow/communication/TelemetrySender.h"
/* TelemetrySender.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <ch/bfh/roboticsLab/yellow/RealtimeThread.h>
#include <ch/bfh/roboticsLab/yellow/communication/SerialServer.h>
#include <ch/bfh/roboticsLab/yellow/communication/ProtocolInterface.h>
#include <ch/bfh/roboticsLab/yellow/StateMachine.h>
#include <ch/bfh/roboticsLab/yellow/driver/LIDAR.h>
#include <ch/bfh/roboticsLab/yellow/LidarAnalysis.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace communication {

/**
 * This class implements a real-time thread that sends telemetry data at regular intervals.
 * @author gabriel.gruener@bfh.ch
 */
class TelemetrySender : public RealtimeThread {

public:

  /**
   * Retrieve the singleton instance of the telemetry sender.
   * @return The TelemetrySender singleton.
   */
  static TelemetrySender& getInstance();

  virtual ~TelemetrySender();

  /**
   * Request that Lidar data be included in the telemetry packet.
   */
  void requestLidar(const uint16_t sendLidarStep);

  /** Request that LIDAR line data be included in the telemetry packet. */
  void requestLidarLines(const ch_bfh_roboticsLab_yellow_communication_LidarLinesParameters& params);

private:
  /** Thread stack size in bytes */
  static constexpr uint32_t STACK_SIZE = 0x4000; // Note big size is due to Telemetry frame with LIDAR data.
  /** Thread period, given in [s]. */
  static constexpr float PERIOD = 0.2f;

  /** Reference to SerialServer to send the data. */
  SerialServer& serialServer;
  /** Reference to StateMachine to retrieve state and controller information. */
  StateMachine& stateMachine;
  /** Reference to Lidar sensor. */
  yellow::driver::LIDAR& lidar;
  /** Reference to Lidar analysis. */
  yellow::LidarAnalysis& lidarAnalysis;

  /** Flag whether lidar data should be transmitted. */
  uint16_t sendLidarStep;

  bool sendLidarLines;
  /** LIDAR line analysis parameters */
  ch_bfh_roboticsLab_yellow_communication_LidarLinesParameters lidarLinesParams;

  /**
   * Create a new TelemetrySender.
   * @param serialServer Reference to the SerialServer.
   * @param protocolInterface Reference to the ProtocolInterface.
   * @param stateMachine Reference to the StateMachine.
   */
  TelemetrySender();
  /** Private empty constructor to force usage of #getInstance. */
  TelemetrySender(TelemetrySender const&);
  /** Private equals operator to force usage of #getInstance. */
  void operator=(TelemetrySender const&);


  /* Implements RealtimeThread::run */
  virtual void run();

};
}
}
}
}
}
