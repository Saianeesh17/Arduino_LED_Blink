#include "AntiDelay.h"

AntiDelay blinkDelay(5000); // 5-second delay
int numBlinks = 0;
bool buttonState = LOW;      // Current button state
bool lastButtonState = LOW;  // Previous button state
bool incrementable = true;

void setup()
{
  Serial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);      // The LED on the breadboard
  pinMode(2, INPUT_PULLUP); // Button input, assuming it's connected to GND
}

void loop()
{
  // Non-blocking delay for 5 seconds
  if (blinkDelay)
  {
    // Toggle the built-in LED
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    
    // Blink the external LED for the number of button presses
    for (int i = 0; i < numBlinks; i++) {
      digitalWrite(12, HIGH);
      delay(500); // Delay for the blink
      digitalWrite(12, LOW);
      delay(500);
    }

    // Reset the number of blinks after the sequence
    numBlinks = 0;
  }

  // Read the current state of the button
  buttonState = digitalRead(2);

  // Detect state change
  if (buttonState != lastButtonState) {
    // Button has been pressed
    if (buttonState == HIGH && digitalRead(LED_BUILTIN) == HIGH) {
      numBlinks++; // Count the button press
      Serial.print("Button pressed, numBlinks: ");
      Serial.println(numBlinks);
    }
  }

  // Save the current state as the last state for the next iteration
  lastButtonState = buttonState;
}
