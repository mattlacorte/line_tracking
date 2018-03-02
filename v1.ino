/* * * * * * * * * * * * * * * * * * * *
 * ECGR 2252 | Sophomore Design        *
 *                                     *
 * TEAM 5                              *
 * Code by Matt LaCorte & Josh Martin  *
 * * * * * * * * * * * * * * * * * * * */

//files to include
#include <msp430g2553.h>  //added by Energia IDE
#include <pins_energia.h>  //stored within folder

/*GLOBAL VARS*/
//motor speeds allow for easy adjustments to speed
int motorspeedl = 200;  //right motor
int motorspeedr = 200;  //left motor

//black line threshhold -- BLACK is high -- WHITE is low
int blackValR = 965; //right sensor threshhold
int blackValL = 700; //left sensor threshhold

//stores vals read by sensors
int r = 0; //left sensor val
int l = 0; //right sensor val


//main setup for hardware declarations
void setup() {

  pinMode(12,OUTPUT);  //motor left forward
  pinMode(13,OUTPUT);  //motor left backward
  pinMode(15,OUTPUT);  //motor right backward
  pinMode(10,OUTPUT);  //motor right forward

  pinMode(8,OUTPUT); //right motor enable
  pinMode(9,OUTPUT); //left motor enable
  
  pinMode(14,OUTPUT); //green led
  pinMode(2,OUTPUT);  //red led
  
  pinMode(7,INPUT);   //left sensor
  pinMode(6,INPUT);   //right sensor
  
  Serial.begin(9600);
  
  delay(1000);
}


//main loop to run through the track
void loop() {
  
  //WHITE WHITE -- drive forwards
  if ((l < blackValL) && (r < blackValR)) {
      digitalWrite(2,LOW);
      digitalWrite(14,LOW);
      
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      
      analogWrite(12, motorspeedl);
      analogWrite(10, motorspeedr);
  }
  
    //BLACK WHITE -- turn right
    else if ((l >= blackValL) && (r < blackValR)) {
      digitalWrite(2,HIGH);
      digitalWrite(14,LOW);

      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      
      analogWrite(10, motorspeedr + 65);         
    }
  
    //WHITE BLACK -- turn right
    else if ((l < blackValL) && (r >= blackValR)) { //Right Turn (WB)

      digitalWrite(2,LOW);
      digitalWrite(14,HIGH);
      
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);

      analogWrite(12, motorspeedl + 65);
    }
  
    //BLACK BLACK -- turn left 90 degrees
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
    }
    
  //NOTHING
    else {
      //pray
    }

  l = analogRead(7); //left sensor val
  r = analogRead(6); //right sensor val

  Serial.print(r);
  Serial.print("  |  ");
  Serial.println(l);
}
