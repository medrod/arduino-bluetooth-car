#include <Servo.h> 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


int lastCommand = 0;
int speed = 0;
int acc = 0 ;
Adafruit_MotorShield AFMS  = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor  = AFMS.getMotor(3);
Servo myservo; 

void setup() {
  Serial.begin(9600);
  myservo.attach(9); 
  myservo.write(90);
  
  AFMS.begin();
  
  myMotor->setSpeed(0);
  myMotor->run(RELEASE);
  
  
}

void loop() { 


  
  
  if (Serial.available()) {
  
    int inByte = Serial.read();

      Serial.print("IN: ");
      Serial.println(inByte);


    if(inByte == 63|| inByte == 159 || inByte == 251 || inByte == 152|| inByte == 154){
      lastCommand = inByte;
      Serial.print("Command: ");
      Serial.println(inByte);
    }else if(lastCommand == 251 || lastCommand == 152|| lastCommand == 154){
      speed = 0;
      myMotor->setSpeed(speed);
      myMotor->run(RELEASE);
      Serial.print("STOP WITH ");
      Serial.println(lastCommand);
    }else if(lastCommand == 63){
      
      if(inByte == 31 || inByte == 0){
        acc = 90;
      }else if(inByte <= 123 && inByte >=96){
        acc = 0;   
      }else if(inByte <=93 && inByte >= 67){
        acc = 180;
      }else{
        Serial.print("IN: ");
        Serial.println(inByte);
      }
      
      
      myservo.write(acc);
    }else if(lastCommand == 159){
      speed = inByte;
      if(inByte == 14){
        speed = 0;
        Serial.println("STOP");
      }else{
        speed = 255;
      }
      myMotor->setSpeed(speed);
      if(speed != 0){
          if(inByte == 41){
            myMotor->run(BACKWARD);
            Serial.println("BACKWARD");
          }else if(inByte == 0){
            myMotor->run(FORWARD);
            Serial.println("FORWARD");
          }
      }
    }
  }
    
}

