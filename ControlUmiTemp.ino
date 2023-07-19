//#include <HTU21D.h>
//#include <Adafruit_HTU21DF.h>
#include "Adafruit_HTU21DF.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
 
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
 
//DHT dht(DHTPIN, DHTTYPE);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

int porta_rele1 = 7;
 
void setup() 
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  lcd.clear();
  lcd.init();
  lcd.backlight();
  pinMode(porta_rele1, OUTPUT); 
  Wire.begin();
}
 
void loop() 
{
  float h = htu.readHumidity();
  int t = htu.readTemperature();

  if (isnan(t) || isnan(h)) {
    lcd.println("Failed to read from DHT");
  } 
  else{
    //mostra os valores no lcd
    lcd.setCursor(0,0);
    lcd.print("Umid:");
    lcd.setCursor(6,0);
    lcd.print(h);
    lcd.setCursor(11,0);
    lcd.print("%t");
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.setCursor(6,1);
    lcd.print(t);
    lcd.setCursor(11,1);
    lcd.println("c");
        
    if ((t==21 || t==22)  && h>= 55 && h<=60 ){
      	digitalWrite(porta_rele1, HIGH);
   }  
    else if ((t==23 || t==24) && h>= 60 && h<=65 ){
      	digitalWrite(porta_rele1, HIGH);
    }
    else if ((t==25 || t==26) && h>= 65 && h<=70 ){
      	digitalWrite(porta_rele1, HIGH);
    }
    else if ((t==27 || t==28 || t==29) && h>= 70 && h<=75 ){
      	digitalWrite(porta_rele1, HIGH);
    }
    else if ((t==30 || t==31 || t==32) && h>= 75 && h<=80 ){
      	digitalWrite(porta_rele1, HIGH);
    }
    else if ((t==33 || t==34 || t==35) && h>= 80 && h<=85 ){
      	digitalWrite(porta_rele1, HIGH);
    }
    else{
       	digitalWrite(porta_rele1, LOW);   
    }
   delay(1000);
   }
}
