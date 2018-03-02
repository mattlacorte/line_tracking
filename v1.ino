#include <msp430g2553.h>
#include <pins_energia.h>

int motorspeedl = 200;
int motorspeedr = 200;

int blackValR = 965; //black value is high num
int blackValL = 700; //black value for left sensor

int r = 0; //left sensor val
int l = 0; //right sensor val

void setup() {

  pinMode(12,OUTPUT); //motor left forward
  pinMode(13,OUTPUT); //motor left backwards
  pinMode(15,OUTPUT);  //motor right backward
  pinMode(10,OUTPUT); //motor right forward

  pinMode(8,OUTPUT); //right side motor do some fancy shit
  pinMode(9,OUTPUT); //left side motor do some fancy shit
  
  pinMode(14,OUTPUT); //green led
  pinMode(2,OUTPUT);  //red led
  
  pinMode(7,INPUT);   //left sensor
  pinMode(6,INPUT);   //right sensor
  Serial.begin(9600);
  delay(1000);

}

void loop() {
//  for(int i =0; i <5;i++){
//    digitalWrite(2,HIGH);
//    digitalWrite(14,HIGH);
//    delay(500);
//    digitalWrite(2,LOW);
//    digitalWrite(14,LOW);
//    delay(500);
//  }

  if ((l < blackValL) && (r < blackValR)) { //Go forward (WW)
      digitalWrite(2,LOW);
      digitalWrite(14,LOW);
      
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      
      analogWrite(12, motorspeedl);
      analogWrite(10, motorspeedr);
  }
  
    else if ((l >= blackValL) && (r < blackValR)) { //Left Turn (BW)
      digitalWrite(2,HIGH);
      digitalWrite(14,LOW);

      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      
      analogWrite(10, motorspeedr + 65);         
    }
  
    else if ((l < blackValL) && (r >= blackValR)) { //Right Turn (WB)

      digitalWrite(2,LOW);
      digitalWrite(14,HIGH);
      
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);

      analogWrite(12, motorspeedl + 65);
    }
  
    else if ((l >= blackValL) && (r >= blackValR)) { //Left Turn (BB)
        digitalWrite(2,HIGH);
        digitalWrite(14,HIGH);
        
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
        
      
        analogWrite(12, 0);
        analogWrite(13, 0);
        analogWrite(10, 0);
        analogWrite(15, 0);
        delay(2000);

        analogWrite(10, motorspeedr);
        delay(2000);

        //while (r < blackValR){
          //analogWrite(10, motorspeedr);
          //r = analogRead(6);
       // }
    }
    
    else {
      
     for(int i = 0; i < 10; i++) {
        digitalWrite(2,HIGH);
        digitalWrite(14,LOW);
        delay(250);
        digitalWrite(2,LOW);
        digitalWrite(14,HIGH);
        delay(250);
      }
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      
      analogWrite(12, 0);
      analogWrite(13, 0);
      analogWrite(10, 0);
      analogWrite(15, 0);
      
    }

  l = analogRead(7); //left sensor val
  r = analogRead(6); //right sensor val

  Serial.println(r);
  Serial.print("  |  ");
  Serial.print(l);
  
}
