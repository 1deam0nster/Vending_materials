#include "A4988.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <gcode.h>
#include <Servo.h>

//------Подключение серв------
Servo servo; 

//------Подключение концевиков------
#define home_switch_z 22 // концевик для Z
#define home_switch_e 21 //концевик для E

#define turrel_switch_x 23 //концевик турелли с капсулами Х
#define turrel_switch_y 24 //концевик турелли с капсулами Y

#define ir_cap_y 27 //концевик капсулы Y
#define ir_cap_x 25 //концевик капсулы X 27


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

// X motor
#define DIR_X 47
#define STEP_X 48
#define ENA_X 46

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

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step, 4 = 1/4, 8 = 1/8 and 16 = 1/6 Microsteps.
#define MICROSTEPS 8

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
A4988 stepperX(MOTOR_STEPS, DIR_X, STEP_X, ENA_X);
A4988 stepperY(MOTOR_STEPS, DIR_Y, STEP_Y, ENA_Y);
A4988 stepperZ(MOTOR_STEPS, DIR_Z, STEP_Z, ENA_Z);
A4988 stepperE(MOTOR_STEPS, DIR_E, STEP_E, ENA_E);

// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick

MultiDriver controller(stepperX, stepperY, stepperZ);
BasicStepperDriver stepper_E(MOTOR_STEPS, DIR_E, STEP_E);
//MultiDriver controller2(stepperE);

//------Настройка команд------

#define NUMCOMMANDS 10
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
void stepper_e();

double X;
double Y;
double Z;
double D;
double N;

commandscallback commands[NUMCOMMANDS] = {{"G1", homing}, {"G0", moviment}, {"S0", servofn}, {"T1", rotate_tower}, {"T2", rotate_tower2}, {"C1", dropcap_x}, {"C2", dropcap_y}, {"S1", rotate_cup_to}, {"S2", rotate_cup_back}, {"E0", stepper_e}};
gcode Commands(NUMCOMMANDS, commands);


void setup() {  
  Commands.begin();
  //  SerialUSB.begin(115200);
  Serial.begin(9600);


  stepperX.begin(MOTOR_X_RPM, MICROSTEPS);
  stepperY.begin(MOTOR_Y_RPM, MICROSTEPS);
  stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS);
  stepper_E.begin(MOTOR_E_RPM, MICROSTEPS);
  
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
  stepperX.setEnableActiveState(LOW);
  stepperY.setEnableActiveState(LOW);
  stepperZ.setEnableActiveState(LOW);
  stepper_E.setEnableActiveState(LOW);
  
  check_servo_x();
  check_servo_y();
}

void loop() {
  Commands.available();
}

