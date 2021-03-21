/* 
 *  LCD displays number
press button displayed number of time
When success, green LED will shw
After 5 seconds you can try again 
*/
#include <LiquidCrystal.h> 
#include "pitches.h"
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// piny do podlaczenia ekranu
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int randomNumber;  // randome number to be guessed
int counter;   // click counter

int buttonPin = 9;  // button pin
int buttonState = 0;         // button state LOW / HIGH
int ledRed = 10;   // led red pin
int ledGreen = 8;  // led green pin
int ledBlue = 13;  // led blue pin

int buzzerPin = 7;

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // initialize screen size
  
  pinMode(buttonPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  initializeGame();
}

void initializeGame() {
  randomSeed(analogRead(0));   // ustaw automat losujący
  randomNumber = random(2, 9);       // wylosuj liczbę
  counter = 0;
  
  ledHigh(ledRed);    // dioda czerwona zaswiecona
  ledLow(ledGreen);
  ledLow(ledBlue);

  noTone(buzzerPin);

  lcd.clear();
  lcd.print(randomNumber);         // display random
  Serial.println(counter);
}

void loop() { 
  gra();
}

void gra() {
    buttonState = digitalRead(buttonPin);

    // jeśli nie jest wciśnęty przycisk to nic nie robimy
    if (buttonState == HIGH) {   
      Serial.println("pressed");
      ledHigh(ledBlue);  // led HIGH if pressed button
        
      // if button pressed, incresce counter
      counter++;
        
     if (counter == randomNumber)
      {
        // SUCCESS
        Serial.println("success!");
        lcd.print(" Brawo!");
        
        ledLow(ledRed);
        ledHigh(ledGreen);
        ledLow(ledBlue);  // turn off blue - success state can be modified, to blink etc.

        starWars();
        delay(5000);  
        initializeGame();  // try one more time
      }
      else {
        Serial.println("count number ");
        Serial.println(counter);
        
        ledLow(ledRed);
        delay(100);    
        ledHigh(ledRed);
        delay(500);    
      }        
    }
    else
    {
      ledLow(ledBlue);  // blue blinks if button pressed
    }

    delay(100);
  }

  // helper to change led state
  void ledHigh(int color) {
    digitalWrite(color, HIGH);
  }
  
  // helper to change led state
  void ledLow(int color) {
    digitalWrite(color, LOW);
  }  

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
}

  void success() {
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(buzzerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(buzzerPin);

  }
  }



 void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}


void starWars() {
 //Play first section
  firstSection();
 
  //Play second section
  secondSection();
 
  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
 
  delay(500);
 
  //Repeat second section
  secondSection();
 
  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(650);
}

 
