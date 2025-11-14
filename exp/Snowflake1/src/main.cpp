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
#include "mapping.h"


//#define LEDS_PIN 18
//#define LEDS_LENGTH 24
#define LEDS_PIN 19
#define LEDS_LENGTH 241

#define FRAME_SIZE 17



uint32_t framebuffer[FRAME_SIZE][FRAME_SIZE] = {0};
auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);


void cross(){
	for (int i=0; i < FRAME_SIZE; i++){
		framebuffer[i][8] = 0xFF0000;
		framebuffer[8][i] = 0x00FF00;
	}
}


void drawFrameBuffer(){
	for (int i=0; i < LEDS_LENGTH; i++){
		uint8_t x =  CIRCLIE_MAPPING[i][0];
		uint8_t y =  CIRCLIE_MAPPING[i][1];

		uint32_t c = framebuffer[x][y];
		uint8_t b = c & 0xFF;
		uint8_t g = (c >> 8) & 0xFF;
		uint8_t r = (c  >> 16) & 0xFF;

		ledStrip.setPixelColor( i,  PicoLed::RGB(r,g,b));
	}
}

void clearFrame(){
    for (int i = 0; i < FRAME_SIZE; i++)
        for (int j = 0; j < FRAME_SIZE; j++)
        	framebuffer[i][j] = 0;
}

void snowflake(uint32_t c) {
    clearFrame();

    // Generate 1/8th of the snowflake (top-left triangle)
    for (int i = 0; i <= FRAME_SIZE / 2; i++) {
        for (int j = 0; j <= i; j++) {
            uint32_t pixel = (rand() % 2) ? c : 0;
            framebuffer[i][j] = pixel;

            // Mirror across vertical
            framebuffer[i][FRAME_SIZE - 1 - j] = pixel;
            // Mirror across horizontal
            framebuffer[FRAME_SIZE - 1 - i][j] = pixel;
            // Mirror across both
            framebuffer[FRAME_SIZE - 1 - i][FRAME_SIZE - 1 - j] = pixel;
            // Mirror across diagonal
            framebuffer[j][i] = pixel;
            framebuffer[FRAME_SIZE - 1 - j][i] = pixel;
            framebuffer[j][FRAME_SIZE - 1 - i] = pixel;
            framebuffer[FRAME_SIZE - 1 - j][FRAME_SIZE - 1 - i] = pixel;
        }
    }
}




int main(){

	stdio_init_all();

    // Initialize LED strip


	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(32);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0xF0 ));
	ledStrip.show();
	sleep_ms(2000);

	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));

	cross();
	drawFrameBuffer();
	ledStrip.show();
	sleep_ms(2000);



	uint32_t colours[] = {
			0x505050,
			0x5050A0,
			0x705050,
			0x507050,
			0x0202A0
	};


	for (;;){
		for (int c = 0; c < 5; c++){
			snowflake(colours[c]);
			drawFrameBuffer();
			for (int i=0; i < 100; i++){
				ledStrip.show();
				sleep_ms(20);
			}
		}
	}


}
