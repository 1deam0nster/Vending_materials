//----------------------------------------------------------------------------------
//   Функция для прокручивания турели
//----------------------------------------------------------------------------------
void turrelFunction() {

  if (digitalRead(turrel_micro_switch) == LOW || digitalRead(turrel_pos) == HIGH) {
    motor_val = 1;
  } else {
    motor_val = 2;
  }

  switch (motor_val) {
    case 1:
      digitalWrite(RELAY_TURREL, LOW);
      break;
    case 2:
      digitalWrite(RELAY_TURREL, HIGH);
      break;
  }
}
