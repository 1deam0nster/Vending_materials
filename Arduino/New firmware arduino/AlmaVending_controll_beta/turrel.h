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

void go_to_pos(){
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
  Serial.println("Pos search----------");
  Serial.println("Current start position: ");
  int pos = turrel.currentPosition();
  Serial.println(pos);
  
  int newIValue = i;
  uint32_t distance = 0;
  
  if (newIValue == 1)
    {
      distance = 0;
    }
  else if (newIValue == 2)
    {
      distance = 820;
    }
  else if (newIValue == 3)
    {
      distance = 1650;
    }
  else if (newIValue == 4)
    {
      distance = 2470;
    }
  else if (newIValue == 5)
    {
      distance = 3270;
    }
  else if (newIValue == 6)
    {
      distance = 4120;
    }
  else if (newIValue == 7)
    {
      distance = -3300;
    }
  else if (newIValue == 8)
    {
      distance = -2500;
    }
  else if (newIValue == 9)
    {
      distance = -1670;
    }
  else if (newIValue == 10)
    {
      distance = -830;
    }
  Serial.println("Distance: ");
  Serial.print(distance);
  
  turrel.setMaxSpeed(700);
  turrel.setAcceleration(200);
  turrel.moveTo(distance);
  turrel.runToPosition();
  
  Serial.println("Current end position: ");
  pos = turrel.currentPosition();
  Serial.println(pos);
}

void go_number_turrel(){
  int newIValue = I;
  if (Commands.availableValue('I'))
    newIValue = Commands.GetValue('I');
  go_line_pos(newIValue);
}

// --------------------- t2 ---------------------
void zero_homing_turrel(){

  // Start Homing procedure of Stepper Motor at startup

  Serial.print("Stepper is Homing . . . . . . . . . . . ");

  
  turrel.setMaxSpeed(400);
  turrel.setAcceleration(100);

  initial_homing=-1;
  while (digitalRead(turrel_zero_homing)) {  // Make the Stepper move CCW until the switch is activated
    turrel.moveTo(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    turrel.run();
    delay(5);
  }
  
  turrel.setCurrentPosition(0);  // Set the current position as zero for now
  turrel.setMaxSpeed(400);
  turrel.setAcceleration(100);
  
  initial_homing=1;
  while (!digitalRead(turrel_zero_homing)) { // Make the Stepper move CW until the switch is deactivated
    turrel.moveTo(initial_homing);  // Set the position to move to
    turrel.run();
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }

  turrel.setCurrentPosition(0);
  Serial.println("Homing Completed");
  Serial.println("Position: ");
  int pos = turrel.currentPosition();
  Serial.println(pos);
}



// --------------------- no command ---------------------
void test(){
  turrel.setMaxSpeed(200.0);
  turrel.setAcceleration(100.0);
  turrel.moveTo(24);
  if (turrel.distanceToGo() == 0)
  turrel.moveTo(-turrel.currentPosition());
  turrel.run();
}


//Для перемещения удобного()
void go(AccelStepper motor, float steps, float speed_value, float acceleration){
      motor.moveTo(motor.currentPosition()+steps);
      motor.setSpeed(speed_value);
      //motor.setAcceleration(acceleration);
      
      // Implementation without acceleration.
      while (motor.distanceToGo() != 0)
        motor.runSpeedToPosition();
        //motor.run();
}




//
//void test23(){
//  turrel.moveTo(500);
//  turrel (turrel.currentPosition() != 300) // Full speed up to 300
//    turrel.run();
//  turrel.runToNewPosition(0); // Cause an overshoot then back to 0  
//}
