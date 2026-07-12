int White1 = 11;
int Green = 10;
int Yellow = 9;
int Red = 8;
int White2 = 7;

int buzzer = 6;

int button1 = 12;
int button2 = 5;

bool buttonpressed = 0;

void setup() {
  // put your setup code here, to run once:

 pinMode(White1, OUTPUT);
 pinMode(Green, OUTPUT);
 pinMode(Yellow, OUTPUT);
 pinMode(Red, OUTPUT);
 pinMode(White2, OUTPUT);

 pinMode(buzzer, OUTPUT);

 pinMode(button1, INPUT_PULLUP);
 pinMode(button2, INPUT_PULLUP);
 
 randomSeed(analogRead(A0));

}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(Green, HIGH);
 digitalWrite(buzzer, HIGH);
 delay(100);
 digitalWrite(buzzer, LOW);
 delay(900);
 digitalWrite(Green, LOW);

 digitalWrite(Yellow, HIGH);
 digitalWrite(buzzer, HIGH);
 delay(100);
 digitalWrite(buzzer, LOW);
 delay(900);
 digitalWrite(Yellow, LOW);

 digitalWrite(Red, HIGH);
 digitalWrite(buzzer, HIGH);
 delay(100);
 digitalWrite(buzzer, LOW);
 delay(random(900,4901));
 digitalWrite(Red, LOW);
 
while(buttonpressed == 0){
  digitalWrite(White1, HIGH);
  digitalWrite(White2, HIGH);
  if(digitalRead(button1) == 0) {
    buttonpressed = 1;
    digitalWrite(White2, LOW);
  }  
  else if(digitalRead(button2) == 0){
    buttonpressed = 1;
    digitalWrite(White1, LOW);  
  }
}
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(1500);
  digitalWrite(White1, LOW);
  digitalWrite(White2, LOW);
  buttonpressed = 0;  
}
