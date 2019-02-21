#line 2 "ch/bfh/roboticsLab/yellow/driver/IMU.h"
/* IMU.h
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

#include <ch/bfh/roboticsLab/util/Util.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

/**
 * This is a device driver class for the ST LSM9DS1 inertial measurement unit.
 * @author marcel.honegger@zhaw.ch
 */
class IMU {

public:


  /**
   * Creates an IMU object.
   * @param spi a reference to an spi controller to use.
   * @param csAG the chip select output for the accelerometer and the gyro sensor.
   * @param csM the chip select output for the magnetometer.
   */
  IMU(SPI& spi, DigitalOut& csAG, DigitalOut& csM);

  /**
   * Deletes the IMU object.
   */
  virtual ~IMU();

  /**
   * Reads the gyroscope about the x-axis.
   * @return the rotational speed about the x-axis given in [rad/s].
   */
  float readGyroX();

  /**
   * Reads the gyroscope about the y-axis.
   * @return the rotational speed about the y-axis given in [rad/s].
   */
  float readGyroY();

  /**
   * Reads the gyroscope about the z-axis.
   * @return the rotational speed about the z-axis given in [rad/s].
   */
  float readGyroZ();

  // TODO Implement method to read gyro XYZ in one call.

  /**
   * Reads the acceleration in x-direction.
   * @return the acceleration in x-direction, given in [m/s2].
   */
  float readAccelerationX();

  /**
   * Reads the acceleration in y-direction.
   * @return the acceleration in y-direction, given in [m/s2].
   */
  float readAccelerationY();

  /**
   * Reads the acceleration in z-direction.
   * @return the acceleration in z-direction, given in [m/s2].
   */
  float readAccelerationZ();

  // TODO Implement method to read accelerometer XYZ in one call.

  /**
   * Reads the magnetic field in x-direction.
   * @return the magnetic field in x-direction, given in [Gauss].
   */
  float readMagnetometerX();

  /**
   * Reads the magnetic field in x-direction.
   * @return the magnetic field in x-direction, given in [Gauss].
   */
  float readMagnetometerY();

  /**
   * Reads the magnetic field in x-direction.
   * @return the magnetic field in x-direction, given in [Gauss].
   */
  float readMagnetometerZ();

  // TODO Implement method to read magnetometer XYZ in one call.

private:

  // Gyro and accelerometer registers
  static const uint8_t WHO_AM_I = 0x0F;
  static const uint8_t CTRL_REG1_G = 0x10;
  static const uint8_t CTRL_REG2_G = 0x11;
  static const uint8_t CTRL_REG3_G = 0x12;
  static const uint8_t OUT_X_L_G = 0x18;
  static const uint8_t OUT_X_H_G = 0x19;
  static const uint8_t OUT_Y_L_G = 0x1A;
  static const uint8_t OUT_Y_H_G = 0x1B;
  static const uint8_t OUT_Z_L_G = 0x1C;
  static const uint8_t OUT_Z_H_G = 0x1D;
  static const uint8_t CTRL_REG4 = 0x1E;
  static const uint8_t CTRL_REG5_XL = 0x1F;
  static const uint8_t CTRL_REG6_XL = 0x20;
  static const uint8_t CTRL_REG7_XL = 0x21;
  static const uint8_t CTRL_REG8 = 0x22;
  static const uint8_t CTRL_REG9 = 0x23;
  static const uint8_t CTRL_REG10 = 0x24;
  static const uint8_t OUT_X_L_XL = 0x28;
  static const uint8_t OUT_X_H_XL = 0x29;
  static const uint8_t OUT_Y_L_XL = 0x2A;
  static const uint8_t OUT_Y_H_XL = 0x2B;
  static const uint8_t OUT_Z_L_XL = 0x2C;
  static const uint8_t OUT_Z_H_XL = 0x2D;

  // Magnetometer registers
  static const uint8_t WHO_AM_I_M = 0x0F;
  static const uint8_t CTRL_REG1_M = 0x20;
  static const uint8_t CTRL_REG2_M = 0x21;
  static const uint8_t CTRL_REG3_M = 0x22;
  static const uint8_t CTRL_REG4_M = 0x23;
  static const uint8_t CTRL_REG5_M = 0x24;
  static const uint8_t OUT_X_L_M = 0x28;
  static const uint8_t OUT_X_H_M = 0x29;
  static const uint8_t OUT_Y_L_M = 0x2A;
  static const uint8_t OUT_Y_H_M = 0x2B;
  static const uint8_t OUT_Z_L_M = 0x2C;
  static const uint8_t OUT_Z_H_M = 0x2D;

  // Note: the full-scale scaling factors are configured in the constructor.
  /** Gyro scaling factor: full scale 245 deg/s in [rad/s]. */
  static constexpr float GYRO_SCALE = 1.0 / 32768.0f * 245.0f * util::RAD;
  /** Accelerometer scaling factor: full scale 2g in [m/s2]. */
  static constexpr float ACCELEROMETER_SCALE = 1.0 / 32768.0f * 2.0f * 9.81f;
  /** MAgnetometer scaling factor: full scale 4 Gauss in [Gauss]. */
  static constexpr float MAGNETOMETER_SCALE = 1.0 / 32768.0f * 4.0f;

  /** Reference to SPI bus. */
  SPI& spi;
  /** Chip select output for the accelerometer and the gyro sensor. */
  DigitalOut& csAG;
  /** Chip select output for the magnetometer. */
  DigitalOut& csM;

  /**
   * This private method allows to write a register value.
   * @param cs the chip select output to use, either csAG or csM.
   * @param address the 7 bit address of the register.
   * @param value the value to write into the register.
   */
  void writeRegister(DigitalOut& cs, uint8_t address, uint8_t value);

  /**
   * This private method allows to read a register value.
   * @param cs the chip select output to use, either csAG or csM.
   * @param address the 7 bit address of the register.
   * @return the value read from the register.
   */
  uint8_t readRegister(DigitalOut& cs, uint8_t address);
};

}
}
}
}
}
