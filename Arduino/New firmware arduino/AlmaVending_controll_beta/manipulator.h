// -----------------Command F0-------------
void go_man_stepper(double d, double s, double a) {
  int dist = d;
  int accel = a;
  int spd = s;
//  turrel.disableOutputs();
  manipul.setMaxSpeed(spd);
  manipul.setAcceleration(accel);
  manipul.moveTo(dist);
  manipul.runToPosition();
//  turrel.enableOutputs();
}

void go_to_pos_man(){
  int newDValue = D;
  int newSValue = S;
  int newAValue = A;
  if (Commands.availableValue('D'))
    newDValue = Commands.GetValue('D');
  if (Commands.availableValue('S'))
    newSValue = Commands.GetValue('S');
  if (Commands.availableValue('A'))
    newAValue = Commands.GetValue('A');
  go_man_stepper(newDValue, newSValue, newAValue);
}

// -----------------Command F1-------------
void up_man(){
}
// -----------------Command F2-------------
void servo_man(){
}
// -----------------Command F3-------------
void to_win_man(){
}
// -----------------Command F4-------------
void to_machine_man(){
}
