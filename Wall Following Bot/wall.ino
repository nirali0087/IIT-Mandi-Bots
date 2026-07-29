#define FRONT_TRIG 4 
#define FRONT_ECHO 5 
#define RIGHT_TRIG 6 

#define LEFT_MOTOR_IN1 8 
#define LEFT_MOTOR_IN2 9 
#define RIGHT_MOTOR_IN3 10 
#define RIGHT_MOTOR_IN4 11 

const int FRONT_STOP_DIST = 20; // If front wall is closer than 20cm, turn left 
const int IDEAL_WALL_DIST = 15; // The robot wants to stay 15cm away from the right wall 
const int ALLOWED_ERROR = 3;    // Allows the robot to be between 12cm and 18cm without 
adjusting 
void setup() { 
Serial.begin(9600); 
  // Setup Sensor Pins 
  pinMode(FRONT_TRIG, OUTPUT); 
  pinMode(FRONT_ECHO, INPUT); 
  pinMode(RIGHT_TRIG, OUTPUT); 
  pinMode(RIGHT_ECHO, INPUT); 
 
  // Setup Motor Pins 
  pinMode(LEFT_MOTOR_IN1, OUTPUT); 
  pinMode(LEFT_MOTOR_IN2, OUTPUT); 
  pinMode(RIGHT_MOTOR_IN3, OUTPUT); 
  pinMode(RIGHT_MOTOR_IN4, OUTPUT); 
} 
 
void loop() { 
  // 1. Read distances from both sensors 
  int frontDistance = getDistance(FRONT_TRIG, FRONT_ECHO); 
  int rightDistance = getDistance(RIGHT_TRIG, RIGHT_ECHO); 
 
  Serial.print("Front: "); Serial.print(frontDistance); 
  Serial.print(" cm, Right: "); Serial.println(rightDistance); 
 
  // 2. The Robot's Brain (Decision Making) 
   
  if (frontDistance > 0 && frontDistance < FRONT_STOP_DIST) { 
    // A wall is right in front of us! Turn hard left to avoid it. 
    turnLeft(); 
  }  
  else { 
    // The path ahead is clear, so focus on following the right wall 
     
    if (rightDistance < (IDEAL_WALL_DIST - ALLOWED_ERROR)) { 
      // Too close to the wall! Steer slightly left away from it. 
      turnSlightLeft(); 
    }  
    else if (rightDistance > (IDEAL_WALL_DIST + ALLOWED_ERROR)) { 
      // Too far from the wall! Steer slightly right towards it. 
      turnSlightRight(); 
    }  
    else { 
      // We are at the perfect distance! Keep moving straight. 
      moveForward(); 
    } 
  } 
 
  // A small delay to keep the robot from reading sensors too fast and glitching 
  delay(50);  
} 
 
// Function to calculate distance from ultrasonic sensors 
int getDistance(int trigPin, int echoPin) { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
   
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout 
  if (duration == 0) return 999; // If no echo, assume path is clear 
   
  return duration * 0.034 / 2; // Convert to cm 
} 
 
// Motor Control Functions 
void moveForward() { 
digitalWrite(LEFT_MOTOR_IN1, HIGH); 
digitalWrite(LEFT_MOTOR_IN2, LOW); 
digitalWrite(RIGHT_MOTOR_IN3, HIGH); 
digitalWrite(RIGHT_MOTOR_IN4, LOW); 
} 
void turnLeft() { 
// Hard left: Left wheel backwards, Right wheel forwards 
digitalWrite(LEFT_MOTOR_IN1, LOW); 
digitalWrite(LEFT_MOTOR_IN2, HIGH); 
digitalWrite(RIGHT_MOTOR_IN3, HIGH); 
digitalWrite(RIGHT_MOTOR_IN4, LOW); 
} 
void turnSlightLeft() { 
// Soft left: Left wheel stops, Right wheel pushes forward 
digitalWrite(LEFT_MOTOR_IN1, LOW); 
digitalWrite(LEFT_MOTOR_IN2, LOW); 
digitalWrite(RIGHT_MOTOR_IN3, HIGH); 
digitalWrite(RIGHT_MOTOR_IN4, LOW); 
} 
void turnSlightRight() { 
// Soft right: Left wheel pushes forward, Right wheel stops 
digitalWrite(LEFT_MOTOR_IN1, HIGH); 
digitalWrite(LEFT_MOTOR_IN2, LOW); 
digitalWrite(RIGHT_MOTOR_IN3, LOW); 
digitalWrite(RIGHT_MOTOR_IN4, LOW); 
} 
void stopMotors() { 
digitalWrite(LEFT_MOTOR_IN1, LOW); 
digitalWrite(LEFT_MOTOR_IN2, LOW); 
digitalWrite(RIGHT_MOTOR_IN3, LOW); 
digitalWrite(RIGHT_MOTOR_IN4, LOW); 
}