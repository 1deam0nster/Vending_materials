//bool ir_cap_check() {
//  bool check_1 = false;
//  bool check_2 = false;
//  bool check_3 = false;
//  bool val = false;
//  delay(50);
//  check_1 = digitalRead(ir_cap);
//  delay(100);
//  check_2 = digitalRead(ir_cap);
//  delay(100);
//  check_3 = digitalRead(ir_cap);
//  delay(50);
//  if (check_1 == true | check_2 == true | check_3 == true) {
//    val = true;
//    return (val);
//  } else {
//    val = false;
//    return (val);
//  }
//}
//
//void check_cap() {
//  bool capsule_state = ir_cap_check();
//  if (capsule_state == true) {
//    Serial.println("Turrel capsule_state == true, проблема");
//    // можно крутануть турель туда-сюда
//    big_servo_close();
//    delay(1000);
//    big_servo_open();
//    capsule_state = ir_cap_check();
//    if (capsule_state == true) {
//      //      Serial.println("Turrel capsule_state == true, проблема возможно нету капсул");
//      Serial.println(F("Cap state false"));
//      // закрываем
//      big_servo_close();
//      close_mini_servo();
//    } else {
//      Serial.println(F("Cap state true"));
//      // капсула присутсвует дропаем
//      big_servo_drop();
//      // закрываем
//      big_servo_close();
//      close_mini_servo();
//    }
//  } else {
//    Serial.println("Turrel capsule_state == false, капсула присутсвует");
//    Serial.println(F("Cap state true"));
//    // капсула присутсвует дропаем
//    big_servo_drop();
//    // закрываем
//    big_servo_close();
//    close_mini_servo();
//  }
//}


void cap_check(){
//    return digitalRead(ir_cream);
  bool check = digitalRead(ir_cap);
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
        case 3: Serial.println("ALL FALSE");  cream_check_value = 0; break;
      }
  }
}

// Открытие и закрытие затвора
void open_mini_servo(){
    //----Открыть затвор
  myservo.attach(turrel_cap_servo_mini);
  for (pos_key = 90; pos_key >= 0; pos_key -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void close_mini_servo(){
  //----Закрыть затвор
  myservo.attach(turrel_cap_servo_mini);
  for (pos_key = 0; pos_key <= 90; pos_key += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}


// -----------------Command C0-------------
void drop_cap()
{
  //приподнимаем капсулы 
  for (big_pos_cap = 1800; big_pos_cap <= 2500; big_pos_cap += 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(5);                       
  }

  //открывваем мини серву
  open_mini_servo();
  
  //положение для загрузки капсулы
  for (big_pos_cap = 2500; big_pos_cap >= 1800; big_pos_cap -= 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(5);                       
  }
  
  //забираем капсулу и идем в позицию проверки
  for (big_pos_cap = 1800; big_pos_cap >= 1200; big_pos_cap -= 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(10);                       
  }

  //код для проверки капсулы
  
  
  //сброс капсулы
  for (big_pos_cap = 1200; big_pos_cap >= 500; big_pos_cap -= 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(5);                       
  }
  
  //возврат в обычное положение
  for (big_pos_cap = 500; big_pos_cap <= 2500; big_pos_cap += 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(2);                       
  }
  
  close_mini_servo();

  //положение для прокручивания турели и загрузки капсулы
  for (big_pos_cap = 2500; big_pos_cap >= 1800; big_pos_cap -= 1) {
    cap_drop.writeMicroseconds(big_pos_cap);              
    delay(5);                       
  }

}




// -----------------Command C1-------------
void check_machine() {
  pinMode(cofe_machine_check_button_pin, OUTPUT);
  digitalWrite(cofe_machine_check_button_pin, LOW);
  delay(2000);
  digitalWrite(cofe_machine_check_button_pin, HIGH);
  Serial.println(F("Check machine true"));
  void display_print();
}

// -----------------Command C2-------------
void start_coffe() {
  pinMode(coffe_machine_start_pin, OUTPUT);
  digitalWrite(coffe_machine_start_pin, LOW);
  //delay(1.5 * 60 * 1000); //sleep some minute
  delay(10000);
  do {
    // 1 - можно загружать
    // 0 - наливает кофе
    machine_sensor = digitalRead(cofe_machine_ir);
    Serial.println("Сенсор == 1");
    digitalWrite(coffe_machine_start_pin, LOW);
  } while (machine_sensor == 1);
  delay(7000);
  digitalWrite(coffe_machine_start_pin, HIGH);
  Serial.println(F("End coffe works"));
}
// -----------------Command C4-------------
void choco_check() {
  if (digitalRead(choco_ir_control) == 0) {
    Serial.println("Choco OK");
  } else {
    Serial.println("Choco False");
  }
}

// -----------------Command C5-------------
void sugar_check() {
  if (digitalRead(sugar_ir_control) == 0) {
    Serial.println("Sugar OK");
  } else {
    Serial.println("Sugar False");
  } 
}

// -----------------Command P0-------------
void sugar_command() {
  sugar.attach(sugar_servo);
  delay(1000);
  sugar.write(80);
  delay(1000);
  sugar.write(180);
  delay(1000);
  sugar.write(80);
  sugar.detach();
}
// -----------------Command P1-------------
void chocolate_command() {
  chocolate.attach(choco_servo);
  delay(100);
  chocolate.write(180);
  delay(1000);
  chocolate.write(70);
  delay(1000);
  chocolate.write(180);
  chocolate.detach();
}
