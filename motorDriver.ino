#include<AFMotor.h>
char serialdata;

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);

void setup() {
  Serial.begin(9600);
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
}

void loop() {
  while(Serial.available()>0)
  serialdata = Serial.read();
  Serial.print(serialdata);

  if(serialdata == '1'){
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    }
 
  else if(serialdata=='0'){
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
    }
}
