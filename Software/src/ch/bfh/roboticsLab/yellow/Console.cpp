#line 2 "ch/bfh/roboticsLab/yellow/Console.cpp"
/* Console.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/Console.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

Console& Console::getInstance() {
  static Console console;
  return console;
}


}
}
}
}
