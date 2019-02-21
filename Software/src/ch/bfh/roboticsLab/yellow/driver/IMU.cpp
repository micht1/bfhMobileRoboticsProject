#line 2 "ch/bfh/roboticsLab/yellow/driver/IMU.cpp"
/* IMU.cpp
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/driver/IMU.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

IMU::IMU(SPI& spi, DigitalOut& csAG, DigitalOut& csM) :
    spi(spi), csAG(csAG), csM(csM) {

  // initialize SPI interface
  spi.format(8, 3);
  spi.frequency(1000000);

  // reset chip select lines to logical high
  csAG = 1;
  csM = 1;

  // initialize accelerometer and gyro
  writeRegister(csAG, CTRL_REG1_G, 0xC3);     // ODR 952 Hz, full scale 245 deg/s
  writeRegister(csAG, CTRL_REG2_G, 0x00);     // disable interrupt generation
  writeRegister(csAG, CTRL_REG3_G, 0x00);     // disable low power mode, disable high pass filter, high pass cutoff frequency 57 Hz
  writeRegister(csAG, CTRL_REG4, 0x38);       // enable gyro in all 3 axis
  writeRegister(csAG, CTRL_REG5_XL, 0x38);    // no decimation, enable accelerometer in all 3 axis
  writeRegister(csAG, CTRL_REG6_XL, 0xC0);    // ODR 952 Hz, full scale 2g
  writeRegister(csAG, CTRL_REG7_XL, 0x00);    // high res mode disabled, filter bypassed
  writeRegister(csAG, CTRL_REG8, 0x00);       // 4-wire SPI interface, LSB at lower address
  writeRegister(csAG, CTRL_REG9, 0x04);       // disable gyro sleep mode, disable I2C interface, disable FIFO
  writeRegister(csAG, CTRL_REG10, 0x00);      // self test disabled

  // initialize magnetometer
  writeRegister(csM, CTRL_REG1_M, 0x10);      // temperature not compensated, low power mode for x & y axis, data rate 10 Hz
  writeRegister(csM, CTRL_REG2_M, 0x00);      // full scale 4 gauss
  writeRegister(csM, CTRL_REG3_M, 0x80);      // disable I2C interface, low power mode, SPI write only, continuous conversion mode
  writeRegister(csM, CTRL_REG4_M, 0x00);      // low power mode for z axis, LSB at lower address
  writeRegister(csM, CTRL_REG5_M, 0x00);      // fast read disabled
}

IMU::~IMU() {
}

void IMU::writeRegister(DigitalOut& cs, uint8_t address, uint8_t value) {

  cs = 0;

  spi.write(0x7F & address);
  spi.write(value & 0xFF);

  cs = 1;
}

uint8_t IMU::readRegister(DigitalOut& cs, uint8_t address) {

  cs = 0;

  spi.write(0x80 | address);
  int32_t value = spi.write(0xFF);

  cs = 1;

  return static_cast<uint8_t>(value & 0xFF);
}

float IMU::readGyroX() {

  uint8_t low = readRegister(csAG, OUT_X_L_G);
  uint8_t high = readRegister(csAG, OUT_X_H_G);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * GYRO_SCALE;
}

float IMU::readGyroY() {

  uint8_t low = readRegister(csAG, OUT_Y_L_G);
  uint8_t high = readRegister(csAG, OUT_Y_H_G);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * GYRO_SCALE;
}

float IMU::readGyroZ() {

  uint8_t low = readRegister(csAG, OUT_Z_L_G);
  uint8_t high = readRegister(csAG, OUT_Z_H_G);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * GYRO_SCALE;
}

float IMU::readAccelerationX() {

  uint8_t low = readRegister(csAG, OUT_X_L_XL);
  uint8_t high = readRegister(csAG, OUT_X_H_XL);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * ACCELEROMETER_SCALE;
}

float IMU::readAccelerationY() {

  uint8_t low = readRegister(csAG, OUT_Y_L_XL);
  uint8_t high = readRegister(csAG, OUT_Y_H_XL);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * ACCELEROMETER_SCALE;
}

float IMU::readAccelerationZ() {

  uint8_t low = readRegister(csAG, OUT_Z_L_XL);
  uint8_t high = readRegister(csAG, OUT_Z_H_XL);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * ACCELEROMETER_SCALE;
}

float IMU::readMagnetometerX() {

  uint8_t low = readRegister(csM, OUT_X_L_M);
  uint8_t high = readRegister(csM, OUT_X_H_M);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * MAGNETOMETER_SCALE;
}

float IMU::readMagnetometerY() {

  uint8_t low = readRegister(csM, OUT_Y_L_M);
  uint8_t high = readRegister(csM, OUT_Y_H_M);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * MAGNETOMETER_SCALE;
}

float IMU::readMagnetometerZ() {

  uint8_t low = readRegister(csM, OUT_Z_L_M);
  uint8_t high = readRegister(csM, OUT_Z_H_M);

  int16_t value = static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | static_cast<uint16_t>(low));

  return static_cast<float>(value) * MAGNETOMETER_SCALE;
}
}
}
}
}
}
