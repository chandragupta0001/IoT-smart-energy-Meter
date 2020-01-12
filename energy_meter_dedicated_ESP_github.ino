
// energy meter IoT device code , to be run on NOde mcu
//serial communication with arduino
//Author: Chandragupta, chandragupta0001@gmail.com
#include <CayenneMQTTESP8266.h>

char ssid[] = "Radar";
char wifiPassword[] = "radar1234@";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "";
char password[] = "";
char clientID[] = "";

unsigned long lastMillis = 0;
 int x=1;
 float power=0;
 float power1=0;
 
void setup() {
	Serial.begin(115200);
 pinMode(2,OUTPUT);// to be connected to relay1
 pinMode(0,OUTPUT);// to be connected to relay2(if you want two lines to be controlled)
 
digitalWrite(2,HIGH);// setting to high as default
digitalWrite(0,HIGH);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
	Cayenne.virtualWrite(0,1);// writing on ceyenne that line is connected
 Cayenne.virtualWrite(2,1);
}

void loop() {
     
     int i=0;
     int j=0;
     // this loop will read data from serial communication
      while (Serial.available() > 0)
      {
           
          j=(Serial.read()-48)+j*10;
           i++;
           power=j;
      }  
     // sometime garbage value may come, to filter out-
   if(power>=0 && power<=1000000){
     
   
    Cayenne.virtualWrite(3,power/100);
    Cayenne.virtualWrite(1,power/100);
    Cayenne.virtualWrite(2,digitalRead(2));
    Cayenne.virtualWrite(0,digitalRead(0));
   }
	Cayenne.loop();

	
	}


//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
digitalWrite(request.channel,getValue.asInt());
x=getValue.asInt();
/*if(getValue.asInt()==0)
{  Cayenne.virtualWrite(0,0);
    Cayenne.virtualWrite(1,0);
    power1=power;
    power=0;
}
if(getValue.asInt()==1){
   Cayenne.virtualWrite(0,power1/100);
    Cayenne.virtualWrite(1,power1/100);
    power=power1;
}*/
//Serial.println("chandragupta");
//Serial.println(request.channel*1000+getValue.asInt());
} 
