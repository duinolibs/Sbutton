#ifndef S_BUTTON_H
#define S_BUTTON_H
#include "Arduino.h"

class Sbutton {
  public:
    Sbutton(byte Npin, byte Npinmode) : _pin(Npin), _pinmode(Npinmode) {
      pinMode(_pin, (_pinmode) ? INPUT : INPUT_PULLUP);
    };

    void tick();
    bool isPressed() {
      return _pressed;
    }

    bool isClicked() {
      return _clicked;
    }

    bool isHeld() {
      return _held;
    }

    bool isHold() {
      return _hold;
    }

    uint8_t hasClicks() {
      return _clicksEnd;
    }

    uint8_t hasClicksWithHeld() {
      return _clicksWithHeld;
    }

    uint8_t hasClicksWithHold() {
      return _clicksWithHold;
    }


private:
    bool _pinmode:1;
    bool _lastState:1;
    bool _pressed:1;
    bool _clicked:1;
    bool _held:1;
    bool _hold:1;
    uint8_t _pin;
    uint8_t _clicks;
    uint8_t _clicksEnd;
    uint8_t _clicksWithHeld;
    uint8_t _clicksWithHold;
    enum button_state {await, pressed, held, released} mode;
    uint32_t _timer;
    uint32_t _lastChange;
};
#endif
