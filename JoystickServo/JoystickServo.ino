/* Lego Crossing steering
 *  by Piotr Orzechowski
 *  06.03.2021
 * 
 */
/* ****************** INCLUDE LIBRARIES ********************** */
#include <U8g2lib.h>
#include <Servo.h>
Servo SERVO_1;

/* ******************* GLOBAL CONSTANTS ********************** */
// Analog Joystick

const PROGMEM int FIRE_BUT2 = 2;  // digital pin connected to switch output

//Tactile switch
const PROGMEM int FIRE_BUT = A2;


/* ******************* GLOBAL VARIABLES ********************** */
bool Switchvalue = HIGH;
int zwrotnica = 1;

/* *******************************************************
 *                         Setup
 ********************************************************* */
void setup() {
  pinMode(FIRE_BUT2, INPUT_PULLUP);
  pinMode(FIRE_BUT, INPUT_PULLUP);
  Serial.begin(9600);

  SERVO_1.attach(6);  
}

/* *******************************************************
 *                       Void Loop
 ********************************************************* */
void loop() {
  if ((!digitalRead(FIRE_BUT))||(!digitalRead(FIRE_BUT2))){
    Switchvalue = false;
  }else{
    Switchvalue = true;
  }

  if (!Switchvalue) {
    zwrotnica = -zwrotnica;
  }
  if (zwrotnica == 1) {
    SERVO_1.write(0);      
  }
  else
  {
    SERVO_1.write(30);      
  }
  delay(400);
}
