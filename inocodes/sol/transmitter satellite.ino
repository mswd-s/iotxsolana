#include "DHT.h"
#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>

#define DHTPIN 2 
#define DHTTYPE DHT11

RF24 radio (9, 10); // CE, CSN
const byte address[6] = "00001";
//const int led_pin = 13;

struct package
{
  float temperature ;
  float humidity ;
};


typedef struct package Package;
Package data;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
//    pinMode(led_pin, OUTPUT);
    dht.begin();
    radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening(); 
Serial.print("START STELLITE COMMUNICATION");
}



void loop()
{
//  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  readSensor();
  Serial.print("HUmidity   ");
  Serial.print(data.humidity);
  Serial.print("    Temperature  ");
  Serial.println(data.temperature);
  radio.write(&data, sizeof(data)); 
//  digitalWrite(led_pin, LOW);
  delay(100);
}

void readSensor()
{
 data.humidity = dht.readHumidity();
 data.temperature = dht.readTemperature();
}