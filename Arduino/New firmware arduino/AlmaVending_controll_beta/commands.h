void big_servo_prepare(){
  //----Запуск капсулы
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 75; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void big_servo_default(){
  //----Запуск капсулы
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 0; pos_cap <= 75; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void big_servo_drop2(){
  //----Запуск капсулы
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 75; pos_cap <= 179; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void big_servo_home(){
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 179; pos_cap >= 75; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

// Открытие, среднее положение и закрытие большой сервы
void big_servo_open(){
  //----Запуск капсулы
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 0; pos_cap <= 80; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void big_servo_drop(){
  //----Среднее положение для проверки капсулы
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 80; pos_cap <= 180; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(35);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}


void big_servo_close(){
  //----Закрытое положение, турель может двигаться
  myservo.attach(turrel_cap_servo);
  for (pos_cap = 180; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
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


//void drop_cap() {
//
//  int pos_cap = 0;
//  int pos_key = 180;
//  #define TIMER 500
//  uint32_t tmr1;
//
//  myservo.attach(turrel_cap_servo);
//  for (pos_cap = 75; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//    delay(30);                       // waits 15ms for the servo to reach the position
//  }
//  myservo.detach();
//
//  myservo.attach(turrel_cap_servo_mini);
//  for (pos_key = 90; pos_key >= 0; pos_key -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
//    delay(5);                       // waits 15ms for the servo to reach the position
//  }
//  myservo.detach();
//  myservo.attach(turrel_cap_servo);
//
//  if (millis() - tmr1 >= TIMER) {  // ищем разницу
//    tmr1 = millis();                   // сброс таймера
//    for (pos_cap = 0; pos_cap <= 75; pos_cap += 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//      delay(30);                       // waits 15ms for the servo to reach the position
//    }
//  }
//
//  if (millis() - tmr1 >= TIMER) {  // ищем разницу
//    tmr1 = millis();                   // сброс таймера
//    for (pos_cap = 75; pos_cap <= 179; pos_cap += 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//      delay(30);                       // waits 15ms for the servo to reach the position
//    }
//  }
//
//  if (millis() - tmr1 >= TIMER) {  // ищем разницу
//    tmr1 = millis();                   // сброс таймера
//    for (pos_cap = 179; pos_cap >= 75; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//      delay(20);                       // waits 15ms for the servo to reach the position
//    }
//
//    for (pos_cap = 75; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//      delay(30);                       // waits 15ms for the servo to reach the position
//    }
//  }
//
//  if (millis() - tmr1 >= TIMER) {  // ищем разницу
//    tmr1 = millis();                   // сброс таймера
//    myservo.detach();
//
//    myservo.attach(turrel_cap_servo_mini);
//    for (pos_key = 0; pos_key <= 90; pos_key += 1) { // goes from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
//      delay(15);                       // waits 15ms for the servo to reach the position
//    }
//    myservo.detach();
//
//    myservo.attach(turrel_cap_servo);
//    for (pos_cap = 0; pos_cap <= 75; pos_cap += 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
//      delay(30);                       // waits 15ms for the servo to reach the position
//    }
//    myservo.detach();
//  }
//
//}




//// Проверки капсулы
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
//    //    Serial.println("Turrel capsule_state == true, проблема");
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
//    //    Serial.println("Turrel capsule_state == false, капсула присутсвует");
//    Serial.println(F("Cap state true"));
//    // капсула присутсвует дропаем
//    big_servo_drop();
//    // закрываем
//    big_servo_close();
//    close_mini_servo();
//  }
//}



// -----------------Command C0-------------
void drop_cap()
{
  big_servo_prepare();
  open_mini_servo();
  delay(500);
  big_servo_default();
  delay(500);
  big_servo_drop2();
  delay(500);
  big_servo_home();
  big_servo_prepare();
  delay(500);
  close_mini_servo();
  big_servo_default();
}




// -----------------Command C1-------------
void check_machine() {
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(2000);
  digitalWrite(16, HIGH);
  Serial.println(F("Check machine true"));
  void display_print();
}

// -----------------Command C2-------------
void start_coffe() {
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  delay(1.5 * 60 * 1000); //sleep some minute
  digitalWrite(17, HIGH);
  Serial.println(F("Start coffee true"));
}
