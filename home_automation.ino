#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include<Wire.h>
#define ACCEPT_TYPE "text/csv" //comma seperated value

//#include <DHT.h>
WiFiClient client;

#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
//int relayInput1 = 2;  //D4
int relayInput1 = 16; //D0
//int relayInput3 = 0;  //D3
//int relayInput4 = 14; //D5
//int relayInput5 = 12; //D6
//int relayInput6 = 13; //D7
//int relayInput7 = 15; //D8
//int relayInput8 = 1;  //Tx
SoftwareSerial pzemSWSerial(4, 5);  // Rx & Tx respectively
PZEM004Tv30 pzem;


const char ssid[] = "GLA-CSED";
const char password[] = "GLACAMPUS";

const char appKey[]="780b4255-60f3-4e42-a645-dc9ccf9b4f65";
const char host[] = "172.16.78.20"; 
const int httpPort = 7080;


const char Thing[] = "Home_automation_thing";
const char Property1[] = "voltage";
const char Property2[] = "current";
const char Property3[] = "energy";
const char Property4[] = "power";
const char Property5[] = "frequency";
const char Property6[] = "power_factor";

const char get_Property1[] = "relay9";
//const char get_Property2[] = "relay2";
//const char get_Property3[] = "relay3";
//const char get_Property4[] = "relay4";
//const char get_Property5[] = "relay5";
//const char get_Property6[] = "relay6";
//const char get_Property7[] = "relay7";
//const char get_Property8[] = "relay8";

void Put(String ThingName, String ThingProperty, String Value)
  {

    Serial.println(host);
  if (!client.connect(host, httpPort))
 {
    Serial.println("connection failed");
    return;
  } else

 {
    Serial.println("Connected to ThingWorx.");
  }
  String url = "/Thingworx/Things/"+ThingName+"/Properties/"+ThingProperty;
  Serial.print("requesting URL: ");
  Serial.println(url);

  String strPUTReqVal = "{\"" + ThingProperty + "\":\"" + Value + "\"}";  
  Serial.print("PUT Value: ");
  Serial.println(strPUTReqVal);

  client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "appKey:"+appKey + "\r\n" +
               "x-thingworx-session: false" + "\r\n" +
               "Accept: application/json" + "\r\n" +
               "Connection: close" + "\r\n" +
               "Content-Type: application/json" + "\r\n" +
               "Content-Length: " + String(strPUTReqVal.length()) + "\r\n\r\n" +
               strPUTReqVal + "\r\n\r\n");  

  while (client.connected())
{
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
}

void setup()
{
  pinMode(relayInput1, OUTPUT);
//  pinMode(relayInput2, OUTPUT);
//  pinMode(relayInput3, OUTPUT);
//  pinMode(relayInput4, OUTPUT);
//  pinMode(relayInput5, OUTPUT);
//  pinMode(relayInput6, OUTPUT);
//  pinMode(relayInput7, OUTPUT);
//  pinMode(relayInput8, OUTPUT);
  
  Serial.begin(115200);  
  pzem = PZEM004Tv30(pzemSWSerial);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
  {
     delay(500);
     Serial.print(".");
   }
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
      delay(100);

}

