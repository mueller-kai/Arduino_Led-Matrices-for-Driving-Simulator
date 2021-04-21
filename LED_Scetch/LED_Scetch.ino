#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 1728
#define NUMMATRIX 1536
#define col_count 96
#define row_count 16

//include functions
uint16_t rowcol( uint8_t row, uint8_t col);
void itterthroughleds(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);
void arrowright(uint8_t red, uint8_t green, uint8_t blue);
void arrowleft(uint8_t red, uint8_t green, uint8_t blue);



//include other files
#include "remap.h"

//initialize unsort leds string. For troubleshooting so to keep this code most similar to original this
//will stay out of setup()
Adafruit_NeoPixel unsort_leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  unsort_leds.begin();
  // End of trinket special code
}

void loop() {
  arrowleft(0, 100, 100);
  //arrowright(0, 100, 100);
  //itterthroughleds(100, 100, 0, 10);
}


//___________________________________Functions_____________________________________

//function that transform a row and colum input into a single integer in the array
uint16_t rowcol( int row, int col)
{
  uint16_t i; 
  i = col_count * row + col;
  return i;
}

//itterate through the sorted LED Matrix from [0][0] to [row_count-1][col_count-1]
void itterthroughleds(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{   
    for(int row = 0; row < row_count; row++)
    {
        for (int col = 0; col < col_count; col++)
        {
            unsort_leds.setPixelColor((sort_leds[rowcol(row,col)]), unsort_leds.Color(red, green, blue));
            unsort_leds.show();
            delay(wait);
        }
    }
}

//Animate a right arrow on Matrix
void arrowright(uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t thickness= 4;
  for(uint8_t animation = 0; animation< col_count; animation ++)
  {
    //print ann arrow point to the right on the left side of the matrix
    for (uint8_t row = 0; row < row_count; row++)
    {
        if(row <= 7)
        {
          for (int col = 0; col <= thickness; col++)
          {   
              unsort_leds.setPixelColor((sort_leds[rowcol(row,col+ row + animation)]), unsort_leds.Color(red, green, blue));
          }
        }
        
        else
        {
          for (uint16_t col = 0; col <= thickness; col++)
          {
              unsort_leds.setPixelColor((sort_leds[rowcol(row, row_count - row + col - 1 + animation)]), unsort_leds.Color(red, green, blue));
          }
        }
    }
    unsort_leds.show();
    delay(10);
    unsort_leds.clear();
  }
}

//Animate a left arrow on Matrix
void arrowleft(uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t thickness = 4;

  for(uint8_t animation = 0; animation <= col_count -1; animation++)
  { 
    //print an arrow pointing to the left, on the right side of the matrix
    for(uint8_t row = 0; row < row_count; row++)
    {
      if(row <= 7)
      {
        for(uint8_t col = col_count-1; col >= col_count-1 - thickness; col--)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row, col - row - animation)]), unsort_leds.Color(red, green, blue));
        }
      }
      else
      {
        for(uint8_t col = col_count-1; col >= col_count-1 - thickness; col--)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row, col - row_count + row + 1 - animation)]), unsort_leds.Color(red, green, blue));
        }
      }
    }
    unsort_leds.show();
    delay(1); 
    unsort_leds.clear();
  //colsing to 8 animation loops
  }
  return;
}
