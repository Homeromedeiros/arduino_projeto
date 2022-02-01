int s =0, m= 0;
void setup(){
Serial.begin(9600);
}

void loop(){
int mi = minuto(), se = segundo();
Serial.print("Tempo: ");
Serial.print(mi);
Serial.print(" : ");
Serial.println(se);
delay(1000);
}

int segundo()
{
  static unsigned long t2 = 0;
  int t = millis();
  if((t - t2) >= 1000){
    t2 = t;
    s++;
  }
  return s;
}

int minuto()
{
  if(s >= 10){
    s = 0;
    m++;
  }
  return m;
}