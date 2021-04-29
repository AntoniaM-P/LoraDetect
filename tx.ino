#include <RadioLib.h>

#define IR_sensor 5
#define RFM95_MISO 12 //data från LoRa till arduino
#define RFM95_MOSI 11 //data från arduino till LoRa
#define RFM95_RST 2
#define RFM95_INT 3   //interrupt pin
#define RFM95_CS 4    //varje enhet koppladtill arduinon behöver en CS pin, enheten är slav om pinen är LOW
#define FRM95_G1 6

//instantierar radion
RFM95 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST, FRM95_G1);

void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
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

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  // NOTE: transmit() is a blocking method!
  //       See example SX127x_Transmit_Interrupt for details
  //       on non-blocking transmission method.
  if(digitalRead(IR_sensor) == HIGH) {
    
  String str = "Rörelse hittad";
  int state = radio.transmit(str);

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    int state = radio.transmit(byteArr, 8);
  */

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F(" success!"));

    // print measured data rate
    Serial.print(F("[RFM95] Datarate:\t"));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));

  } else if (state == ERR_TX_TIMEOUT) {
    // timeout occurred while transmitting packet
    Serial.println(F("timeout!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  // wait for a second before transmitting again
  //delay(1000);
  }
}
