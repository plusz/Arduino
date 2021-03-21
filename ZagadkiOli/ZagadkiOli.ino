/* 
 *  LCD displays number
press button displayed number of time
When success, green LED will shw
After 5 seconds you can try again 
*/
#include <LiquidCrystal.h> 
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
