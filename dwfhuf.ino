#include <Servo.h>
#define PIN_TRIG 8
#define PIN_ECHO 7
#define flamePin 2
#define BuzzerPin 13
Servo myservo1;
Servo myservo2;
Servo myservo3;
void setup() {
  Serial.begin(115200);
  pinMode(flamePin, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo1.attach(11);  
  myservo2.attach(10);  
  myservo3.attach(9);  
}
int tat123(){
  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(0);
}
int bat123(){
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(180);
}

void loop() {
  // Start a new measurement:
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  int duration = pulseIn(PIN_ECHO, HIGH);
  float khoangcach = duration / 58;
  int flameState = digitalRead(flamePin);
  if (flameState == LOW) { 
    Serial.println("Lửa được phát hiện!");
    delay(100);
    bat123();
    while (flameState == LOW || khoangcach < 200){
      tone(BuzzerPin, 262, 250);
    }
  } else Serial.println("Không có lửa.");
  delay(500);

  // Read the result:
  
  Serial.print("Distance in CM: ");
  Serial.println(khoangcach);
  if (khoangcach < 200 ){
    bat123();
  } else tat123();
  delay(1000);
}
