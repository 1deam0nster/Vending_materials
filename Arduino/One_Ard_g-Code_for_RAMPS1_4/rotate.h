// -----------------Command S1 & S2-------------
void rotate_cup_to() {
  int pos;
  servo.attach(7);
  //-----Подать стаканчик клиенту
  for (pos = 65; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  servo.detach();
}

void rotate_cup_back() {
  int pos;
  servo.attach(7);
  //-----Подать стаканчик клиенту
  for (pos = 180; pos >= 65; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  servo.detach();
}
