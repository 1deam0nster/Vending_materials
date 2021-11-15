void gotoLocation(double x, double y, double z)
{
  int stepsx = (x - X) * STEPS_MM; // DISTANCE VARIATION X
  int stepsy = (y - Y) * STEPS_MM; // DISTANCE VARIATION Y
  int stepsz = (z - Z) * STEPS_MM; // DISTANCE VARIATION Y

  nav_X.enable();// ENABLE MOTOR X
  nav_Y.enable();
  nav_Z.enable();

  controller.move(stepsx, stepsy, stepsz);//SEND CURRENT STEPS FOR DRIVE

  X = x; // SET LAST POSITION
  Y = y;
  Z = z;

  nav_X.disable();// DISABLE MOTOR Y
  nav_Y.disable();
  nav_Z.disable();
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
