#include "SButton.h"

void SbuttonBase::tick() {
  _clicked = 0;
  _released = 0;
  uint32_t t = millis();
  bool reading = digitalRead(_pin) == (_pinmode) ? HIGH : LOW;
  if (reading != _lastState) {
    _lastChange = t;
  }
  if (t - _lastChange > SB_DEB_TIMER) {
    if (reading == (_pinclosed) ? _pressed : !_pressed) {
      _pressed = (_pinclosed) ? !reading : reading;
    }

    if (_pressed) {
      if (mode == await) {
        mode = pressed;
        _clicked = 1;
      }
    } else {
      if (mode == pressed) {
        mode = await;
        _released = 1;
      }
    }
  }
  _lastState = reading;
}

void SbuttonMultiClick::tick() {
  _clicked = 0;
  _clicksEnd = 0;
  _released = 0;
  uint32_t t = millis();
  bool reading = digitalRead(_pin) == (_pinmode) ? HIGH : LOW;
  if (reading != _lastState) {
    _lastChange = t;
  }
  if (t - _lastChange > SB_DEB_TIMER) {
    if (reading == (_pinclosed) ? _pressed : !_pressed) {
      _pressed = (_pinclosed) ? !reading : reading;
    }

    if (_pressed) {
      switch (mode) {
        case await:
          mode = pressed;
          _timer = t;
          _clicks = 1;
          _clicked = 1;
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
        case pressed:  if (_clicks == 15) {
            mode = await;
            _clicksEnd = _clicks;
            _clicks = 0;
            _released = 1;
          } else mode = released; _timer = t; break;
        case released: if (t - _timer >= SB_RELEASE_TIMER) {
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

void SbuttonHold::tick() {
  _clicked = 0;
  _endClick = 0;
  _held = 0;
  _released = 0;
  uint32_t t = millis();
  bool reading = digitalRead(_pin) == (_pinmode) ? HIGH : LOW;
  if (reading != _lastState) {
    _lastChange = t;
  }
  if (t - _lastChange > SB_DEB_TIMER) {
    if (reading == (_pinclosed) ? _pressed : !_pressed) {
      _pressed = (_pinclosed) ? !reading : reading;
    }

    if (_pressed) {
      switch (mode) {
        case await:
          mode = pressed;
          _timer = t;
          _clicked = 1;
          _doubleClick = 0;
          break;
        case pressed:
          if (t - _timer >= SB_HOLD_TIMER) {
            mode = held;
            _timer = t;
            _held = 1;
          }
          break;
        case released:
          mode = pressed;
          _timer = t;
          _clicked = 1;
          _doubleClick = 1;
          break;

      }
    } else {
      switch (mode) {
        case pressed: if (_doubleClick) {
            mode = await;
            _endClick = 1;
          }
          else mode = released; _timer = t;  _released = 1; break;
        case held: mode = await; _timer = t;  _released = 1; break;
        case released: if (t - _timer >= SB_RELEASE_TIMER) {
            mode = await;
            _endClick = 1;
            _timer = t;
          } break;
      }
    }
  }
  _lastState = reading;
}

void Sbutton::tick() {
  _clicked = 0;
  _released = 0;
  _held = 0;
  _clicksEnd = 0;
  _clicksWithHeld = 0;
  _clicksWithHold = 0;
  uint32_t t = millis();
  bool reading = digitalRead(_pin) == (_pinmode) ? HIGH : LOW;
  if (reading != _lastState) {
    _lastChange = t;
  }
  if (t - _lastChange > SB_DEB_TIMER) {
    if (reading == (_pinclosed) ? _pressed : !_pressed) {
      _pressed = (_pinclosed) ? !reading : reading;
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
          if (t - _timer >= SB_HOLD_TIMER) {
            mode = held;
            _timer = t;
            _held = 1;
            _clicksWithHeld = _clicks - 1;
          }
          break;
        case held:
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
        case pressed:  if (_clicks == 15) {
            mode = await;
            _clicksEnd = _clicks;
            _clicks = 0;
          } else mode = released; _timer = t; _released = 1; break;
        case held: mode = await; _timer = t; _clicks = 0; _released = 1; break;
        case released: if (t - _timer >= SB_RELEASE_TIMER) {
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
