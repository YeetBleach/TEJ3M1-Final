#include <Arduino.h>
#include <Joystick.h>

Joystick_ Joystick;

const int firstPin = 2;
const int numButtons = 11;
const int debounceSamples = 10;      // Total samples over 15 ms

void setup() {
    for (int i = firstPin; i < firstPin + numButtons; i++) {
        pinMode(i, INPUT_PULLUP);
    }
    Joystick.begin();
}

void loop() {
    for (int i = 0; i < numButtons; i++) {
        int samplesHigh = 0;
        int samplesLow = 0;
        for (int j = 0; j < debounceSamples; j++) {
            if ((!digitalRead(i + firstPin)) == HIGH) {
                samplesHigh++;
            } else {
                samplesLow++;
            }
            delayMicroseconds(100);
        }
        if (samplesHigh > samplesLow) {
            Joystick.setButton(i, true);
        } else {
            Joystick.setButton(i, false);
        }
    }
    delay(20);
}

