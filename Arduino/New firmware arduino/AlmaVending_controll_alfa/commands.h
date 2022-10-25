// -----------------Command C0-------------
void drop_cap()
{
  //----Открыть затвор
  myservo.attach(8);
  for (pos_key = 155; pos_key >= 50; pos_key -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
  
  delay(2000);
  
  //----Запуск капсулы
  myservo.attach(7);

  for (pos_cap = 0; pos_cap <= 90; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  delay(2000);
  
  for (pos_cap = 90; pos_cap <= 180; pos_cap += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(1000);
  
  for (pos_cap = 180; pos_cap >= 0; pos_cap -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos_cap);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  myservo.detach();

  //----Закрыть затвор
  myservo.attach(8);
  for (pos_key = 50; pos_key <= 155; pos_key += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos_key);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
  
}
