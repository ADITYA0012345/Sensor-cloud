#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>
#define pulse D3 
#define DHTPIN D4 
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  
const char* ssid = "******";  
const char* password = "***********"; 
 
WiFiClient client;  
unsigned long myChannelNumber = *******;  
const char * myWriteAPIKey = "*****************";  
volatile int Pulse;
uint8_t temperature, humidity;  
void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");   
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop()   
{    
  Pulse = analogRead(pulse);
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%"); 
  Serial.print("BPM: ");
  Serial.println(Pulse);
   ThingSpeak.writeField(myChannelNumber, 1, Pulse, myWriteAPIKey);
   delay(15000);
   ThingSpeak.writeField(myChannelNumber, 2, temperature, myWriteAPIKey); 
   delay(15000);
   ThingSpeak.writeField(myChannelNumber, 3, humidity, myWriteAPIKey);
     
 
  delay(15000); 

