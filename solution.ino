/*
Solution for KMA Maze

V1
Samy Ibrahim
Updated: Dec. 18, 2021
*/



#include <Servo.h>  
Servo myservo;      

int Echo = A4;  
int Trig = A5;

// General Definitions
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 140

// Line Tracking Specific Definitions
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
}


int Distance_test() {
  digitalWrite(Trig, LOW);  
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);  
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;      
  return (int)Fdistance;
}  

void setup() {
  myservo.attach(3,700,2400);  
  Serial.begin(9600);  
 
  // Enable Pins for Obstacle Avoidance
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  // Enable Pins for Line Tracking Module
  pinMode(10,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT);
 
  stop();
}

void loop() {
   
    if(LT_M){
      forward();
     
      myservo.write(90);  
      //delay(100);
      middleDistance = Distance_test();
     
      if(middleDistance <= 25) {    
        stop();
        delay(200);                        
        myservo.write(10);
       
        right();
        delay(500);
        while(!LT_M);
      }
    }
    else if(!LT_R) {
      left();
      while(!LT_M);  
      //delay(100);
    }  
    else if(!LT_L) {
      right();
      while(!LT_M);  
      //delay(100);
    }                    
}
