#include <Servo.h> 
#include <gcode.h>
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 120
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 47
#define STEP 46
//Uncomment line to use enable/disable functionality
#define SLEEP 48

//Turrel IR sensor for find zero
#define turrel_homing A15
#define turrel_zero_homing A13
#define ir_cap A14


// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
Servo myservo;
//
//void open_mini_servo();
//void close_mini_servo();
//void big_servo_open();
//void big_servo_drop();
//void big_servo_close();


void servofn();
void relayfn();
void turrelfn();
void homing_turrel();
void zero_homing_turrel();

void drop_cap();
void check_machine();
void start_coffe();

void start_coffe_machine();

double N;
double D;
double T;

#define NUMCOMMANDS 9

commandscallback commands[NUMCOMMANDS] = {
  {"G0", start_coffe_machine},
  {"C0", drop_cap}, {"C1", check_machine}, {"C2", start_coffe},
  {"S0", servofn}, {"R0", relayfn}, {"T0", turrelfn}, {"T1", homing_turrel}, {"T2", zero_homing_turrel}



};
gcode Commands(NUMCOMMANDS,commands);

int pos_turrel;
int pos_key = 180;
int pos_cap = 0;


void setup()
{
  pinMode(ir_cap, INPUT_PULLUP);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  stepper.setEnableActiveState(LOW);
  Serial.begin(9600);
  Commands.begin("ok"); //responce => ok, rs or !!
  check_machine();
}

void loop() 
{
  Commands.available();
}

#include "cap_turrel.h"
#include "commands.h"
#include "general_commands.h"
#include "servo.h"
#include "relay.h"
