//a very basic hydrostat using the DHT11 sensor, this can be used on the ATTINY AVR chips comfirmed working
// uses basic timer functions to make sure a condition has been present for a certain time to prevent "cycling"
#include <dht11.h>
dht11 DHT11;
int humidity=0;
const int dhtpin=A0;// the pin the signal wire of the dht11 is hooked into
const int relay=13;// relay switch,whatever
const int trigger=75;// the humidty to trigger the output on
unsigned long timenow=0;
unsigned long countdowntimer=0;
unsigned long thresholdtimer=0;
unsigned long senseinterval=0;

void setup() {
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
}

void loop() {
 timenow=millis();
 checkhumidity();
 relayfunctions();
}

void checkhumidity(){
  if(timenow-senseinterval>=5000){
  senseinterval=timenow;
  DHT11.read(dhtpin);
  humidity = DHT11.humidity;
  Serial.println(humidity);
}
}

void relayfunctions(){
  if(humidity>=trigger){
    if(timenow>=thresholdtimer){
      digitalWrite(relay,HIGH);
      countdowntimer=timenow+12000;
    }
  }else{
    thresholdtimer=timenow+15000;
    if(timenow>=countdowntimer){
      digitalWrite(relay,LOW);
    }
  }
}
