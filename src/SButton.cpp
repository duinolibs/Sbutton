#include "SButton.h"
void Sbutton::tick() {
  hasClicks = false;
  isHolded = false;  
  isHold = false;
  isHoldAfterClicks = 0;
  isClicked = false;
  uint32_t t = millis();
  bool reading = digitalRead(pin) == (pinmode)? HIGH : LOW;
   if (reading != lastState) {
    lastChange = t;
  }
  if(t-lastChange>50){
        if (reading != isPressed) {
      isPressed = reading;}

  if (isPressed) {
    switch (mode) {
      case await:
        mode = pressed;
        timer = t;
        clicks = 1;
        isClicked = true;
        break;
      case pressed:
        if (t - timer >= 500) {
          mode = held;
          timer = t;
          isHolded = true;
          isHoldAfterClicks = clicks-1;
        }
        break;
      case held:
        isHold = true;
        break;
      case released:
        mode = pressed;
        timer = t;
        clicks ++;
        isClicked = true;
        break;
    }
  } else {
    switch (mode) {
      case pressed: mode = released; timer = t; isHold = false; break;
      case held: mode = await; timer = t; isHold = false; break;
      case released: if (t - timer >= 500) {
          mode = await;
          timer = t;
          hasClicks = clicks;
          clicks = 0;
        } break;
    }
  }
}
lastState = reading;
}
