#include <Servo.h> 
const int TRIG_PIN = 13; 
const int ECHO_PIN = 12; 
const int SERVO_PIN = 2; 
const int ENA = 3; 
const int IN1 = 4; 
const int IN2 = 5; 
const int IN3 = 6; 
const int IN4 = 7; 
const int ENB = 11; 
const int STOP_DIST = 20; 
const int TURN_SPEED = 140; 
int currentSpeed = 0; 
 
Servo scanner; 
 
void setup() { 
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 
   
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT); 
   
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
   
  scanner.attach(SERVO_PIN); 
  scanner.write(90); 
  delay(1000); 
} 
 
void loop() { 
  scanner.write(90); 
  int frontDist = getDistance(); 
   
  if (frontDist > STOP_DIST) { 
    moveForward(); 
  } else { 
    avoidObstacle(); 
  } 
} 
 
int getDistance() { 
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
   
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW); 
   
  long dur = pulseIn(ECHO_PIN, HIGH, 30000); 
   
  if (dur == 0) { 
    return 400; 
  } 
   
  return dur * 0.034 / 2; 
} 
 
void moveForward() { 
  // Adjust RIGHT_MAX or LEFT_MAX if the robot drifts 
  int LEFT_MAX = 190;   
  int RIGHT_MAX = 150;  
   
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
   
  while (currentSpeed < LEFT_MAX) { 
    currentSpeed += 10; 
     
    if (currentSpeed > LEFT_MAX) { 
      currentSpeed = LEFT_MAX; 
    } 
     
    int rightSpeed = currentSpeed; 
    if (rightSpeed > RIGHT_MAX) { 
      rightSpeed = RIGHT_MAX;  
    } 
     
    analogWrite(ENA, currentSpeed);  
    analogWrite(ENB, rightSpeed);    
    delay(15); 
  } 
} 
 
void moveBackward() { 
  analogWrite(ENA, TURN_SPEED); 
  analogWrite(ENB, TURN_SPEED); 
   
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
} 
 
void stopRobot() { 
  currentSpeed = 0; 
   
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
} 
 
void turnLeft() { 
  analogWrite(ENA, TURN_SPEED); 
  analogWrite(ENB, TURN_SPEED); 
   
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
   
  delay(300); 
  stopRobot(); 
  delay(200); 
} 
 
void turnRight() { 
  analogWrite(ENA, TURN_SPEED); 
  analogWrite(ENB, TURN_SPEED); 
   
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
   
  delay(300); 
  stopRobot(); 
  delay(200); 
} 
 
int lookLeft() { 
  scanner.write(170); 
  delay(500); 
  int dist = getDistance(); 
   
  scanner.write(90); 
  delay(200); 
   
  return dist; 
} 
 
int lookRight() { 
  scanner.write(10); 
  delay(500); 
  int dist = getDistance(); 
   
  scanner.write(90); 
  delay(200); 
   
  return dist; 
} 
 
void avoidObstacle() { 
  stopRobot(); 
  delay(200); 
   
  moveBackward(); 
  delay(400); 
   
  stopRobot(); 
  delay(300); 
   
  while (true) { 
    if (lookLeft() > STOP_DIST) { 
      turnLeft(); 
      break;  
    } 
     
    if (lookRight() > STOP_DIST) { 
      turnRight(); 
      break;  
    } 
     
    moveBackward(); 
    delay(400); 
     
    stopRobot(); 
    delay(200);  
  }  
} 
 