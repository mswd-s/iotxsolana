//Receiver coding for the nrf24L01 radio transceiver.
//Hello World Example
// https://www.electroniclinic.com/
/*
pins connections

vcc 3.3
gnd gnd
ce pin9
scn pin10
sck pin13
mosi pin11
moso pin12


*/
#include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 #define CE_PIN 9
 #define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);

char data[50] = "";

void setup()
 {
 Serial.begin(9600);
 delay(1000);
 Serial.println("Nrf24L01 Receiver Starting");
radio.begin();
 radio.openReadingPipe(1,pipe);
 radio.startListening();;
 }

void loop()
 {
 if ( radio.available() )
 {
 bool done = false;
 while (!done)
 {
 done = radio.read( data, sizeof(data) );
Serial.println(data);
 }
 }
 else
 {
 Serial.println("No radio available");
 }
 }
