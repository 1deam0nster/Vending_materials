/*
  LINEAR KINEMATICS
  Download the STEPPER DRIVER library as you already have the A4988 and DRV8825
  drive libraries available at: https://github.com/laurb9/StepperDriver
  Before using the example, make sure that the stepper motor library is installed.
  example by Leandro Lima / HeavyTech @2019
*/



#include "A4988.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <gcode.h>
#include <Servo.h>

//------Подключение концевиков------
#define home_switch 22 // концевик для Z
#define home_switch2 24 //концевик для E
#define home_switch3 23 //концевик для Y
#define home_switch4 25 //концевик капсулы Y
//#define home_switch5 30

//------Подключение серв------
Servo servo;
Servo servo2;

#define NUMCOMMANDS 8
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
//Number of steps to take 1 millimeter
#define STEPS_MM 80
// Target RPM for X axis motor
#define MOTOR_X_RPM 30
#define MOTOR_Y_RPM 10
#define MOTOR_Z_RPM 120
#define MOTOR_E_RPM 120
//#define MOTOR_E1_RPM 120
//#define MOTOR_E2_RPM 120

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

//// E1 motor
//#define DIR_E1 41
//#define STEP_E1 43
//#define ENA_E1 39
//
//// E2 motor
//#define DIR_E2 47
//#define STEP_E2 32
//#define ENA_E2 45

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
//BasicStepperDriver stepperE(MOTOR_STEPS, DIR_Y, STEP_Y);
//MultiDriver controller2(stepperE);

// OR
// synchronized move, trajectory is a straight line
//SyncDriver controller(stepperX, stepperY);
void homing();
void moviment();
void gotoLocation();
void servofn();
void stepper_e();
void turrelfn();
void dropcap();
void rotate_cup_back();
void rotate_cup_to();
void rotate_tower();

/*
  G28 - HOMING
  G0 - SET COORDINATES -> G0 X{n} Y{n}
*/

commandscallback commands[NUMCOMMANDS] = {{"G1", homing}, {"G0", moviment}, {"S0", servofn}, {"S1", rotate_cup_to}, {"S2", rotate_cup_back}, {"E0", stepper_e}, {"C0", dropcap}, {"C1", rotate_tower}};
gcode Commands(NUMCOMMANDS, commands);

double X;
double Y;
double Z;
double E;
double D;
double N;
double T;








void setup() {
  //  while (!Serial) ;
  //------Pins для концевиков-------
  pinMode(home_switch, INPUT_PULLUP);
  pinMode(home_switch2, INPUT_PULLUP); //свитч на турели
  pinMode(home_switch3, INPUT_PULLUP);
  pinMode(home_switch4, INPUT_PULLUP);


  /*
     Set target motors RPM.
  */
  Commands.begin();
  //  SerialUSB.begin(115200);
  Serial.begin(9600);
  //Serial2.begin(9600);
  stepperX.begin(MOTOR_X_RPM, MICROSTEPS);
  stepperY.begin(MOTOR_Y_RPM, MICROSTEPS);
  stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS);
  stepperE.begin(MOTOR_E_RPM, MICROSTEPS);

  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
  stepperX.setEnableActiveState(LOW);
  stepperY.setEnableActiveState(LOW);
  stepperZ.setEnableActiveState(LOW);
  stepperE.setEnableActiveState(LOW);

  delay(500);
  //----Проверка на нижнюю серву
  servo.attach(9);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка на верхнюю серву
  servo2.attach(8);
  servo2.write(0);
  delay(500);
  servo2.write(50);
  delay(1000);
  servo2.detach();

  //----Крутить турель с капсулами
  check_turrelfn();
}

void loop() {
  Commands.available();
  delay(100);

}

void homing()
{

  // first, check if stopper was hit
  //  if (digitalRead(home_switch) == HIGH) {
  //    stepperX.enable();
  //    stepperX.move(10000);
  //  } else {
  //    Serial.println("STOPPER REACHED");
  //    stepperX.startBrake();
  //    stepperX.disable();// DISABLE MOTOR Y
  //  }

  long initial_homing = -1;

  // Start Homing procedure of Stepper Motor at startup
  //  Serial.print("StepperX is Homing . . . . . . . . . . . ");
  //
  //  while (digitalRead(home_switch)) {  // Make the Stepper move CCW until the switch is activated
  //    stepperX.enable();
  //    stepperX.move(initial_homing);  // Set the position to move to
  //    initial_homing--;  // Decrease by 1 for next move if needed
  //    delay(5);
  //  }
  //
  //  initial_homing = 1;
  //  while (!digitalRead(home_switch)) { // Make the Stepper move CW until the switch is deactivated
  //    stepperX.enable();
  //    stepperX.move(initial_homing);  // Set the position to move to
  //    initial_homing++;  // Decrease by 1 for next move if needed
  //    delay(5);
  //  }
  //
  //  stepperX.disable();// DISABLE MOTOR X
  //
  //  //------------------------------
  //
  //  // Start Homing procedure of Stepper Motor at startup
  //  Serial.print("StepperY is Homing . . . . . . . . . . . ");
  //    while (digitalRead(home_switch3)) {  // Make the Stepper move CCW until the switch is activated
  //    stepperY.enable();
  //    stepperY.move(initial_homing);  // Set the position to move to
  //    initial_homing--;  // Decrease by 1 for next move if needed
  //    delay(5);
  //  }
  //
  //  initial_homing = 1;
  //  while (!digitalRead(home_switch3)) { // Make the Stepper move CW until the switch is deactivated
  //    stepperY.enable();
  //    stepperY.move(initial_homing);  // Set the position to move to
  //    initial_homing++;  // Decrease by 1 for next move if needed
  //    delay(5);
  //  }
  //
  //  stepperY.disable();// DISABLE MOTOR Y

  //------------------------------

  // Start Homing procedure of Stepper Motor at startup
  Serial.print("StepperZ is Homing . . . . . . . . . . . ");
  while (digitalRead(home_switch)) {  // Make the Stepper move CCW until the switch is activated
    stepperZ.enable();
    stepperZ.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }

  initial_homing = 1;
  while (!digitalRead(home_switch)) { // Make the Stepper move CW until the switch is deactivated
    stepperZ.enable();
    stepperZ.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }

  stepperZ.disable();// DISABLE MOTOR X


  //------------------------------
  // Start Homing procedure of Stepper Motor at startup
  //stepperE.move(1000);


  Serial.print("StepperE is Homing . . . . . . . . . . . ");
  while (digitalRead(home_switch2)) {  // Make the Stepper move CCW until the switch is activated
    stepperE.enable();
    stepperE.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }

  initial_homing = 1;
  while (!digitalRead(home_switch2)) { // Make the Stepper move CW until the switch is deactivated
    stepperE.enable();
    stepperE.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }

  stepperE.disable();// DISABLE MOTOR X

}

