int pin=4;// to read signal from energy meter
#include <SoftwareSerial.h>
SoftwareSerial swSer(2,3);//rx tx

float duration;
int timeout=100000;
float power1;
unsigned long power;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  swSer.begin(115200);
 

}

void loop() {
  // put your main code here, to run repeatedly:
duration = pulseIn(pin, LOW, timeout);

power1=(1125/duration)*1000000;// my energy meter has meter constant of 36000 impulse per kilo watt hour, heb=nce 1125 comes during calaculation to convert those impulse to power
 power=power1*100;
 swSer.print(power);
 Serial.println(power);
 delay(150);
 
}
