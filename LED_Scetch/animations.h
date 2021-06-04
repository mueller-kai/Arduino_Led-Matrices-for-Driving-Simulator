#ifndef animations.h
#define animations.h

//include other files
#include "remap.h"

//define the Neopixel array of LEDs that are connected to PIN 6
Adafruit_NeoPixel unsort_leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//_____________________________functions___________________________
// __________these functions animate Arrows on the matrix__________



//function that transform a row and colum input into a single integer in a sorted array
uint16_t rowcol(int row, int col)
{
  uint16_t i; 
  i = col_count * row + col;
  return i;
}

uint8_t height_limiter(uint8_t input)
{
  uint8_t limiter;
  limiter = (16 - input)/ 2;
  return limiter;
}

//itterate through the sorted LED Matrix from [0][0] to [row_count-1][col_count-1]
void itterthroughleds(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{   
    for(int row = 16; row < row_count -16; row++)
    {
        for (int col = 16; col < col_count - 16; col++)
        {
            unsort_leds.setPixelColor((sort_leds[rowcol(row,col)]), unsort_leds.Color(red, green, blue));
            unsort_leds.show();
            delay(wait);
        }
    }
}

//arrow_right
void arrow_right(uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t thickness= 4;
  for(uint8_t animation = 0; animation< col_count; animation ++)
  {
    //drawing 4 instances of the arrow
    for(uint8_t instance = 0; instance < 4; instance++)
    {
      //print ann arrow point to the right on the left side of the matrix
      for (uint8_t row = 16; row < row_count; row++)
      {
          if(row <= 23)
          {
            for (int col = 0 ; col <= thickness; col++)
            {   
                unsort_leds.setPixelColor((sort_leds[rowcol(row,col+ row - matrixbuffer + animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
            }
          }
          
          else
          {
            for (uint16_t col = 0 ; col <= thickness; col++)
            {
                unsort_leds.setPixelColor((sort_leds[rowcol(row, row_count - row - matrixbuffer + col - 1 + animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
            }
          }
      }
    }
    unsort_leds.show();
    delay(1);
    unsort_leds.clear();
  }
}

//Animate a left arrow on Matrix

//TO BE DONE

void arrow_left(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness)
{
  for(uint8_t animation = 0; animation <= col_count -1; animation++)
  {
    //draw 4 instances of an arrow
    for(uint8_t instance_of_arrow = 0; instance_of_arrow < 4; instance_of_arrow++)
    
      //print an arrow pointing to the left, on the right side of the matrix
      for(uint8_t row = 16; row < row_count - matrixbuffer; row++)
      {
        if(row <= 23)
        {
          for(uint8_t col = col_count-1 - (instance_of_arrow * 24); col >= col - thickness; col--)
          {
            unsort_leds.setPixelColor((sort_leds[rowcol(row, col - row + matrixbuffer  - animation)]), unsort_leds.Color(red, green, blue));
          }
        }
        else
        {
          for(uint8_t col = col_count-1 - (instance_of_arrow * 24); col >= col - thickness; col--)
          {
            unsort_leds.setPixelColor((sort_leds[rowcol(row, col - row_count - matrixbuffer + row + 1 - animation)]), unsort_leds.Color(red, green, blue));
          }
        }
      }
    unsort_leds.show();
    delay(1); 
    unsort_leds.clear();
  }
}

//animate arrow top right
void arrow_topright(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation++) 
  {
    for(uint8_t instance = 0; instance < 3; instance++)
    {
      //print a box
      for(uint8_t row = 32; row < row_count; row ++)
      {
        for(uint8_t col = 0; col < wideness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col + animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
        }
      }
  
      //darken leds in bottom left corner to create an arrow
      for(uint8_t row = 32 + thickness; row < row_count; row ++)
      {
        for(uint8_t col = 0; col < wideness - thickness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col + animation + (instance * 32))]), unsort_leds.Color(0, 0, 0));
        }
      }
    }
      unsort_leds.show();
      delay(1);
      unsort_leds.clear();
  }
}

//animate arrow pointing top left
void arrow_topleft(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness)
{
  uint8_t wideness = 16;
  //animate the arrow
  for(uint8_t animation = 0; animation < 32; animation++)
  {
    //to avoid the first arrow to be animated and drawn instance will start at 1.
    for(uint8_t instance = 1; instance < 4; instance++)
    {    
      
      //draw the arrow
      for(uint8_t row = 32; row < row_count; row++)
      {
        for(uint8_t col = 0; col < wideness; col++)
        {
           unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col - animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
        }
      }
    
      //darken pixels in bottom right to create an arrow pointing to top left
      for(uint8_t row = 32 + thickness; row < row_count; row++)
      {
        for(uint8_t col = thickness; col < wideness; col++)
        {
           unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col - animation + (instance * 32))]), unsort_leds.Color(0, 0, 0));
        }
      }
    }
   unsort_leds.show();
   delay(1);
   unsort_leds.clear();
  }
}

