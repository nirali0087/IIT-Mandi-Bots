#include "BluetoothSerial.h" 
BluetoothSerial SerialBT; 
#define IN1 13 
#define IN2 12 
#define IN3 14 
#define IN4 27 
#define ENA 26 
#define ENB 25 
char command;  
void setup() { 
Serial.begin(115200); 
   
  SerialBT.begin("Robosoccer_ESP32");  
  Serial.println("Bluetooth Started! Ready to pair..."); 
 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT); 
 
  analogWrite(ENA, 205); 
  analogWrite(ENB, 255); 
} 
 
void loop() { 
   
  if (SerialBT.available()) { 
    command = SerialBT.read(); 
    executeCommand(command); 
  } 
} 
 
void executeCommand(char cmd) { 
  switch (cmd) { 
    case 'f':  
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
      break; 
       
    case 'B':  
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
      break; 
       
    case 'R':  
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
      break; 
       
    case 'L':  
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
      break; 
       
    case 'S':  
    default: 
      digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); 
      break; 
  } 
} 