void homing()
{

  long initial_homing = -1;
  Serial.print("StepperZ is Homing");
    while (digitalRead(home_switch_z)) {  // Make the Stepper move CCW until the switch is activated
    stepperZ.enable();
    stepperZ.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }

  initial_homing = 1;
  while (!digitalRead(home_switch_z)) { // Make the Stepper move CW until the switch is deactivated
    stepperZ.enable();
    stepperZ.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
  Serial.println("");
  Serial.println("Z homing OK");
  stepperZ.disable();// DISABLE MOTOR X


  initial_homing = -1;
  Serial.print("StepperE is Homing");
  while (digitalRead(home_switch_e)) {  // Make the Stepper move CCW until the switch is activated
    stepper_E.enable();
    stepper_E.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(1);
  }

  initial_homing = 1;
  while (!digitalRead(home_switch_e)) { // Make the Stepper move CW until the switch is deactivated
    stepper_E.enable();
    stepper_E.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(1);
  }
  
  Serial.println("");
  Serial.println("E homing OK");
  stepper_E.disable();
  
}

void gotoLocation(double x, double y, double z)
{
  int stepsx = (x - X) * STEPS_MM; // DISTANCE VARIATION X
  int stepsy = (y - Y) * STEPS_MM; // DISTANCE VARIATION Y
  int stepsz = (z - Z) * STEPS_MM; // DISTANCE VARIATION Y

  stepperX.enable();// ENABLE MOTOR X
  stepperY.enable();
  stepperZ.enable();
  
  controller.move(stepsx, stepsy, stepsz);//SEND CURRENT STEPS FOR DRIVE

  X = x; // SET LAST POSITION
  Y = y;
  Z = z;
  
  stepperX.disable();// DISABLE MOTOR Y
  stepperY.disable();
  stepperZ.disable();
}

void moviment() {
  double newXValue = X;
  double newYValue = Y;
  double newZValue = Z;
  if (Commands.availableValue('X')) // ADDED parameter X in G0
    newXValue = Commands.GetValue('X');
  if (Commands.availableValue('Y')) // ADDED parameter Y in G0
    newYValue = Commands.GetValue('Y');
  if (Commands.availableValue('Z')) // ADDED parameter Z in G0
    newZValue = Commands.GetValue('Z');
  gotoLocation(newXValue, newYValue, newZValue);
}

// -----------------Command S0-------------
void servo_degrid(double n, double d)
{
  int serv_number = n;
  int deg = d;
  //-----Подключаем сервоприводы
  servo.attach(serv_number);

  //----Открыть клешню
  servo.write(deg);
  delay(1000);

  //-----Отключаем сервоприводы
  servo.detach();
  //Commands.comment("D:" + String(d)); // DEBUG SERIAL

}

void servofn() {

  double newNValue = N;
  if (Commands.availableValue('N')) // ADDED parameter D in S0
  newNValue = Commands.GetValue('N');
  
  double newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in S0
    newDValue = Commands.GetValue('D');
  
  servo_degrid(newNValue, newDValue);
}

// -----------------Command T1-------------
void rotate_tower() {
  check_turrelfn();
}

//крутим турель Х до концевика
void homing_turrel()
{
  long initial_homing = -1;
  stepperX.enable();
  stepperX.move(200);
  delay(1000);
  while (digitalRead(turrel_switch_x)) {  // Make the Stepper move CCW until the switch is activated
    stepperX.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  initial_homing = 1;
  while (!digitalRead(turrel_switch_x)) { // Make the Stepper move CW until the switch is deactivated
    stepperX.enable();
    stepperX.move(turrel_switch_x);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
//  stepperX.move(-200);
  stepperX.disable();// DISABLE MOTOR X
}

//преверка есть ли капсула, крутим турель Х
void check_turrelfn()
{
  int capsule_state = digitalRead(ir_cap_x);

  //---------- 1 проверка-----------
  if (capsule_state == true) {
    //----Открываем вехнюю серву
    servo.attach(8);
    servo.write(0);

    //----Запуск поиска нуля
    homing_turrel();

    //----Закрываем верхнюю серву
    servo.write(50);
    delay(1000);
    servo.detach();
    delay(1000);

    capsule_state = digitalRead(ir_cap_x);
    //----Если приехала пустая ячейка, запускаем еще раз
    //---------- 2 проверка-----------
    if (capsule_state == true) {
      //----Открываем вехнюю серву
      servo.attach(8);
      servo.write(0);

      //----Запуск поиска нуля
      homing_turrel();

      //----Закрываем верхнюю серву
      servo.write(50);
      delay(1000);
      servo.detach();
    }

    capsule_state = digitalRead(ir_cap_x);
    //----Если приехала пустая ячейка, пишем что пустая турель
    //---------- 3 проверка-----------
    if (capsule_state == true) {
      //---Пишем в серийный порт что нету капсул в турели
      Serial.println("Turrel X - false");
    }

  } else {
    Serial.println("Turrel 1 - true");
  }
}

//--Проверка второй турели
void check_servo_x(){
  //----Проверка на нижнюю серву
  servo.attach(9);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка на верхнюю серву
  servo.attach(8);
  servo.write(0);
  delay(500);
  servo.write(50);
  delay(1000);
  servo.detach();
}

// -----------------Command C1-------------
void dropcap_x()
{
  //----закрыть нижнюю
  servo.attach(9);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----открыть верх
  servo.attach(8);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка капсул в башне
  //check_turrelfn();               -----Из за висяка МК отдельная команда C1
}





// -----------------Command T2-------------
void rotate_tower2() {
  check_turrelfn2();
}

//крутим турель Х до концевика
void homing_turrel2()
{
  long initial_homing = -1;
  stepperY.enable();
  stepperY.move(-200);
  delay(1000);
  while (digitalRead(turrel_switch_y)) {  // Make the Stepper move CCW until the switch is activated
    stepperY.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  initial_homing = 1;
  while (!digitalRead(turrel_switch_y)) { // Make the Stepper move CW until the switch is deactivated
    stepperY.enable();
    stepperY.move(turrel_switch_y);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
  stepperY.move(-200);
  stepperY.disable();// DISABLE MOTOR X
}

//преверка есть ли капсула, крутим турель Х
void check_turrelfn2()
{
  int capsule_state = digitalRead(ir_cap_y);

  //---------- 1 проверка-----------
  if (capsule_state == true) {
    //----Открываем вехнюю серву
    servo.attach(10);
    servo.write(0);

    //----Запуск поиска нуля
    homing_turrel2();

    //----Закрываем верхнюю серву
    servo.write(50);
    delay(1000);
    servo.detach();
    delay(1000);

    capsule_state = digitalRead(ir_cap_y);
    //----Если приехала пустая ячейка, запускаем еще раз
    //---------- 2 проверка-----------
    if (capsule_state == true) {
      //----Открываем вехнюю серву
      servo.attach(10);
      servo.write(0);

      //----Запуск поиска нуля
      homing_turrel2();

      //----Закрываем верхнюю серву
      servo.write(50);
      delay(1000);
      servo.detach();
    }

    capsule_state = digitalRead(ir_cap_y);
    //----Если приехала пустая ячейка, пишем что пустая турель
    //---------- 3 проверка-----------
    if (capsule_state == true) {
      //---Пишем в серийный порт что нету капсул в турели
      Serial.println("Turrel Y - false");
    }

  } else {
    Serial.println("Turrel Y - true");
  }
}

//--Проверка второй турели
void check_servo_y(){
  //----Проверка на нижнюю серву
  servo.attach(10);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка на верхнюю серву
  servo.attach(11);
  servo.write(0);
  delay(500);
  servo.write(50);
  delay(1000);
  servo.detach();
}

// -----------------Command C1-------------
void dropcap_y()
{
  //----закрыть нижнюю
  servo.attach(11);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----открыть верх
  servo.attach(10);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка капсул в башне
  //check_turrelfn();               -----Из за висяка МК отдельная команда C1
}

// -----------------Command S1 & S2-------------
void rotate_cup_to() {
  int pos;
  servo.attach(7);
  //-----Подать стаканчик клиенту
  for (pos = 80; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  servo.detach();
}

void rotate_cup_back() {
  int pos;
  servo.attach(7);
  //-----Подать стаканчик клиенту
  for (pos = 180; pos >= 80; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  servo.detach();
}

// -----------------Command E0-------------
void stepper_e()
{
  int newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in E0
    newDValue = Commands.GetValue('D');
  steppere_degreed(newDValue);
//  stepper_E.enable();
//  stepper_E.move(1000);
//  stepper_E.disable();
}

void steppere_degreed(double d)
{
  int deg = d;
  stepper_E.enable();
  stepper_E.move(deg);
  stepper_E.disable();
}
