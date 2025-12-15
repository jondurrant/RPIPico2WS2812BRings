# RPIPico2WS2812BRings
These are some demo's and experiments with a set of WS2812B LED Rings setup as a circle of LEDs.
There are 241 LED in total: 1+8+12+16+24+32+40+48+60 and I sourced this from [AliExpress](https://s.click.aliexpress.com/e/_c30FJsNx)

I've connected them to GPIO PIN 19 via a logic level shifter. All of the examples use that.

More on this on my YouTube channe [DrJonEA](https://youtube.com/@drjonea).

For a guide on cloning and building this and other of my repos see the [guide](https://drjonea.co.uk/2025/12/15/building-my-projects-from-repo/) on my blog.

## Examples
### Animations
A collection of animations each one running for 10 seconds

### Map
Demonstration of mapping the rings of LED to a normalised grid and framebuffer.

### Rings
Test of each of the rings

### Rotating Arcs
Using the rings as seperate LED strip and making an Arc light and rotate on each ring

### Santa
Using the MAP to draw an image (originated from a png) onto the circle of LEDs. So translating the regular rectangle to the visible cicle.

### Snowflake1
A simple snowflake drawing algorithm.