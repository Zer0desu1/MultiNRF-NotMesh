#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins

const byte slaveAddress[6] = "1Node";  

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, slaveAddress);
    radio.startListening();
}

void loop() {
    if (radio.available()) {
        char text[32] = "";  
        radio.read(&text, sizeof(text));
        Serial.print("Received: ");
        Serial.println(text);
    }
    delay(100);  
}
