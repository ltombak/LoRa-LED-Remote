# LoRa LED Remote
 Change the color of an LED with a button on a remote arduino.

 The developpment board used in this project is the UCA Education Board provided by Fabien Ferrero (see https://github.com/FabienFerrero/UCA_Education_Board).
 This board is powered by an ATMega328p and has a LoRa modem (RFM95) with antenna built-in. Ther is also some buttons and LEDs.

 The LEDs are ws2812b which are adressable RGB LED.

 The goal of this mini project was to be able to control the color of a LED wirelessly. To do that, I used LoRa PHY technology.

 On one card, when you press a button a message is sent to the other card and the LEDs change their colors in the following order: RED-GREEN-BLUE-OFF.

 The Code for the LoRa PHY part is available in the UCA_Education_Board repository.

 This project was made @FablabUCA, fablab of the Université Côte d'Azur, Nice, France.
