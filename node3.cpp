#include <iostream>
#include <RF24/RF24.h>
#include <unistd.h>

using namespace std;

// CE and CSN 
RF24 radio(22, 0);

const uint8_t slaveAddress[6] = "3Node";  

void setup() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, slaveAddress);
    radio.startListening();
}

void receive_data() {
    if (radio.available()) {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        cout << "Received: " << text << endl;
    }
}

int main(int argc, char** argv) {
    setup();
    while (true) {
        receive_data();
        usleep(100000);  
    }
    return 0;
}