void loop()
{
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  if(isnan(voltage)){
      voltage = 0.00;
  } 
  if(isnan(current)){
      current = 0.00;
  }
  if(isnan(energy)){
      energy = 0.00;
  }
  if(isnan(power)){
      power = 0.00;
  }
  if(isnan(pf)){
      pf = 0.00;
  }
  if(isnan(frequency)){
      frequency = 0.00;
  }
      Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      Serial.print("Current: ");      Serial.print(current,3);      Serial.println("A");
      Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
      Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      Serial.print("PF: ");           Serial.println(pf); 
              
  delay(1000);
 
  String strVoltage = String(voltage);
  String strCurrent = String(current,3);
  String strEnergy = String(energy);
  String strPower = String(power);
  String strFrequency = String(frequency);
  String strPF = String(pf);
 

  Put(Thing,Property1,strVoltage);  
  Put(Thing,Property2,strCurrent);
  Put(Thing,Property3,strEnergy);
  Put(Thing,Property4,strPower);
  Put(Thing,Property5,strFrequency);
  Put(Thing,Property6,strPF);
  
  String res1 = Get(Thing,get_Property1); 
//  String res2 = Get(Thing,get_Property2);
//  String res3 = Get(Thing,get_Property3); 
//  String res4 = Get(Thing,get_Property4);
//  String res5 = Get(Thing,get_Property5);
//  String res6 = Get(Thing,get_Property6);
//  String res7 = Get(Thing,get_Property7);
//  String res8 = Get(Thing,get_Property8);

//  Serial.println(res1);
//  Serial.println(res2);
//  Serial.println(res3);
//  Serial.println(res4);
//  Serial.println(res5);
//  Serial.println(res6);
//  Serial.println(res7);
//  Serial.println(res8);//  "relay":"1.0"/r/n
  
//  Serial.println(res1[11]);
//  Serial.println(res2[11]);
//  Serial.println(res3[11]);
//  Serial.println(res4[11]);
//  Serial.println(res5[11]);
//  Serial.println(res6[11]);
//  Serial.println(res7[11]);
//  Serial.println(res8[11]);
  
  
  if(res1[11]=='f')
  {
    digitalWrite(relayInput1,HIGH);
    Serial.println("relayoff");
  }
  else if(res1[11]=='t'){
    digitalWrite(relayInput1,LOW);
    Serial.println("relayon");
  }
//    if(res2[11]=='f')
//  {
//    digitalWrite(relayInput2,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res2[11]=='t'){
//    digitalWrite(relayInput2,LOW);
//    Serial.println("relayon");
//  }
//    if(res3[11]=='f')
//  {
//    digitalWrite(relayInput3,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res3[11]=='t'){
//    digitalWrite(relayInput3,LOW);
//    Serial.println("relayon");
//  }
//      if(res4[11]=='f')
//  {
//    digitalWrite(relayInput4,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res4[11]=='t'){
//    digitalWrite(relayInput4,LOW);
//    Serial.println("relayon");
//  }
//      if(res5[11]=='f')
//  {
//    digitalWrite(relayInput5,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res5[11]=='t'){
//    digitalWrite(relayInput5,LOW);
//    Serial.println("relayon");
//  }
//      if(res6[11]=='f')
//  {
//    digitalWrite(relayInput6,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res3[11]=='t'){
//    digitalWrite(relayInput6,LOW);
//    Serial.println("relayon");
//  }
//      if(res7[11]=='f')
//  {
//    digitalWrite(relayInput7,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res7[11]=='t'){
//    digitalWrite(relayInput7,LOW);
//    Serial.println("relayon");
//  }
//      if(res8[11]=='f')
//  {
//    digitalWrite(relayInput8,HIGH);
//    Serial.println("relayoff");
//  }
//  else if(res8[11]=='t'){
//    digitalWrite(relayInput8,LOW);
//    Serial.println("relayon");
//  }
  delay(1000);
}



String Get(String get_Thing, String get_Property)
{              
        HTTPClient http;
        int httpCode = -1;
        String fullRequestURL = "http://" + String(host) +":"+ String(httpPort)+ "/Thingworx/Things/" 
                                + get_Thing + "/Properties/" + get_Property + "?appKey=" + appKey;
                                
        Serial.println(fullRequestURL);
        http.begin(client, fullRequestURL);
        http.addHeader("Accept",ACCEPT_TYPE,false,false);        
        httpCode = http.GET();
        Serial.println(httpCode);
        
        String responses;
        if(httpCode > 0)        
        {             
           responses= http.getString(); 
             //Serial.println(responses);      
             //Serial.print(responses[9]);        
        }
        else         
        {
            Serial.printf("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
        }
        http.end();
        return responses;        
}
