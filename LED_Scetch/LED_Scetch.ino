
//Include CAN Bus Libs
#include <SPI.h>//SPI is used to talk to the CAN Controller
#include <mcp_can.h>

//set SPI Chip Select to pin 10
MCP_CAN CAN(10);
//declare Variables for CAN Bus Communication
unsigned char len = 0; //create variable for length of msg
unsigned char buf[8]; //create buffer space (8 bytes big) to later asigned to the read msg to
                      //Datatype char is used to safe space: char = 8 bits, int = 16 bits
unsigned int canID;  //create space for ID of CAN msg
unsigned char incoming_msg;//ceate space for incoming msg dont get confused by char  type. Char is just used to only create 8 bits of space. The space will later be used by an int!

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

void setup() {
// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

// This code sets up the connection between Arduino and CAN-BUS
/*
Serial.begin(115200);   //to communicate with Serial monitor

//tries to initialize, if failed --> it will loop here for ever
START_INIT:
    if(CAN_OK == CAN.begin(CAN_500KBPS))      //setting CAN baud rate to 500Kbps
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
*/

//Initialise LED Array
unsort_leds.begin();
}

void loop() {

//This code loops as long as arduino is active
if(CAN_MSGAVAIL == CAN.checkReceive())        //check if data coming
{
    CAN.readMsgBuf(&len, buf);    //read data,  len: data length, buf: data buffer the Information in the message will be written to buf 
    canID = CAN.getCanId();       //getting the ID of the incoming message
    
    //Checking for ID, What ID we need to check for is declared in the Code for the
    //Navigation System
    if (canID == 0xF1 )
    {
      //Print some Information about the msg
      Serial.print("ID is: ");
      Serial.print(canID, HEX);     //printing the ID in its standard form, HEX
      Serial.print("Length is: ");
      Serial.println(len);

      //Check the first 8 Bit/ 1 byte of the msg. See documentation for further explenation
      incoming_msg = buf[0];
      //check what number has been sent and do the corresponding animation
      switch(incoming_msg)
      {
        case 1: arrow_ahead(0, 255, 255, 5, 1); break;
        case 2: arrow_down(0, 255, 255, 5, 1); break;
        case 3: arrow_right(0, 255, 255, 4, 1); break;
        case 4: arrow_left(0, 255, 255, 4, 1); break;
        case 5: arrow_topleft(0, 255, 255, 4, 1); break;
        case 6: arrow_topright(0, 255, 255, 4, 1); break;
        case 7: arrow_downleft (0, 255, 255, 4, 1); break;
        case 8: arrow_downright(0, 255, 255, 4, 1); break;
        default: Serial.print("Mesage did not match any of the cases"); break;
      }
      
      
    }
  }

}
