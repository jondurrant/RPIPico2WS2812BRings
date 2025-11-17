/*
 * main.cpp
 * Drive  WB2812B on GP19
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>
#include "ColorUtils.h"



#define LEDS_PIN 19
#define LEDS_LENGTH 241



int main(){
	uint8_t r,g,b;

	stdio_init_all();

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(32);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));
	ledStrip.show();
	sleep_ms(2000);


	for (;;){
		for (int i=0; i < LEDS_LENGTH; i++){
			ColorUtils::valToRGB(
					(double)i / (double) LEDS_LENGTH,
					r, g, b
					);
			ledStrip.setPixelColor(i , PicoLed::RGB(r,g,b));
			ledStrip.show();
			sleep_ms(100);
		}
		sleep_ms(2000);
		ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));
		ledStrip.show();
	}


}
