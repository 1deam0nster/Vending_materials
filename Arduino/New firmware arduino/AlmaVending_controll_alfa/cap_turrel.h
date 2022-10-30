void turrel_rotate(double d)
{
  int deg = d;
  stepper.enable();
  //  stepper_E.move(deg);
  stepper.rotate(deg);
  stepper.disable();
}

void turrelfn()
{
  //    // energize coils - the motor will hold position
  //    stepper.enable();
  //
  //    /*
  //     * Moving motor one full revolution using the degree notation
  //     */
  //    stepper.rotate(6000);
  //
  //    /*
  //     * Moving motor to original position using steps
  //     */
  //    // stepper.move(-MOTOR_STEPS*MICROSTEPS);
  //    // pause and allow the motor to be moved by hand
  //    stepper.disable();
  int newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in E0
    newDValue = Commands.GetValue('D');
  turrel_rotate(newDValue);
}

// -----------------Command T1-------------
//void turrel_home() {
////  check_turrelfn();
//  homing_turrel();
//}

//крутим турель Х до концевика
void homing_turrel()
{
  long initial_homing = -1;
  stepper.enable();
  stepper.move(200);
  delay(10);
  while (!digitalRead(turrel_homing)) {  // Make the Stepper move CCW until the switch is activated
    stepper.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
//  initial_homing = 1;
//  while (!digitalRead(turrel_homing)) { // Make the Stepper move CW until the switch is deactivated
//    stepper.enable();
//    stepper.move(initial_homing);  // Set the position to move to
//    initial_homing--;  // Decrease by 1 for next move if needed
//    delay(5);
//  }
  stepper.disable();// DISABLE MOTOR X
}


////преверка есть ли капсула
//void check_turrelfn()
//{
//  bool capsule_state = ir_cap();
//  if (capsule_state == true) {
//    //---Пишем в серийный порт что нету капсул в турели
//    Serial.println("Turrel capsule - false");
//  } else {
//    Serial.println("Turrel capsule - true");
//  }
//}
