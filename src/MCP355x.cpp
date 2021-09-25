//----------------------------------------------------
// File:  MCP355x.cpp
// Version:   v0.1.1
// Change date: 25.09.2021
// Autor:     4Source
// Homepage:  github.com/4Source
//----------------------------------------------------
#include "MCP355x.h"

MCP355x::MCP355x(uint8_t cs, uint8_t sdo, uint8_t conversionMode, uint8_t spiMode, uint32_t spiClockSpeed){
	//Save Values
	pin_CS = cs;
	pin_SDO = sdo;	
	mode_CONVERSION = conversionMode;
	mode_SPI = spiMode;
	mode_SPI_SPEED = min(spiClockSpeed, 5000000);
	
	//Setup PINs
	pinMode(pin_SDO, INPUT);  					//SDO as Input
	pinMode(pin_CS, OUTPUT);  					//CS as Output

	digitalWrite(pin_CS, HIGH);

	//Setup SPI
	SPI.begin();
}

void MCP355x::begin(){
	digitalWrite(pin_CS, LOW);
	
	if(mode_CONVERSION == HIGH) {				//Single Conversion
		while(!checkState()){					//Whait for RDY-Bit 
			digitalWrite(pin_CS, HIGH);
			delay(1);
			digitalWrite(pin_CS, LOW);
			delay(1);
		}
	}
}

void MCP355x::end(){
	digitalWrite(pin_CS, HIGH);
}

bool MCP355x::checkState(){
	if(digitalRead(pin_SDO) == LOW){
		SPI.beginTransaction(SPISettings(mode_SPI_SPEED, MSBFIRST, mode_SPI));
		digitalWrite(pin_CS, LOW);	
		
		if(mode_SPI == SPI_MODE0){				//Read Data with SPI_MODE0
			c.bytes[3] = SPI.transfer(0x00);
			c.bytes[2] = SPI.transfer(0x00);
			c.bytes[1] = SPI.transfer(0x00);
			c.bytes[0] = SPI.transfer(0x00);
			c.value >>= 7;
			
			if((c.bytes[3] & (1 << 5)) || (c.bytes[3] & (1 << 6))){		//Check OVL | OVH 
				
			}
		}
		else if(mode_SPI == SPI_MODE3){			//Read Data with SPI_MODE3
			c.bytes[2] = SPI.transfer(0x00);
			c.bytes[1] = SPI.transfer(0x00);
			c.bytes[0] = SPI.transfer(0x00);
			SPI.transfer(0x00);
			c.bytes[3] = 0x00;
		}
		
		if(mode_CONVERSION == HIGH){
			digitalWrite(pin_CS, HIGH);			//Go Shutdown
		}
		SPI.endTransaction();
		state_READY = true;
	}
	return state_READY;
}

bool MCP355x::isReady(){
	return state_READY;
}

int32_t MCP355x::getValue(){
	state_READY = false;
	return c.value;
}


	
	
	
	