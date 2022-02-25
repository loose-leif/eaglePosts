#include "Wire.h"


void receiveEvent(){

    while(1 < Wire.available()){

        char c = Wire.read();
        Serial.print(c);

    }

    char c = Wire.read();
    Serial.println(c);

}

void setup(){

    Wire.begin(2);
    Wire.onReceive(receiveEvent);
    Serial.begin(9600);

}

void loop(){

    delay(1000);

}

