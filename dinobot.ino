#include <Servo.h>

Servo headServo, leftArmServo, rightArmServo;
const int trigPinLeft = 6;
const int trigPinRight = 8;
const int echoPinLeft = 7;
const int echoPinRight = 9;
int angle = 90;
long distanceRight;
long durationRight;
long distanceLeft;
long durationLeft;
long totalDistance;

void setup() {
  Serial.begin(9600);
  headServo.attach(5);
  headServo.write(angle);
  leftArmServo.attach(10);
  rightArmServo.attach(11);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
}

void loop() {
  follow();
  leftArm();
  rightArm();
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  durationLeft = pulseIn(echoPinLeft, HIGH);
  distanceLeft = durationLeft*0.034/2;

  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  durationRight = pulseIn(echoPinRight, HIGH);
  distanceRight = durationRight*0.034/2;

  Serial.print("Distance Left: ");
  Serial.println(distanceLeft);  
  Serial.print("Distance Right: ");
  Serial.println(distanceRight);
  headServo.write(angle);
}

void follow() {
  totalDistance = distanceLeft - distanceRight;
  if(totalDistance > 0){
    angle = angle + 1;
  }
  else if(totalDistance < 0){
    angle = angle - 1;
  } 
  else if(totalDistance = 0){
    angle = angle;
  }

}

void leftArm(){
  if(distanceLeft <= 5)
  leftArmServo.write(45);
  else leftArmServo.write(0); 
}

void rightArm(){
  if(distanceRight <= 5)
  rightArmServo.write(0);
  else rightArmServo.write(45);
}

