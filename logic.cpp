#include "USB.h"
#include "USBHIDKeyboard.h"

#define HIDdisablePin 10
#define message 1
#define shortcut 2

USBHIDKeyboard Keyboard;

void setup() {
  Serial.begin(9600);
  pinMode(HIDdisablePin, INPUT_PULLUP);
  delay(20);
  // disable the mouse unless HIDdisablePin is connected to ground
  if (digitalRead(HIDdisablePin) == HIGH) {
    while (1) { /* infinite loop */
      Serial.println("AAAAAAAAA");
    }
  }
  // The rest of your code after this line

  pinMode(message, INPUT_PULLUP);
  pinMode(shortcut, INPUT_PULLUP);
  // initialize keyboard control:
   Keyboard.begin(); // optional keyboard region setting
  USB.begin();
}

void loop() {
  Serial.println("Entered Loop");

  if (digitalRead(message) == LOW) {
    // write a keyboard message
       Keyboard.print("Interaction Design ZHdK!");
      delay(400);
  } 
  if (digitalRead(shortcut) == LOW) {
    // focus on a random application window in OSX
      Keyboard.press(KEY_RIGHT_GUI);
      Keyboard.press(KEY_TAB);
      delay(100);
      Keyboard.release(KEY_TAB);
      delay(100);
      int randomCount = random(6);
      int count = 0;
      while (count < randomCount) {
        count++; 
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_TAB);
      delay(400);
      }
      Keyboard.releaseAll();
  } 

  delay(10);
}