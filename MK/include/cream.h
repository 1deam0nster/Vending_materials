//
//// -----------------Command M4-------------
//void milk_stepper_cmd() {
//
//  if (milk_stepper >= 0 and milk_stepper < 8  ) {
//    milk_stepper += 1;
//    //  EEPROM.put(0, milk_stepper_1);
//    stepper_M0.enable();
//    stepper_M0.move(-3610);
//    stepper_M0.disable();
//
//    EEPROM.put(0, milk_stepper);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper = ");
//    Serial.print(milk_stepper);
//    Serial.println(" ");
//    
//  }
//
//  if (milk_stepper > 9 and milk_stepper < 16  ) {
//    milk_stepper += 1;
//    //  EEPROM.put(0, milk_stepper);
//    stepper_M1.enable();
//    stepper_M1.move(-3610);
//    stepper_M1.disable();
//
//    EEPROM.put(0, milk_stepper);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper = ");
//    Serial.print(milk_stepper);
//    Serial.println(" ");
//  }
//
//  if (milk_stepper >= 16 and milk_stepper < 24  ) {
//    milk_stepper += 1;
//    //  EEPROM.put(0, milk_stepper);
//    stepper_M2.enable();
//    stepper_M2.move(-3600);
//    stepper_M2.disable();
//
//    EEPROM.put(0, milk_stepper);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper = ");
//    Serial.print(milk_stepper);
//    Serial.println(" ");
//  }
//
//  if (milk_stepper == 24 ) {
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper = empty");
//    Serial.println(" ");
//  }
//  
//  if (milk_stepper == 8 || milk_stepper == 16 ) {
//    milk_stepper += 1;
//  }
//
//
//}





// -----------------Command M0-------------
void milk_stepper_cmd() {

//  if (milk_stepper_1 >= 0 and milk_stepper_1 < 9  ) {
//    milk_stepper_1 += 1;
//    //  EEPROM.put(0, milk_stepper_1);
//    stepper_M0.enable();
//    stepper_M0.move(-3610);
//    stepper_M0.disable();
//
//    EEPROM.put(0, milk_stepper_1);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper_1 = ");
//    Serial.print(milk_stepper_1);
//    Serial.println(" ");
//    
//  }
//
//  if (milk_stepper_2 >= 0 and milk_stepper_2 < 9 and milk_stepper_1 == 10 ) {
//    milk_stepper_2 += 1;
//    //  EEPROM.put(0, milk_stepper);
//    stepper_M1.enable();
//    stepper_M1.move(-1805);
//    stepper_M1.disable();
//
//    EEPROM.put(0, milk_stepper_2);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper_2 = ");
//    Serial.print(milk_stepper_2);
//    Serial.println(" ");
//  }
//
//
//  if (milk_stepper_3 >= 0 and milk_stepper_3 < 9 and milk_stepper_1 == 10 and milk_stepper_2 == 10  ) {
//    milk_stepper_3 += 1;
//    //  EEPROM.put(0, milk_stepper);
//    stepper_M2.enable();
//    stepper_M2.move(1805);
//    stepper_M2.disable();
//
//    EEPROM.put(0, milk_stepper_3);
//
//    // -----------------Print Variable-------------
//    Serial.print("Milk stepper_3 = ");
//    Serial.print(milk_stepper_3);
//    Serial.println(" ");
//  }
//
//  if (milk_stepper_3 == 9) {
//    milk_stepper_3 += 1;
//  }
//
//  if (milk_stepper_1 == 9) {
//    milk_stepper_1 += 1;
//  }
//
//  if (milk_stepper_2 == 9 ) {
//    milk_stepper_2 += 1;
//  }
//  if (milk_stepper_3 == 10 or milk_stepper_1 == 10 or milk_stepper_2 == 10 ) {
//    // -----------------Print Variable-------------
////    Serial.print("Milk steppers = empty");
////    Serial.println(" ");
//  }
  
  
//  if (milk_stepper == 8 || milk_stepper == 16 ) {
//    milk_stepper += 1;
//  }


}
// -----------------Command M1-------------
void milk_stepper_reset_cmd() {

//  int init_stepper_1 = 0;
//  int init_stepper_2 = 0;
//  int init_stepper_3 = 0;
//  EEPROM.put(0, init_stepper_1);
//  delay(5);
//  EEPROM.get(0, milk_stepper_1);
//  delay(5);
//  EEPROM.put(0, init_stepper_2);
//  delay(5);
//  EEPROM.get(0, milk_stepper_2);
//  delay(5);
//  EEPROM.put(0, init_stepper_3);
//  delay(5);
//  EEPROM.get(0, milk_stepper_3);
//  delay(5);
//
//  // -----------------Print Variable-------------
//  Serial.print("Milk steppers reset");
}
