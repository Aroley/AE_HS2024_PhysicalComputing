
#include "USB.h"
#include "USBHIDKeyboard.h"


#define readPinA 5 
#define readPinB 6  
#define readPinC 7  
#define readPinD 21  
#define pinA 4     
#define pinB 2     
#define pinC 1 

USBHIDKeyboard Keyboard;

// Arrays containing keys
char chipArrayA[] = {'!','N', ' ', 'Y', 'E', 'G', 'Q', 'J'};
char chipArrayB[] = {'?', 'P', '.', 'F', '@', '<', 'M', 'X'};
char chipArrayC[] = {'W', 'Z', 'U', 'I', 'R', 'S', 'D', 'H'};
char chipArrayD[] = {'A', 'T', 'V', 'B', 'O', 'C', 'L', 'K'};

// OG
/*
char chipArrayA[] = {'backspace','!', '?', ' ', '.', '@', 'A', 'B'};
char chipArrayB[] = {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char chipArrayC[] = {'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'};
char chipArrayD[] = {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};*/

char currentKey;

const int timeThreshold = 4;
int currentTimeA = 0;
int currentTimeB = 0;
int currentTimeC = 0;
int currentTimeD = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(readPinA, INPUT_PULLUP);
  pinMode(readPinB, INPUT_PULLUP);
  pinMode(readPinC, INPUT_PULLUP);
  pinMode(readPinD, INPUT_PULLUP);

  Keyboard.begin();
  USB.begin();
}

void loop() {

  // Chip A reading
   int chipA = readChip(readPinA);

   if (chipA!=0) {
    currentKey = chipArrayA[chipA-1]; 
    currentTimeA++;
    Serial.print(currentKey);
    
    
    if(currentTimeA >= timeThreshold){
      currentTimeA = 0;
      
    Keyboard.println(currentKey);
    }
   

    /*Serial.print("chipA pin : ");
    Serial.println(chipA);
    Serial.print("chipA key : ");
    Serial.println(currentKey);*/
   } else{
    currentTimeA = 0;
   }

   // Chip B reading
   int chipB = readChip(readPinB);
   if (chipB!=0) {
    currentKey = chipArrayB[chipB-1]; 
    currentTimeB++;
    
    if(currentTimeB >= timeThreshold){
      currentTimeB = 0;
      
    if (currentKey=='<') {
    Keyboard.press(KEY_BACKSPACE);
    delay(100);
    Keyboard.releaseAll();
    Serial.println(currentKey);
    Serial.println(chipB);
    }else{
    Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipB);
    }

    }
       /*Serial.print("chipB pin : ");
    Serial.println(chipB);
    Serial.print("chipB key : ");
    Serial.println(currentKey);*/
   } else{
    currentTimeB = 0;
   }
   
  // Chip C reading
   int chipC = readChip(readPinC);
   if (chipC!=0) {
    currentKey = chipArrayC[chipC-1]; 
    currentTimeC++;
    
    
    if(currentTimeC >= timeThreshold){
      currentTimeC = 0;
      
    Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipC);
    }
       /*Serial.print("chipC pin : ");
    Serial.println(chipC);
    Serial.print("chipC key : ");
    Serial.println(currentKey);*/
   } else{
    currentTimeC = 0;
   }

  // Chip D reading
   int chipD = readChip(readPinD);

   
   if (chipD!=0) {
    currentKey = chipArrayD[chipD-1]; 
    currentTimeD++;
    
    
    if(currentTimeD >= timeThreshold){
      currentTimeD = 0;
      
   Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipC);
    }
  
   } else{
    currentTimeD = 0;
   }


  delay(100);

}


int readChip(int readPin) {

  //Only reading input 0 of the multiplexer
  digitalWrite(pinA, LOW);
    delay(1);
  digitalWrite(pinB, LOW);
    delay(1);
  digitalWrite(pinC, LOW);
    delay(1);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 1;
  }

  //Only reading input 1 of the multiplexer
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 2;
  }

  //Only reading input 2 of the multiplexer
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 3;
  }

  //Only reading input 3 of the multiplexer
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 4;
  }

  //Only reading input 4 of the multiplexer
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 5;
  }
  //Only reading input 5 of the multiplexer
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 6;
  }
  //Only reading input 6 of the multiplexer
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 7;
  }

  //Only reading input 7 of the multiplexer
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  // Serial.print(digitalRead(readPin));
  // Serial.print("  ");

  if (digitalRead(readPin) == LOW) {
    return 8;
  }
  //  Serial.println(Letter);
  return 0;
}
