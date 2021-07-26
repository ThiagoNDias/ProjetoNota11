/* Projeto Nota 11
* v1.00.00
*/

const long p0 = 11427000;
const int VERMELHO = 10;
const int AMARELO = 11;
const int VERDE = 12;
const int SENSOR = 1;
int VALORSENSOR = 0;
int RELE = 7;

const float e = 2.7182;
const double varp0 = 30300;

int I = 20;
#include "LiquidCrystal.h"
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

#define ADDO 6
#define ADSK 13

unsigned long ReadCount();
unsigned long convert;

void setup() {
  Serial.begin(9600);
  pinMode(VERMELHO,OUTPUT);
  pinMode(AMARELO,OUTPUT);
  pinMode(VERDE,OUTPUT);
  pinMode(RELE,OUTPUT);
  lcd.begin(16, 2);
  pinMode(ADDO, INPUT_PULLUP);
  pinMode(ADSK, OUTPUT);
}

void loop() {
  convert = ReadCount();
  Serial.println(convert);
  delay(1000);
  int VALORSENSOR = analogRead(SENSOR);
  Serial.println(VALORSENSOR);
  delay(20);

  if(VALORSENSOR < 400 ) {
    digitalWrite(RELE, LOW);
    delay(200);
    } else {
      digitalWrite(RELE,HIGH);
      delay(200);
      }
      
  double PESO = (convert-p0)/varp0;
  Serial.println(p0);
  delay(20);
  
  if(I == 20) {
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("UNIP");
    lcd.setCursor(0,0);
    lcd.print("PROJETO NOTA 11");
    delay(4000);
    I = I+1;
    } else {
      int LX = (8.2838*pow(e,(0.0057*VALORSENSOR)));
      lcd.clear();
      lcd.print("LUZ");
      lcd.setCursor(9,0);
      lcd.print(LX);
      lcd.print(" LX");
      lcd.setCursor(0,1);
      lcd.print("PESO");
      lcd.setCursor(9,1);
      lcd.print(PESO);
      lcd.print(" KG");
      delay(500);
      }
      
  if(PESO < 6) {
    digitalWrite(VERDE,HIGH);
    digitalWrite(VERMELHO,LOW);
    digitalWrite(AMARELO,LOW);
    delay(30);
    } else {
      if(PESO < 12) {
        digitalWrite(AMARELO,HIGH);
        digitalWrite(VERMELHO,LOW);
        digitalWrite(VERDE,LOW);
        delay(30);
        } else {
          if(PESO < 30) {
            digitalWrite(VERMELHO,LOW);
            digitalWrite(VERDE,LOW);
            digitalWrite(AMARELO,HIGH);
            delay(200);
            digitalWrite(AMARELO,LOW);
            delay(200);
            } else {
              if(PESO < 40) {
                digitalWrite(AMARELO,LOW);
                digitalWrite(VERDE,LOW);
                digitalWrite(VERMELHO,HIGH);
                delay(30);
                } else {
                  digitalWrite(AMARELO,LOW);
                  digitalWrite(VERDE,LOW);
                  digitalWrite(VERMELHO,HIGH);
                  delay(200);
                  digitalWrite(VERMELHO,LOW);
                  delay(200);
                  }
              }
          }
      }
  }
  
unsigned long ReadCount() {
  unsigned long Count = 0;
  unsigned char i;
  
  digitalWrite(ADSK, LOW);
  
  while(digitalRead(ADDO));
  
  for(i = 0; i < 24; i++) {
    digitalWrite(ADSK, HIGH);
    Count = Count << 1;
    digitalWrite(ADSK, LOW);
    
    if(digitalRead(ADDO)) Count++;
    }
  digitalWrite(ADSK, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK, LOW);
  
  return(Count);
}
