#include <Servo.h> 
#include <gcode.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 120
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 34
#define STEP 36
//Uncomment line to use enable/disable functionality
#define SLEEP 35

//Turrel IR sensor for find zero
#define turrel_homing A15
#define ir_cap A14


// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
Servo myservo;

void servofn();
void drop_cap();
void relayfn();
void turrelfn();
void homing_turrel();

double N;
double D;
double T;

#define NUMCOMMANDS 5

commandscallback commands[NUMCOMMANDS] = {{"S0", servofn}, {"R0", relayfn}, {"C0", drop_cap}, {"T0", turrelfn}, {"T1", homing_turrel}};
gcode Commands(NUMCOMMANDS,commands);




int pos_key = 180;
int pos_cap = 0;


void setup()
{
  pinMode(ir_cap, INPUT_PULLUP);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  stepper.setEnableActiveState(LOW);

  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  delay(1000);
  digitalWrite(45, LOW);
  Commands.begin("ok"); //responce => ok, rs or !!
}

void loop() 
{
  Commands.available();
}

#include "cap_turrel.h"
#include "commands.h"
#include "servo.h"
#include "relay.h"
