#line 2 "ch/bfh/roboticsLab/yellow/communication/TelemetrySender.cpp"
/* TelemetrySender.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <mbed.h>

#include <ch/bfh/roboticsLab/yellow/communication/TelemetrySender.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace communication {

TelemetrySender& TelemetrySender::getInstance() {
  static TelemetrySender telemetrySender;
  return telemetrySender;
}

TelemetrySender::TelemetrySender() :
    RealtimeThread(PERIOD, osPriorityNormal, STACK_SIZE), serialServer(SerialServer::getInstance()), stateMachine(StateMachine::getInstance()), lidar(
        driver::LIDAR::getInstance()), lidarAnalysis(LidarAnalysis::getInstance()), sendLidarStep(0), sendLidarLines(false) {
}

TelemetrySender::~TelemetrySender() {
}

void TelemetrySender::run() {

  Stream outgoing;
  while (waitForNextPeriod()) {

    ch_bfh_roboticsLab_yellow_communication_Telemetry telemetry = { };

    // Report timestamp
    telemetry.timestamp = (us_ticker_read() / 1000);
    telemetry.has_timestamp = true;

    // Report current state
    telemetry.state.stateName = ProtocolInterface::getStateName(stateMachine.getState());
    telemetry.has_state = true;

    // Report estimated odometry
    telemetry.odometry.pose.x = stateMachine.controller.getX();
    telemetry.odometry.pose.y = stateMachine.controller.getY();
    telemetry.odometry.pose.alpha = stateMachine.controller.getAlpha();
    telemetry.has_odometry = true;

    // Report IR sensors
    telemetry.ir.sensor[0].distance = peripherals::irSensors[0];
    telemetry.ir.sensor[1].distance = peripherals::irSensors[1];
    telemetry.ir.sensor[2].distance = peripherals::irSensors[5];
    telemetry.ir.sensor_count = 3;
    telemetry.has_ir = true;

    // Report Lidar if requested
    if (sendLidarStep > 0) {

      // Step size of lidar scan to send [deg]. (e.g. =2 send every 2 deg)
      uint16_t counter = 0;
      for (uint16_t i = 0; i < 360; i += sendLidarStep) {
        telemetry.lidar.points[counter].angle = i;
        telemetry.lidar.points[counter].distance = lidar.getDistance(i);
        telemetry.lidar.points[counter].quality = lidar.getQuality(i);
        telemetry.lidar.points[counter].has_quality = true;
        ++counter;
      }
      telemetry.lidar.points_count = counter;
      telemetry.has_lidar = true;
      // Reset Lidar step to 0 as this is a one-time request
      sendLidarStep = 0;
    }

    // Report Lidar lines if requested
    if (sendLidarLines) {
      LidarAnalysis::LineContainer lines = lidarAnalysis.getLines(
          lidarLinesParams.has_minRangeDistance ? lidarLinesParams.minRangeDistance : LidarAnalysis::MIN_RANGE_DISTANCE_DEFAULT,
          lidarLinesParams.has_maxLineImprecision ? lidarLinesParams.maxLineImprecision : LidarAnalysis::MAX_LINE_IMPRECISION_DEFAULT,
          lidarLinesParams.has_maxAngleBetweenLines ? lidarLinesParams.maxAngleBetweenLines : LidarAnalysis::MAX_ANGLE_BETWEEN_LINES_DEFAULT);
      // Note: for protobuf limiting max number of lines reported (see yellow.options next to yellow.proto)
      const uint8_t MAX_LINES = 20;
      const uint8_t size = lines.size() < MAX_LINES ? lines.size() : MAX_LINES;

      for (uint8_t i = 0; i < size; ++i) {
        LidarAnalysis::Line l = lines.at(i);
        telemetry.lidarLines.lines[i].start.x = l.first.x;
        telemetry.lidarLines.lines[i].start.y = l.first.y;
        telemetry.lidarLines.lines[i].end.x = l.second.x;
        telemetry.lidarLines.lines[i].end.y = l.second.y;
        telemetry.lidarLines.lines[i].has_end = true;
      }
      telemetry.lidarLines.lines_count = size;
      telemetry.has_lidarLines = true;
      sendLidarLines = false;
    }

    serialServer.send(ProtocolInterface::reportTelemetry(telemetry, outgoing));
  }
}

void TelemetrySender::requestLidar(const uint16_t sendLidarStep) {
  this->sendLidarStep = sendLidarStep;
}

void TelemetrySender::requestLidarLines(const ch_bfh_roboticsLab_yellow_communication_LidarLinesParameters& params) {
  this->lidarLinesParams = params;
  sendLidarLines = true;
}

}
}
}
}
}
