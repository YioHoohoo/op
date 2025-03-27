#include "Bkkeypad.h"

bkkeypad::bkkeypad() : _hwnd(0), _mode(0) {}

bkkeypad::~bkkeypad() { UnBind(); }

long bkkeypad::UnBind() {
  _hwnd = NULL;
  _mode = 0;
  return 1;
}