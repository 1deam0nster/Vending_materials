void command_x()
{
  get_cap_x();
  loud_cap();
  get_cupple();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("X1-GOOD");
}

void command_x_a()
{
  get_cap_x();
  loud_cap();
  get_cupple();
  servo_sugar();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("X2-GOOD");
}

void command_x_b()
{
  get_cap_x();
  loud_cap();
  get_cupple();
  servo_cream();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("X3-GOOD");
}

void command_x_a_b()
{
  get_cap_x();
  loud_cap();
  get_cupple();
  servo_cream();
  servo_sugar();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("X4-GOOD");
}
//------------------Command for y ---------
void command_y()
{
  get_cap_y();
  loud_cap();
  get_cupple();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("Y1-GOOD");
}

void command_y_a()
{
  get_cap_y();
  loud_cap();
  get_cupple();
  servo_sugar();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("Y2-GOOD");
}

void command_y_b()
{
  get_cap_y();
  loud_cap();
  get_cupple();
  servo_cream();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("Y3-GOOD");
}

void command_y_a_b()
{
  get_cap_y();
  loud_cap();
  get_cupple();
  servo_cream();
  servo_sugar();
  delay(70000);
  //  check_rotation();
  to_client();
  Serial.println("Y4-GOOD");
}

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
}

// -----------------Command B3-------------
void loud_cap()
{
  open_cofe();
  delay(500);
  servo.attach(6);
  servo_r.attach(7);
  //----Открыть клешню
  servo.write(0);
  //----Выровнять
  servo_r.write(65);
  delay(50);
  open_cofe();
  delay(500);
  gotoLocation(70, 120, 0);
  gotoLocation(133, 120, 0);
  gotoLocation(133, 120, 30);
  servo.write(110);
  delay(200);
  gotoLocation(103, 120, 30);
  servo.write(112);
  //  gotoLocation(95, 122, 10);
  gotoLocation(95, 120, 10);
  delay(500);
  gotoLocation(95, 120, 0);
  gotoLocation(67, 40, 0);
  //  servo_r.write(70);
  //----Вставляем капсулу в машину
  //  servo_r.write(65);
  gotoLocation(67, 40, 70);
  delay(200);
  servo.write(80);
  gotoLocation(67, 40, 0);
  close_cofe();//подольше сделать
  delay(3000);
}

// -----------------Command B4-------------
void get_cupple()
{
  servo_r.write(70);
  gotoLocation(14, 4, 0);
  gotoLocation(14, 4, 67);
  delay(500);
  start_cofe();
  delay(10);
  servo.write(90);
  cup();
  //delay(00);
  servo.write(90);
  gotoLocation(14, 30, 60);
  servo.write(100);
  gotoLocation(14, 30, 0);
  gotoLocation(14, 100, 24);
  gotoLocation(65, 100, 24);
  //  gotoLocation(65, 100, 30);
  //  delay(3000);
}

// -----------------Command B5-------------
void to_client()
{
  gotoLocation(40, 90, 0);
  //  rotate_cup_to();
  int pos;
  //  for (pos = 65; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
  //    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15);                       // waits 15ms for the servo to reach the position
  //  }
  for (pos = 65; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  gotoLocation(70, 90, 0);
  gotoLocation(70, 110, 0);
  delay(300);
  servo.write(60);
  delay(500);
  gotoLocation(0, 110, 0);

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

  //  for (pos = 180; pos >= 65; pos -= 1) { // goes from 180 degrees to 0 degrees
  //    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15);                       // waits 15ms for the servo to reach the position
  //  }
  for (pos = 0; pos <= 65; pos += 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  gotoLocation(0, 0, 0);

  homing();
  servo.detach();
  servo_r.detach();
  open_cofe();
  delay(3500);
  close_cofe();
}

// -----------------Command B6-------------
void test()
{
  Serial1.print("1");
  Serial.println("test");
  if (Serial1.available()) {
//    int a = Serial1.read();
//    Serial.println(a);

    incomingByte = Serial1.read(); // read the incoming byte:

    Serial.print(" I received:");

    Serial.println(incomingByte);
  }
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

void check_rotation()
{

  int buttonState = digitalRead(rotationButton);
  Serial.print("Button state = ");
  Serial.println(buttonState);

  while (buttonState == 0) {
    Serial.println(buttonState);
    buttonState = digitalRead(rotationButton);
    delay(1000);
    if (buttonState == 1) {
      delay(500);
      buttonState = digitalRead(rotationButton);
      if (buttonState == 1) {
        Serial.print("Слава яйцам, а то я аж прихуел немного ");
        break;
      }
    }
  }

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
