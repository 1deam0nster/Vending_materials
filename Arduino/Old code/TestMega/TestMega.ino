
#include <Arduino.h>
#include "A4988.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include "BasicStepperDriver.h"
#include <Servo.h>
#include <gcode.h>


//------Переменная для ШД сахара
int milk_stepper_1 = 0;
int milk_stepper_2 = 0;
int milk_stepper_3 = 0;

//------Переменные для IR датчиков турели------
bool check_1 = false;
bool check_2 = false;
bool check_3 = false;
bool check_4 = false;
bool check_5 = false;
bool val = false;

//------Подключение серв------
Servo servo;
Servo servo_r; 
Servo servo_sug;

//------Подключение концевиков------
#define stop_x 20
#define stop_y 34
#define stop_z 33

#define home_switch_z 22 // концевик для Z
#define home_switch_e 21 //концевик для E

#define turrel_switch_x 23 //концевик турелли с капсулами Х
#define turrel_switch_y 24 //концевик турелли с капсулами Y

#define ir_cap_y 26 //концевик капсулы Y
#define ir_cap_x 25 //концевик капсулы X 27

bool cup_table; 
#define ir_cup A4

//-----Реле на кофемашину-----
#define OPEN 37
#define START_COFE 35
#define CLOSE 36

//-----Для выдачи стаканчиков -----
#define RELAY_CUP 16
#define RELAY_TURREL 15

const int turrel_pos = 19;     // номер входа, подключенный к кнопке Turret position
const int turrel_micro_switch = 17;     // номер входа, подключенный к кнопке Turret micro switch
const int cup_splitter = 18;     // номер входа, подключенный к кнопке Cup splitter
int motor_val = 3;

//------Подключение ШД------
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
//Number of steps to take 1 millimeter
#define STEPS_MM 80
// Target RPM for X axis motor
#define MOTOR_X_RPM 30
#define MOTOR_Y_RPM 30
#define MOTOR_Z_RPM 120
#define MOTOR_E_RPM 120
#define MOTOR_M0_RPM 120
#define MOTOR_M1_RPM 120
#define MOTOR_M2_RPM 120
#define NAV_MOTOR_X_RPM 120
#define NAV_MOTOR_Y_RPM 120
#define NAV_MOTOR_Z_RPM 120

// X motor
#define DIR_X A1
#define STEP_X A0
#define ENA_X A2

// Y motor
#define DIR_Y 50
#define STEP_Y 51
#define ENA_Y 49

// Z motor
#define DIR_Z A2
#define STEP_Z A3
#define ENA_Z A1

//// E0 motor
#define DIR_E 53
#define STEP_E A0
#define ENA_E 52

///из первой ардуины
// X motor
#define NAV_DIR_X 28
#define NAV_STEP_X 27
#define NAV_ENA_X 29

// Y motor
#define NAV_DIR_Y 31
#define NAV_STEP_Y 30
#define NAV_ENA_Y 32

// Z motor
#define NAV_DIR_Z 4
#define NAV_STEP_Z 5
#define NAV_ENA_Z 3

// M0 motor
#define DIR_M0 39
#define STEP_M0 38
#define ENA_M0 40

// M1 motor
#define DIR_M1 A6
#define STEP_M1 A5
#define ENA_M1 A7

// M2 motor
#define DIR_M2 A9
#define STEP_M2 A8
#define ENA_M2 A1

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step, 4 = 1/4, 8 = 1/8 and 16 = 1/6 Microsteps.
#define MICROSTEPS 8

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
 #include "DRV8825.h"
// #define MODE0 10
// #define MODE1 11
// #define MODE2 12
// DRV8825 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MODE0, MODE1, MODE2);

