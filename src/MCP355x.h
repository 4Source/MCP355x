//----------------------------------------------------
// File:  MCP355x.h
// Version:   v0.1.1
// Change date: 25.09.2021
// Autor:     4Source
// Homepage:  github.com/4Source
//----------------------------------------------------

#ifndef MCP355x_h
#define MCP355x_h

#include "Arduino.h"
#include <SPI.h>

class MCP355x {
	private:
		uint8_t pin_CS;
		uint8_t pin_SDO;
		
		uint8_t mode_CONVERSION;		//HIGH: Single Conversion Mode || LOW: Continuous Conversion Mode
		uint8_t mode_SPI;
		uint32_t mode_SPI_SPEED;
		
		uint8_t state_READY;
		
		union{
			int32_t value;
			uint8_t bytes[4];
			  
		} c ;

	public:
		MCP355x(uint8_t, uint8_t, uint8_t, uint8_t, uint32_t);
		
		void begin();
		void end();
		bool checkState();
		bool isReady();

		int32_t getValue();
};
#endif
