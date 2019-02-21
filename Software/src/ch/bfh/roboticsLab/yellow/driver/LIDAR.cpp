#line 2 "ch/bfh/roboticsLab/yellow/driver/LIDAR.cpp"
/* LIDAR.cpp
 * Copyright (c) ZHAW, BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/driver/LIDAR.h>

#include <ch/bfh/roboticsLab/yellow/Peripherals.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

const uint16_t LIDAR::SCAN_SIZE;

LIDAR& LIDAR::getInstance() {
  static LIDAR lidar;
  return lidar;
}

LIDAR::LIDAR() :
    serial(peripherals::lidarSerialTx, peripherals::lidarSerialRx), pwm(peripherals::pwmLidar) {

  pwm.period(0.00005f);
  // Note Lidar PWM is unidirectional: 0 is stop, 1 is max speed.
  pwm.write(0.0f);

  // initialize serial interface
  serial.baud(115200);
  serial.format(8, SerialBase::None, 1);

  // initialize local values

  headerCounter = 0;
  dataCounter = 0;

  for (uint16_t i = 0; i < 360; i++) {
    distances[i] = DEFAULT_DISTANCE;
    qualities[i] = DEFAULT_QUALITY;
  }
}

LIDAR::~LIDAR() {

  stop();
}

void LIDAR::start() {

  // start serial interrupt
  serial.attach(callback(this, &LIDAR::receive), RawSerial::RxIrq);

  pwm.write(0.6f);
  Thread::wait(1000);

  // start the continuous operation of the LIDAR
  serial.putc(START_FLAG);
  serial.putc(SCAN);
}

void LIDAR::stop() {

  // stop the LIDAR
  serial.putc(START_FLAG);
  serial.putc(STOP);
  pwm.write(0.0f);

  // stop serial interrupt
  serial.attach(NULL, RawSerial::RxIrq);
}

int16_t LIDAR::getDistance(int16_t angle) {

  while (angle < 0)
    angle += 360;
  while (angle >= 360)
    angle -= 360;

  return distances[angle];
}

std::vector<int16_t> LIDAR::getDistances(const uint16_t& step) {

  auto s = util::saturate(step, static_cast<uint16_t>(1), static_cast<uint16_t>(360));
  std::vector<int16_t> d(SCAN_SIZE / s);
  for (uint16_t i = 0; i < SCAN_SIZE; i += s)
    d.push_back(distances[i]);
  return d;
}

uint8_t LIDAR::getQuality(int16_t angle) {

  while (angle < 0)
    angle += 360;
  while (angle >= 360)
    angle -= 360;

  return qualities[angle];
}

std::vector<uint8_t> LIDAR::getQualities(const uint16_t& step) {

  auto s = util::saturate(step, static_cast<uint16_t>(1), static_cast<uint16_t>(360));
  std::vector<uint8_t> q(SCAN_SIZE / s);
  for (uint16_t i = 0; i < SCAN_SIZE; i += s)
    q.push_back(qualities[i]);
  return q;
}

void LIDAR::receive() {

  // read received characters while input buffer is full
  if (serial.readable()) {

    // read single character from serial interface
    uint8_t c = serial.getc();

    // add this character to the header or to the data buffer
    if (headerCounter < HEADER_SIZE) {
      headerCounter++;
    } else {
      if (dataCounter < DATA_SIZE) {
        data[dataCounter] = c;
        dataCounter++;
      }
      if (dataCounter >= DATA_SIZE) {

        // data buffer is full, process measurement
        uint8_t quality = (data[0] >> 2) & 0xFF;
        int16_t angle = 360 - (((uint16_t) data[1] | ((uint16_t) data[2] << 8)) >> 1) / 64;
        int16_t distance = ((uint16_t) data[3] | ((uint16_t) data[4] << 8)) / 4;

        if ((quality < QUALITY_THRESHOLD) || (distance < DISTANCE_THRESHOLD))
          distance = DEFAULT_DISTANCE;

        // store distance in [mm] into array of full scan
        while (angle < 0)
          angle += 360;
        while (angle >= 360)
          angle -= 360;
        distances[angle] = distance;
        qualities[angle] = quality;

        // reset data counter
        dataCounter = 0;
      }
    }
  }
}

}
}
}
}
}
