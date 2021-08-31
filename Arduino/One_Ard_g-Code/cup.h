//----------------------------------------------------------------------------------
//   Функция для выдачи стаканчика
//----------------------------------------------------------------------------------
void cup() {
  digitalWrite(RELAY_CUP, LOW);
  delay(1000);
  cup_fn();
}

void cup_fn() {
  int buttonState = digitalRead(cup_splitter);
  do {
    digitalWrite(RELAY_CUP, LOW);
    buttonState = digitalRead(cup_splitter);
    Serial.println(buttonState);
  } while (buttonState == true);
  delay(7000);
  digitalWrite(RELAY_CUP, HIGH);
  return;
}
