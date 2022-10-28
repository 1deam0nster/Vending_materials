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
//  servo_sug.attach(12);
//  delay(300);
//  servo_sug.write(70);
//  delay(1000);
//  servo_sug.write(165);
//  delay(1000);
//  servo_sug.detach();
//  Serial.println("S3-GOOD");
  
  servo.attach(2);
  int pos=180;
  servo.write(180);
  for (pos = 180; pos >= 0; pos--) {
        // Отправляем текущий угол на серво
  servo.write(pos);
        // Ждём 15 мс
  delay(15);
  }
  servo.detach();
  Serial.println("S3-GOOD");
  
}
