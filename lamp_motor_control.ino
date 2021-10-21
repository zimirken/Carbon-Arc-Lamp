/* Motor controller for arc lamp
 *  Attempts to maintain a current set by the potentiometer, unless the retract switch is on.
 *  For attiny85
 *  
 *  turn on the power with the retract switch closed and immediately switch it to set the max motor speed to the potentiometer value.
 */
#include <EEPROM.h>

//outputs
static int MotorA = PB0;
static int MotorB = PB1;

//inputs
static int CurrentSensePin = A3;
static int CurrentSetPin = A1;
static int RetractSwitch = PB4;

byte MaxSpeed = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(MotorA, OUTPUT);
  pinMode(MotorB, OUTPUT);
  pinMode(RetractSwitch, INPUT);
  digitalWrite(RetractSwitch, HIGH);
  delay(100);
  if(digitalRead(RetractSwitch) == 0) {
    delay(1000);
    if(digitalRead(RetractSwitch) == 0) {
      EEPROM.write(1, byte(map(analogRead(CurrentSetPin),0,1024,0,255)));
    }
  }
  
    MaxSpeed == EEPROM.read(1);
  
}

void loop() {
  int CurrentRead = analogRead(CurrentSensePin);
  int SetRead = analogRead(CurrentSetPin);

    //if retract switch is pressed or current sense is maxed out, reverse motor.
  if(digitalRead(RetractSwitch) == 0 || CurrentRead > SetRead) {
    analogWrite(MotorA, 0);
    if (digitalRead(RetractSwitch) == 0) {
      analogWrite(MotorB, MaxSpeed);
    }
    else {
      int mincurrent2 = map(CurrentRead, 1024, SetRead, MaxSpeed, 0);
      if (mincurrent2 < 0) {
        mincurrent2 = 0;
      }
      analogWrite(MotorB, mincurrent2);
    }
    
  }
  else {
    analogWrite(MotorB, 0);
    int mincurrent = map(CurrentRead, 0, SetRead, MaxSpeed, 0);
    if (mincurrent < 0) {
      mincurrent = 0;
    }
    analogWrite(MotorA, mincurrent);
  }

}
