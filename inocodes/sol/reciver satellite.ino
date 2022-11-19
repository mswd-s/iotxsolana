#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
struct package
{
  float temperature ;
  float humidity ;
};

typedef struct package Package;
Package data;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
   // char text[32] = "";
    radio.read(&data, sizeof(data));
    Serial.print("Humidity  ");
    Serial.print(data.humidity);
    Serial.print("      Temperature  ");
    Serial.println(data.temperature);
    delay(1000);
    
    
  }
  
}