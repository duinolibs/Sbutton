#include "SButton.h"
void setup() {
  Serial.begin(9600);
}
Sbutton btn (3,0);
void loop() {
btn.tick();
if(btn.isPressed) digitalWrite(13,1); else digitalWrite(13,0);
if(btn.isClicked) Serial.print("Clicked ");
if(btn.isHolded) Serial.print("Hold "+String(btn.isHoldAfterClicks)+"\n");
if(btn.hasClicks) Serial.print("Clicks:"+String(btn.hasClicks)+"\n");
}
