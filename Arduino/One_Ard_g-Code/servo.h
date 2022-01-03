// -----------------Command S0-------------
void servo_degrid(double n, double d)
{
  int serv_number = n;
  int deg = d;
  //-----Подключаем сервоприводы
  servo.attach(serv_number);

  //----Открыть клешню
  servo.write(deg);
  delay(1000);

  //-----Отключаем сервоприводы
  servo.detach();
  //Commands.comment("D:" + String(d)); // DEBUG SERIAL

}

void servofn() {

  double newNValue = N;
  if (Commands.availableValue('N')) // ADDED parameter D in S0
    newNValue = Commands.GetValue('N');

  double newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in S0
    newDValue = Commands.GetValue('D');

  servo_degrid(newNValue, newDValue);
}

void servo_sugar(){
  servo_sug.attach(12);
  delay(300);
  servo_sug.write(70);
  delay(1000);
  servo_sug.write(165);
//  delay(1000)
//  servo.write(180);
  delay(1000);
  servo_sug.detach();
  Serial.println("S3-GOOD");
}

void servo_cream(){
  //открываем верхнюю серву
  servo_cr.attach(A8);
  delay(300);
//  servo_cr.write(140);
//  delay(1000);
  servo_cr.write(90);
  delay(1500);
  servo_cr.write(150);
  delay(500);
  servo_cr.detach();
  //открываем нижнюю серву
  delay(1000);
  servo_cr.attach(A9);
  delay(300);
//  servo_cr.write(20);
//  delay(1000);
  servo_cr.write(120);
  delay(1500);
  servo_cr.write(0);
  delay(500);
  servo_cr.detach();
  Serial.println("S3-GOOD");
}