//animate arrow pointing down right
void arrow_downright(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation++) 
  {
    for(uint8_t instance = 0; instance < 3; instance++)
    {
      //print a box
      for(uint8_t row = 0; row < row_count - 32; row ++)
      {
        for(uint8_t col = 0; col < wideness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row + animation, col + animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
        }
      }
  
      //darken leds in bottom left corner to create an arrow
      for(uint8_t row = 0; row < row_count -32 -thickness; row ++)
      {
        for(uint8_t col = 0; col < wideness - thickness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row + animation, col + animation + (instance * 32))]), unsort_leds.Color(0, 0, 0));
        }
      }
    }
      unsort_leds.show();
      delay(1);
      unsort_leds.clear();
  }
}

//animate arrow pointing down left
void arrow_downleft(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation++) 
  {
    //to keep the first arrow from beeing drawn, instance starts at 1
    for(uint8_t instance = 1; instance < 4; instance++)
    {
      //print a box
      for(uint8_t row = 0; row < row_count - 32; row ++)
      {
        for(uint8_t col = 0; col < wideness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row + animation, col - animation + (instance * 32))]), unsort_leds.Color(red, green, blue));
        }
      }
  
      //darken leds in bottom left corner to create an arrow
      for(uint8_t row = 0; row < row_count -32 -thickness; row ++)
      {
        for(uint8_t col = thickness; col < wideness; col++)
        {
          unsort_leds.setPixelColor((sort_leds[rowcol(row + animation, col - animation + (instance * 32))]), unsort_leds.Color(0, 0, 0));
        }
      }
    }
      unsort_leds.show();
      delay(1);
      unsort_leds.clear();
  }
}

//draw an arrow strainght ahead
//TO BE DONE
void arrow_ahead(uint8_t red, uint8_t green, uint8_t blue)
{
  for(uint8_t row = 16; row < 32; row++)
  {
    for(uint8_t col = 16; col < 48; col ++)
    {
       {
       unsort_leds.setPixelColor((sort_leds[rowcol(row, col)]), unsort_leds.Color(red, green, blue)); 
       }
    }
  }
  //darken Pixels
  for(uint8_t row = 16; row < 32; row++)
  {
    for(uint8_t col = 16; col < row; col++)
    {
      unsort_leds.setPixelColor((sort_leds[rowcol(row, col)]), unsort_leds.Color(0, 0, 0)); 
    }
  }
  
  for(uint8_t row = 16; row < 32; row++)
  {
    for(uint8_t col = 48; col  > 64 - row ; col--)
    {
      unsort_leds.setPixelColor((sort_leds[rowcol(row, col)]), unsort_leds.Color(0, 0, 0)); 
    }
  }
  
  unsort_leds.show();
  delay(1);
  unsort_leds.clear();
}



//____________________OLD Arrow Dumping space ______________________

/*
//Animate a right arrow on Matrix
void arrow_right(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness)
{
  for (int8_t animation = 0; animation < col_count; animation ++)
  {
    //draw 4 instances of the arrow on the board
    for (uint8_t instances_of_arrow = 0; instances_of_arrow < 4; instances_of_arrow++)
    {
      //print an arrow point to the right on the left side of the matrix. The arrow is drawn in the buffer zone therfore, you will not see it until animated.
      for (uint8_t row = 16; row < row_count - matrixbuffer; row++)
      { 
          //check if its the upper half of the arrow
          if(row <= 23)
          {
            for (int col = 0 + (instances_of_arrow * 24); col <= col + thickness; col++)
            {   
                unsort_leds.setPixelColor((sort_leds[rowcol(row, col+ row - matrixbuffer + animation)]), unsort_leds.Color(red, green, blue));
            }
          }
          else
          {
            for (uint16_t col = 0 + (instances_of_arrow * 24); col <= col + thickness; col++)
            {   
                unsort_leds.setPixelColor((sort_leds[rowcol(row, row_count - row + matrixbuffer + col - 1 + animation)]), unsort_leds.Color(red, green, blue));
            }
          }
      }
    }
  unsort_leds.show();
  delay(10);
  unsort_leds.clear();
  }
}
*/

#endif
