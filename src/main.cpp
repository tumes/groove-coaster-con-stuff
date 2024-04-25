#include <Arduino.h>

#include <NintendoSwitchControlLibrary.h>

// Pin setup. I generally went in order but tackled the LED buttons after the
// fact, so if I had to do it over again, I'd cluster them with their respective
// button sensors.
const byte HatPins[] = {0, 1, 2, 3};
const byte HatPinCount = sizeof(HatPins) / sizeof(HatPins[0]);
const byte ButtonPins[] = {4, 5, 6, 7};
const byte ButtonCount = sizeof(ButtonPins) / sizeof(ButtonPins[0]);
const uint16_t ButtonConstants[] = {Button::X, Button::A, Button::B, Button::Y};
const byte LedButtonPins[] = {8, 9, 10};
const byte LedButtonCount = sizeof(LedButtonPins) / sizeof(LedButtonPins[0]);
const uint16_t LedButtonConstants[] = {Button::L, Button::R, Button::PLUS};
const byte LedPins[] = {16, 14, 15};
// Some jank to get 8 directions out of 4 switches.
const int HatVals[] = {1, 2, 4, 8};

void setup() {
  for (int i = 0; i < HatPinCount; i++) {
    pinMode(HatPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < ButtonCount; i++) {
    pinMode(ButtonPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < LedButtonCount; i++) {
    pinMode(LedButtonPins[i], INPUT_PULLUP);
    pinMode(LedPins[i], OUTPUT);
  }
}

void loop() {
  // I hate this code but I'm a web developer, so I have no clue how to do this
  // idiomatically. Big ups to ChatpGPT, which I asked to try to improve this
  // code and which gave me something so compact and cryptic it took me an hour
  // to figure out that it was all hallucinated BS. In short this makes the 8
  // directions work.
  // This correlates to the left dome on the ASC.
  int hatVal = Hat::NEUTRAL;
  int sum = 0;
  for (int i = 0; i < HatPinCount; i++) {
    if (digitalRead(HatPins[i]) == LOW) {
      sum += HatVals[i];
    }
    if (sum > 0) {
      switch (sum) {
      case 1:
        hatVal = Hat::UP;
        break;
      case 3:
        hatVal = Hat::UP_RIGHT;
        break;
      case 2:
        hatVal = Hat::RIGHT;
        break;
      case 6:
        hatVal = Hat::DOWN_RIGHT;
        break;
      case 4:
        hatVal = Hat::DOWN;
        break;
      case 12:
        hatVal = Hat::DOWN_LEFT;
        break;
      case 8:
        hatVal = Hat::LEFT;
        ;
        break;
      case 9:
        hatVal = Hat::UP_LEFT;
        break;
      }
    }
  }
  SwitchControlLibrary().pressHatButton(hatVal);

  // This correlates to the right dome on the ASC.
  for (int i = 0; i < ButtonCount; i++) {
    if (digitalRead(ButtonPins[i]) == LOW) {
      SwitchControlLibrary().pressButton(ButtonConstants[i]);
    } else {
      SwitchControlLibrary().releaseButton(ButtonConstants[i]);
    }
  }
  // This handles the dome buttons and the ASC start button.
  for (int i = 0; i < LedButtonCount; i++) {
    if (digitalRead(LedButtonPins[i]) == LOW) {
      SwitchControlLibrary().pressButton(LedButtonConstants[i]);
      digitalWrite(LedPins[i], HIGH);
    } else {
      SwitchControlLibrary().releaseButton(LedButtonConstants[i]);
      digitalWrite(LedPins[i], LOW);
    }
  }
  SwitchControlLibrary().sendReport();
}
