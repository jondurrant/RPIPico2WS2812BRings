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

		if (i >=  LEDS_LENGTH -9){
			printf("%d= (%d,%d) = %lX (%X,%X,%X)\n", i, x, y, c,r,g,b);
		}

		ledStrip.setPixelColor( i,  PicoLed::RGB(r,g,b));
	}
}

void clearFrame(){
    for (int i = 0; i < FRAME_SIZE; i++)
        for (int j = 0; j < FRAME_SIZE; j++)
        	framebuffer[i][j] = 0;
}

void squares(int size=2){
	uint32_t colours[6] = {
			0xE50000,
			0xFF8d00,
			0xFFEE00,
			0x008121,
			0x004cff,
			0x760088
	};
	for (int x=0; x < FRAME_SIZE; x++){
		for (int y=0; y < FRAME_SIZE; y++){
			int sqr = (x / size + 1) * (y/size + 1) -1;
			int c = sqr %6;
			framebuffer[x][y] = colours[c];
		}
	}
}

void hzLine(int y=8){
	clearFrame();
	for (int x=0; x < FRAME_SIZE; x++){
		framebuffer[x][y] = 0x000000FF;
	}
}

void vtLine(int x=8){
	clearFrame();
	for (int y=0; y < FRAME_SIZE; y++){
		framebuffer[x][y] = 0x000000FF;
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


	for (;;){
		for (int sz=1; sz < 10; sz++){
			squares(sz);
		//for (int l=0; l < FRAME_SIZE; l++){
			//vtLine(l);
			drawFrameBuffer();
			for (int i=0; i < 100; i++){
				ledStrip.show();
				sleep_ms(20);
			}
		}
	}


}
