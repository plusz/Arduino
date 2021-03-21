

/* Lego Crossing steering
 *  by Piotr Orzechowski
 *  06.03.2021
 * 
 */
/* ****************** INCLUDE LIBRARIES ********************** */
#include <U8g2lib.h>
#include <Servo.h>
#include <IRremote.h>


/* ******************* GLOBAL CONSTANTS ********************** */
// Analog Joystick
const PROGMEM int FIRE_BUT2 = 2;  // digital pin connected to switch output
//Tactile switch
const PROGMEM int FIRE_BUT = A2;
// IR pin
const int RECV_PIN = 10;

Servo SERVO_1;

/* ******************* GLOBAL VARIABLES ********************** */
bool Switchvalue = HIGH;
int zwrotnica = 1;

/* *******************************************************
 *                         Setup
 ********************************************************* */
void setup() {
  pinMode(FIRE_BUT2, INPUT_PULLUP);
  pinMode(FIRE_BUT, INPUT_PULLUP);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  
  Serial.begin(9600);

  SERVO_1.attach(6);  
  
}

/* *******************************************************
 *                       Void Loop
 ********************************************************* */
void loop() {
  /*
   if ((!digitalRead(FIRE_BUT))||(!digitalRead(FIRE_BUT2))){
    Switchvalue = false;
  }else{
    Switchvalue = true;
  }
  */

    if (IrReceiver.decode()) {  // Grab an IR code
        // Check if the buffer overflowed
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            //Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
        } else {
            //Serial.println(IrReceiver.decodedIRData.decodedRawData);
            Switchvalue = true;
            if (3927309826 == IrReceiver.decodedIRData.decodedRawData
            || 3994144050 == IrReceiver.decodedIRData.decodedRawData)
            {
              Switchvalue = false;
            }
        }
        IrReceiver.resume();                            // Prepare for the next value
    }

  if (!Switchvalue) {
    zwrotnica = -zwrotnica;
  }
  if (zwrotnica == 1) {
    SERVO_1.write(0);      
  }
  else
  {
    SERVO_1.write(70);      
  }
  delay(1000);
}
