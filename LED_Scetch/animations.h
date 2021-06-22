#ifndef animations
#define animations

//include other files
#include "remap.h"

//define the Neopixel array of LEDs that are connected to PIN 6
//this needs to be defined in animations.h otherwise IDE will trough an Error
Adafruit_NeoPixel unsort_leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//_____________________________functions___________________________
//__________these functions animate Objects on the matrix__________



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
void arrow_right(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness, uint8_t animation_speed)
{
  //The Animation will only count to 32, because if an instance is animated 32 columns to thr right is is exactly in the place of the next arrow.
  //For example: The first arrow is not visible in the matrix because it is drawn in the buffer zone, but if it is animated 32 columns o the right it is exactly in the position of the second arrow.
  //At this point all arrows (execpt the fourth) have reached the position of their right neighbour arrow, therefore the animation can be started again from 0.
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed)
  {
    //drawing 4 instances of the arrow
    for(uint8_t instance = 0; instance < 4; instance++)
    {
      //print ann arrow point to the right on the left side of the matrix
      for (uint8_t row = matrixbuffer; row < row_count; row++)
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
void arrow_left(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness, uint8_t animation_speed)
{
  //The Animation will only count to 32, because if an instance is animated 32 columns to thr right is is exactly in the place of the next arrow.
  //For example: The first arrow is not visible in the matrix because it is drawn in the buffer zone, but if it is animated 32 columns o the right it is exactly in the position of the second arrow.
  //At this point all arrows (execpt the fourth) have reached the position of their right neighbour arrow, therefore the animation can be started again from 0.
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed)
  {
    //draw 4 instances of an arrow
    for(uint8_t instance = 0; instance < 4; instance++)
    
      //print an arrow pointing to the left, on the right side of the matrix
      for(uint8_t row = matrixbuffer; row < row_count - matrixbuffer; row++)
      {
        if(row <= 23)
        {
          //TO DO why does a thickness of 5 lead to a thickness of 4 
          for(uint8_t col = col_count-1 - (row - matrixbuffer); col > col_count - (row - matrixbuffer) - thickness -1; col--)
          {
            unsort_leds.setPixelColor((sort_leds[rowcol(row, col - animation - (instance * 32))]), unsort_leds.Color(red, green, blue));
          }//col - row + matrixbuffer  - animation - (instance_of_arrow * 32)
        }
        else
        {
          for(uint8_t col = col_count - (32 - row); col > col_count - (32 - row) - thickness -1 ; col--)
          {
            unsort_leds.setPixelColor((sort_leds[rowcol(row, col - animation - (instance * 32) + 1)]), unsort_leds.Color(red, green, blue));//+1 to ensure symtery
          }//- row_count - matrixbuffer + row + 1 - animation - (instance_of_arrow * 32)
        }
      }
    unsort_leds.show();
    delay(1); 
    unsort_leds.clear();
  }
}


//animate arrow top right
void arrow_topright(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness, uint8_t animation_speed)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed) 
  {
    for(uint8_t instance = 0; instance < 3; instance++)
    {
      //print a box
      for(uint8_t row = 32; row < row_count -1; row ++) //1 row from bottom is cropped to ensure symetry
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
void arrow_topleft(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness, uint8_t animation_speed)
{
  uint8_t wideness = 16;
  //animate the arrow
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed)
  {
    //to avoid the first arrow to be animated and drawn instance will start at 1.
    for(uint8_t instance = 1; instance < 4; instance++)
    {    
      
      //draw A BOX
      for(uint8_t row = 32; row < row_count -1; row++) //1 row from bottom is cropped to ensure symetry
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
void arrow_downright(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness, uint8_t animation_speed)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed) 
  {
    for(uint8_t instance = 0; instance < 3; instance++)
    {
      //print a box
      for(uint8_t row = 1; row < row_count - 32; row ++)//cropp row 0 from arrow to ensure symetry
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
void arrow_downleft(uint8_t red, uint8_t green, uint8_t blue,uint8_t thickness, uint8_t animation_speed)
{
  //wideness from left to right
  uint8_t wideness = 16;
  for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed) 
  {
    //to keep the first arrow from beeing drawn, instance starts at 1
    for(uint8_t instance = 1; instance < 4; instance++)
    {
      //print a box
      for(uint8_t row = 1; row < row_count - 32; row ++)//1row is croped to ensure symetry
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


//animate an arrows down
void arrow_down(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness, uint8_t animation_speed)
{
  uint8_t arrow_height = 16;
  uint8_t arrow_width = 32;
  
 for(uint8_t animation = 0; animation < 32; animation = animation + animation_speed)
 {
      for(uint8_t instances = 0; instances < 4; instances++)
      {
          //Draw a box
          for(uint8_t row = 1; row < arrow_height; row++)
          {
            for(uint8_t col = matrixbuffer; col < 48; col ++)
            {
               {
               unsort_leds.setPixelColor((sort_leds[rowcol(row+ animation, col + (instances*32))]), unsort_leds.Color(red, green, blue)); 
               }
            }
          }
          
          //darken Pixels creating a trinangle 
          for(uint8_t row = 0; row < 32; row++)
          {
            for(uint8_t col = matrixbuffer; col < row + matrixbuffer; col++)
            {
              unsort_leds.setPixelColor((sort_leds[rowcol(row+ animation, col+(instances*32))]), unsort_leds.Color(0, 0, 0)); 
            }
          }
          for(uint8_t row = 0; row < 32; row++)
          {
            for(uint8_t col = 48; col  > 48 - row ; col--)
            {
              unsort_leds.setPixelColor((sort_leds[rowcol(row+animation, col+(instances*32))]), unsort_leds.Color(0, 0, 0)); 
            }
          }
          
          //Darken pixels further to create arrow
          for(uint8_t row = 0; row < arrow_height - thickness; row++)
          {
            for(uint8_t col = (row +1) + thickness + matrixbuffer; col < (arrow_width + matrixbuffer)  - thickness - row; col++)
            {
              unsort_leds.setPixelColor((sort_leds[rowcol(row + animation, col + (instances*32))]), unsort_leds.Color(0, 0, 0));
            }
          }
      }
    unsort_leds.show();
    delay(1);
    unsort_leds.clear();
  } 
}


//Draw an arrow straight ahead
void arrow_ahead(uint8_t red, uint8_t green, uint8_t blue, uint8_t thickness, uint8_t animation_speed)
{
  uint8_t arrow_height = 16;
  uint8_t arrow_width = 32;

         for(uint8_t animation = 0; animation < 33; animation = animation + animation_speed)
         {
            for(uint8_t instances = 0; instances < 4; instances++)
            {
              //draw box
              for(uint8_t row = 32; row < row_count -1; row++)
              {
                for(uint8_t col = 16; col < 48; col ++)
                {
                   {
                   unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col + (instances*32))]), unsort_leds.Color(red, green, blue)); 
                   }
                }
              }
              //darken pixels to create a triangle
              for(uint8_t row = 32; row < row_count; row++)
              {
                for(uint8_t col = matrixbuffer; col <  arrow_width + (arrow_width - row) - 1; col++)
                {
                  unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col+ (instances*32))]), unsort_leds.Color(0, 0, 0));
                }
              }
              for(uint8_t row = 32; row < row_count; row++) 
              {
                for(uint8_t col = 48; col > 32 + (row - 32);col--)
                {
                  unsort_leds.setPixelColor((sort_leds[rowcol(row  -animation, col + (instances*32))]), unsort_leds.Color(0, 0, 0));
                }
              }

            //darken pixels to create an arrow
            for(uint8_t row = row_count - 1; row > row_count - 1 - arrow_height + thickness; row--)
            { 
              for(uint8_t col = 16 + thickness + (row_count - 1 - row) ; col < (arrow_width + matrixbuffer) - thickness - (row_count - 1 - row); col++)
              {
                unsort_leds.setPixelColor((sort_leds[rowcol(row - animation, col + (instances*32))]), unsort_leds.Color(0, 0, 0));
              }
            }
          }
  unsort_leds.show();
  delay(1);
  unsort_leds.clear();
     }
}

void lights_show()
{
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
}

//____________________OLD Arrows Dumping space ______________________

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
