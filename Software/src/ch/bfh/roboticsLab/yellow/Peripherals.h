#line 2 "ch/bfh/roboticsLab/yellow/Peripherals.h"
/* Peripherals.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

#include <ch/bfh/roboticsLab/yellow/driver/EncoderCounter.h>
#include <ch/bfh/roboticsLab/yellow/driver/IRSensor.h>
#include <ch/bfh/roboticsLab/yellow/driver/IMU.h>
#include <ch/bfh/roboticsLab/yellow/driver/LIDAR.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/** This namespace contains static references to all peripherals. */
namespace peripherals {

/** Main LED on NUCLEO board */
static DigitalOut led(LED1);

/***   Motor control objects  ***/
/** Motor enable switch */
static DigitalOut enableMotorDriver(PB_2);
/** Left wheel PWM */
static PwmOut pwmLeft(PA_8);
/** Right wheel PWM */
static PwmOut pwmRight(PA_9);
/** minimum allowed value for duty cycle (2%) */
static const float MIN_DUTY_CYCLE = 0.02f;
/** maximum allowed value for duty cycle (98%) */
static const float MAX_DUTY_CYCLE = 0.98f;
/** supply voltage for power stage in [V] */
static const float MAX_VOLTAGE = 12.0f;
/** speed constant of motor, given in [rpm/V] */
static const float KN = 40.0f;

/** Left wheel Encoder Counter. */
static driver::EncoderCounter counterLeft(PB_6, PB_7);
/** Right wheel Encoder Counter. */
static driver::EncoderCounter counterRight(PA_6, PC_7);
/** Resolution of encoder counter [counts/rev] */
static const float COUNTS_PER_TURN = 1200.0f;


/***   LEDs aligned to IR Sensors   ***/
/** LED 0 */
static DigitalOut led0(PC_8);
/** LED 1 */
static DigitalOut led1(PC_6);
/** LED 2 */
static DigitalOut led2(PB_12);
/** LED 3 */
static DigitalOut led3(PA_7);
/** LED 4 */
static DigitalOut led4(PC_0);
/** LED 5 */
static DigitalOut led5(PC_9);
/** Number of IR LEDs */
static const uint8_t N_LEDs = 6;
/** Array containing all 6 LEDs*/
static DigitalOut irLEDs[] = { led0, led1, led2, led3, led4, led5 };

/***   IR Sensors   ***/
/** IR Sensor's enable switch */
static DigitalOut enableIRSensors(PC_1);
/** Unique analog input to read all 6 IR sensors. */
static AnalogIn distanceSensor(PB_1);
/** IR Sensors multiplexer control bit 0. */
static DigitalOut multiplexBit0(PH_1);
/** IR Sensors multiplexer control bit 1. */
static DigitalOut multiplexBit1(PC_2);
/** IR Sensors multiplexer control bit 2. */
static DigitalOut multiplexBit2(PC_3);
static driver::Multiplexer multiplexer(multiplexBit0, multiplexBit1, multiplexBit2);
/** Number of IR sensors */
static const uint8_t N_IRs = 6;
/** IR Sensor 0 */
static driver::IRSensor irSensor0(distanceSensor, multiplexer, 0);
/** IR Sensor 1 */
static driver::IRSensor irSensor1(distanceSensor, multiplexer, 1);
/** IR Sensor 2 */
static driver::IRSensor irSensor2(distanceSensor, multiplexer, 2);
/** IR Sensor 3 */
static driver::IRSensor irSensor3(distanceSensor, multiplexer, 3);
/** IR Sensor 4 */
static driver::IRSensor irSensor4(distanceSensor, multiplexer, 4);
/** IR Sensor 5 */
static driver::IRSensor irSensor5(distanceSensor, multiplexer, 5);
/** Array containing all 6 IR sensors */
static driver::IRSensor irSensors[] = { irSensor0, irSensor1, irSensor2, irSensor3, irSensor4, irSensor5 };

/** Threshold to turn on IR-LED if the corresponding IR-Sensor measurement is below it. */
static const float irLEDThreshold = 0.25f;

/** User push button */
static DigitalIn userButton(USER_BUTTON);


/***   LIDAR   ***/
/** LIDAR PWM */
static PwmOut pwmLidar(PA_10);
/** LIDAR serial interface TX pin */
static const PinName lidarSerialTx(PA_0);
/** LIDAR serial interface RX pin */
static const PinName lidarSerialRx(PA_1);


/***   WiFi   ***/
/** WiFi serial interface TX pin */
static const PinName wifiSerialTx(PB_10);
/** WiFi serial interface RX pin */
static const PinName wifiSerialRx(PC_5);


/***   IMU   ***/
/** Chip select digital output for the IMU's accelerometers and gyros. */
static DigitalOut imuChipSelectAccGyro(PA_15);
/** Chip select digital output for the IMU's magnetometers. */
static DigitalOut imuChipSelectMagnetometer(PD_2);
/** IMU's SPI bus. */
static SPI imuSPI(PC_12, PC_11, PC_10);
/** IMU object. */
static driver::IMU imu(imuSPI, imuChipSelectAccGyro, imuChipSelectMagnetometer);

}
}
}
}
}
