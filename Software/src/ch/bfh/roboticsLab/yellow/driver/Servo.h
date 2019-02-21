#line 2 "ch/bfh/roboticsLab/yellow/driver/Servo.h"
/* Servo.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

/**
 * This class implements the interfacew to a hardware servo.
 * It writes to the PWM output attached to the servo control pin respecting the Servo PWM encoding rules.
 *
 * @author gabriel.gruener@bfh.ch
 */
class Servo {

public:

    /**
     * Create a new Servo object that writes to the specified PwmOut pin.
     * @param pwmOut PwmOut to write to.
     * @param range PWM frequency range of the servo [s]. Defaults to 0.001 seconds.
     * @param angle Servo angular full-range displacement [deg]. Defaults to 90 degrees.
     */
    Servo(PwmOut pwmOut, const float& range=0.001, const float& angle=90.0);

    /**
     * Set the servo position in percent of range.
     * @param percent A normalised position [0..1] of the full range.
     */
    void write(const float& percent);

    /**
     * Read the servo motor's last written position as range percent.
     * @param returns A normalised position [0..1] of the full range.
     */
    float read() const;

    /**
     * Set the servo motor's absolute position.
     * Assumes the servo moves between 0 deg and the full-range angle defined in the constructor.
     * @param angle Servo position [deg].
     */
    void position(const float& angle);

    // Calls write
    Servo& operator= (float percent);
    // Copy constructor
    Servo& operator= (Servo& rhs);
    // Calls read
    operator float();

private:
    /** PwmOut channel to control the servo. */
    PwmOut pwmOut;
    /** Central servo pulse width. */
    static constexpr float center = 0.0015;
    /** Pulse width range [s]. */
    const float range;
    /** Servo angle range [deg]. */
    const float angle;
    /** Last percent value written [0..1]. */
    float lastPercent;
};


}
}
}
}
}
