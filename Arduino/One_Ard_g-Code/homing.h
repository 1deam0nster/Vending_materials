void homing()
{
  long initial_homing = -1;

  // Start Homing procedure of Stepper Motor at startup
  //Serial.print("StepperZ is Homing . . . . . . . . . . . ");
  while (digitalRead(stop_z)) {  // Make the Stepper move CCW until the switch is activated
    nav_Z.enable();
    nav_Z.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
  }

  initial_homing = 1;
  while (!digitalRead(stop_z)) { // Make the Stepper move CW until the switch is deactivated
    nav_Z.enable();
    nav_Z.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
  }

  nav_Z.disable();// DISABLE MOTOR Z
  
  delay(1000);
  // Start Homing procedure of Stepper Motor at startup
  //Serial.print("StepperX is Homing . . . . . . . . . . . ");

  while (digitalRead(stop_x)) {  // Make the Stepper move CCW until the switch is activated
    nav_X.enable();
    nav_X.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
  }

  initial_homing = 1;
  while (!digitalRead(stop_x)) { // Make the Stepper move CW until the switch is deactivated
    nav_X.enable();
    nav_X.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
  }

  nav_X.disable();// DISABLE MOTOR X
  delay(1000);
  //------------------------------

  // Start Homing procedure of Stepper Motor at startup
  //Serial.print("StepperY is Homing . . . . . . . . . . . ");
  while (digitalRead(stop_y)) {  // Make the Stepper move CCW until the switch is activated
    nav_Y.enable();
    nav_Y.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
  }

  initial_homing = 1;
  while (!digitalRead(stop_y)) { // Make the Stepper move CW until the switch is deactivated
    nav_Y.enable();
    nav_Y.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
  }

  nav_Y.disable();// DISABLE MOTOR Y






  initial_homing = -1;
  //Serial.print("StepperZ is Homing");
  while (digitalRead(home_switch_z)) {  // Make the Stepper move CCW until the switch is activated
    turel_Z.enable();
    turel_Z.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
  }

  initial_homing = 1;
  while (!digitalRead(home_switch_z)) { // Make the Stepper move CW until the switch is deactivated
    turel_Z.enable();
    turel_Z.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
  }
  //Serial.println("");
  //Serial.println("Z homing OK");
  turel_Z.disable();// DISABLE MOTOR X


  initial_homing = -1;
  //Serial.print("StepperE is Homing");
  while (digitalRead(home_switch_e)) {  // Make the Stepper move CCW until the switch is activated
    stepper_E.enable();
    stepper_E.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
  }

  initial_homing = 1;
  while (!digitalRead(home_switch_e)) { // Make the Stepper move CW until the switch is deactivated
    stepper_E.enable();
    stepper_E.move(initial_homing);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
  }

  //Serial.println("");
  //Serial.println("E homing OK");
  stepper_E.disable();
  Serial.println("G1_OK");
}
