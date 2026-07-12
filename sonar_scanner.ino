#include <Servo.h>
Servo s;
int trig = 5;
int echo =6;
long duration;
float distance;
int buzzer = 9;
int p = 12;
int t = 11;
int u = 10;

void setup() {
  // put your setup code here, to run once:
  s.attach(3);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(p, OUTPUT);
  pinMode(t, OUTPUT);
  pinMode(u, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=180; i++){
    s.write(i);
    delay(10);
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration*0.017;

    if(distance>40){
      digitalWrite(p, LOW);
      digitalWrite(t, LOW);
      digitalWrite(u, HIGH);
      noTone(buzzer);
    }
    else if(distance>10){
      digitalWrite(p, LOW);
      digitalWrite(t, HIGH);
      digitalWrite(u, LOW);
      tone(buzzer, 100);
    }
    else {
      digitalWrite(p, HIGH);
      digitalWrite(t, LOW);
      digitalWrite(u, LOW);
      tone(buzzer, 500);      
    }
  }

  for(int i=180; i>=0; i--){
    s.write(i);
    delay(10);
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    duration = pulseIn(echo, HIGH);
    distance = duration*0.017;

    if(distance>40){
      digitalWrite(p, LOW);
      digitalWrite(t, LOW);
      digitalWrite(u, HIGH);
      noTone(buzzer);
    }
    else if(distance>10){
      digitalWrite(p, LOW);
      digitalWrite(t, HIGH);
      digitalWrite(u, LOW);
      tone(buzzer, 100);
    }
    else {
      digitalWrite(p, HIGH);
      digitalWrite(t, LOW);
      digitalWrite(u, LOW);
      tone(buzzer, 500);      
    }
  }
}
