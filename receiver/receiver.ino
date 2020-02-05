#include <SPI.h>
#include <LoRa.h>
#include <FastLED.h>


#define NUM_LEDS 9
#define DATA_PIN 4
CRGB leds[NUM_LEDS];
int chgcompt = 0;

int counter = 0;

// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 7; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8
String payload = "hello"; // you can change the payload

// RFM95 parameters, do not change
#define SS 10
#define RST 8
#define DI0 2
#define BAND 865E6  // Here you define the frequency carrier

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //The LEDs used are ws2812b, refer to FastLED library to change it
  while (!Serial);

  Serial.println("LoRa Receiver");
  Serial.print("SetFrequency : ");
  Serial.print(BAND);
  Serial.println("Hz");
  Serial.print("SetSpreadingFactor : SF");
  Serial.println(spreadingFactor);


  SPI.begin();
  LoRa.setPins(SS,RST,DI0);


  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 LoRa.setTxPower(txPower,1);
 LoRa.setSpreadingFactor(spreadingFactor);
 LoRa.setSignalBandwidth(signalBandwidth);
 LoRa.setCodingRate4(codingRateDenominator);
 LoRa.setPreambleLength(preambleLength);

}

void loop() {
  String message = ""; //To save the messages received by LoRa modem


   // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      //Serial.print((char)LoRa.read());
      message = String(message + (char)LoRa.read());//Saving the message to check it later
    }
    Serial.print(message);
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    Serial.println(chgcompt);//chgcompt is used to change the color of the LEDs always in the same cycle

    if(message == "Red")
    {
      Serial.println(chgcompt);
      Serial.println("Changement de couleur");
      chgcompt++;
      Serial.println(chgcompt);
      if(chgcompt == 0)
      {
        for(int i=1; i <9; i++)
        {
          leds[i] = CRGB::Black;// LEDs are OFF
        }
        FastLED.show();
      }
      else if(chgcompt == 1)
      {
        for(int i=1; i <9; i++)
        {
          leds[i] = CRGB::Red;
        }
        FastLED.show();
      }
      else if(chgcompt == 2)
      {
        for(int i=1; i <9; i++)
        {
          leds[i] = CRGB::Green;
        }
        FastLED.show();
      }
      else if(chgcompt == 3)
      {
        for(int i=1; i <9; i++)
        {
          leds[i] = CRGB::Blue;
        }
        FastLED.show();
        chgcompt = -1;
      }
    }
  }
}
