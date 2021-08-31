// -----------------Command R1-------------

void relay_pr(double n, double t){
//  int rel = n;
//  uint32_t del = t;
//  uint32_t num_rel;
//  
//  if (rel == 1)
//    {
//      num_rel = 14;
//    }
//  else if (rel == 2)
//    {
//      num_rel = 15;
//    }
//  else if (rel == 3)
//    {
//      num_rel = 16;
//    }
//  else if (rel == 4)
//    {
//      num_rel = 29;
//    }
//  else if (rel == 5)
//    {
//      num_rel = 31;
//    }
//  else if (rel == 6)
//    {
//      num_rel = 2;
//    }
//  else if (rel == 7)
//    {
//      num_rel = 1;
//    }
//  else if (rel == 8)
//    {
//      num_rel = 0;
//    }
  
//  Serial.print("relay = ");
//  Serial.println(num_rel);
//  Serial.print("delayRelay = ");
//  Serial.println(del);
//  Serial.println("-------------");
  
//  digitalWrite(num_rel, LOW);
//  delay(del);
//  digitalWrite(num_rel, HIGH);
}

void relay()
{
//  int newNValue = N;
//  int newTValue = T;
//
//  if (Commands.availableValue('N')) // ADDED parameter D in S0
//  newNValue = Commands.GetValue('N');
//  
//  if (Commands.availableValue('T')) // ADDED parameter D in S0
//  newTValue = Commands.GetValue('T');
//
//  Serial.print("relay = ");
//  Serial.println(newNValue);
//  Serial.print("delayRelay = ");
//  Serial.println(newTValue);
//  Serial.println("-------------");
//  
//  relay_pr(newNValue, newTValue);
  
}

void open_cofe(){
  digitalWrite(OPEN, LOW);
  delay(70);
  digitalWrite(OPEN, HIGH);
}

void close_cofe(){
  digitalWrite(CLOSE, LOW);
  delay(70);
  digitalWrite(CLOSE, HIGH);
}

void start_cofe(){
  digitalWrite(START_COFE, LOW);
  delay(70);
  digitalWrite(START_COFE, HIGH);
}
