#include <Arduino.h>
#include <Joystick.h>

Joystick_ Joystick;


const int firstPin =2;
const int numButtons =12;
int lastButtonState[numButtons] = {};
const int debounceDelay = 20;

int lastRawState[numButtons] = {};
unsigned long lastDebounceTime[numButtons] = {};
int debouncedState[numButtons] = {}; 

void getDebouncedButtons(int* buttonStates){
  for (int i=0; i<numButtons;i++){
    int rawState = !digitalRead(i + firstPin);
    if (rawState != lastRawState[i]){
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay){
      debouncedState[i] = rawState; 
    }

    lastRawState[i] = rawState;
    buttonStates[i] = debouncedState[i];
  }
}



void setup() {
  for (int i = 2; i < 13; i++) {
    pinMode(i, INPUT);
  }
  Joystick.begin();
}

void loop() {
  int buttonStates[numButtons];
  getDebouncedButtons(buttonStates);

  for (int index = 0; index < numButtons; index++) {
    if (buttonStates[index] != lastButtonState[index]) {
      Joystick.setButton(index, buttonStates[index]);
      lastButtonState[index] = buttonStates[index];
    }
  }
  delay(50);
}