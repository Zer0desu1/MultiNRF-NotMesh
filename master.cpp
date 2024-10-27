#include <iostream>
#include <RF24/RF24.h>
#include <unistd.h>

using namespace std;
//This is master rpi code
// CE and CSN 
RF24 radio(22, 0);


const uint8_t addresses[][6] = {"1Node", "2Node","3Node"};  

void setup() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();  
}

void send_data() {
    for (int i = 0; i < 3; ++i) {  
        radio.openWritingPipe(addresses[i]); 
        
        string message = "Hello " + string((char*)addresses[i]);
        bool result = radio.write(message.c_str(), message.length() + 1);  // Send the message
        

        if (result) {
            cout << "Message sent to " << (char*)addresses[i] << ": " << message << endl;
        } else {
            cout << "Failed to send message to " << (char*)addresses[i] << endl;
        }
        usleep(100000);  
    }
}

int main(int argc, char** argv) {
    setup();
    while (true) {
        send_data();
        sleep(1);  
    }
    return 0;
}
