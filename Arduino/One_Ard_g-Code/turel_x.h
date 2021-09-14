// -----------------Command T1-------------
void rotate_tower() {
  check_turrelfn();
}

//крутим турель Х до концевика
void homing_turrel()
{
  long initial_homing = -1;
  turel_X.enable();
  turel_X.move(200);
  delay(1000);
  while (digitalRead(turrel_switch_x)) {  // Make the Stepper move CCW until the switch is activated
    turel_X.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  initial_homing = 1;
  while (!digitalRead(turrel_switch_x)) { // Make the Stepper move CW until the switch is deactivated
    turel_X.enable();
    turel_X.move(turrel_switch_x);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
  //  stepperX.move(-200);
  turel_X.disable();// DISABLE MOTOR X
}

//тройная проверка инфракрасного датчика на турели X
bool ir_cap_check_x() {
  bool check_1 = false;
  bool check_2 = false;
  bool check_3 = false;
  bool check_4 = false;
  bool check_5 = false;
  bool val = false;
  delay(50);
  check_1 = digitalRead(ir_cap_x);
  delay(100);
  check_2 = digitalRead(ir_cap_x);
  delay(100);
  check_3 = digitalRead(ir_cap_x);
  delay(100);
  check_4 = digitalRead(ir_cap_x);
  delay(100);
  check_5 = digitalRead(ir_cap_x);
  delay(50);
  if (check_1 == true | check_2 == true | check_3 == true | check_4 == true | check_5 == true) {
    val = true;
    return (val);
  } else {
    val = false;
    return (val);
  }
}



//преверка есть ли капсула, крутим турель Х
void check_turrelfn()
{
  bool capsule_state = ir_cap_check_x();

  //---------- 1 проверка-----------
  if (capsule_state == true) {
    //----Открываем вехнюю серву
    servo.attach(8);
    servo.write(0);

    //----Запуск поиска нуля
    homing_turrel();

    //----Закрываем верхнюю серву
    servo.write(50);
    delay(1000);
    servo.detach();
    delay(1000);

    capsule_state = ir_cap_check_x();
    //----Если приехала пустая ячейка, запускаем еще раз
    //---------- 2 проверка-----------
    if (capsule_state == true) {
      //----Открываем вехнюю серву
      servo.attach(8);
      servo.write(0);

      //----Запуск поиска нуля
      homing_turrel();

      //----Закрываем верхнюю серву
      servo.write(50);
      delay(1000);
      servo.detach();
    }

    capsule_state = ir_cap_check_x();
    //----Если приехала пустая ячейка, пишем что пустая турель
    //---------- 3 проверка-----------
    if (capsule_state == true) {
      //---Пишем в серийный порт что нету капсул в турели
      Serial.println("Turrel X capsule - false");
    }

  } else {
    Serial.println("Turrel X capsule - true");
  }
}

//--Проверка второй турели
void check_servo_x() {
  //----Проверка на нижнюю серву
  servo.attach(9);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка на верхнюю серву
  servo.attach(8);
  servo.write(0);
  delay(500);
  servo.write(50);
  delay(1000);
  servo.detach();
}

// -----------------Command C1-------------
void dropcap_x()
{
  //----закрыть нижнюю
  servo.attach(9);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----открыть верх
  servo.attach(8);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка капсул в башне
  //check_turrelfn();               -----Из за висяка МК отдельная команда C1
}
