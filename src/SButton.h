#ifndef S_BUTTON_H
#define S_BUTTON_H
#include "Arduino.h"
class Sbutton {
  public:
    Sbutton(byte Npin, byte Npinmode) : pin(Npin), pinmode(Npinmode) {
      pinMode(pin, (pinmode) ? INPUT : INPUT_PULLUP);
    };
    void tick();
    bool isPressed;
    bool isClicked;
    bool isHolded;
    bool isHold;
    uint8_t hasClicks;
    uint8_t isHoldAfterClicks;

  private:
    uint8_t pin;
    bool pinmode;
    uint32_t timer;
    uint8_t clicks;
    bool lastState = 0;
    uint32_t lastChange;
    enum button_state {await, pressed, held, released} mode;
};
#endif
