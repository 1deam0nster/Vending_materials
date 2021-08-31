// -----------------Command B1-------------
void get_cap_x()
{
  turel_Z.enable();
  turel_Z.move(6500);  
  //400 - турель Y
  //6500 - турель X
  //9000 - на выдачу
  dropcap_x();
  turel_Z.move(2600);
  turel_Z.disable();
}

// -----------------Command B2-------------
void loud_cap()
{
  open_cofe();
  servo.attach(6);
  servo_r.attach(7);
  //----Открыть клешню
  servo.write(10);
  //----Выровнять
  servo_r.write(65);
  open_cofe();
  gotoLocation(30, 122, 0);
  gotoLocation(130, 122, 0);
  gotoLocation(130, 122, 40);
  servo.write(110);
  gotoLocation(80, 122, 20);
  gotoLocation(67, 40, 0);
  //----Вставляем капсулу в машину
  gotoLocation(67, 40, 65);
  servo.write(85);
  gotoLocation(67, 40, 0);
  delay(1000);
  close_cofe();
}

void get_cupple()
{
  
}
