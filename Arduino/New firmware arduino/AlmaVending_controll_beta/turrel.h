// --------------------- T0 ---------------------
void turrel_rotate(double d, double s, double a) {
  int dist = d;
  int accel = a;
  int spd = s;
  turrel.disableOutputs();
  turrel.setMaxSpeed(spd);
  turrel.setAcceleration(accel);
  turrel.moveTo(dist);
  turrel.runToPosition();
  turrel.enableOutputs();
  
}

void go_to_pos() {
  int newDValue = D;
  int newSValue = S;
  int newAValue = A;
  if (Commands.availableValue('D'))
    newDValue = Commands.GetValue('D');
  if (Commands.availableValue('S'))
    newSValue = Commands.GetValue('S');
  if (Commands.availableValue('A'))
    newAValue = Commands.GetValue('A');
  turrel_rotate(newDValue, newSValue, newAValue);
}

// --------------------- t3 ---------------------
void go_line_pos(double i) {
  //  Serial.println("Pos search----------");
  //  Serial.println("Current start position: ");
  //  int pos = turrel.currentPosition();
  //  Serial.println(pos);

  int newIValue = i;
  uint32_t distance = 0;

  switch (newIValue) {
    case 1: distance = 0; break;  // выбираем это
    case 2: distance = 850; break;
    case 3: distance = 1700; break;
    case 4: distance = 2550; break;
    case 5: distance = 3340; break;
    case 6: distance = -4100; break;
    case 7: distance = -3330; break;
    case 8: distance = -2530; break;
    case 9: distance = -1700; break;
    case 10: distance = -850; break;
  }

  //  Serial.println("Distance: ");
  //  Serial.print(distance);
  turrel.disableOutputs();
  turrel.setMaxSpeed(700);
  turrel.setAcceleration(200);
  turrel.moveTo(distance);
  turrel.runToPosition();
  turrel.enableOutputs();
  Serial.println("Current end position: ");
  turrelCurrentPosition = turrel.currentPosition();
  Serial.println(turrelCurrentPosition);
  Serial.println(F("Go to position true"));
  SET_DATA(turrelCurrentPosition);
  
}

void go_number_turrel() {
  int newIValue = I;
  if (Commands.availableValue('I'))
    newIValue = Commands.GetValue('I');
  go_line_pos(newIValue);
}

// --------------------- t2 ---------------------
void zero_homing_turrel() {

  turrel.disableOutputs();
  turrel.setMaxSpeed(600);
  turrel.setAcceleration(500);

  long initial_homing = -1;
  while (digitalRead(turrel_zero_homing)) {  // Make the Stepper move CCW until the switch is activated
    turrel.moveTo(initial_homing);           // Set the position to move to
    initial_homing--;                        // Decrease by 1 for next move if needed
    turrel.run();
    delay(5);
  }

  turrel.setCurrentPosition(0);  // Set the current position as zero for now
  turrel.setMaxSpeed(600);
  turrel.setAcceleration(500);

  initial_homing = 1;
  while (!digitalRead(turrel_zero_homing)) {  // Make the Stepper move CW until the switch is deactivated
    turrel.moveTo(initial_homing);            // Set the position to move to
    turrel.run();
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  turrel.enableOutputs();

  turrel.setCurrentPosition(0);
  Serial.println(F("Homing true"));
  turrelCurrentPosition = 0;
  SET_DATA(turrelCurrentPosition);

}

void get_position() {
  Serial.print(F("EEPRO Position: "));
  Serial.println(GET_DATA);
  turrelCurrentPosition = turrel.currentPosition();
  Serial.print(F("Position: "));
  Serial.println(turrelCurrentPosition);
  SET_DATA(turrelCurrentPosition);
  void display_print();
}

//----------------------------------------------------------------------------------
//   Функция для прокручивания турели стаканчиков
//----------------------------------------------------------------------------------
void turrelFunction() {

  if (digitalRead(turrel_micro_switch) == LOW || digitalRead(turrel_pos) == HIGH) {
    motor_val = 1;
  } else {
    motor_val = 2;
  }

  switch (motor_val) {
    case 1:
      digitalWrite(RELAY_TURREL, LOW);
      break;
    case 2:
      digitalWrite(RELAY_TURREL, HIGH);
      break;
  }
}

//----------------------------------------------------------------------------------
//   Функция для выдачи стаканчика
//----------------------------------------------------------------------------------


void cup_fn() {
  digitalWrite(RELAY_CUP, LOW);
  delay(1000);
  int buttonState = digitalRead(cup_splitter);
  do {
    digitalWrite(RELAY_CUP, LOW);
    buttonState = digitalRead(cup_splitter);
    //Serial.println(buttonState);
    DEBUG(buttonState);
  } while (buttonState == true);
  delayMicroseconds(7000);
  digitalWrite(RELAY_CUP, HIGH);
  return;
}

void cup() {
  digitalWrite(RELAY_CUP, LOW);
  delay(7000);
  cup_fn();
}

// --------------------- no command ---------------------
//Для перемещения удобного()
void go(AccelStepper motor, float steps, float speed_value, float acceleration) {
  motor.moveTo(motor.currentPosition() + steps);
  motor.setSpeed(speed_value);
  //motor.setAcceleration(acceleration);

  // Implementation without acceleration.
  while (motor.distanceToGo() != 0)
    motor.runSpeedToPosition();
  //motor.run();
}
