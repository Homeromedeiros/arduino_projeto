#include <SoftwareSerial.h> // incluir biblioteca para motor
#define rxPin 15  
#define txPin 14  
SoftwareSerial smcSerial = SoftwareSerial(rxPin, txPin);

#include <math.h>
#define variavel 13

// variavéis para o motor e sensor
int encoderA = 18, encoderB = 19; 
const uint16_t sensor = A8; 
int valpot, valmot; 
volatile uint16_t R_time, F_time, Ttime;
int i, cont = 0, soma = 0, vetor[variavel];
uint16_t maior = 0, menor = 10000, media; 
volatile uint16_t erro = 0;
 

void exitSafeStart()
{
  smcSerial.write(0x83);
}
void setMotorSpeed(int speed)
{
  if (speed < 0){
    smcSerial.write(0x86); 
    speed = -speed;
  }else{
    smcSerial.write(0x85); 
  }
  smcSerial.write(speed & 0x1F);
  smcSerial.write(speed >> 5);
}

void setup()
{
  smcSerial.begin(19200);
  Serial.begin(250000); 

  pinMode (encoderA, INPUT);
  pinMode (encoderB, INPUT);
  pinMode (sensor, INPUT);

  //zerando os vetores para o filtro
  for(i=0; i<variavel; i++)
    vetor[i] = 0;
  
  //interrupcao para calcular a velocidade
  attachInterrupt(digitalPinToInterrupt(encoderA), RisingTime, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB), FallingTime, FALLING);
  
  delay(5);
  smcSerial.write(0xAA); 
  exitSafeStart(); 
}

void RisingTime(){
 R_time = micros();
}

void FallingTime(){
  F_time = micros();
  Ttime  = ((F_time - R_time)*2); //periodo completo de um pulso do motor
  }
void loop()
{
  volatile uint16_t IRPM, ORPM, X;//entrada e saida de 16bits em RPM
  
  valpot = analogRead(sensor);
  IRPM = map(valpot,0,1023,0,3200);
        
    //laço do filtro media movel
    for(cont = 0; cont < variavel; cont++){
      vetor[cont] = Ttime;
      soma = soma + vetor[cont];
      if(vetor[cont] <menor){
        menor=vetor[cont];
      }
      if(vetor[cont] > maior){
        maior=vetor[cont];
      }
      delay(5);
    }
    media = (soma-maior-menor)/(variavel-2); 
    
    if (cont >= variavel){
      soma = 0;
      menor = 10000;
      maior = 0;
    }
  
  ORPM = ((1139715)/media); //(((60*10^6)/16)/(Ttime*102)*31)
  
  erro = abs(IRPM - ORPM);
  X = ((2*IRPM) - ORPM);

  setMotorSpeed(X);
}