A4988 turelX(MOTOR_STEPS, DIR_X, STEP_X, ENA_X);
A4988 turelY(MOTOR_STEPS, DIR_Y, STEP_Y, ENA_Y);
DRV8825 turelZ(MOTOR_STEPS, DIR_Z, STEP_Z, ENA_Z);
DRV8825 stepperE(MOTOR_STEPS, DIR_E, STEP_E, ENA_E);
A4988 stepperM0(MOTOR_STEPS, DIR_M0, STEP_M0, ENA_M0);
A4988 stepperM1(MOTOR_STEPS, DIR_M1, STEP_M1, ENA_M1);
A4988 stepperM2(MOTOR_STEPS, DIR_M2, STEP_M2, ENA_M2);
A4988 nav_X(MOTOR_STEPS, NAV_DIR_X, NAV_STEP_X, NAV_ENA_X);
A4988 nav_Y(MOTOR_STEPS, NAV_DIR_Y, NAV_STEP_Y, NAV_ENA_Y);
DRV8825 nav_Z(MOTOR_STEPS, NAV_DIR_Z, NAV_STEP_Z, NAV_ENA_Z);
// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick

//MultiDriver controller(turel_X, turel_Y, turel_Z);
MultiDriver controller(nav_X, nav_Y, nav_Z);
BasicStepperDriver stepper_E(MOTOR_STEPS, DIR_E, STEP_E);
BasicStepperDriver stepper_M0(MOTOR_STEPS, DIR_M0, STEP_M0);
BasicStepperDriver stepper_M1(MOTOR_STEPS, DIR_M1, STEP_M1);
BasicStepperDriver stepper_M2(MOTOR_STEPS, DIR_M2, STEP_M2);
BasicStepperDriver turel_X(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver turel_Y(MOTOR_STEPS, DIR_Y, STEP_Y);
BasicStepperDriver turel_Z(MOTOR_STEPS, DIR_Z, STEP_Z);

//BasicStepperDriver nav_X(MOTOR_STEPS, DIR_X2, STEP_X2);
//BasicStepperDriver nav_Y(MOTOR_STEPS, DIR_Y2, STEP_Y2);
//BasicStepperDriver nav_Z(MOTOR_STEPS, DIR_Z2, STEP_Z2);
//MultiDriver controller2(stepperE);

//------Настройка команд------
//#define NUMCOMMANDS 10
void homing();
void moviment();
void gotoLocation();
void servofn();
void rotate_tower();
void rotate_tower2();
void check_servo_x();
void dropcap_x();
void check_servo_y();
void dropcap_y();
void rotate_cup_back();
void rotate_cup_to();
void stepper_e0();
void stepper_e1();
void relay();
void turrelFunction();
void cup();
void cup_fn();
void check_turrelfn();
void check_turrelfn2();
void open_cofe();
void close_cofe();
void start_cofe();
void servo_sugar();
void milk_stepper_cmd();
void milk_stepper_reset_cmd();

//------для объединения комманд
void command_x();
void command_x_a();
void command_x_b();
void command_x_a_b();
void command_y();
void command_y_a();
void command_y_b();
void command_y_a_b();
void get_cap_x();
void get_cap_y();
void loud_cap();
void get_cupple();
void to_client();
void test();
void table();
void m0();
void m6();
void m7();

double X;
double Y;
double Z;
double D;
double N;
double T;

commandscallback commands[35] = {
{"X1", command_x}, {"X2", command_x_a}, {"X3", command_x_b}, {"X4", command_x_a_b},
{"Y1", command_y}, {"Y2", command_y_a}, {"Y3", command_y_b}, {"Y4", command_y_a_b},
{"B1", get_cap_x}, {"B2", get_cap_y}, {"B3", loud_cap}, {"B4", get_cupple}, {"B5", to_client}, {"B6", test}, {"T3", table}, {"M4", milk_stepper_cmd}, {"M5", milk_stepper_reset_cmd}, {"M6", m6}, {"M7", m7},
{"M1", open_cofe}, {"M2", close_cofe}, {"M3", start_cofe}, {"G1", homing}, {"G0", moviment}, {"S0", servofn}, {"S3", servo_sugar},
{"T1", rotate_tower}, {"T2", rotate_tower2}, {"C1", dropcap_x}, {"C2", dropcap_y}, {"S1", rotate_cup_to}, {"S2", rotate_cup_back}, 
{"E0", stepper_e0}, {"E1", stepper_e1}, {"C0", cup}
};
gcode Commands(35, commands);


void setup() {
//  tmr.setPeriodMode();
    //------Pins для концевиков-------
  pinMode(stop_x, INPUT_PULLUP);
  pinMode(stop_y, INPUT_PULLUP);
  pinMode(stop_z, INPUT_PULLUP);

  pinMode(home_switch_z, INPUT_PULLUP);
  pinMode(home_switch_e, INPUT_PULLUP);
  
  pinMode(ir_cap_x, INPUT_PULLUP);
  pinMode(ir_cap_y, INPUT_PULLUP);

  pinMode(ir_cup, INPUT_PULLUP);
  //------Pins для реле-------
//  pinMode(r1, OUTPUT);
//  digitalWrite(r1, HIGH);
//  pinMode(r2, OUTPUT);
//  digitalWrite(r2, HIGH);
//  pinMode(r3, OUTPUT);
//  digitalWrite(r3, HIGH);
//  pinMode(r4, OUTPUT);
//  digitalWrite(r4, HIGH);
//  pinMode(r5, OUTPUT);
//  digitalWrite(r5, HIGH);
//  pinMode(r6, OUTPUT);
//  digitalWrite(r6, HIGH);
//  pinMode(r7, OUTPUT);
//  digitalWrite(r7, HIGH);
//  pinMode(r8, OUTPUT);
//  digitalWrite(r8, HIGH);
  pinMode(OPEN, OUTPUT);
  digitalWrite(OPEN, HIGH);
  pinMode(START_COFE, OUTPUT);
  digitalWrite(START_COFE, HIGH);
  pinMode(CLOSE, OUTPUT);
  digitalWrite(CLOSE, HIGH);
  
  //------Для стаканчиков-----
  pinMode(turrel_pos, INPUT);
  pinMode(turrel_micro_switch, INPUT);
  pinMode(cup_splitter, INPUT_PULLUP);
  pinMode(RELAY_CUP, OUTPUT);
  pinMode(RELAY_TURREL, OUTPUT);
  digitalWrite(RELAY_CUP, HIGH);
  digitalWrite(RELAY_TURREL, HIGH);
  
  //  SerialUSB.begin(115200);
  Serial.begin(9600);

  turel_X.begin(MOTOR_X_RPM, MICROSTEPS);
  turel_Y.begin(MOTOR_Y_RPM, MICROSTEPS);
  turel_Z.begin(MOTOR_Z_RPM, MICROSTEPS);
  stepper_E.begin(MOTOR_E_RPM, MICROSTEPS);
  stepper_M0.begin(MOTOR_M0_RPM, MICROSTEPS);
  stepper_M1.begin(MOTOR_M1_RPM, MICROSTEPS);
  stepper_M2.begin(MOTOR_M2_RPM, MICROSTEPS);
  nav_X.begin(NAV_MOTOR_X_RPM, MICROSTEPS);
  nav_Y.begin(NAV_MOTOR_Y_RPM, MICROSTEPS);
  nav_Z.begin(NAV_MOTOR_Z_RPM, MICROSTEPS);
  
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
  turel_X.setEnableActiveState(LOW);
  turel_Y.setEnableActiveState(LOW);
  turel_Z.setEnableActiveState(LOW);
  stepper_E.setEnableActiveState(LOW);
  stepper_M0.setEnableActiveState(LOW);
  stepper_M1.setEnableActiveState(LOW);
  stepper_M2.setEnableActiveState(LOW);
  nav_X.setEnableActiveState(LOW);
  nav_Y.setEnableActiveState(LOW);
  nav_Z.setEnableActiveState(LOW);

//  check_servo_x();
//  check_servo_y();

    //----Читаем значения переменных с сахаром и сливками
//  EEPROM.get(0, milk_stepper_1);
//  EEPROM.get(1, milk_stepper_2);
//  EEPROM.get(2, milk_stepper_3);
}

void loop() {
   Commands.available();

  //----------------------------------------------------------------------------------
  //   Крутим турель если нету стаканчика
  //----------------------------------------------------------------------------------
  turrelFunction();

}

#include "turell_cup.h" ;
#include "cup.h" ;
#include "homing.h" ;
#include "relay.h" ;
#include "servo.h" ;
#include "turel_x.h" ;
#include "turel_y.h" ;
#include "move.h" ;
#include "rotate.h" ;
#include "steppers.h" ;
#include "custom.h" ;
#include "cream.h" ;
