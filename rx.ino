#include <RadioLib.h>

#define IR_sensor 5
#define RFM95_MISO 12 //data från LoRa till arduino
#define RFM95_MOSI 11 //data från arduino till LoRa
#define RFM95_RST 2
#define RFM95_INT 3   //interrupt pin
#define RFM95_CS 4    //varje enhet koppladtill arduinon behöver en CS pin, enheten är slav om pinen är LOW
#define RFM95_G1 6

//instantierar radion
RFM95 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST, RFM95_G1);
void setup() {
  Serial.begin(9600);

  // initialize SX1278 with defult settings
  Serial.print(F("[RFM95] Initializing ... "));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {

  //Serial.print(F("[RFM95] Waiting for incoming transmission ... "));

  // you can receive data as an Arduino String
  // NOTE: receive() is a blocking method!
  //       See example ReceiveInterrupt for details
  //       on non-blocking reception method.
  String str;
  int state = radio.receive(str);

  // you can also receive data as byte array
  /*
    byte byteArr[8];
    int state = radio.receive(byteArr, 8);
  */
  if (state == ERR_NONE) {
    // packet was successfully received
    //Serial.println(F("success!"));

    // print the data of the packet
    Serial.print(F("[RFM95] Data:\t\t\t"));
    Serial.println(str);

    // print the RSSI (Received Signal Strength Indicator)
    // of the last received packet
    Serial.print(F("[RFM95] RSSI:\t\t\t"));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));

    // print the SNR (Signal-to-Noise Ratio)
    // of the last received packet
    Serial.print(F("[RFM95] SNR:\t\t\t"));
    Serial.print(radio.getSNR());
    Serial.println(F(" dB"));

    // print frequency error
    // of the last received packet
    Serial.print(F("[RFM95] Frequency error:\t"));
    Serial.print(radio.getFrequencyError());
    Serial.println(F(" Hz"));

  } else if (state == ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    //Serial.println(F("timeout!"));

  } else if (state == ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
}
