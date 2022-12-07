// НАСТРОЙКИ
#define INIT_KEY 0     // ключ первого запуска. 0-254, на выбор eeprom position

// ---- Турель загрузки капсул ---
#define turrel_cap_homing 15 // -----Удалить
#define turrel_zero_homing 52 //Определения нулевой точки турели
#define ir_cap 53 //Проверка наличия капсулы
#define turrel_cap_servo 2 //Выдача капсулы
#define turrel_cap_servo_mini 5 //Задвижка очереди
#define directionPin 47 // direction_ct
#define stepPin 46 // step_ct
//#define enablePin 48
#define button_plus 24
#define button_minus 25
// ---- Команды ---
#define NUMCOMMANDS 10


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



//ПЕРЕМЕННЫЕ
//---Глобальные переменные---
int pos_cap = 0;
int pos_key = 180;
int turrelCurrentPosition;
bool calibrating = false;
int menu_val = 1;

//---turrel---
void go_to_pos();
void go_number_turrel();
void zero_homing_turrel();
void get_position();
void correct_pos();

//---relay, servo---
void servofn();
void relayfn();

//---commands---
void drop_cap();
void check_machine();
void start_coffe();
void start_coffe_machine();

//---commands variable---
double N;
double D;
double A;
double S;
double I;
double T;

//---commands array---
commandscallback commands[NUMCOMMANDS] = {
  {"G0", start_coffe_machine},
  {"C0", drop_cap}, {"C1", check_machine}, {"C2", start_coffe},
  {"T0", go_to_pos}, {"T2", zero_homing_turrel}, {"T1", go_number_turrel}, {"T3", get_position},
  {"S0", servofn}, {"R0", relayfn},
};

//ОБЬЕКТЫ
AccelStepper turrel(1, stepPin, directionPin); // pin 3 = step, pin 6 = direction
Servo myservo;
Servo testservo;
gcode Commands(NUMCOMMANDS, commands);


void setup()
{

  //  turrel.setEnablePin(48);
  turrel.setMaxSpeed(1000);
  turrel.setSpeed(300);
  turrel.setAcceleration(400);


  pinMode(turrel_cap_homing, INPUT_PULLUP);
  pinMode(ir_cap, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println(GET_DATA);
  testservo.attach(22);
  delay(100);
  testservo.write(180);
  delay(1000);
  testservo.detach();
}

void loop() {
  for (;;) {
    // ваш код
    Commands.available();

 }
}

#include "turrel.h"
#include "commands.h"
#include "general_commands.h"
#include "servo.h"
#include "relay.h"
