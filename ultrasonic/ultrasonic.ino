const int triggerpin=3;
const int echopin=4;
int gled=6;
int rled=7;
long distance,duration; 
void setup() {
  Serial.begin(9600);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(triggerpin,OUTPUT);
  

}

void loop() {
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=duration*(0.034/2.0);
  Serial.println(distance);
  
  if(distance<50){
    digitalWrite(rled,1);
    digitalWrite(gled,0);
    Serial.println("red");
  }
  else{
    digitalWrite(gled,1);
    digitalWrite(rled,0);
    Serial.println("green");
  }
  delay(1000);
  
  

}
