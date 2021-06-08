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

  arrow_ahead(0, 255, 255, 5, 1);
  arrow_down(0, 255, 255, 5, 1);
  arrow_downleft (0, 255, 255, 4, 1);
  arrow_downright(255, 255, 0, 4, 1);
  arrow_topleft(255, 0, 255, 4, 1);
  arrow_topright(0, 255, 255, 4, 1);  

  arrow_right(0, 0, 255, 4, 1);
  arrow_right(255, 0, 0, 6, 1);
  arrow_right(0, 0, 255, 10, 1);
  
  arrow_left(255, 255, 0, 4, 1);
  arrow_left(255, 0, 255, 8, 1);
  arrow_left(0, 255, 255, 6, 2);
  arrow_left(255, 0, 255, 6, 2);
  arrow_left(255, 255, 0, 6, 2);
  arrow_left(255, 0, 255, 6, 2);
  arrow_left(100, 100, 50, 6, 2);
    
  arrow_ahead(10, 10, 10, 5, 1);
  arrow_ahead(0, 255, 255, 10, 2);
  delay(10000);
 
  //itterthroughleds(100, 100, 0, 1);

}
