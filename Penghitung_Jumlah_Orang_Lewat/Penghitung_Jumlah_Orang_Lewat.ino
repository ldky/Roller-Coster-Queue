#define trigPin 2
#define echoPin 3
int button = 4;
int count = 0;
int currentState = 0;
int previousState = 0;
byte pin = 5;
byte seven_seg_digits[10][7] ={{0,0,0,0,0,0,1}, //= 0
                               { 1,0,0,1,1,1,1 },  // = 1
                               { 0,0,1,0,0,1,0 },  // = 2
                               { 0,0,0,0,1,1,0 },  // = 3
                               { 1,0,0,1,1,0,0 },  // = 4
                               { 0,1,0,0,1,0,0 },  // = 5
                               { 0,1,0,0,0,0,0 },  // = 6
                               { 0,0,0,1,1,1,1 },  // = 7
                               { 0,0,0,0,0,0,0 },  // = 8
                               { 0,0,0,0,1,0,0 },   // = 9                                 
                               };
const int segmentPins[8] = {12,11,10,9,8,7,6,5};
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT);
  for (int i =0; i < 8; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  sevenSegWrite(0);
  writeDot(13); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //Konfigurasi Sensor Jarak
  long waktu, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  waktu = pulseIn(echoPin, HIGH);
  distance = (waktu/2)/29,1;

  int buttonState = digitalRead(button);
  if (distance <= 40){
    currentState = 1;
  }
  else {
    currentState = 0;
  }
  delay (100);
  if (currentState != previousState){
    if (currentState == 1){
      count = count +1;
      Serial.println(count);
      sevenSegWrite(count);
      delay (1000);
      if (count > 5){
        Serial.println("Slot penuh");
        count = 5;
      }
    }
  }
  if (buttonState == HIGH){
    count = 0;
    sevenSegWrite(0);
    Serial.println("Berhasil Direset");
  }
}

void sevenSegWrite(byte digit){
  byte pin = 5;
  for (byte segCount = 0; segCount <= 6; ++segCount){
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void writeDot(byte dot){
  digitalWrite(9, dot);
}
