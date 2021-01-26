 /******************************************************************
 Trinket:        USB+   Gnd   Pin #0  Pin #1  Pin #2 A1
 Connection:     Servo+  -   Servo1 Servo2   Potentiometer wiper
 
 *******************************************************************/

#include <Adafruit_SoftServo.h> // SoftwareServo (works on non PWM pins)

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
unsigned long stagedTime = 0; //Initialize timer when staged for race state is detected (IR or capacitive detection of lane pin).
unsigned long racingTime = 0; //Initialize timer when staged for race state is detected (IR, capacitive, or accelerometer)

Adafruit_SoftServo esc;

#define SERVOPIN  0                         // Servo control output pin
#define LEDPIN    1                         // LED output pin
#define IRBEAMPIN 2                         // IR beam input pin
//#define CAPCONTPIN TBD                    // Capacitive contact sensor input pin 
//#define ACCXPIN TBD                       // X-axis accelerometer input pin

#define OFFSPEED    0                       // Lowest ESC speed (range 0-180)
#define STAGEDSPEED 25                      // ESC speed when staged before race start (sdle speed to avoid start torque surge while racing)
#define RACINGSPEED 180                     // Maximum ESC speed when race start detected 

#define MINIMUMSTAGEDDURATION 2000          // Minimum duration car must be stage to enter race mode in milliseconds
#define MAXIMUMRACEDURATION 2000            // Maximum duration of racing speed in milliseconds (changed from orginal 1500 ms)

enum raceState {
  OFF,
  STAGED,
  RACING,
  //ACCELERATING
  //DECELERATING
  DONE                                      // Do not allow motor to turn back on after race until power reset
};
raceState currentState = OFF;

void setup() {
  // ESC
  pinMode(SERVOPIN, OUTPUT);                // Set up ESC control pin as an output
  esc.attach(SERVOPIN);                     // Attach the pin to the software servo library
  // LED
  pinMode(LEDPIN, OUTPUT);                  // Set Trinket pin 1 as an output for LED
  // IR BEAM
  pinMode(IRBEAMPIN, INPUT);                // Set up IR beam pin as input
  digitalWrite(IRBEAMPIN, HIGH);            // Enable the internal pull up resistor
  //pinMode(CAPCONTPIN, INPUT);                // Set up the contact capacitor pin as input
  //digitalWrite(CAPCONTPIN, HIGH);            // Enable the internal pull up resistor
  
  // Interrupt Registers
     // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;                             // Set up a 2ms interrupt // any number is OK 
  TIMSK |= _BV(OCIE0A);                     // Turn on the compare interrupt (below!)
}

void loop() {
  // Use the IR beam sensor to determine the current state of the race
  if (digitalRead(IRBEAMPIN) == HIGH)       // IR beam NOT broken
  //if (digitalRead(CAPCONTPIN) == HIGH)       // No capacitance contact detected
  {
    if (currentState == STAGED) {           // If car is currently staged
      // If car has been staged for longer than the staged duration
      if ((millis() - stagedTime) > MINIMUMSTAGEDDURATION) {
        racingTime = millis();              // Start race duration timer
        currentState = RACING;              // ENTER RACE MODE
      }
      else
        currentState = OFF;                 // Off mode
    }
  }
  else {                                    // IR beam BROKEN
    if (currentState == OFF) {
      stagedTime = millis();                // Start "Staged" timer
      currentState = STAGED;                // CAR IS STAGED
    } 
  }

  // Turn off the motor after a specified race duration
  if (currentState == RACING) {             // If the car is currently racing
    // Measure the race duration and compare it to maximum race duration
    if ((millis() - racingTime) > MAXIMUMRACEDURATION) {
      currentState = DONE;                  // Turn ESC off
    }
  }
  // Set the ESC speed depending on the current state
  if (currentState == STAGED) {
    esc.write(STAGEDSPEED);
    digitalWrite(LEDPIN, HIGH);             // Turn ON LED
  }
  else if (currentState == RACING)
    esc.write(RACINGSPEED);
  else {
    esc.write(OFFSPEED);
    digitalWrite(LEDPIN, LOW);              // Turn OFF LED
  }
  delay(1);
}

// The SIGNAL(TIMER0_COMPA_vect) function is the interrupt that will be called by the microcontroller every 2 milliseconds (See TrinkeKnob example).
SIGNAL(TIMER0_COMPA_vect) {
  counter += 2;                             // Add two milliseconds to the elapsed time
  if (counter >= 20) {                      // Has 20ms elapsed?
    counter = 0;                            // Reset the timer
    esc.refresh();                          // Refesh the software based servo control
  }
}
