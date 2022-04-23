#include "SButton.h"
void Sbutton::tick() {
  _clicked = 0;
  _held = 0;
  _hold = 0;
  _clicksEnd = 0;
  _clicksWithHeld = 0;
  _clicksWithHold = 0;
  uint32_t t = millis();
  bool reading = digitalRead(_pin) == (_pinmode) ? HIGH : LOW;
  if (reading != _lastState) {
    _lastChange = t;
  }
  if (t - _lastChange > 50) {
    if (reading != _pressed) {
      _pressed = reading;
    }

    if (_pressed) {
      switch (mode) {
        case await:
          mode = pressed;
          _timer = t;
          _clicks = 1;
          _clicked = 1;
          break;
        case pressed:
          if (t - _timer >= 500) {
            mode = held;
            _timer = t;
            _held = 1;
           _clicksWithHeld = _clicks - 1;
          }
          break;
        case held:
          _hold = 1;
          _clicksWithHold = _clicks - 1;
          break;
        case released:
          mode = pressed;
          _timer = t;
          _clicks ++;
          _clicked = 1;
          break;
      }
    } else {
      switch (mode) {
        case pressed: mode = released; _timer = t; break;
        case held: mode = await; _timer = t; _hold = 0; break;
        case released: if (t - _timer >= 500) {
            mode = await;
            _timer = t;
            _clicksEnd = _clicks;
            _clicks = 0;
          } break;
      }
    }
  }
  _lastState = reading;
}
