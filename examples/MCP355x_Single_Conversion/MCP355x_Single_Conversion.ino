//----------------------------------------------------
// File:  MCP355x Single Conversion
// Version:   v0.1.0
// Change date: 15.07.2021
// Autor:     4Source
// Homepage:  github.com/4Source
//----------------------------------------------------

//PINs
#define CS 8
#define SDO 12
#define SCK 13

#define CONVERSION_MODE HIGH            //HIGH: Single Conversion Mode || LOW: Continuous Conversion Mode
#define SPI_MODE SPI_MODE0              //SPI_MODE 1,1 (3): 24 Clocks  3 byte OL OH 21 20 ... 1 0 ||SPI_MODE 0,0 (0): 25 Clocks 4 byte DR OL OH 21 20 ... 1 0 x x x x x x x
#define SPI_CLOCK 500000   				//max. Speed is 5MHz

#include <MCP355x.h>

MCP355x adc(CS, SDO, CONVERSION_MODE, SPI_MODE, SPI_CLOCK);

void setup() {
	//Setup Serial Communication
	Serial.begin(9600);
	adc.begin();
}

void loop() {
	if(adc.isReady()){
		Serial.println(adc.getValue());
	}

}