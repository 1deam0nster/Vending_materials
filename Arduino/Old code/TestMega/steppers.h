// -----------------Command E0-------------
void steppere_degreed(double d)
{
  int deg = d;
  stepper_E.enable();
  stepper_E.move(deg);
  stepper_E.disable();
}

void stepper_e0()
{
  int newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in E0
    newDValue = Commands.GetValue('D');
  steppere_degreed(newDValue);
  //  stepper_E.enable();
  //  stepper_E.move(1000);
  //  stepper_E.disable();
}

// -----------------Command E1-------------
void steppere1_degreed(double d)
{
  int deg = d;
  turel_Z.enable();
  turel_Z.move(deg);
  turel_Z.disable();
}

void stepper_e1()
{
  int newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in E0
    newDValue = Commands.GetValue('D');
  steppere1_degreed(newDValue);
  //  stepper_E.enable();
  //  stepper_E.move(1000);
  //  stepper_E.disable();
}
