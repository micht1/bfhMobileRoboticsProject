#line 2 "ch/bfh/roboticsLab/yellow/Console.h"
/* Console.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This class offers quick access to the serial console of the application by providing a static instance.
 *
 * The Console connects to the #TX and #RX pins at #BAUD_RATE.
 *
 * Usage:
 * <code>
 * #include <ch/bfh/roboticsLab/yellow/Console.h>
 * ...
 * Console& con = ch::bfh::roboticsLab::yellow::Console::getInstance();
 * con.printf("Hello World at zero: %d\r\n", 0);
 * </code>
 *
 * @author gabriel.gruener@bfh.ch
 */
class Console : public Serial {

public:
  /** Serial console baud rate. */
  static const int BAUD_RATE = 115200;
  /** Serial console transmit pin. */
  static const PinName TX = USBTX;
  /** Serial console receive pin. */
  static const PinName RX = USBRX;

  /**
   * Retrieve the singleton instance of the serial console.
   * @return Pointer to console instance.
   */
  static Console& getInstance();

  virtual ~Console() {}

private:
  // Make constructor private to forbid public instantiation
  /** Create the singleton Console object. */
  Console() : Serial(TX, RX) {
    baud(BAUD_RATE);
    format(8, SerialBase::None, 1);
  }

  /** Private empty constructor to force usage of #getInstance. */
  Console(Console const&);
  /** Private equals operator to force usage of #getInstance. */
  void operator=(Console const&);

};

}
}
}
}
