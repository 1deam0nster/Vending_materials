// --------------------- M0 ---------------------
void turrel_rotate_cream(double d, double s, double a) {
  int dist = d;
  int accel = a;
  int spd = s;
//  turrel.disableOutputs();
  cream.setMaxSpeed(spd);
  cream.setAcceleration(accel);
  cream.moveTo(dist);
  cream.runToPosition();
//  turrel.enableOutputs();
}

void go_to_pos_cream() {
  int newDValue = D;
  int newSValue = S;
  int newAValue = A;
  if (Commands.availableValue('D'))
    newDValue = Commands.GetValue('D');
  if (Commands.availableValue('S'))
    newSValue = Commands.GetValue('S');
  if (Commands.availableValue('A'))
    newAValue = Commands.GetValue('A');
  turrel_rotate_cream(newDValue, newSValue, newAValue);
}

// --------------------- M1 ---------------------
void go_line_pos_cream(double i) {
  //  Serial.println("Pos search----------");
  //  Serial.println("Current start position: ");
  //  int pos = turrel.currentPosition();
  //  Serial.println(pos);

  int newIValue = i;
  uint32_t distance = 0;

//  switch (newIValue) {
//    case 1: distance = 0; break;  // выбираем это
//    case 2: distance = 2800; break;
//    case 3: distance = 5600; break;
//    case 4: distance = 8400; break;
//    case 5: distance = -5600; break;
//    case 6: distance = -3300; break;
//  }

  switch (newIValue) {
    case 1: distance = 0; break;  // выбираем это
    case 2: distance = 1400; break;
    case 3: distance = 2800; break;
    case 4: distance = 4200; break;
    case 5: distance = 5600; break;
    case 6: distance = 7000; break;
  }

//  Serial.println("Distance: ");
//  Serial.print(distance);
//  turrel.disableOutputs();
  cream.setMaxSpeed(700);
  cream.setAcceleration(200);
  cream.moveTo(distance);
  cream.runToPosition();
//  turrel.enableOutputs();
  Serial.println("Current end position: ");
  //turrelCurrentPositionCream = cream.currentPosition();
  //Serial.println(turrelCurrentPositionCream);
  Serial.println(F("Go to position true"));
//  SET_DATA(turrelCurrentPosition);
  
}

void go_number_turrel_cream() {
  int newIValue = I;
  if (Commands.availableValue('I'))
    newIValue = Commands.GetValue('I');
  go_line_pos_cream(newIValue);
}

// --------------------- M2 ---------------------
void zero_homing_turrel_cream() {

//  turrel.disableOutputs();
  cream.setMaxSpeed(1000);
  cream.setAcceleration(1000);
  cream.setSpeed(700);
  
  long initial_homing = -1;
  while (digitalRead(cream_homing)) {  // Make the Stepper move CCW until the switch is activated
    cream.moveTo(initial_homing);           // Set the position to move to
    initial_homing--;                        // Decrease by 1 for next move if needed
    cream.run();
    delay(5);
  }

  cream.setCurrentPosition(0);  // Set the current position as zero for now
  cream.setMaxSpeed(1000);
  cream.setAcceleration(1000);
  cream.setSpeed(700);
  
  initial_homing = 1;
  while (!digitalRead(cream_homing)) {  // Make the Stepper move CW until the switch is deactivated
    cream.moveTo(initial_homing);            // Set the position to move to
    cream.run();
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
//  turrel.enableOutputs();

  cream.setCurrentPosition(0);
  Serial.println(F("Homing true"));
  //turrelCurrentPositionCream = 0;
  //SET_DATA(turrelCurrentPosition);

}

//--------------------- M3 ---------------------
void get_position_cream() {
//  Serial.print(F("EEPRO Position: "));
//  Serial.println(GET_DATA);
//  turrelCurrentPosition = turrel.currentPosition();
//  Serial.print(F("Position: "));
//  Serial.println(turrelCurrentPosition);
//  SET_DATA(turrelCurrentPosition);
//  void display_print();
  Serial.println(GET_CREAM_POS_NUM);
}

// --------------------- M5 ---------------------
void cream_restart_eeprom_position() {
  SET_CREAM_POS_NUM(1);
}

// --------------------- M4 ---------------------
void cream_drop() {
  go_line_pos_cream(GET_CREAM_POS_NUM);
  myservo.attach(cream_servo);
  delay(2000);
  myservo.write(110);
  delay(2000);
  myservo.write(0);
  delay(2000);
  cream_check();
  myservo.write(110);
  delay(1000);
  myservo.detach();
}

void cream_next(){
  myservo.write(110);
  delay(1000);
  int cream_pos_num = GET_CREAM_POS_NUM + 1;
  SET_CREAM_POS_NUM(cream_pos_num);
  go_line_pos_cream(cream_pos_num);
  cream_drop();
}

void cream_check(){
//    return digitalRead(ir_cream);
  bool check = digitalRead(ir_cream);
  bool check_state;
  DEBUG(cream_check_value);
  cream_check_value += 1;
  switch (check) {
    case 0: 
      check_state = 0;
      Serial.println("Cream OK"); 
      break; 
    case 1: 
      check_state = 1; 
      switch (cream_check_value) {
        case 0: Serial.println("Cream FALSE"); cream_drop(); break;
        case 1: Serial.println("Cream FALSE"); cream_drop(); break;
        case 2: Serial.println("Cream FALSE"); cream_drop(); break;
        case 3: 
          Serial.println("ALL FALSE");  
          cream_check_value = 0;
          if (GET_CREAM_POS_NUM == 6)
            Serial.println("CREAM EMPTY");
          else
            cream_next();
            break;
      }
  }
}


// --------------------- M6 ---------------------
void cream_servo_test(){
  myservo.attach(cream_servo);
  delay(2000);
  myservo.write(110);
  delay(2000);
  myservo.write(0);
  delay(2000);
  cream_check();
  myservo.write(110);
  delay(1000);
  myservo.detach();
}
