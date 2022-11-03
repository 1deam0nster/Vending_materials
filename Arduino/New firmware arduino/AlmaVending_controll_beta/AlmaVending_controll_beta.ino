#include <gcode.h>
#include <AccelStepper.h>
#include <Servo.h> 

const int directionPin = 47;
const int stepPin = 46;
const int enablePin = 48;

AccelStepper turrel(1, stepPin, directionPin); // pin 3 = step, pin 6 = direction
Servo myservo;

//Turrel IR sensor for find zero
#define turrel_cap_homing A15
#define turrel_zero_homing A13
#define ir_cap A14


long initial_homing=-1;  // Used to Home Stepper at startup
int pos_cap = 0;
int pos_key = 180;

// turrel
void go_to_pos(); 
void go_number_turrel();
void zero_homing_turrel();
void get_position();

//relay, servo
void servofn();
void relayfn();

//commands
void drop_cap();
void check_machine();
void start_coffe();

void start_coffe_machine();

double N;
double D;
double A;
double S;
double I;
double T;

#define NUMCOMMANDS 10

commandscallback commands[NUMCOMMANDS] = {
  {"G0", start_coffe_machine},
  {"C0", drop_cap}, {"C1", check_machine}, {"C2", start_coffe},
  {"T0", go_to_pos}, {"T2", zero_homing_turrel}, {"T1", go_number_turrel}, {"T3", get_position},
  {"S0", servofn}, {"R0", relayfn},
};
gcode Commands(NUMCOMMANDS,commands);



void setup()
{
//  turrel.setEnablePin(enablePin);
  turrel.setMaxSpeed(1000);
  turrel.setSpeed(200);
  turrel.setAcceleration(300);

  pinMode(turrel_cap_homing, INPUT_PULLUP);
  pinMode(ir_cap, INPUT_PULLUP);
  Serial.begin(9600);
//  Commands.begin("ok"); //responce => ok, rs or !!
}

void loop() {
  Commands.available();
}

#include "turrel.h"
#include "commands.h"
#include "general_commands.h"
#include "servo.h"
#include "relay.h"
