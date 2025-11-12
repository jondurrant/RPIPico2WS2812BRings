/*
 * main.cpp
 * Drive 12 WB2812B on GP15
 * Produce a chaser pattern
 *
 *  Created on: 15 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>
#include <VirtualStrip.hpp>
#include "Ring.h"
#include <math.h>
#include "ColorUtils.h"


//#define LEDS_PIN 18
//#define LEDS_LENGTH 24
#define LEDS_PIN 19
#define LEDS_LENGTH 241



int main(){

	stdio_init_all();

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(32);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0xF0 ));
	ledStrip.show();
	sleep_ms(2000);

	//1+8+12+16+24+32+40+48+60
	int start = 0;
	int end =  60 ;
	PicoLed::PicoLedController ring60 = ledStrip.slice(start, end);
	start = end;
	end = start + 48;
	PicoLed::PicoLedController ring48 = ledStrip.slice(start,  end);
	start = end;
	end = start + 40 ;
	PicoLed::PicoLedController ring40 = ledStrip.slice(start, end);
	start = end;
	end = start + 32 ;
	PicoLed::PicoLedController ring32 = ledStrip.slice(start, end);
	start = end;
	end = start + 24 ;
	PicoLed::PicoLedController ring24 = ledStrip.slice(start, end);
	start = end;
	end = start + 16 ;
	PicoLed::PicoLedController ring16 = ledStrip.slice(start, end);
	start = end;
	end = start + 12 ;
	PicoLed::PicoLedController ring12 = ledStrip.slice(start, end);
	start = end;
	end = start + 8 ;
	PicoLed::PicoLedController ring8 = ledStrip.slice(start, end);
	start = end;
	end = start  + 1;
	PicoLed::PicoLedController ring1 = ledStrip. slice(start, end);


	Ring rings[9];
	rings[0].setLeds(&ring60);
	rings[0].setColor(PicoLed::RGB(0xE5, 0, 0));

	rings[1].setLeds(&ring48);
	rings[1].setColor(PicoLed::RGB(0xFF, 0x8D, 0));
	rings[1].setRadOffset(M_PI);

	rings[2].setLeds(&ring40);
	rings[2].setColor(PicoLed::RGB(0xFF, 0xEE, 0));
	rings[2].setRadOffset(M_PI/2.0);

	rings[3].setLeds(&ring32);
	rings[3].setColor(PicoLed::RGB(0x00, 0x81, 0x21));
	rings[3].setRadOffset(M_PI/-2.0);

	rings[4].setLeds(&ring24);
	rings[4].setColor(PicoLed::RGB(0x00, 0x4c, 0xFF));
	rings[4].setRadOffset(M_PI/4.0);

	rings[5].setLeds(&ring16);
	rings[5].setColor(PicoLed::RGB(0x76, 0x0, 0x88));
	rings[5].setRadOffset(M_PI/-4.0);

	rings[6].setLeds(&ring12);
	rings[6].setColor(PicoLed::RGB(0xF5, 0xAB, 0xB9));
	rings[6].setRadOffset(M_PI/3.0);

	rings[7].setLeds(&ring8);
	rings[7].setColor(PicoLed::RGB(0x5B, 0xCF, 0xFB));
	rings[7].setRadOffset(M_PI/-3.0);


	uint8_t r,g,b;
	for (;;){
		for (float f=0.0; f < M_PI *2.0; f+=0.1){
			for (int i=0;  i<8; i++){
				float r = f;
				if (i%2 != 0){
					r = (M_PI * 2) - f;
				}
				rings[i].drawArc(r);
			}
			ColorUtils::valToRGB(f/(M_PI * 2.0), r, g, b);
			ring1.setPixelColor(0, PicoLed::RGB(r,g,b));

			ledStrip.show();
			sleep_ms(20);
		}
	}


}
