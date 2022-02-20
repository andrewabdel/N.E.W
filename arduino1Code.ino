
#define echoPin 7 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int buzzer = 13;
int number;
void setup() {
  
   pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  lcd.begin(16, 2);

  pinMode(10,INPUT);
  digitalWrite(10, HIGH);
}
void loop() {
 
  int digitalVal = digitalRead(10);
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<30){
     tone(buzzer, 500); // Send 1KHz sound signal...
  }
 else{
    noTone(buzzer);     // Stop sound...
 }
 if(HIGH == digitalVal){//if tilt switch is not breakover
  lcd.print("Call SOS phone #!!!");
  lcd.setCursor(0,1) ;
  lcd.print("  289-829-3388  ");
  tone(buzzer, 1000);
}



}
