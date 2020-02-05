#include <SPI.h>
#include <LoRa.h>


int Pin_button_2 = 14;//Pin of BT2 on the UCA Education Board
int button_2;


int counter = 0;//Used for LoRa

// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 7; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8
String payload = "Red"; // you can change the payload

#define SS 10
#define RST 8
#define DI0 2
#define BAND 865E6  // Here you define the frequency carrier

void setup() {
  Serial.begin(115200);
  pinMode(Pin_button_2, INPUT);
  while (!Serial);

  Serial.println("LoRa Sender");
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
// LoRa.setPolarity(1);
 //LoRa.setFSK();

}

void loop() {
  button_2 = digitalRead(Pin_button_2);
  if(button_2 == 0)//When the button is pressed, the message is sent
  {
    delay(300);//If the delay is removed, you will not be able to chose the color (too fast)
    LoRa.beginPacket();
    LoRa.print(payload);

    LoRa.endPacket();
    counter++;

    Serial.print("Sending packet with payload {");
    Serial.print(payload);
    Serial.print("} N°");
    Serial.println(counter);
  }
}
