// https://chariscat.wordpress.com/2020/12/01/adding-additional-analog-inputs-in-arduino-cd4051be-multiplexing-chip/

// https://www.ti.com/lit/ds/symlink/cd4051b.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1737097661544&ref_url=https%253A%252F%252Fwww.ti.com%252Fgeneral%252Fdocs%252Fsuppproductinfo.tsp%253FdistId%253D10%2526gotoUrl%253Dhttps%253A%252F%252Fwww.ti.com%252Flit%252Fgpn%252Fcd4051b

#include "USB.h"
#include "USBHIDKeyboard.h"

#define readPinA 21 
#define readPinB 7  
#define readPinC 6  
#define readPinD 5  
#define pinS2 4     
#define pinS1 2     
#define pinS0 1     

#define KEY_BACKSPACE 0xB2 
#define KEY_SPACE 0x2C 
#define KEY_1 0x1E 
#define KEY_2 0x1F 
#define KEY_DOT 0x37 
#define KEY_SLASH 0x38 
#define KEY_LEFT_SHIFT 0xE1 

#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D

USBHIDKeyboard Keyboard;

// Arrays containing 8 keycodes each:
const uint8_t chipArrayA[] = {KEY_BACKSPACE, KEY_1, KEY_2, KEY_SLASH, KEY_DOT, KEY_SPACE, KEY_A, KEY_B}; // KEY_1, KEY_2, KEY_SLASH need LEFTSHIFT pressed
const uint8_t chipArrayB[] = {KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J};
const uint8_t chipArrayC[] = {KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R};
const uint8_t chipArrayD[] = {KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z};

unsigned uint8_t currentKey;


void setup() {
  Serial.begin(9600);

  //Set pins D0, D1, and D2 as digital outs
  pinMode(pinS2, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS0, OUTPUT);
  pinMode(readPinA, INPUT_PULLUP);
  pinMode(readPinB, INPUT_PULLUP);
  pinMode(readPinC, INPUT_PULLUP);
  pinMode(readPinD, INPUT_PULLUP);

  Serial.println("Setup done");
}

void loop() {

  // Chip A reading
   int chipA = readChip(readPinA);
   if (chipA!=0) {
    currentKey = chipArrayA[chipA]; 
    /*if (chipA==1 || chipA==2 || chipA==3) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(currentKey);
    Keyboard.releaseAll();
    }*/

    Serial.print("chipA letter : ");
    Serial.println(chipA);
    Serial.print("chipA key : ");
    Serial.println(currentKey);
   }
   
  

  // Chip B reading
  int chipB = readChip(readPinB);
  if (chipB!=0) {
    currentKey = chipArrayB[chipB]; // Read out array position
    Serial.print("chipB letter : ");
    Serial.println(chipB);
    Serial.print("chipB key : ");
    Serial.println(currentKey);
   }

  // Chip C reading
  int chipC = readChip(readPinC);
  if (chipC!=0) {
    currentKey = chipArrayC[chipC]; // Read out array position
    Serial.print("chipC letter : ");
    Serial.println(chipC);
    Serial.print("chipC key : ");
    Serial.println(currentKey);
   }
  


  // Chip D reading
  int chipD = readChip(readPinD);
  if (chipD!=0) {
    currentKey = chipArrayD[chipD]; // Read out array position
    Serial.print("chipD letter : ");
    Serial.println(chipD);
    Serial.print("chipD key : ");
    Serial.println(currentKey);
   }

  delay(1600);
}

int readChip(int readPin) {

  //Only reading input 0 of the multiplexer
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS1, LOW);
  digitalWrite(pinS0, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 1;
  }

  //Only reading input 1 of the multiplexer
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS1, LOW);
  digitalWrite(pinS0, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 2;
  }

  //Only reading input 2 of the multiplexer
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS1, HIGH);
  digitalWrite(pinS0, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 3;
  }

  //Only reading input 3 of the multiplexer
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS1, HIGH);
  digitalWrite(pinS0, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 4;
  }

  //Only reading input 4 of the multiplexer
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS1, LOW);
  digitalWrite(pinS0, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 5;
  }
  //Only reading input 5 of the multiplexer
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS1, LOW);
  digitalWrite(pinS0, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 6;
  }
  //Only reading input 6 of the multiplexer
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS1, HIGH);
  digitalWrite(pinS0, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 7;
  }

  //Only reading input 7 of the multiplexer
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS1, HIGH);
  digitalWrite(pinS0, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 8;
  }
  //  Serial.println(Letter);
  return 0;
}
