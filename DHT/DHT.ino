#include <Wire.h>
#include<DHT.h>

String SendData;
String RecvData;

DHT dht11(8,DHT11);
void setup() 
{
  dht11.begin();
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  Wire.begin(8);  //0x08 = 0b00001000 = 8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);
}
 
void loop() 
{
  float hum = dht11.readHumidity();
  float temp = dht11.readTemperature();
  
  Serial.print("Humidity = ");
  Serial.print(hum);
  Serial.print("\t");
  Serial.print("Temeperature = ");
  Serial.println(temp);
  
  SendData = String(hum)+ "," + String(temp);
  Serial.println(SendData);
  
  Serial.println(RecvData);
  if(RecvData=="1")
  {
    digitalWrite(13,1);
  }
  else
  {
    digitalWrite(13,0);
  }
  
  //Wire.end();
  delay(1000);

}

void sendEvent(int howmany)
{
  for(int i =0; i<SendData.length() ;i++)
  {
    Wire.write(SendData[i]);
  
  }
}

void receiveEvent(int howmany)
{
  while (Wire.available())
  {
    char c = Wire.read();
    RecvData += c;
  }
}
