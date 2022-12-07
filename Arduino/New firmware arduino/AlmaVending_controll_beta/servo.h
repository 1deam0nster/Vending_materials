// -----------------Command S0-------------
void servo_degrid(double n, double d)
{
  int serv_number = n;
  int deg = d;
  //-----Подключаем сервоприводы
  myservo.attach(serv_number);

  //----Открыть клешню
  myservo.write(deg);
  delay(1000);

  //-----Отключаем сервоприводы
  myservo.detach();
  //Commands.comment("D:" + String(d)); // DEBUG SERIAL

}

void servofn() {
  void servo_test();

  double newNValue = N;
  if (Commands.availableValue('N')) // ADDED parameter D in S0
    newNValue = Commands.GetValue('N');

  double newDValue = D;
  if (Commands.availableValue('D')) // ADDED parameter D in S0
    newDValue = Commands.GetValue('D');

  servo_degrid(newNValue, newDValue);
}