void gotoLocation(double x, double y, double z)
{
  int stepsx = (x - X) * STEPS_MM; // DISTANCE VARIATION X
  int stepsy = (y - Y) * STEPS_MM; // DISTANCE VARIATION Y
  int stepsz = (z - Z) * STEPS_MM; // DISTANCE VARIATION Y
  //int stepse = (e - E) * STEPS_MM; // DISTANCE VARIATION Y


  stepperX.enable();// ENABLE MOTOR X
  stepperY.enable();
  stepperZ.enable();
  //stepperE.enable();

  controller.move(stepsx, stepsy, stepsz);//SEND CURRENT STEPS FOR DRIVE
  //controller2.move(stepse);

  X = x; // SET LAST POSITION
  Y = y;
  Z = z;
  // E = e;

  stepperX.disable();// DISABLE MOTOR Y
  stepperY.disable();
  stepperZ.disable();
  //stepperE.disable();

  //Commands.comment("X:" + String(x) + "; Y:" + String(y) + "; Z:" + String(z)); // DEBUG SERIAL
}

// added paramenter x and y in function MOVIMENT > SET GOTO LOCATION;
void moviment() {
  double newXValue = X;
  double newYValue = Y;
  double newZValue = Z;
  //double newEValue = E;
  if (Commands.availableValue('X')) // ADDED parameter X in G0
    newXValue = Commands.GetValue('X');
  if (Commands.availableValue('Y')) // ADDED parameter Y in G0
    newYValue = Commands.GetValue('Y');
  if (Commands.availableValue('Z')) // ADDED parameter Z in G0
    newZValue = Commands.GetValue('Z');
  // if (Commands.availableValue('E')) // ADDED parameter Z in G0
  //   newZValue = Commands.GetValue('E');
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

// -----------------Command E0-------------
void stepper_e()
{
  int newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in E0
    newDValue = Commands.GetValue('D');
  steppere_degreed(newDValue);
}

void steppere_degreed(double d)
{
  int deg = d;
  stepperE.enable();
  stepperE.move(deg);
  stepperE.disable();
}


// -----------------Command S1-------------
void rotate_cup_to(){
    int pos;
    servo2.attach(7);
    //-----Подать стаканчик клиенту
    for (pos = 14; pos <= 150; pos += 1) { // goes from 180 degrees to 0 degrees
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    servo.detach();
}

void rotate_cup_back(){
    int pos;
    servo2.attach(7);
    //-----Подать стаканчик клиенту
    for (pos = 150; pos >= 14; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    servo.detach();
}
// -----------------Command C0-------------
void dropcap()
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


void homing_turrel()
{
  long initial_homing = -1;
  stepperY.enable();
  stepperY.move(-200);
  delay(1000);
  while (digitalRead(home_switch3)) {  // Make the Stepper move CCW until the switch is activated
    stepperY.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  initial_homing = 1;
  while (!digitalRead(home_switch3)) { // Make the Stepper move CW until the switch is deactivated
    stepperY.enable();
    stepperY.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
  stepperY.move(-200);
  stepperY.disable();// DISABLE MOTOR X
}

// -----------------Command C1-------------
void rotate_tower() {
  check_turrelfn();
}

// -----------------Check tower cup-------------

void check_turrelfn()
{
  int capsule_state = digitalRead(home_switch4);

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

    capsule_state = digitalRead(home_switch4);
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

    capsule_state = digitalRead(home_switch4);
    //----Если приехала пустая ячейка, пишем что пустая турель
    //---------- 3 проверка-----------
    if (capsule_state == true) {
      //---Пишем в серийный порт что нету капсул в турели
      Serial.print("Turrel 1 - false");
    }


  } else {
    Serial.print("Turrel 1 - true");
  }
}
