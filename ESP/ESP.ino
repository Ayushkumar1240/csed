#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <WiFiClient.h>
#define ACCEPT_TYPE "text/csv"
WiFiClient client;
String data;
const char ssid[] = "GLA-CSED";
const char password[] = "GLACAMPUS";

const char host[] = "172.16.78.20";  //dcs.glaitm.org - Domain Name
const int httpPort = 7080;
const char appKey[]= "2c80c7e7-18c1-4f61-b023-90daa914070f";

const char Thing[] = "csed_fan_automation_thing";
const char Property1[] = "Humidity";
const char Property2[] = "Temperature";
const char Property3[] = "Switch";

void setup()
{
  Wire.begin(4,5);  
  Serial.begin(115200);
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

}


void loop()
{
  Wire.requestFrom(8, 11); //Address,Number of bytes(Character)  //0x08 = 8;
  data = "";
  while (0 < Wire.available())
  {
    char c = Wire.read();
    data += c;
  }
  String Hum = data.substring(0,4);
  String Temp = data.substring(6,10);
  float h = Hum.toFloat();
  float t = Temp.toFloat();
  Serial.print("Humidity = ");
  Serial.print(Hum);
  Serial.print("\t");
  Serial.print("Temeperature = ");
  Serial.println(Temp);
  
  Put(Thing,Property1,h);
  Put(Thing,Property2,t);

  String res = Get(Thing,Property3);
  Serial.print(res); //fan_control,0
  Serial.println(res[10]);
 
 
  Wire.beginTransmission(8);
  Wire.write(res[10]);
  Wire.endTransmission();

  delay(1000);
}

void Put(String ThingName, String ThingProperty, float Value)
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
  String url = "/Thingworx/Things/" + ThingName + "/Properties/" + ThingProperty;
  Serial.print("requesting URL: ");
  Serial.println(url);

  String strPUTReqVal = "{\"" + ThingProperty + "\":\"" + Value + "\"}";  
  Serial.print("PUT Value: ");
  Serial.println(strPUTReqVal);

  client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "appKey:"+ appKey + "\r\n" +
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
