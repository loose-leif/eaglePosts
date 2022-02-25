// /***************************************************
// Copyright (c) 2018 Luis Llamas
// (www.luisllamas.es)
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
//  ****************************************************/
 
//  #include "I2CScanner.h"

//  #include<ADS1115_WE.h> 
//  #include<Wire.h>
//  #include "string.h"
//  #define I2C_ADDRESS 0x48	

// I2CScanner scanner;
// ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);


// void setup() 
// {
// 	Serial.begin(9600);
// 	while (!Serial) {};

// 	scanner.Init();

// 	if(!adc.init()){
//     Serial.println("ADS1115 not connected!");
//     }

// 	adc.setVoltageRange_mV(ADS1115_RANGE_6144);
// 	adc.setCompareChannels(ADS1115_COMP_0_GND);
// 	adc.setMeasureMode(ADS1115_CONTINUOUS);
// 	Serial.println("ADS1115 Example Sketch - Continuous Mode");
//   	Serial.println("All values in volts");
//   	Serial.println();
// }

// void loop() 
// {
// 	//scanner.Scan();

// 	float testADC;

// 	testADC = readChannel(ADS1115_COMP_0_GND);

// 	Serial.println(testADC);

// 	String testString = "";

// 	testString.concat(testADC);

// 	char john[50] = {};
	
// 	testString.toCharArray(john, testString.length());

// 	Wire.beginTransmission(2);

// 	Wire.write(john);

// 	Wire.endTransmission();

// 	delay(3000);

// }

// float readChannel(ADS1115_MUX channel) {
//   float voltage = 0.0;
//   adc.setCompareChannels(channel);
//   voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
//   return voltage;
// }
