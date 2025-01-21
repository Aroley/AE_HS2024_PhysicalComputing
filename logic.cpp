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



USBHIDKeyboard Keyboard;


// Arrays containing keys
char chipArrayA[] = {'backspace','!', '?', ' ', '.', '@', 'A', 'B'};
char chipArrayB[] = {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char chipArrayC[] = {'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'};
char chipArrayD[] = {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char currentKey;

const int timeThreshold = 24;
int currentTimeA = 0;
int currentTimeB = 0;
int currentTimeC = 0;
int currentTimeD = 0;


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

  Keyboard.begin();

}

void loop() {


  // Chip A reading
   int chipA = readChip(readPinA);
   if (chipA!=0) {
    currentKey = chipArrayA[chipA-1]; 
    currentTimeA++;
    Serial.print(currentKey);
    Serial.println(currentTimeA);
    
    
    if(currentTimeA >= timeThreshold){
      currentTimeA = 0;
      
    if (chipA==1) {
    Keyboard.press(KEY_BACKSPACE);
    delay(100);
    Keyboard.releaseAll();
    }else{
    Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipA);
    }
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
    Serial.print(currentKey);
    Serial.println(currentTimeB);
    
    if(currentTimeB >= timeThreshold){
      currentTimeB = 0;
      
    Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipB);

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
    Serial.print(currentKey);
    Serial.println(currentTimeC);
    
    
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
    Serial.print(currentKey);
    Serial.println(currentTimeD);
    
    
    if(currentTimeD >= timeThreshold){
      currentTimeD = 0;
      
    Keyboard.print(currentKey);
    Serial.println(currentKey);
    Serial.println(chipD);
    }
       /*Serial.print("chipC pin : ");
    Serial.println(chipC);
    Serial.print("chipC key : ");
    Serial.println(currentKey);*/
   } else{
    currentTimeD = 0;
   }


  delay(100);
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
