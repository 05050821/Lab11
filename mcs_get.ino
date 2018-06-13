#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Kuo";
char _lwifi_pass[] = "0966526920";
MCSDevice mcs("D9WhZZ4g", "K0I0M27gyTQhSAtL");

MCSControllerOnOff led("pin");
MCSDisplayOnOff remote("recive");
void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
  

    mcs.connect();
  }
  Serial.println("MCS Connected!");
  mcs.addChannel(led);
  mcs.addChannel(remote);

  pinMode(7, OUTPUT);
  while(!mcs.connected())
  {
    Serial.println("MCS.connect()...");
    mcs.connect();
  }

}


void loop()
{
  while(!led.valid())
{
    Serial.println("read LED value from MCS...");
    led.value();   //取得MCS數值
}
Serial.print("done, LED value = ");
Serial.println(led.value());  //顯示出來
digitalWrite(7,led.value() ? HIGH : LOW);


  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);

  if (led.value() == 1) {
    digitalWrite(7, HIGH);

  } else {
    digitalWrite(7, LOW);

  }
  if(!remote.set(led.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(remote.value());
    }

  delay(200);
}
