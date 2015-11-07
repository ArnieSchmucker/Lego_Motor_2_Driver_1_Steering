#include <IRremote.h>
//No speed control on steering motor.  Would need to modify the card for that.
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define POWER 0x10EFD827 
#define A 0x10EFF807 
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF

const byte rtMotorPin1 = 4;
const byte rtMotorPin2 = 5;  //pwm
const byte ltMotorPin1 = 7;  
const byte ltMotorPin2 = 6;  //pwm
const byte strMotorPin1 = 8;
const byte strMotorPin2 = 9;  //pwm

int rtSpeed = 0;
int ltSpeed = 0;
boolean motorDir = 0;
boolean strDir = 0;

void setup()
{
  
  pinMode(rtMotorPin1, OUTPUT);
  pinMode(rtMotorPin2, OUTPUT);
  pinMode(ltMotorPin1, OUTPUT);
  pinMode(ltMotorPin2, OUTPUT);
  pinMode(strMotorPin1, OUTPUT);
  pinMode(strMotorPin2, OUTPUT);
  
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{

  
  if (irrecv.decode(&results)) 
  {
    if (results.value == POWER) 
    {
      //Serial.println("POWER");    
    }
     if (results.value == A) 
    {
      //Serial.println("A");    
    }
     if (results.value == B) 
    {
      //Serial.println("B");  
    }
     if (results.value == C) 
    {
      //Serial.println("C");
    }
     if (results.value == UP) 
    {
      //Serial.println("UP");
      rtSpeed = 255;
      ltSpeed = 255;
      motorDir = 0;
    }
     if (results.value == DOWN) 
    {
      //Serial.println("DOWN");
      rtSpeed = 255;
      ltSpeed = 255;
      motorDir = 1;
    }
     if (results.value == LEFT) 
    {
      //Serial.println("LEFT");
      strDir = 0;
      strMotor(strDir);
      delay(200);
      strMotorOff();
    }
     if (results.value == RIGHT) 
    {
      //Serial.println("RIGHT");
      strDir = 1;
      strMotor(strDir);
      delay(200);
      strMotorOff();
    }
     if (results.value == SELECT) 
    {
      //Serial.println("SELECT");
      rtSpeed = 0;
      ltSpeed = 0;
    }
    irrecv.resume();
  }
  
  rtMotor(rtSpeed, motorDir);
  ltMotor(ltSpeed, motorDir);
}

void rtMotor(int rtPwm, boolean reverse)
{
  analogWrite(rtMotorPin2, rtPwm);
  if (reverse) {
    digitalWrite(rtMotorPin1, LOW);
  }
  else {
    digitalWrite(rtMotorPin1, HIGH);
  }
}

void ltMotor(int ltPwm, boolean reverse)
{
    analogWrite(ltMotorPin2, ltPwm);
  if (reverse) {
    digitalWrite(ltMotorPin1, LOW);
  }
  else {
    digitalWrite(ltMotorPin1, HIGH);
  }
}

void strMotor(boolean reverse)
{
  if (reverse) {
    digitalWrite(strMotorPin1, HIGH);
    digitalWrite(strMotorPin2, LOW);
  }
  else {
    digitalWrite(strMotorPin1, LOW);
    digitalWrite(strMotorPin2, HIGH);
  }
  
}

void strMotorOff()
{
  digitalWrite(strMotorPin1, HIGH);
  digitalWrite(strMotorPin2, HIGH);
}









