// --------------------- T0 ---------------------
void turrel_rotate(double d, double s, double a) {
  int dist = d;
  int accel = a;
  int spd = s;
  turrel.setMaxSpeed(spd);
  turrel.setAcceleration(accel);
  turrel.moveTo(dist);
  turrel.runToPosition();
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
    case 2: distance = 820; break;
    case 3: distance = 1650; break;
    case 4: distance = 2470; break;
    case 5: distance = 3270; break;
    case 6: distance = -3300; break;
    case 7: distance = -3300; break;
    case 8: distance = -2500; break;
    case 9: distance = -1670; break;
    case 10: distance = -830; break;
  }


  // if (newIValue == 1) {
  //   distance = 0;
  // } else if (newIValue == 2) {
  //   distance = 820;
  // } else if (newIValue == 3) {
  //   distance = 1650;
  // } else if (newIValue == 4) {
  //   distance = 2470;
  // } else if (newIValue == 5) {
  //   distance = 3270;
  // } else if (newIValue == 6) {
  //   distance = 4120;
  // } else if (newIValue == 7) {
  //   distance = -3300;
  // } else if (newIValue == 8) {
  //   distance = -2500;
  // } else if (newIValue == 9) {
  //   distance = -1670;
  // } else if (newIValue == 10) {
  //   distance = -830;
  // }
  //  Serial.println("Distance: ");
  //  Serial.print(distance);

  turrel.setMaxSpeed(700);
  turrel.setAcceleration(200);
  turrel.moveTo(distance);
  turrel.runToPosition();
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


  turrel.setMaxSpeed(1000);
  turrel.setSpeed(600);
  turrel.setAcceleration(500);

  long initial_homing = -1;
  while (digitalRead(turrel_zero_homing)) {  // Make the Stepper move CCW until the switch is activated
    turrel.moveTo(initial_homing);           // Set the position to move to
    initial_homing--;                        // Decrease by 1 for next move if needed
    turrel.run();
    delay(5);
  }

  turrel.setCurrentPosition(0);  // Set the current position as zero for now
  turrel.setMaxSpeed(1000);
  turrel.setSpeed(600);
  turrel.setAcceleration(500);

  initial_homing = 1;
  while (!digitalRead(turrel_zero_homing)) {  // Make the Stepper move CW until the switch is deactivated
    turrel.moveTo(initial_homing);            // Set the position to move to
    turrel.run();
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }

  turrel.setCurrentPosition(0);
  Serial.println(F("Homing true"));
  turrelCurrentPosition = 0;
  SET_DATA(turrelCurrentPosition);

  //  myOLED.clrScr();                                   // Чистим экран.
  //  myOLED.print( "Турель в нулевой позиции"    , 0, 0);    // Выводим текст начиная с 0 столбца 0 строки.
  //  myOLED.print( turrelCurrentPosition , 0, 2);    // Выводим текст по центру 2 строки.
  //  delay(3000);
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