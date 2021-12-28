#include <WiFiManager.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define nameofdevice "Device 1"

FirebaseData firedb;


int status;

void setup()
{
  status = 1;
  pinMode(D2, OUTPUT);
  pinMode(A0, INPUT);
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  WiFiManager wm;

  bool res;

  res = wm.autoConnect("Air Pollution Detector", "pollution");
  if (!res) {
    Serial.println("Failed to connect");
  }
  else {
    Serial.println("connected...yeey :)");
    Firebase.begin( "firebaseio.com", "auth");
    Serial.println("Firebase Connected");
  }

}

void loop()
{

  int value = analogRead(A0);
  Serial.println(value);

    if (status == 1)    {
        if (value > 700)
        {
          Firebase.setString(firedb, "/database/Device 1/Pollution Level", "Device1" );
          Firebase.setString(firedb, "/database/alerts", "Device1" );
          digitalWrite(D2,HIGH);
          status = 0;
        }
    }
else{
    if (value < 700 )
    {

        status = 1;
                  digitalWrite(D2,LOW);

     }
}
delay(1000);
}
