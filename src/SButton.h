#ifndef S_BUTTONA_H
#define S_BUTTONA_H
#include "Arduino.h"

#define SB_DEB_TIMER 50
#define SB_HOLD_TIMER 500
#define SB_RELEASE_TIMER 500

class SbuttonBase {
  public:
  SbuttonBase(uint8_t Npin) : _pin(Npin), _pinmode(0), _pinclosed(0) {
      pinMode(_pin, INPUT);
    };
    SbuttonBase(uint8_t Npin, bool Npinmode) : _pin(Npin), _pinmode(Npinmode), _pinclosed(0) {
      pinMode(_pin, (_pinmode) ? INPUT : INPUT_PULLUP);
    };
    SbuttonBase(uint8_t Npin, bool Npinmode, bool Npinclosed) : _pin(Npin), _pinmode(Npinmode), _pinclosed(Npinclosed) {
      pinMode(_pin, (_pinmode) ? INPUT : INPUT_PULLUP);
    };
    virtual void tick();
    bool isPressed() {
      return _pressed;
    }
    bool isClicked() {
      return _clicked;
    }
    bool isReleased() {
      return _released;  
    }
  protected:
    bool _pinmode: 1;
    bool _pinclosed: 1;
    bool _lastState: 1;
    bool _pressed: 1;
    bool _clicked: 1;
    bool _released: 1;
    uint8_t _pin;
    enum button_state {await, pressed, held, released} mode;
    uint32_t _lastChange;
};

class SbuttonMultiClick: public SbuttonBase {
  public:
    SbuttonMultiClick(uint8_t Npin) : SbuttonBase(Npin) {};
    SbuttonMultiClick(uint8_t Npin, bool Npinmode) : SbuttonBase(Npin, Npinmode) {};
    SbuttonMultiClick(uint8_t Npin, bool Npinmode, bool Npinclosed) : SbuttonBase(Npin, Npinmode, Npinclosed) {};
    void tick() override;
    uint8_t hasClicks() {
      return _clicksEnd;
    }
    bool hasSingle() {
      return _clicksEnd == 1;
    }
    bool hasDouble() {
      return _clicksEnd == 2;
    }
    bool hasTriple() {
      return _clicksEnd == 3;
    }

  protected:
    uint8_t _clicks: 4;
    uint8_t _clicksEnd: 4;
    uint32_t _timer;
};



class SbuttonHold: public SbuttonBase {
  public:
    SbuttonHold(uint8_t Npin) : SbuttonBase(Npin) {};
    SbuttonHold(uint8_t Npin, bool Npinmode) : SbuttonBase(Npin, Npinmode) {};
    SbuttonHold(uint8_t Npin, bool Npinmode, bool Npinclosed) : SbuttonBase(Npin, Npinmode, Npinclosed) {};
    void tick() override;
    bool hasSingle() {
      return _endClick & !_doubleClick;
    }
    bool hasDouble() {
      return _endClick & _doubleClick;
    }
    bool isHeld() {
      return _held;
    }
    bool isHold() {
      return mode == held;
    }

  protected:
    bool _held: 1;
    bool _doubleClick: 1;
    bool _endClick: 1;
    uint32_t _timer;
};

class Sbutton: public SbuttonMultiClick {
  public:
    Sbutton(uint8_t Npin) : SbuttonMultiClick(Npin) {};
    Sbutton(uint8_t Npin, bool Npinmode) : SbuttonMultiClick(Npin, Npinmode) {};
    Sbutton(uint8_t Npin, bool Npinmode, bool Npinclosed) : SbuttonMultiClick(Npin, Npinmode, Npinclosed) {};
    void tick() override;
    bool isHeld() {
      return _held;
    }
    bool isHold() {
      return mode == held;
    }
    uint8_t hasClicksWithHeld() {
      return _clicksWithHeld;
    }
    uint8_t hasClicksWithHold() {
      return _clicksWithHold;
    }

  protected:
    uint8_t _clicksWithHeld: 4;
    uint8_t _clicksWithHold: 4;
    bool _held: 1;
};

#endif
