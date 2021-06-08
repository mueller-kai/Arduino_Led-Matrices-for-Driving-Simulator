#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 1728
#define NUMMATRIX 1536
#define matrixbuffer 16
#define col_count 128
#define row_count 48

//include other files
#include "remap.h"
#include "animations.h"

/*include functions
uint16_t rowcol( uint8_t row, uint8_t col);
void itterthroughleds(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);
void arrow_right(uint8_t red, uint8_t green, uint8_t blue);
void arrow_left(uint8_t red, uint8_t green, uint8_t blue);
*/

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  unsort_leds.begin();
}

void loop() {
  arrow_ahead(0, 100, 100, 6);
  //arrow_downleft (0, 100, 100, 4);
  //arrow_downright(0, 100, 100, 4);
  //arrow_topleft(0, 100, 100, 4);
  //arrow_topright(0, 100, 100, 4);
  //arrow_right(0, 100, 100);
  //arrow_left(0, 100, 100, 4);
  //arrow_right(0, 100, 100, 4);
  //itterthroughleds(100, 100, 0, 1);
}
