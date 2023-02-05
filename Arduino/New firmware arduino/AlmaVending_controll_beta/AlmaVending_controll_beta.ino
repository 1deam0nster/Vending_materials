// НАСТРОЙКИ
#define INIT_KEY 0     // ключ первого запуска. 0-254, на выбор eeprom position

// раздефайнить или задефайнить для использования
#define DEBUG_ENABLE
#ifdef DEBUG_ENABLE
#define DEBUG(x) Serial.println(x)
#else
#define DEBUG(x)
#endif

// ---- Турель загрузки капсул ---
#define turrel_cap_homing 15 // -----Удалить
#define turrel_zero_homing 52 //Определения нулевой точки турели
#define ir_cap 53 //Проверка наличия капсулы
#define turrel_cap_servo 2 //Выдача капсулы
#define turrel_cap_servo_mini 5 //Задвижка очереди
#define directionPin 47 // direction_ct
#define stepPin 46 // step_ct
#define turrelEnablePin 48

// ---- Кофе машина ---
#define cofe_machine_ir 24 //end of prog
#define coffe_machine_start_pin 51 //magnit pin 22
#define cofe_machine_check_button_pin 50 //sensor button 51

// ---- Турель для выдачи сливок ---
#define dir_sc 44
#define step_sc 45
#define cream_servo 9 //или 10
#define cream_homing 12 // концевик турели 12
#define ir_cream 11 // датчик препятствия 11 
int cream_turrel_number = 1;

// ---- Манипулятор ---
#define step_manipul 37
#define dir_manipul 43
#define servo_manipul 3

// ---- Команды ---
#define NUMCOMMANDS 27

//-----Для выдачи стаканчиков -----
#define RELAY_CUP 22
#define RELAY_TURREL 25
#define turrel_pos 19     // номер входа, подключенный к кнопке Turret position
#define turrel_micro_switch 38     // номер входа, подключенный к кнопке Turret micro switch
#define cup_splitter 18     // номер входа, подключенный к кнопке Cup splitter
int motor_val = 3;

//-----Сахар -----
#define sugar_servo 4
#define sugar_ir_control 49

//-----Шоколад -----
#define choco_servo 8
#define choco_ir_control 36

// БИБЛИОТЕКИ
#include <gcode.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <EEPROM.h>


// МАКРОФУНКЦИИ
// печать в серийный порт, кастом функция
#define printWords()   \
  Serial.print("OK");

// данный код будет выполняться каждые 100 мс
#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr += (x);\
  if (flag)

#define GET_DATA EEPROM.read(0)
#define SET_DATA(x) EEPROM.write(0, (x))
#define GET_CREAM_POS_NUM EEPROM.read(1)
#define SET_CREAM_POS_NUM(x) EEPROM.write(1, (x))


//ПЕРЕМЕННЫЕ
//---Глобальные переменные---
int big_pos_cap = 0;
int mini_pos_cap = 0;


int pos_cap = 0; //удалить
int pos_key = 180;
int turrelCurrentPosition;
//bool calibrating = false;

int cream_check_value = 0;
int cap_check_value = 0;
bool machine_sensor;

//---turrel---
void go_to_pos();
void go_number_turrel();
void zero_homing_turrel();
void get_position();
//void correct_pos();

//---turrel_cream---
void go_to_pos_cream();
void go_number_turrel_cream();
void zero_homing_turrel_cream();
void get_position_cream();
void cream_drop();
void cream_check();
void cream_servo_test();

//---cup turrel---
void turrelFunction();
void cap_check();

//---relay, servo---
void servofn();
void relayfn();

//---commands---
void drop_cap();
void check_machine();
void start_coffe();
void start_coffe_machine();
void sugar_command();
void chocolate_command();
void cup_fn();
void choco_check();
void cream_check();
void sugar_check();
void cream_restart_eeprom_position();

//---manipulaator---
void go_to_pos_man();
void go_man_stepper();
void up_man();
void servo_man();
//void get_position();
void to_win_man();
void to_machine_man();

