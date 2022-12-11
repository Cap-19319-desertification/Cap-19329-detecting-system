#include <WiFi.h>
#include <FirebaseESP32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WIFI_SSID "OMEN"
#define WIFI_PASSWORD "12345678"

#define FIREBASE_HOST "https://cap-2-7a769-default-rtdb.firebaseio.com"


#define FIREBASE_AUTH "c3AFtz9vr8vmx8I7hNVqvKcFIYcIOfXW6LCXRUHe"


FirebaseData fbdo;

String output = "output";

#define ONE_WIRE_PIN 35
OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);





unsigned long time1;


const int dry =3250 ; 
const int wet = 2060;

#define sensor  34 

float gas_value;





void setup()
{

  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);

  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  time1=millis();
 
delay(20000);

}



void loop(){

sensors.requestTemperatures();
 

int sensorVal = analogRead(33);
int percentageHumididy = map(sensorVal, wet, dry, 100, 0);

gas_value=analogRead(sensor);
float gas_value_ppm = map(gas_value, 0, 4095, 0, 10000);





          
           if(millis()-time1>=1000){
           Firebase.setInt(fbdo, output + "/Humidity", percentageHumididy );
           Firebase.setFloat(fbdo, output + "/Methane concentration", gas_value_ppm );
           Firebase.setFloat(fbdo, output + "/Celsius temperature", sensors.getTempCByIndex(0) );
        
            time1=millis();
          
           }
          
           
  //    Firebase.end(fbdo); 
  
}
