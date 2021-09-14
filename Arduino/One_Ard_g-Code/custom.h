// -----------------Command B1-------------
void get_cap_x()
{
  //check_turrelfn();
  turel_Z.enable();
  turel_Z.move(6530);
  //400 - турель Y
  //6500 - турель X
  //9000 - на выдачу
  dropcap_x();
  turel_Z.move(2670);
  turel_Z.disable();
  Serial.println("B1-GOOD");
}

void get_cap_y()
{
  //check_turrelfn2();
  turel_Z.enable();
  turel_Z.move(400);
  //400 - турель Y
  //6500 - турель X
  //9000 - на выдачу
  dropcap_y();
  turel_Z.move(8790);
  turel_Z.disable();
  Serial.println("B2-GOOD");
}

// -----------------Command B3-------------
void loud_cap()
{
  open_cofe();
  delay(500);
  servo.attach(6);
  servo_r.attach(7);
  //----Открыть клешню
  servo.write(10);
  //----Выровнять
  servo_r.write(65);
  delay(50);
  open_cofe();
  delay(500);
  gotoLocation(30, 122, 0);
  gotoLocation(130, 122, 0);
  gotoLocation(130, 122, 25);
  servo.write(110);
  delay(200);
  gotoLocation(97, 122, 25);
  //  gotoLocation(95, 122, 10);
  gotoLocation(97, 122, 20);
  delay(500);
  gotoLocation(67, 40, 0);
  //----Вставляем капсулу в машину
  gotoLocation(67, 40, 70);
  delay(200);
  servo.write(85);
  gotoLocation(67, 40, 0);
  close_cofe();//подольше сделать
  Serial.println("B3-GOOD");
}

// -----------------Command B4-------------
void get_cupple()
{
  gotoLocation(10, 4, 0);
  gotoLocation(10, 4, 67);
  servo.write(76);
  cup();
  //delay(00);
  servo.write(100);
  gotoLocation(10, 23, 67);
  gotoLocation(10, 23, 0);
  gotoLocation(10, 95, 24);
  gotoLocation(65, 95, 24);
  gotoLocation(65, 95, 30);
  //  delay(3000);
  Serial.println("B4-GOOD");
}

// -----------------Command B5-------------
void to_client()
{
  gotoLocation(40, 95, 0);
  //  rotate_cup_to();
  int pos;
  for (pos = 65; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  gotoLocation(70, 90, 0);
  gotoLocation(70, 120, 0);
  delay(300);
  servo.write(30);
  gotoLocation(0, 120, 0);

  cup_table = digitalRead(ir_cup);
  if (cup_table == HIGH) {
    stepper_E.enable();
    stepper_E.move(33000);
  }
  cup_table = digitalRead(ir_cup);
  do {
    cup_table = digitalRead(ir_cup);
    //Serial.println("Есть стаканчик");
  } while (cup_table == LOW);
  delay(7000);
  stepper_E.move(-33000);
  stepper_E.disable();

  for (pos = 180; pos >= 65; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  gotoLocation(0, 0, 0);
  
  homing();
  servo.detach();
  servo_r.detach();
  Serial.println("B5-GOOD");
}

// -----------------Command B6-------------
void test()
{
  //  stepper_E.enable();
  //  stepper_E.move(33000);
  //  delay(3000);
  //  stepper_E.move(-33000);
  //  stepper_E.disable();
  start_cofe();
  if (tmr.tick())
    start_cofe();
  delay(15000);
}

// -----------------Command T3-------------
void table()
{
  cup_table = digitalRead(ir_cup);
  if (cup_table == HIGH) {
    stepper_E.enable();
    stepper_E.move(33000);
  }
  cup_table = digitalRead(ir_cup);
  do {
    cup_table = digitalRead(ir_cup);
//    Serial.println("Есть стаканчик");
  } while (cup_table == LOW);
  delay(7000);
  stepper_E.move(-33000);
  stepper_E.disable();
  
}

// -----------------Command M0-------------
void m6()
{
  stepper_M1.enable();
  stepper_M1.move(-3610);
  stepper_M1.disable();
  delay(100);
}

void m7()
{
  stepper_M2.enable();
  stepper_M2.move(-3610);
  stepper_M2.disable();
  delay(100);
}



//Команды
//g1
//b1
//b3
//b4
//b6
//b5
//m0
//S0 n2 D90
//S0 n2 D180


//1.20 ждать после того как стакан приехал
//0.25 начало
//0.28 вкл б4
//0.45 приехал стакан
//1.57 выкл