//---commands variable---
double N;
double D;
double A;
double S;
double I;
double T;
double B;

//---commands array---
commandscallback commands[NUMCOMMANDS] = {
  {"G0", start_coffe_machine},
  {"C0", drop_cap}, {"C1", check_machine}, {"C2", start_coffe}, {"C3", cup_fn}, {"C4", choco_check}, {"C5", sugar_check},
  {"P0", sugar_command}, {"P1", chocolate_command},
  {"T0", go_to_pos}, {"T1", go_number_turrel}, {"T2", zero_homing_turrel}, {"T3", get_position},
  {"M0", go_to_pos_cream}, {"M1", go_number_turrel_cream}, {"M2", zero_homing_turrel_cream}, {"M3", get_position_cream}, {"M4", cream_drop}, {"M5", cream_restart_eeprom_position}, {"M6", cream_servo_test},
  {"F0", go_to_pos_man}, {"F1", up_man}, {"F2", servo_man}, {"F3", to_win_man}, {"F3", to_machine_man},
  {"S0", servofn}, {"R0", relayfn},
};

//ОБЬЕКТЫ
AccelStepper turrel(1, stepPin, directionPin); // pin 3 = step, pin 6 = direction
AccelStepper manipul(1, step_manipul, dir_manipul); // pin 3 = step, pin 6 = direction
AccelStepper cream(1, step_sc, dir_sc); // pin 3 = step, pin 6 = direction

Servo cap_drop;
Servo myservo;
Servo sugar;
Servo chocolate;
Servo manipulator;
//Servo cream;
gcode Commands(NUMCOMMANDS, commands);


void setup()
{


  turrel.setEnablePin(48);
  turrel.setMaxSpeed(1000);
  turrel.setSpeed(600);
  turrel.setAcceleration(500);
  turrel.setEnablePin(turrelEnablePin);
  turrel.enableOutputs();
  
  pinMode(turrel_cap_homing, INPUT_PULLUP);
  pinMode(ir_cap, INPUT_PULLUP);
  
  //------Проверка остатка сахара и шоколада-----
  pinMode(sugar_ir_control, INPUT_PULLUP);
  pinMode(choco_ir_control, INPUT_PULLUP);
  pinMode(cofe_machine_ir, INPUT_PULLUP);
  pinMode(ir_cream, INPUT_PULLUP);
  
  //------Для стаканчиков-----
  pinMode(turrel_pos, INPUT_PULLUP);
  pinMode(turrel_micro_switch, INPUT_PULLUP);
  pinMode(cup_splitter, INPUT_PULLUP);
  pinMode(RELAY_CUP, OUTPUT);
  pinMode(RELAY_TURREL, OUTPUT);
  digitalWrite(RELAY_CUP, HIGH);
  digitalWrite(RELAY_TURREL, HIGH);

//  turrel_drop.attach(turrel_cap_servo);
  cap_drop.attach(turrel_cap_servo);
  cap_drop.writeMicroseconds(1800);

  manipulator.attach(servo_manipul);
  
//  #ifdef DEBUG_ENABLE
    Serial.begin(9600);
//  #endif

//  Serial.println(GET_DATA);
  
  
}

void loop() {
  for (;;) {
    // ваш код
    Commands.available();
    turrelFunction();
//    DEBUG(digitalRead(ir_cream)); // 0 - есть капсула, 1 - нету
//    DEBUG(digitalRead(cofe_machine_sensor));
//    DEBUG(digitalRead(sugar_ir_control));
//    DEBUG(digitalRead(choco_ir_control));
//    DEBUG(digitalRead(turrel_micro_switch));
//    DEBUG(digitalRead(turrel_pos));
//    DEBUG(digitalRead(cup_splitter));
//    DEBUG(digitalRead(cream_homing));
 }
}
#include "turrel_cream.h"
#include "turrel.h"
#include "commands.h"
#include "general_commands.h"
#include "servo.h"
#include "relay.h"
#include "manipulator.h"
