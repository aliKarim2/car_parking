/*Ali Karim 4/3/2025
This program uses an ultrasonic sensor to move a servo
The servo is only triggered by the sensor when the green LED is active 
Activate the green LED with the button
A timer will play where the servo can now be triggered via ultrasonic
When the timer is over, the red LED will be on again, and the green LED turns off

Analogy: A car parking payment system. A customer needs to pay (activate button) and then
the system senses the driver's vehicle (ultrasonic sensor) and raises a gate (servo motor).
*/


#include "SR04.h"
#include <Servo.h>
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const int SERVO_PIN = 3;
const int BUTTON_PIN = 11;
const int RED_PIN = A0;
const int GREEN_PIN = A1;

const int CLOSE_ANGLE = 25;
const int OPEN_ANGLE = 115;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN); //define ultrasonic sensor
long distance;

Servo myservo;

void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  myservo.attach(SERVO_PIN);  // attaches the servo on pin 3 to the servo object

   Serial.begin(9600);
   delay(1000);


   digitalWrite(RED_PIN, HIGH); //red pin is initially on


  myservo.write(CLOSE_ANGLE);
}

unsigned long time = 0;
bool ledState = false;
bool objectDetected = false;
void loop() {

  //when the timer ends:
  if (ledState && millis() - time >= 3000) {
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    ledState = false;
  }


  if(digitalRead(BUTTON_PIN) == LOW){
    //button is pressed, put green
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
    time = millis();
    ledState = true;

  }

  //Detect object with ultrasonic sensor
  distance=sr04.Distance();
  if(distance <= 20){ //obj is <20cm away
    objectDetected = true;
  }
  else{//obj is far
    objectDetected = false;
  }


  //Move servo
  if(digitalRead(GREEN_PIN) == HIGH && objectDetected){

    myservo.write(OPEN_ANGLE);      // "open" servo
    delay(2000);  //servo stays "open" for 2 seconds
  }
  else{
    myservo.write(CLOSE_ANGLE); // "close" servo
  }

    

}