#include <Arduino.h>
// #include <EEPROM.h>

#include <NintendoSwitchControlLibrary.h>

const byte HatPins[] = {0, 1, 2, 3};
const byte HatPinCount = sizeof(HatPins) / sizeof(HatPins[0]);
const byte ButtonPins[] = {4, 5, 6, 7};
const byte ButtonCount = sizeof(ButtonPins) / sizeof(ButtonPins[0]);
const uint16_t ButtonConstants[] = {Button::X, Button::A, Button::B, Button::Y};
const byte LedButtonPins[] = {8, 9, 10};
const byte LedButtonCount = sizeof(LedButtonPins) / sizeof(LedButtonPins[0]);
const uint16_t LedButtonConstants[] = {Button::L, Button::R,
                                       Button::PLUS};
const byte LedPins[] = {16, 14, 15};
// const byte StartPin = 10;
// const byte DomePin = 18;
// const int eeAddress = 450;
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
  // pinMode(DomePin, OUTPUT);
  // delay(100);

  // if (digitalRead(StartPin) == LOW) {
  //   byte currentValue = EEPROM.read(eeAddress);
  //
  //   EEPROM.write(eeAddress, !currentValue);
  // }

  // byte domeIsOn = EEPROM.read(eeAddress);

  // if (domeIsOn) {
  //   digitalWrite(DomePin, HIGH);
  // } else {
  //   digitalWrite(DomePin, LOW);
  // }
}

void loop() {
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

  for (int i = 0; i < ButtonCount; i++) {
    if (digitalRead(ButtonPins[i]) == LOW) {
      SwitchControlLibrary().pressButton(ButtonConstants[i]);
    } else {
      SwitchControlLibrary().releaseButton(ButtonConstants[i]);
    }
  }
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
