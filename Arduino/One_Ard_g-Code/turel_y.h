// -----------------Command T2-------------
void rotate_tower2() {
  check_turrelfn2();
}

//крутим турель Х до концевика
void homing_turrel2()
{
  long initial_homing = -1;
  turel_Y.enable();
  turel_Y.move(200);
  delay(1000);
  while (digitalRead(turrel_switch_y)) {  // Make the Stepper move CCW until the switch is activated
    turel_Y.move(initial_homing);  // Set the position to move to
    initial_homing++;  // Decrease by 1 for next move if needed
    delay(5);
  }
  initial_homing = 1;
  while (!digitalRead(turrel_switch_y)) { // Make the Stepper move CW until the switch is deactivated
    turel_Y.enable();
    turel_Y.move(turrel_switch_y);  // Set the position to move to
    initial_homing--;  // Decrease by 1 for next move if needed
    delay(5);
  }
//  stepperY.move(-200);
  turel_Y.disable();// DISABLE MOTOR Y
}



//преверка есть ли капсула, крутим турель Y
void check_turrelfn2()
{
  int capsule_state = digitalRead(ir_cap_y);

  //---------- 1 проверка-----------
  if (capsule_state == true) {
    //----Открываем вехнюю серву
    servo.attach(10);
    servo.write(0);

    //----Запуск поиска нуля
    homing_turrel2();

    //----Закрываем верхнюю серву
    servo.write(50);
    delay(1000);
    servo.detach();
    delay(1000);

    capsule_state = digitalRead(ir_cap_y);
    //----Если приехала пустая ячейка, запускаем еще раз
    //---------- 2 проверка-----------
    if (capsule_state == true) {
      //----Открываем вехнюю серву
      servo.attach(10);
      servo.write(0);

      //----Запуск поиска нуля
      homing_turrel2();

      //----Закрываем верхнюю серву
      servo.write(50);
      delay(1000);
      servo.detach();
    }

    capsule_state = digitalRead(ir_cap_y);
    //----Если приехала пустая ячейка, пишем что пустая турель
    //---------- 3 проверка-----------
    if (capsule_state == true) {
      //---Пишем в серийный порт что нету капсул в турели
      Serial.println("Turrel Y capsule - false");
    }

  } else {
    Serial.println("Turrel Y capsule - true");
  }
}

//--Проверка второй турели
void check_servo_y() {
  //----Проверка на нижнюю серву
  servo.attach(11);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка на верхнюю серву
  servo.attach(10);
  servo.write(0);
  delay(500);
  servo.write(50);
  delay(1000);
  servo.detach();
}

// -----------------Command C1-------------
void dropcap_y()
{
  //----закрыть нижнюю
  servo.attach(11);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----открыть верх
  servo.attach(10);
  servo.write(0);
  delay(1000);
  servo.write(50);
  delay(1000);
  servo.detach();

  //----Проверка капсул в башне
  //check_turrelfn();               -----Из за висяка МК отдельная команда C1
}
