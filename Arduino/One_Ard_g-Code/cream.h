
// -----------------Command M0-------------
void milk_stepper() {

  if (milk_stepper >= 0 and milk_stepper < 6  ) {
    milk_stepper += 1;
    //  EEPROM.put(0, milk_stepper_1);
    stepper_M0.enable();
    stepper_M0.move(-3600);
    stepper_M0.disable();

    EEPROM.put(0, milk_stepper);

    // -----------------Print Variable-------------
    Serial.print("Milk stepper = ");
    Serial.print(milk_stepper);
    Serial.println(" ");
  }


  
  if (milk_stepper > 6 and milk_stepper < 12  ) {
    milk_stepper += 1;
    //  EEPROM.put(0, milk_stepper);
    stepper_M1.enable();
    stepper_M1.move(-3600);
    stepper_M1.disable();

    EEPROM.put(0, milk_stepper);

    // -----------------Print Variable-------------
    Serial.print("Milk stepper = ");
    Serial.print(milk_stepper);
    Serial.println(" ");
  }

  if (milk_stepper > 12 and milk_stepper < 18  ) {
    milk_stepper += 1;
    //  EEPROM.put(0, milk_stepper);
    stepper_M2.enable();
    stepper_M2.move(-3600);
    stepper_M2.disable();

    EEPROM.put(0, milk_stepper_1);

    // -----------------Print Variable-------------
    Serial.print("Milk stepper = ");
    Serial.print(milk_stepper);
    Serial.println(" ");
  }

  if (milk_stepper == 18 ) {
    // -----------------Print Variable-------------
    Serial.print("Milk stepper = empty");
    Serial.println(" ");
  }
  
  if (milk_stepper == 6 || milk_stepper == 12) {
    milk_stepper += 1;
  }


}
// -----------------Command M1-------------
void milk_stepper_reset() {

  int init_stepper = 0;
  EEPROM.put(0, init_stepper);
  delay(5);
  EEPROM.get(0, milk_stepper);
  delay(5);

  // -----------------Print Variable-------------
  Serial.print("Milk stepper = ");
  Serial.print(milk_stepper);
  Serial.println(" ");
}
