// Открытие, среднее положение и закрытие большой сервы
void big_servo_open(){
  //----Запуск капсулы
  myservo.attach(7);
  for (pos_cap = 0; pos_cap <= 80; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void big_servo_drop(){
  //----Среднее положение для проверки капсулы
  myservo.attach(7);
  for (pos_cap = 80; pos_cap <= 180; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(35);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}


void big_servo_close(){
  //----Закрытое положение, турель может двигаться
  myservo.attach(7);
  for (pos_cap = 180; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}


// Открытие и закрытие затвора
void open_mini_servo(){
    //----Открыть затвор
  myservo.attach(8);
  for (pos_key = 90; pos_key >= 0; pos_key -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void close_mini_servo(){
  //----Закрыть затвор
  myservo.attach(8);
  for (pos_key = 0; pos_key <= 90; pos_key += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}





// Проверки капсулы
bool ir_cap_check() {
  bool check_1 = false;
  bool check_2 = false;
  bool check_3 = false;
  bool val = false;
  delay(50);
  check_1 = digitalRead(ir_cap);
  delay(100);
  check_2 = digitalRead(ir_cap);
  delay(100);
  check_3 = digitalRead(ir_cap);
  delay(50);
  if (check_1 == true | check_2 == true | check_3 == true) {
    val = true;
    return (val);
  } else {
    val = false;
    return (val);
  }
}

void check_cap(){
  bool capsule_state = ir_cap_check();
  if (capsule_state == true) {
    Serial.println("Turrel capsule_state == true, проблема");
    // можно крутануть турель туда-сюда
    big_servo_close();
    delay(1000);
    Serial.println("Shake turrel");

//    stepper.begin(120, 2);
//    stepper.enable();
//    stepper.rotate(100);
//    stepper.rotate(-100);
//    stepper.rotate(100);
//    stepper.rotate(-100);
//    stepper.rotate(100);
//    stepper.rotate(-100);
//    stepper.begin(120, 1);
//    stepper.disable();
//    delay(1000);
    big_servo_open();
    capsule_state = ir_cap_check();
    if (capsule_state == true) {
      Serial.println("Turrel capsule_state == true, проблема возможно нету капсул");
      Serial.println("Обратное сообщение для разберри");
      // закрываем
      big_servo_close();
      close_mini_servo();
    } else {
      Serial.println("Turrel capsule_state == false, капсула появилась");
      // капсула присутсвует дропаем
      big_servo_drop();
      // закрываем
      big_servo_close();
      close_mini_servo();
    }
  } else {
    Serial.println("Turrel capsule_state == false, капсула присутсвует");
    // капсула присутсвует дропаем
    big_servo_drop();
    // закрываем
    big_servo_close();
    close_mini_servo();
  }
}



// -----------------Command C0-------------
void drop_cap()
{
  //----Открыть затвор
  open_mini_servo();
  delay(500);
  big_servo_open();
  //----Проверка капсулы
  delay(500);
  check_cap();
}




// -----------------Command C1-------------
void check_machine(){
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(2000);
  digitalWrite(16, HIGH);
}

// -----------------Command C2-------------
void start_coffe(){
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  delay(1.5 * 60 * 1000); //sleep some minute
  digitalWrite(17, HIGH);
}
