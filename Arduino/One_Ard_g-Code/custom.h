// -----------------Command B1-------------
void get_cap_x()
{ 
  check_turrelfn();
  turel_Z.enable();
  turel_Z.move(6500);  
  //400 - турель Y
  //6500 - турель X
  //9000 - на выдачу
  dropcap_x();
  turel_Z.move(2670);
  turel_Z.disable();
}

void get_cap_y()
{ 
  check_turrelfn2();
  turel_Z.enable();
  turel_Z.move(400);  
  //400 - турель Y
  //6500 - турель X
  //9000 - на выдачу
  dropcap_y();
  turel_Z.move(8770);
  turel_Z.disable();
}

// -----------------Command B2-------------
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
  gotoLocation(130, 122, 45);
  servo.write(110);
  delay(200);
//  gotoLocation(95, 122, 10);
  gotoLocation(95, 122, 20);
  gotoLocation(67, 40, 0);
  //----Вставляем капсулу в машину
  gotoLocation(67, 40, 65);
  servo.write(85);
  gotoLocation(67, 40, 0);
  close_cofe();//подольше сделать
}

void get_cupple()
{
  gotoLocation(12, 2, 65);
  cup();
  gotoLocation(12, 95, 24);
  gotoLocation(65, 95, 24);
  delay(3000);   
}

void to_client()
{
  gotoLocation(40, 95, 0);
//  rotate_cup_to();
  int pos;
  for (pos = 65; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  gotoLocation(70, 110, 0);
  servo.write(30);
  gotoLocation(0, 110, 0);
  steppere_degreed(25000);
  delay(3000);
  steppere_degreed(-25000);
//  rotate_cup_back();
  for (pos = 180; pos >= 65; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_r.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  homing();
}
