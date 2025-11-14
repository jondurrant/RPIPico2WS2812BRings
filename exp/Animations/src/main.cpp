/*
 * main.cpp
 * Drive 12 WB2812B on GP15
 * Produce a chaser pattern
 *
 *  Created on: 15 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"

#include "Canvas.h"

#include "Animation.h"
#include "Santa.h"
#include "Snowflakes.h"
#include "Arcs.h"
#include "Bauble.h"

#define ANIM_TIME 10000


auto controller  = PicoLed::addLeds<PicoLed::WS2812B>(
		pio0,
		0,
		LEDS_PIN,
		LEDS_LENGTH,
		PicoLed::FORMAT_GRB);


int main(){

	stdio_init_all();

    Canvas canvas(&controller);
	Santa santa(&canvas);
	santa.poll();
	canvas.show();
	sleep_ms(6000);

	Snowflakes snowflakes(&canvas);

	Arcs arcs(&canvas);

	Bauble bauble(&canvas);

	Animation * pAnim[4] = {
			&santa,
			&arcs,
			&snowflakes,
			&bauble
	};

	int animInx = 0;
	uint32_t last = to_ms_since_boot (get_absolute_time());
	for (;;){
		uint32_t now = to_ms_since_boot (get_absolute_time());
		if ((last + ANIM_TIME) < now){
			last = now;
			animInx++;
			if (animInx > 3){
				animInx = 0;
			}
			pAnim[animInx]->reset();
		}
		pAnim[animInx]->poll();
		sleep_ms(20);

	}

}
