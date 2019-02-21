#line 2 "ch/bfh/roboticsLab/yellow/driver/LIDAR.h"
/* LIDAR.h
 * Copyright (c) ZHAW, BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

#include <vector>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

/**
 * This is a device driver class for the RoboPeak LIDAR A1.
 * @author marcel.honegger@zhaw.ch
 * @author gabriel.gruener@bfh.ch
 */
class LIDAR {

public:

  /** Number of data points of one LIDAR scan (at 1 degree resolution) in degrees. */
  static const uint16_t SCAN_SIZE = 360;

  /**
   * Retrieve the LIDAR singleton.
   * @return The LIDAR singleton.
   */
  static LIDAR& getInstance();

  /**
   * Stops the lidar and deletes this object.
   */
  virtual ~LIDAR();

  /** Starts the Lidar rotation and measurement. */
  void start();

  /** Stops the Lidar rotation and measurement. */
  void stop();

  /**
   * Retrieves the distance measurement of the lidar at a given angle.
   * @param angle The angle in [deg] in the range 0..359.
   * @return The measured distance in [mm].
   */
  int16_t getDistance(int16_t angle);

  /**
   * Retrieve all distances of the latest LIDAR measurement starting from 0 degrees with the given step size.
   * @param step Step angle in degrees (e.g. step = 2: return LIDAR data every 2 degrees). Defaults to 1.
   * @return vector with (#SCAN_SIZE/step) elements containing the LIDAR distances.
   */
  std::vector<int16_t> getDistances(const uint16_t& step=1);

  /**
   * Returns the quality measurement of the LIDAR at the given angle.
   * @param angle The angle in [deg] in the range 0..359.
   * @return The measured quality [0..63].
   */
  uint8_t getQuality(int16_t angle);

  /**
   * Retrieve all qualitites of the latest LIDAR measurement ordered from 0 degree with the given step size.
   * @param step Step angle in degrees (e.g. step = 2: return LIDAR data every 2 degrees). Defaults to 1.
   * @return vector with (#SCAN_SIZE/step) elements containing the LIDAR measurement quality.
   */
  std::vector<uint8_t> getQualities(const uint16_t& step=1);

private:

  /** Number of bytes in header. */
  static const uint16_t HEADER_SIZE = 7;
  /** Number of bytes in payload. */
  static const uint16_t DATA_SIZE = 5;

  /** Start flag byte. */
  static const uint8_t START_FLAG = 0xA5;
  /** Scan command byte. */
  static const uint8_t SCAN = 0x20;
  /** Stop command byte. */
  static const uint8_t STOP = 0x25;
  /** Reset command byte. */
  static const uint8_t RESET = 0x40;

  /** Minimum quality to accept the measurement. Below this limit the DEFAULT_DISTANCE will be assigned. */
  static const uint8_t QUALITY_THRESHOLD = 10;
  /** Minimum distance [mm] to accept the measurement. Below this limit the DEFAULT_DISTANCE will be assigned. */
  static const int16_t DISTANCE_THRESHOLD = 10;
  /** Default value for a distance measurement (very far away). */
  static const int16_t DEFAULT_DISTANCE = 10000;
  /** Default value for a quality measurement (lowest quality). */
  static const uint8_t DEFAULT_QUALITY = 0;

  /** Serial interface for communication with Lidar. */
  RawSerial serial;

  /** PWM output to control the scanner motor. */
  PwmOut pwm;

  /** Header bytes counter. */
  uint8_t headerCounter;
  /** Data bytes counter. */
  uint8_t dataCounter;
  /** Array to store the data bytes. */
  uint8_t data[DATA_SIZE];
  /** Measured distance for every angle value, in [mm] */
  int16_t distances[SCAN_SIZE];
  /** Measured quality for every angle value, given in [0..63]. */
  uint8_t qualities[SCAN_SIZE];


  /** Creates a LIDAR object. */
  LIDAR();
  /** Private empty constructor to force usage of #getInstance. */
  LIDAR(LIDAR const&);
  /** Private equals operator to force usage of #getInstance. */
  void operator=(LIDAR const&);

  /**
   * This method is called by the serial interrupt service routine.
   * It handles the reception of measurements from the LIDAR.
   */
  void receive();
};

}
}
}
}
}
