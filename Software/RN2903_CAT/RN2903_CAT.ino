/* 5 Feb 2017   Zaki   Support for Single Channel Packet Forwarder */
/*
  Sample Code for RN2903 LoRa Shield
  Edited by Somboon Sopee, Micro4you.com
  Aug 16, 2018.
*/
#include "LoRaWAN.h"
#include <SoftwareSerial.h>

#define ON 1
#define OFF 0

//************** Device parameters for registration *****************
char DEVICE_ADDR[] = "0021E880";  //4 bytes required
char NWK_SESSION_KEY[] = "28AED22B7E1516A609CFABF715884F3C"; // 16 bytes required
char APP_SESSION_KEY[] = "1628AE2B7E15D2A6ABF7CF4F3C158809"; //16 bytes required
char APP_KEY[] = "1628AE2B7E15D2A6ABF7CF4F3C158809"; //16 bytes required
char APP_EUI[] =  "1628AE2B7E15D2A6";  //8 bytes required

char txData[]="05689f066701F5";      //sample data to be transmitted - must be hexadecimal values **see more Cayenne LPP

LoRaWAN LoRaWAN(8,9); // Software Serial RX, TX   ** Set to 8, 9 for Arduino Uno R3 board
void setup() { 


delay(1000);                //startup delay - gives Lora module time to reset if cold start
Serial.begin(9600);        //terminal serial port, 9600 = Default, 57600 = Haxiot shield

//LoRaWAN.LoRaResetModule();                          //restore module to factory default settings and reset device
LoRaWAN.LoRaDeviceEUI();                            //retrieves EUI from module and auto sets 
LoRaWAN.LoRaDevAddr(DEVICE_ADDR);                   //sets device addresss
LoRaWAN.LoraApplicationEUI(APP_EUI);                //sets application EUI
LoRaWAN.LoRaNetworkSessionKey(NWK_SESSION_KEY);     //sets network session key
LoRaWAN.LoRaApplicationSessionKey(APP_SESSION_KEY); //sets application session key
LoRaWAN.LoRaApplicationKey(APP_KEY);                //sets application key
LoRaWAN.LoRaAdaptiveDataRate(ON);      //set to ON to enable, OFF to disable
LoRaWAN.LoRaTXPower(20);                //dBM 10(Min), 12, 14, 16, 18, 20(Max)
LoRaWAN.LoRaChannelPlan(0,7);          //(start channel, end channel) - channel range 0 to 63
LoRaWAN.LoRaSaveConfig();                           //save configuration settings to module eeprom

//************* Connect to LoRaWAN Network Server****************//
// Comment out 
LoRaWAN.LoRaJoinABP ();       //Connect with Access By Personalization (ABP) networks
//LoRaWAN.LoRaJoinOTAA ();    //Connect with Over The Air Activation (OTAA) networks 


LoRaWAN.LoRaShowConfig();             //display current module configuration for debugging only

}

void loop() {

  //*************** Display received data from LoRaWAN 
  while (LoRaWAN.loraSerial.available()) {
    Serial.write(LoRaWAN.loraSerial.read());
  }
    delay(20000);
    //delay(20000);
    //delay(20000);
    //delay(20000);      
  {
      //*************** Display then transmit data to LoRaWAN
    Serial.print("Sending: ");Serial.println(txData);
    LoRaWAN.LoRaTransmit(1, 89, txData);   //type 0 = Confirmed, 1 = Unconfirmed / port number 1 to 223 / data payload
    delay(20000);
  }
}

