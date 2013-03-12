
#define galaxyversion 1.1 // version of this code. will be used for bluetooth handshake to determine capabilities
//flags
boolean demo = true;
boolean colordemo=false;
uint8_t compassdebug = 0;
boolean acceloutput=false;
int opmode=0; //0==normal ,1=menu,2=irsetup
boolean planeoutput=false;
boolean compassoutput=false;
boolean irsetupflag=false;
uint8_t calflag; //compass calibration flag. -1 = recalibrate compass;0=get raw calibration data;1=do nothing
boolean serialoutput=true;// will the serial respond?
boolean uartoutput=true;// will the uart respond?
//paramaters
int pattern = -1;
int nextspeed=0;
byte colorschemeselector = 0;
uint8_t brightness = 3; //lower=brighter
uint16_t patternswitchspeed = 1500; //# of frames between pattern switches
uint8_t patternswitchspeedvariance = 0;//# of frames the pattern switch speed can vary + and - so total variance could be 2x 
uint16_t transitionspeed = 30;// # of framestransition lasts 
uint8_t transitionspeedvariance = 0;// # of frames transition lenght varies by, total var 2X, 1X in either + or -

void (*renderEffect[])(byte) = {
  SparkleLights,
  Bam,
  IDK,
  FourColorStrobe,
  TwoColorStrobe,
  OneColorStrobe,
  SpreadPOV,//*****************************
  TimePOV,
  SlagPOV,
  AmericanFlagPOV,
  RingsPOV,
  ArrowPOV,//        These are
  MultiBoxPOV,//      New Patterns
  NewPOV,//            3-11-13
  CrossTheTPOV,
  TheBigDownPOV,
  TheBigDownSquarePOV,
  UpDownPOV,
  DoubleDimePOV,//**************************
  FourWayCheckersPOV,
  FourColorCheckersPOV,
  ZigZagPOV,
  CrazyCirclesPOV,
  testcolorPOV,
  colorflag,
  PlaidPOV,
  SmallCirclePOV,
  QuadHelixPOV,
  WavePOV,
  HeartPOV,
  MazePOV,
  StarPOV,
  WavyPOV,
  MoonPOV,
  CatPOV,
  OooPOV,
  ChainsPOV,
  MiniTriPOV,
  FourSquare,
  Checkerboard,
  FourSquare,
  Checkerboard,
  Slider,
  Smiley,
  Float,
  Zag,
  NewCircle,
  DoubleHelix,
  Bubbles,
  Move,
  DiagCheckers,
  /*
   * Fixed color patterns
   */
  sparklefade, 
  rainbowChase, //stock
  colorDrift,//fades the whole hoop quickly around the color wheel
  raindance,//changes speeds quickly and smoothly
  sineChase, //stock
  sineDance, //not set up to dance yet just a placeholder
  rainbowsineChase,//needs to be stretched to fit entire color wheel
  longsinechasecolordrift,//needs to be stretched to fit hoop
  colorDriftsineChase,//ok
  sineChase, //stock  
  wavyFlag,// stock
  simpleOrbit,//not sure whats going on here...
  sineCompass, //needs smoothing
  POV,
  /*
   * Color scheme responsive patterns
   */
  HeartPOV,
  MazePOV,
  StarPOV,
  WavyPOV,
  MoonPOV,
  CatPOV,
  OooPOV,
  ChainsPOV,
  MiniTriPOV,
  schemetest,//non moving
  fourfade,
  petechase,
  Whacky,
  //  halfrandom,
  //  quarterrandom,
  //  accelschemesparklefade,//increases in colors and brightness depending on how hard you shake it
  accelsparklefade,//increases in colors and brightness depending on how hard you shake it
  // compassschemesparklefade,
  //  eightfade,//eight going around leaving a train(broken)
  // blankfade,
  //  accel1,
  onefade,//one going around leaving a trail
  //schemesparklefadelong,
  schemesparklefade,
  schemetestfade,//needs to "dance"
  schemetestlongfade,//needs to "dance"
  mixColor8Chase,//almost sinechase but with my mixcolor8
  //is 4 byte * >> faster?
  who,//untested
  rainbowChase, //stock
  raindance,//smoothly picks a new speed every so often
  compassheading,//compass X,Y,Z mapped to one blip each
  compassheadingRGBFade,//fade RGB according to compass xyz
  Dice,//plane calculation 
  // what,
  // when,
  // where,
  // why,
  // how,
  //  schemestretch,//
  schemetest,//non moving
  schemetestlong,//non moving
  schemefade,//like color drift but for schemes
  MonsterHunter,
  pacman,   //mr pac man bounces back from end to end and builds 
  strobe, //strobes to color schemes
  fans, 
  scrolls,//need to replace with older version



  //##########in development###########
  // somekindaChase,
  //blank,
  // thingeyDrift,
  //  rotate,//not sure whats going on here
  //  rainStrobe2at1,
  //strobefans2at1,
  // schemetest2at1,
  //  MonsterStrobe2at1,
  //  schemetestlongrain2at1,
  // schemetestrain2at1,    

  // onespin,//not up to par
  // onespinfade,//interesting but not what i was going for
  //needs to store index and message string in progmem
  // 


}
,
(*renderAlpha[])(void) = {
  renderAlpha00,
  renderAlpha01,
  //  renderAlpha02 
};

//########################################################################################################################
/*
/*
 Smoothing
 Reads repeatedly from an analog input, calculating a running average
 and printing it to the computer. Keeps ten readings in an array and
 continually averages them.
 The circuit:
 * Analog sensor (potentiometer will do) attached to analog input 0
 Created 22 April 2007
 By David A. Mellis <dam@mellis.org>
 modified 9 Apr 2012
 by Tom Igoe
 http://www.arduino.cc/en/Tutorial/Smoothing
 This example code is in the public domain.
 */

/*
 * RGBConverter.h - Arduino library for converting between RGB, HSV and HSL
 * 
 * Ported from the Javascript at http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript
 * The hard work was Michael's, all the bugs are mine.
 *
 * Robert Atkins, December 2010 (ratkins_at_fastmail_dot_fm).
 *
 * https://github.com/ratkins/RGBConverter
 *
 */

/*

 
 HMC5883L_Example.pde - Examhsvple sketch for integration with an HMC5883L triple axis magnetomerwe.
 Copyright (C) 2011 Love Electronics (loveelectronics.co.uk)
 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*****************************************************************************/
// Example to control LPD8806-based RGB LED Modules in a strip
// Original code by Adafruit
// SPI additions by cjbaar
/*****************************************************************************/


// Example to control LPD8806-based RGB LED Modules in a strip; originally
// intended for the Adafruit Digital Programmable LED Belt Kit.
// REQUIRES //Timer1 LIBRARY: http://www.arduino.cc/playground/Code///Timer1
// ALSO REQUIRES LPD8806 LIBRARY, which should be included with this code.

// I'm generally not fond of canned animation patterns. Wanting something
// more nuanced than the usual 8-bit beep-beep-boop-boop pixelly animation,
// this program smoothly cycles through a set of procedural animated effects
// and transitions -- it's like a Video Toaster for your waist! Some of the
// coding techniques may be a bit obtuse (e.g. function arrays), so novice
// programmers may have an easier time starting out with the 'strandtest'
// program also included with the LPD8806 library.

#include "LSM303.h"
LSM303 compass;
LSM303::vector running_min = {
  2047, 2047, 2047}
, running_max = {
  -2048, -2048, -2048};



//ir remote stuffs
#include <IRremote.h>
int irrxpin=18;
IRrecv irrecv(irrxpin);
decode_results results;
#define ircsetup 6
unsigned long irc[ircsetup];
unsigned long irc2[ircsetup]= {
  0,0,0,0,0,0};
/*  2155864095,//sirius sat radio remote
 2155847775,
 2155815135,
 2155811055,
 2155860015,
 2155851855,
 2155827375,
 2155835535,
 2155868175,
 2155809015,
 2155831455}; */
/*
279939191,
 279928991,
 279937151,
 279933071,
 279941231,
 279912671,
 279949391,
 279920831,
 279965711,
 279904511,
 279961631}; //kenmore ac remote
 */
//boolean irsetupflag = false;


//##########eeprom stuffs
//using the eeprom code modified from
//http://www.openobject.org/opensourceurbanism/Storing_Data#Writing_to_the_EEPROM
#include <EEPROM.h>
unsigned long firstTwoBytes;
unsigned long secondTwoBytes;
//###########adafruit lpd8806 stuffs
#include <avr/pgmspace.h>
#include "SPI.h"
#include "LPD8806.h"
#include "TimerOne.h"
#include <Wire.h>
// Declare the number of pixels in strand; 32 = 32 pixels in a row. The
// LED strips have 32 LEDs per meter, but you can extend or cut the strip.
const int numPixels = 106;
#define numPixelsHolder numPixels;
uint8_t framecounter,framecounter1;
int rotationspeed;
int upperend;

// 'const' makes subsequent array declarations possible, otherwise there
// would be a pile of malloc() calls later.

// Instantiate LED strip; arguments are the total number of pixels in strip,
// the data pin number and clock pin number:
LPD8806 strip = LPD8806(numPixels);
int tCounter = 0;

// You can also use hardware SPI for ultra-fast writes by omitting the data
// and clock pin arguments. This is faster, but the data and clock are then
// fixed to very specific pin numbers: on Arduino 168/328, data = pin 11,
// clock = pin 13. On Mega, data = pin 51, clock = pin 52.
//LPD8806 strip = LPD8806(numPixels);
boolean back = false;
int crazycounter;
//#####################menu stuffs
uint8_t menuphase = 0,menuphase0 = 0,menuphase1 = 0,menuphase2 = 0;
//##############compass stuffs

int lmheading;
int plane,ax,ay,az,axlast,aylast,azlast;
boolean compassreadphase = 0;
uint16_t yzheadingdegrees,xzheadingdegrees,xyheadingdegrees,xyheadingdegreescalibrated,xyheadingdegreesmin,xyheadingdegreesmax,
xzheadingdegreescalibrated,xzheadingdegreesmin,xzheadingdegreesmax,
yzheadingdegreescalibrated,yzheadingdegreesmin,yzheadingdegreesmax,xyheadingdegreeslast,xzheadingdegreeslast,yzheadingdegreeslast;
float xyheading, xzheading ,yzheading,xyheadinglast, xzheadinglast ,yzheadinglast, xytravel,xztravel,yztravel;



//############### stuff for the averages for the accell
const int numReadingsax = 6;
const int numReadingsay = 6;
const int numReadingsaz = 6;
int readingsax[numReadingsax],readingsay[numReadingsay],readingsaz[numReadingsaz]; // the readings from the analog input
int indexax,indexay,indexaz; // the index of the current reading
int totalax,totalay,totalaz; // the running total
int averageax,averageay,averageaz;
//##############bluetooth serial port
HardwareSerial Uart = HardwareSerial();

//#############compass stuff
uint8_t error = 0;

//#############software debounce for the button and button
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
uint16_t debounceDelay = 200;
uint8_t button = 0;
uint8_t longbutton = 0;
uint8_t lastbuttonstate = 0;
char serInStr[35]; // array that will hold the serial input string
char urtInStr[35]; // array that will hold the serial input string


#define maroon 0x800000
#define dark red 0x8B0000
#define brown 0xA52A2A
#define firebrick 0xB22222
#define crimson 0xDC143C
#define red 0xFF0000
#define tomato 0xFF6347
#define coral 0xFF7F50
#define indian red 0xCD5C5C
#define lightcoral 0xF08080
#define darksalmon 0xE9967A
#define salmon 0xFA8072
#define lightsalmon 0xFFA07A
#define orangered 0xFF4500
#define darkorange 0xFF8C00
#define orange 0xFFA500
#define gold 0xFFD700
#define dark golden rod 0xB8860B
#define goldenrod 0xDAA520
#define palegolden rod 0xEEE8AA
#define darkkhaki 0xBDB76B
#define khaki 0xF0E68C
#define olive 0x808000
#define yellow 0xFFFF00
#define yellowgreen 0x9ACD32
#define darkolive green 0x556B2F
#define olivedrab 0x6B8E23
#define lawngreen 0x7CFC00
#define chartreuse 0x7FFF00
#define greenyellow 0xADFF2F
#define darkgreen 0x006400
#define green 0x00FF00
#define forestgreen 0x228B22
#define lime 0x00FF00
#define limegreen 0x32CD32
#define lightgreen 0x90EE90
#define palegreen 0x98FB98
#define darkseagreen 0x8FBC8F
#define mediumspringgreen 0x00FA9A
#define springgreen 0x00FF7F
#define seagreen 0x2E8B57
#define mediumaquamarine 0x66CDAA
#define mediumseagreen 0x3CB371
#define lightseagreen 0x20B2AA
#define darkslategray 0x2F4F4F
#define teal 0x008080
#define darkcyan 0x008B8B
#define aqua 0x00FFFF
#define cyan 0x00FFFF
#define lightcyan 0xE0FFFF
#define darkturquoise 0x00CED1
#define turquoise 0x40E0D0
#define mediumturquoise 0x48D1CC
#define paleturquoise 0xAFEEEE
#define aquamarine 0x7FFFD4
#define powderblue 0xB0E0E6
#define cadetblue 0x5F9EA0
#define steelblue 0x4682B4
#define cornflowerblue 0x6495ED
#define deepskyblue 0x00BFFF
#define dodgerblue 0x1E90FF
#define lightblue 0xADD8E6
#define skyblue 0x87CEEB
#define lightskyblue 0x87CEFA
#define midnightblue 0x191970
#define navy 0x000080
#define darkblue 0x00008B
#define mediumblue 0x0000CD
#define blue 0x0000FF
#define royalblue 0x4169E1
#define blueviolet 0x8A2BE2
#define indigo 0x4B0082
#define darkslateblue 0x483D8B
#define slateblue 0x6A5ACD
#define mediumslateblue 0x7B68EE
#define mediumpurple 0x9370DB
#define darkmagenta 0x8B008B
#define darkviolet 0x9400D3
#define darkorchid 0x9932CC
#define mediumorchid 0xBA55D3
#define purple 0x800080
#define thistle 0xD8BFD8
#define plum 0xDDA0DD
#define violet 0xEE82EE
#define magenta 0xFF00FF
#define orchid 0xDA70D6
#define mediumvioletred 0xC71585
#define palevioletred 0xDB7093
#define deeppink 0xFF1493
#define hotpink 0xFF69B4
#define lightpink 0xFFB6C1
#define pink 0xFFC0CB
#define antiquewhite 0xFAEBD7
#define beige 0xF5F5DC
#define bisque 0xFFE4C4
#define blanchedalmond 0xFFEBCD
#define wheat 0xF5DEB3
#define cornsilk 0xFFF8DC
#define lemonchiffon 0xFFFACD
#define lightgolden rod yellow 0xFAFAD2
#define lightyellow 0xFFFFE0
#define saddlebrown 0x8B4513
#define sienna 0xA0522D
#define chocolate 0xD2691E
#define peru 0xCD853F
#define sandybrown 0xF4A460
#define burlywood 0xDEB887
#define tanish 0xD2B48C
#define rosybrown 0xBC8F8F
#define moccasin 0xFFE4B5
#define navajowhite 0xFFDEAD
#define peachpuff 0xFFDAB9
#define mistyrose 0xFFE4E1
#define lavenderblush 0xFFF0F5
#define linen 0xFAF0E6
#define oldlace 0xFDF5E6
#define papayawhip 0xFFEFD5
#define seashell 0xFFF5EE
#define mintcream 0xF5FFFA
#define slategray 0x708090
#define lightslategray 0x778899
#define lightsteelblue 0xB0C4DE
#define lavender 0xE6E6FA
#define floralwhite 0xFFFAF0
#define aliceblue 0xF0F8FF
#define ghostwhite 0xF8F8FF
#define honeydew 0xF0FFF0
#define ivory 0xFFFFF0
#define azure 0xF0FFFF
#define snow 0xFFFAFA
#define black 0x000000
#define dimgrey 0x696969
#define grey 0x808080
#define darkgrey 0xA9A9A9
#define silver 0xC0C0C0
#define lightgrey 0xD3D3D3
#define gainsboro 0xDCDCDC
#define whitesmoke 0xF5F5F5
#define white 0xFFFFFF
// 256/8=32
// we are using roygbiv plus teal = roygtbiv, 2 steps between each primary except g&b
// each primary color and there are 8 colors which goes into 256 evenly; 256%8=0
long eightcolorschema[][8] PROGMEM={

  /*
  0 reserved for user color scheme
   1 Major
   2 Natural minor
   3 Harmonic minor
   4 Dorian
   5 Mixolydian
   6 Red-Green 1/4
   7 Green-Blue 1/4
   8 Blue-Red 1/4
   9 Red-Blue 1/2
   10 Green-Red 1/2
   11 Blue-Green 1/2
   12 Solid Red
   13 Solid Orange
   14 Solid Orange
   15 Solid Yellow
   16 Solid Green
   17 Solid Teal
   18 Solid Blue
   19 Solid Indigo
   20 Solid Violet
   21 Red and Black
   22 Orange and Black
   23 Yellow and Black
   24 Green and Black
   25 Teal and Black
   26 Blue and Black
   27 Indigo and Black
   28 Violet and Black
   29 Red and White
   30 Orange and White
   31 Yellow and White
   32 Green and White
   33 Teal and White
   34 Blue and White
   35 Indigo and White
   36 Violet and White  
   37 Rainbow
   */
  red,orange,yellow,green,teal,blue,indigo,violet,//placeholder for user color scheme
  //splitting a color wheel up into 3 sections 1 for each 
  //primary color, and then splitting each section in half 2 more times
  //gives us 12 different sections which is the same number of steps in halftones
  //between octaves. Major, minor, etc use 8 of the 12 spots. we have eight
  //colors per scheme. this set uses red as the root note
  //are always red.
  //
  //http://www.bandnotes.info/tidbits/scales/half-whl.htm
  //
  //  Major Scale: R, W, W, H, W, W, W, H
  //  Natural Minor Scale: R, W, H, W, W, H, W, W
  //  Harmonic Minor Scale: R, W, H, W, W, H, 1 1/2, H   (notice the step and a half)
  //  Dorian Mode is: R, W, H, W, W, W, H, W
  //  Mixolydian Mode is: R, W, W, H, W, W, H, W
  //1 to 5
  // major
  0xff0000,0x808000,0x00ff00,0x00c040,0x0040c0,0x4000c0,0xc00040,0xff0000,

  //natural minor
  0xff0000,0x808000,0x40c000,0x00c040,0x0040c0,0x0000ff,0x800080,0xff0000,

  //harmonic minor
  0xff0000,0x808000,0x40c000,0x00c040,0x0040c0,0x0000ff,0xc00040,0xff0000,

  //dorian mode
  0xff0000,0x808000,0x40c000,0x00c040,0x0040c0,0x4000c0,0x800080,0xff0000,

  //Mixolydian Mode
  0xff0000,0x808000,0x00ff00,0x00c040,0x0040c0,0x4000c0,0x800080,0xff0000,

  //6-11
  //0x80 is 50%, 0x40 is 25%, 0xc0 is 75%, 0x00 is 0% and ff is 100%, format 0xRRGGBB in hex 0-f
  //24-31 stretch between 2 primary colors 3 steps between and back
  //1st is primary1,
  //2nd  is 3/4 p1 and 1/4 p2.
  //3rd is a 5050 mix between the 2 primaries,
  //4th is 3/4 p2 and 1/4 p1, 
  //5th is second primary, 
  //6th is 3/4 p2 and 1/4 p1, 
  //7th is 50%p1 and 50%p2,  
  //8th is 3/4p1 and 1/4p2 , 
  //and 1th (9th %8 in getschemacolor) is first primary
  0xff0000,0xc04000,0x808000,0x40c000,0x00ff00,0x40c000,0x808000,0xc04000,//red p1 to green p2  1/4 increments
  0x00ff00,0x00c040,0x008080,0x0040c0,0x0000ff,0x0040c0,0x008080,0x00c040,//green p1 to blue p2 1/4 increments
  0x0000ff,0x4000c0,0x800080,0xc00040,0xff0000,0xc00040,0x800080,0x4000c0,//blue p1 to red p2 1/4 increments
  0xff0000,0x808000,0x00ff00,0x008080,0x0000ff,0x008080,0x00ff00,0x808000,//red to blue 1/2 increments
  0x00ff00,0x008080,0x0000ff,0x800080,0xff0000,0x800080,0x0000ff,0x008080,//green to red  1/2 increments
  0x0000ff,0x800080,0xff0000,0x808000,0x00ff00,0x808000,0xff0000,0x800080, //blue to green 1/2 increments

  //12-20 single color roygtbiv
  red,red,red,red,red,red,red,red,
  orange,orange,orange,orange,orange,orange,orange,orange,
  yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,
  green,green,green,green,green,green,green,green,
  teal,teal,teal,teal,teal,teal,teal,teal,
  blue,blue,blue,blue,blue,blue,blue,blue,
  indigo,indigo,indigo,indigo,indigo,indigo,indigo,indigo,
  violet,violet,violet,violet,violet,violet,violet,violet,

  //21-28 2 color roygtbiv and black
  red,0,red,0,red,0,red,0,
  orange,0,orange,0,orange,0,orange,0,
  yellow,0,yellow,0,yellow,0,yellow,0,
  green,0,green,0,green,0,green,0,
  teal,0,teal,0,teal,0,teal,0,
  blue,0,blue,0,blue,0,blue,0,
  indigo,0,indigo,0,indigo,0,indigo,0,
  violet,0,violet,0,violet,0,violet,0,

  //29-36 2 color roygtbiv and white
  red,white,red,white,red,white,red,white,
  orange,white,orange,white,orange,white,orange,white,
  yellow,white,yellow,white,yellow,white,yellow,white,
  green,white,green,white,green,white,green,white,
  teal,white,teal,white,teal,white,teal,white,
  blue,white,blue,white,blue,white,blue,white,
  indigo,white,indigo,white,indigo,white,indigo,white,
  violet,white,violet,white,violet,white,violet,white,

  red,orange,yellow,green,teal,blue,indigo,violet, //rainbow!


  //6 of 32
  //40-47

  //7 of 32
  //48-55

  //8 of 32
  //56-63

  //9 of 32
  //64-71

  //10 of 32
  //72-79

  //11 of 32
  //80-87

  //12 of 32
  //88-95

  //13 of 32
  //96-103

  //14 of 32
  //104-111

  //15 of 32
  //112-119

  //16 of 32
  //120-127

  //17 of 32
  //128-135

  //18 of 32
  //136-143

  //19 of 32
  //144-151

  //20 of 32
  //152-159

  //21 of 32
  //160-167

  //22 of 32
  //168-175

  //23 of 32
  //176-183

  //24 of 32
  //184-191

  //25 of 32
  //192-199

  //26 of 32
  //200-207

  //27 of 32
  //208-215

  //28 of 32
  //216-223

  //29 of 32
  //224-231

  //30 of 32
  //232-239

  //31 of 32
  //240-247

  //32 of 32
  //248-255

  //2 color shift alternating every other base
  red,purple,blue,purple,red,purple,blue,purple,
  red,yellow,green,yellow,red,yellow,green,yellow,
  green,cyan,blue,cyan,green,cyan,blue,cyan,



  azure,snow,lavender,aliceblue,honeydew,seashell,lightslategray,lavenderblush, //0

  red,green,blue,magenta,teal,yellow,white,black,//1
  grey,orange,seashell,peru,red,azure,black,silver,//2
  purple,black,green,black,purple,black,green,black,//3
  purple,white,green,white,purple,white,green,white,//4
  red,purple,blue,purple,red,purple,blue,purple,//5
  green,teal,blue,teal,green,teal,blue,teal,//6
  yellow,orange,white,cornflowerblue,mistyrose,gainsboro,whitesmoke,aliceblue,//7

};

//##############bitmap storage
/* string index of character table
 !"#$%&'()*+,-./ //start 0 end 15
 0123456789:;>=<? //start 16 end 31
 @ABCDEFGHIJKLMNO //start 32 end 47
 PQRSTUVWXYZ[ ]^_ //START 48 END 63
 `abcdefghijklmno //start 64 end 79
 pqrstuvwxyz{|}~~ //start 80 end 95
 */
//uint8_t message[2] ={2,2};
// led character definitions modified from http://www.edaboard.com/thread45151.html
// 5 data columns + 1 space
// for each character
//   why are we storing blank spaces?
 const byte rgbImages[][256] PROGMEM = {
  //who knows what that one is...
  0x7,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x7,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
  0x1,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,
  0x1,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
  0x1,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,
  0x1,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,
  0x1,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,
  0x1,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
  0x1,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,0x9,
  0x1,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,0xA,
  0x1,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB,
  0x1,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,0xC,
  0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,
  0x1,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,0xE,
  0x1,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
 
  //single 1color line
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,

0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,//PLAID 1
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,
0X1,0X1,0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,
0X2,0X2,0X1,0X1,0X3,0X3,0X1,0X1,0X4,0X4,0X1,0X1,0X5,0X5,0X1,0X1,

0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,//small circle
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,
0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,0X2,0X2,0X2,0X2,0X1,0X1,0X1,0X1,
0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,0X1,0X2,0X2,0X1,0X1,0X1,0X1,0X1,

0X0,0X1,0X1,0X1,0X1,0X1,0X1,0X0,0X2,0X3,0X3,0X3,0X3,0X3,0X3,0X2,//quad helix
0X1,0X0,0X1,0X1,0X1,0X1,0X0,0X1,0X3,0X2,0X3,0X3,0X3,0X3,0X2,0X3,
0X1,0X1,0X0,0X1,0X1,0X0,0X1,0X1,0X3,0X3,0X2,0X3,0X3,0X2,0X3,0X3,
0X1,0X1,0X1,0X0,0X0,0X1,0X1,0X1,0X3,0X3,0X3,0X2,0X2,0X3,0X3,0X3,
0X4,0X4,0X4,0X5,0X5,0X4,0X4,0X4,0X6,0X6,0X6,0X7,0X7,0X6,0X6,0X6,
0X4,0X4,0X5,0X4,0X4,0X5,0X4,0X4,0X6,0X6,0X7,0X6,0X6,0X7,0X6,0X6,
0X4,0X5,0X4,0X4,0X4,0X4,0X5,0X4,0X6,0X7,0X6,0X6,0X6,0X6,0X7,0X6,
0X5,0X4,0X4,0X4,0X4,0X4,0X4,0X5,0X7,0X6,0X6,0X6,0X6,0X6,0X6,0X7,
0X0,0X1,0X1,0X1,0X1,0X1,0X1,0X0,0X2,0X3,0X3,0X3,0X3,0X3,0X3,0X2,
0X1,0X0,0X1,0X1,0X1,0X1,0X0,0X1,0X3,0X2,0X3,0X3,0X3,0X3,0X2,0X3,
0X1,0X1,0X0,0X1,0X1,0X0,0X1,0X1,0X3,0X3,0X2,0X3,0X3,0X2,0X3,0X3,
0X1,0X1,0X1,0X0,0X0,0X1,0X1,0X1,0X3,0X3,0X3,0X2,0X2,0X3,0X3,0X3,
0X4,0X4,0X4,0X5,0X5,0X4,0X4,0X4,0X6,0X6,0X6,0X7,0X7,0X6,0X6,0X6,
0X4,0X4,0X5,0X4,0X4,0X5,0X4,0X4,0X6,0X6,0X7,0X6,0X6,0X7,0X6,0X6,
0X4,0X5,0X4,0X4,0X4,0X4,0X5,0X4,0X6,0X7,0X6,0X6,0X6,0X6,0X7,0X6,
0X5,0X4,0X4,0X4,0X4,0X4,0X4,0X5,0X7,0X6,0X6,0X6,0X6,0X6,0X6,0X7,

0X0,0X1,0X2,0X3,0X4,0X5,0X6,0X7,0X7,0X6,0X5,0X4,0X3,0X2,0X1,0X0,//wave
0X1,0X2,0X3,0X4,0X5,0X6,0X7,0X0,0X0,0X7,0X6,0X5,0X4,0X3,0X2,0X1,
0X2,0X3,0X4,0X5,0X6,0X7,0X0,0X1,0X1,0X0,0X7,0X6,0X5,0X4,0X3,0X2,
0X3,0X4,0X5,0X6,0X7,0X0,0X1,0X2,0X2,0X1,0X0,0X7,0X6,0X5,0X4,0X3,
0X4,0X5,0X6,0X7,0X0,0X1,0X2,0X3,0X3,0X2,0X1,0X0,0X7,0X6,0X5,0X4,
0X5,0X6,0X7,0X0,0X1,0X2,0X3,0X4,0X4,0X3,0X2,0X1,0X0,0X7,0X6,0X5,
0X6,0X7,0X0,0X1,0X2,0X3,0X4,0X5,0X5,0X4,0X3,0X2,0X1,0X0,0X7,0X6,
0X7,0X0,0X1,0X2,0X3,0X4,0X5,0X6,0X6,0X5,0X4,0X3,0X2,0X1,0X0,0X7,
0X0,0X1,0X2,0X3,0X4,0X5,0X6,0X7,0X7,0X6,0X5,0X4,0X3,0X2,0X1,0X0,
0X1,0X2,0X3,0X4,0X5,0X6,0X7,0X0,0X0,0X7,0X6,0X5,0X4,0X3,0X2,0X1,
0X2,0X3,0X4,0X5,0X6,0X7,0X0,0X1,0X1,0X0,0X7,0X6,0X5,0X4,0X3,0X2,
0X3,0X4,0X5,0X6,0X7,0X0,0X1,0X2,0X2,0X1,0X0,0X7,0X6,0X5,0X4,0X3,
0X4,0X5,0X6,0X7,0X0,0X1,0X2,0X3,0X3,0X2,0X1,0X0,0X7,0X6,0X5,0X4,
0X5,0X6,0X7,0X0,0X1,0X2,0X3,0X4,0X4,0X3,0X2,0X1,0X0,0X7,0X6,0X5,
0X6,0X7,0X0,0X1,0X2,0X3,0X4,0X5,0X5,0X4,0X3,0X2,0X1,0X0,0X7,0X6,
0X7,0X0,0X1,0X2,0X3,0X4,0X5,0X6,0X6,0X5,0X4,0X3,0X2,0X1,0X0,0X7,


0x1,0x1,0x1,0x1,0x8,0x8,0x8,0x8,0x2,0x2,0x2,0x2,0x8,0x8,0x8,0x8,
0x3,0x3,0x3,0x3,0x8,0x8,0x8,0x8,0x4,0x4,0x4,0x4,0x8,0x8,0x8,0x8,//4way checkers
0x5,0x5,0x5,0x5,0x8,0x8,0x8,0x8,0x6,0x6,0x6,0x6,0x8,0x8,0x8,0x8,
0x7,0x7,0x7,0x7,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x1,0x1,0x1,0x1,0x8,0x8,0x8,0x8,0x2,0x2,0x2,0x2,
0x8,0x8,0x8,0x8,0x3,0x3,0x3,0x3,0x8,0x8,0x8,0x8,0x4,0x4,0x4,0x4,
0x8,0x8,0x8,0x8,0x5,0x5,0x5,0x5,0x8,0x8,0x8,0x8,0x6,0x6,0x6,0x6,
0x8,0x8,0x8,0x8,0x7,0x7,0x7,0x7,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,
0x1,0x1,0x1,0x1,0x8,0x8,0x8,0x8,0x2,0x2,0x2,0x2,0x8,0x8,0x8,0x8,
0x3,0x3,0x3,0x3,0x8,0x8,0x8,0x8,0x4,0x4,0x4,0x4,0x8,0x8,0x8,0x8,
0x5,0x5,0x5,0x5,0x8,0x8,0x8,0x8,0x6,0x6,0x6,0x6,0x8,0x8,0x8,0x8,
0x7,0x7,0x7,0x7,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x1,0x1,0x1,0x1,0x8,0x8,0x8,0x8,0x2,0x2,0x2,0x2,
0x8,0x8,0x8,0x8,0x3,0x3,0x3,0x3,0x8,0x8,0x8,0x8,0x4,0x4,0x4,0x4,
0x8,0x8,0x8,0x8,0x5,0x5,0x5,0x5,0x8,0x8,0x8,0x8,0x6,0x6,0x6,0x6,
0x8,0x8,0x8,0x8,0x7,0x7,0x7,0x7,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,


0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,
0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,
0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,
0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,//4 color checkers
0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,
0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,
0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,
0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,
0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,
0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,
0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,
0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,
0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,
0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,
0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,
0x4,0x4,0x4,0x4,0x3,0x3,0x3,0x3,0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,

0x0,0x0,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,0x0,0x0,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x0,0x0,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,//zig zag
0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,0x0,0x0,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x0,0x0,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,0x0,0x0,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x0,0x0,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,
0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,0x0,0x0,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x5,0x5,0x6,0x6,0x7,0x7,0x8,0x8,

0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x1,0x8,0x8,0x8,0x8,0x2,0x8,0x8,0x8,//crazy circles
0x8,0x0,0x0,0x0,0x8,0x8,0x1,0x1,0x1,0x8,0x8,0x2,0x2,0x2,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x2,0x2,0x2,0x2,0x2,0x8,
0x8,0x0,0x0,0x0,0x8,0x8,0x1,0x1,0x1,0x8,0x8,0x2,0x2,0x2,0x8,0x8,
0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x1,0x8,0x8,0x8,0x8,0x2,0x8,0x8,0x8,
0x8,0x8,0x8,0x3,0x8,0x8,0x8,0x8,0x4,0x8,0x8,0x8,0x8,0x5,0x8,0x8,
0x8,0x3,0x3,0x3,0x8,0x8,0x4,0x4,0x4,0x8,0x8,0x5,0x5,0x5,0x8,0x8,
0x3,0x3,0x3,0x3,0x3,0x4,0x4,0x4,0x4,0x4,0x5,0x5,0x5,0x5,0x5,0x8,
0x8,0x3,0x3,0x3,0x8,0x8,0x4,0x4,0x4,0x8,0x8,0x5,0x5,0x5,0x8,0x8,
0x8,0x8,0x3,0x8,0x8,0x8,0x8,0x4,0x8,0x8,0x8,0x8,0x5,0x8,0x8,0x8,
0x8,0x8,0x6,0x8,0x8,0x8,0x8,0x7,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,
0x8,0x6,0x6,0x6,0x8,0x8,0x7,0x7,0x7,0x8,0x8,0x0,0x0,0x0,0x8,0x8,
0x6,0x6,0x6,0x6,0x6,0x7,0x7,0x7,0x7,0x7,0x0,0x0,0x0,0x0,0x0,0x8,
0x8,0x6,0x6,0x6,0x8,0x8,0x7,0x7,0x7,0x8,0x8,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x6,0x8,0x8,0x8,0x8,0x7,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//spread
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,
//TimeBomb
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,
0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,
0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,
0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,
0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
//slag
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//aMERICAN,0xFLAg
//Flag,0xif,0xand,0x8,0x=,0xblack,0x9,0x=,0xwhite,0x,0xROYGBV,0x=,0x(ABCDEF)
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0xE,0x9,0xE,0x9,0xE,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0xE,0x9,0xE,0x9,0xE,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0xE,0x9,0xE,0x9,0xE,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0xE,0x9,0xE,0x9,0xE,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0xE,0x9,0xE,0x9,0xE,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0xE,0x9,0xE,0x9,0xE,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,0xA,0xA,0x9,0x9,
//rINGS
0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x0,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x8,0x0,0x0,
0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x0,0x8,0x8,0x8,0x0,
0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,
0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x8,0x0,0x0,0x0,0x8,0x8,0x0,
0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,
0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,
0x0,0x8,0x8,0x8,0x0,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,
0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,
0x0,0x0,0x8,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,
0x0,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//aRROW
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x8,0x0,0x0,0x0,0x0,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x0,0x0,0x0,0x0,
0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,0x0,0x0,0x0,0x8,
0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//mULTIBOX
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,
0x0,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x1,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x1,
0x1,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x1,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
0x2,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x2,
0x2,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x2,
0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,
0x3,0x8,0x8,0x8,0x3,0x3,0x8,0x8,0x8,0x8,0x3,0x3,0x8,0x8,0x8,0x3,
0x3,0x8,0x8,0x8,0x3,0x3,0x8,0x8,0x8,0x8,0x3,0x3,0x8,0x8,0x8,0x3,
0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,

//INWARD,0xREFLECTION,0xOF,0xPOST,0xMORTEM,0xEXPRESSION
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x2,0x3,0x4,0x4,0x3,0x3,0x4,0x4,0x3,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x2,0x3,0x4,0x4,0x3,0x3,0x4,0x4,0x3,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x2,0x4,0x4,0x3,0x3,0x3,0x3,0x4,0x4,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x2,0x4,0x4,0x3,0x3,0x3,0x3,0x4,0x4,0x2,0x2,0x1,0x1,
0x1,0x1,0x2,0x4,0x4,0x3,0x3,0x2,0x2,0x3,0x3,0x4,0x4,0x2,0x1,0x1,
0x1,0x1,0x2,0x4,0x4,0x3,0x3,0x2,0x2,0x3,0x3,0x4,0x4,0x2,0x1,0x1,
0x1,0x1,0x4,0x4,0x3,0x3,0x2,0x2,0x2,0x2,0x3,0x3,0x4,0x4,0x1,0x1,
0x1,0x1,0x4,0x4,0x3,0x3,0x2,0x2,0x2,0x2,0x3,0x3,0x4,0x4,0x1,0x1,
0x1,0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x1,
0x1,0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,0x1,
0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,
0x4,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x1,0x1,0x2,0x2,0x3,0x3,0x4,0x4,
0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x4,0x4,0x1,0x1,0x2,0x2,0x3,0x3,0x4,
0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x4,0x4,0x1,0x1,0x2,0x2,0x3,0x3,0x4,
//CrossTheT
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,
//The,0xBig,0xDown
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//The Big Down Square
0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x8,
0x8,0x8,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x0,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,

//Manson's revenge
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,0x8,0x0,0x0,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
//doubleDime
0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x1,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x1,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x1,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x1,0x0,0x0,0x8,0x8,
0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x0,0x0,0x0,0x0,0x0,0x8,0x8,
0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0,0x8,0x8,0x8,
0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//1colorstrobe
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//2colorstrobe
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//4colorstrobe
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
//Sparklelights
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x8,
//bam
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x1,0x8,0x8,0x1,0x8,0x8,0x1,0x8,0x1,0x8,0x8,0x1,0x8,0x8,0x8,0x8,
0x8,0x1,0x1,0x1,0x8,0x1,0x1,0x8,0x1,0x1,0x8,0x1,0x8,0x8,0x1,0x8,
0x8,0x1,0x2,0x2,0x2,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x1,0x1,0x2,0x1,0x1,0x2,0x1,0x1,0x1,0x1,0x1,0x2,0x1,0x2,0x1,0x8,
0x8,0x1,0x2,0x1,0x2,0x2,0x1,0x1,0x2,0x2,0x1,0x2,0x2,0x2,0x2,0x2,
0x8,0x1,0x2,0x2,0x2,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x2,0x2,0x2,0x2,
0x1,0x1,0x2,0x1,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,
0x8,0x1,0x2,0x1,0x1,0x2,0x1,0x2,0x2,0x2,0x1,0x2,0x1,0x1,0x1,0x2,
0x8,0x1,0x2,0x1,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x1,0x1,0x2,
0x1,0x1,0x2,0x2,0x2,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x1,0x1,0x2,
0x8,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
0x8,0x8,0x8,0x1,0x8,0x1,0x8,0x8,0x1,0x1,0x8,0x1,0x8,0x8,0x1,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
//IDK
0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x3,0x8,0x8,0x8,0x3,
0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x1,0x1,0x8,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
0x8,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x8,0x8,0x1,0x1,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x8,0x8,0x3,
0x8,0x8,0x1,0x1,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
0x0,0x0,0x8,0x8,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x3,0x8,0x8,0x8,0x3,
0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
0x8,0x8,0x8,0x0,0x0,0x1,0x1,0x8,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
0x8,0x8,0x8,0x8,0x2,0x2,0x8,0x8,0x8,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x8,0x8,0x1,0x1,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x8,0x8,0x3,
0x8,0x8,0x1,0x1,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x3,0x8,
0x8,0x1,0x1,0x8,0x8,0x8,0x8,0x0,0x0,0x8,0x8,0x8,0x8,0x3,0x8,0x8,
};



const uint16_t Images[][16] PROGMEM = {
  0b0000000000000000,0b0001110001110000,0b0011111011111000,0b0111111111111100,//*********
  0b0111111011111100,0b0111111111111100,0b0011111111111000,0b0001111111110000,//Heart 0
  0b0000111111100000,0b0000011111000000,0b0000001110000000,0b0000000100000000,
  0b0000000000000000,0b0000000000000000,0b0000000000000000,0b0000000000000000,//*********

  0b0000000100000000,0b0000000100000000,0b0000001110000000,0b0000001110000000,//star 1
  0b0000011111000000,0b1111111111111111,0b0011111111111100,0b0001111111111000,
  0b0000111111110000,0b0001111111111000,0b0011110001111100,0b0111000000011100,
  0b0110000000001100,0b1000000000000010,0b0000000000000000,0b0000000000000000,


  0b0110011001100110,0b1111000011110000,0b0110011001100110,0b0000111100001111,//wavy 2
  0b0110011001100110,0b1111000011110000,0b0110011001100110,0b0000111100001111,
  0b0110011001100110,0b1111000011110000,0b0110011001100110,0b0000111100001111,
  0b0110011001100110,0b1111000011110000,0b0110011001100110,0b0000111100001111,

  0b0001000000000000,0b0001000000100000,0b0010000000100000,0b0110000011111000,//moon 3
  0b1110000001100000,0b1110000010010000,0b1111000000000000,0b1111000000000000,
  0b1111000000000000,0b0111100000000000,0b0111110000000000,0b0001111100000000,
  0b0000111111001000,0b0000011111110000,0b0000000111100000,0b0000000000000000,

  0b0000000000000000,0b0000000000000000,0b0001100000000000,0b0010000000000000,//cat 4
  0b0010000000000000,0b0010000000000100,0b0001000000001110,0b0001111111111100,
  0b0001111111111000,0b0011111111111000,0b0010100001001100,0b0100100001000110,
  0b0100100001000010,0b0100010001000001,0b0000000000000000,0b0000000000000000, 

  0b1110011100111001,0b1010010100101010,0b1110011100111001,0b0000000000000000,//Ooo 5
  0b1110011100111001,0b1010010100101010,0b1110011100111001,0b0000000000000000,
  0b1110011100111001,0b1010010100101010,0b1110011100111001,0b0000000000000000,
  0b1110011100111001,0b1010010100101010,0b1110011100111001,0b0000000000000000,

  0b1011101111111010,0b1010101000001010,0b1110101011101010,0b0000101010101010,//maze 6
  0b1111101010111010,0b1000001010000010,0b1111111010111111,0b0000000010100001,
  0b1010100000000010,0b1000001011101001,0b1011101000001011,0b1010101111111010,
  0b1110011100111001,0b1010111111111110,0b1010000000000001,0b1011111111111111,

  0b0110110110110110,0b1001001001001001,0b0110110110110110,0b0110110110110110,//chains7
  0b1001001001001001,0b0110110110110110,0b0110110110110110,0b1001001001001001,
  0b0110110110110110,0b0110110110110110,0b1001001001001001,0b0110110110110110,
  0b0110110110110110,0b1001001001001001,0b0110110110110110,0b0110110110110110,

  0b0001001111100100,0b0010100101001010,0b0111110010011111,0b0001001111100100,//mini tri8
  0b0010100101001010,0b0111110010011111,0b0001001111100100,0b0010100101001010,
  0b0111110010011111,0b0001001111100100,0b0010100101001010,0b0111110010011111,
  0b0001001111100100,0b0010100101001010,0b0111110010011111,0b0001001111100100,

  0b1111111011111110,0b1000001010000010,0b1000001010000010,0b1000001010000010,//4Square
  0b1000001010000010,0b1000001010000010,0b1111111011111110,0b0000000000000000,
  0b1111111011111110,0b1000001010000010,0b1000001010000010,0b1000001010000010,//4Square
  0b1000001010000010,0b1000001010000010,0b1111111011111110,0b0000000000000000,

  0b0000111100001111,0b0000111100001111,0b0000111100001111,0b0000111100001111,//checker
  0b1111000011110000,0b1111000011110000,0b1111000011110000,0b1111000011110000,
  0b0000111100001111,0b0000111100001111,0b0000111100001111,0b0000111100001111,
  0b1111000011110000,0b1111000011110000,0b1111000011110000,0b1111000011110000,


  0b0011001100110011,0b1001100110011001,0b1100110011001100,0b0110011001100110, //slider
  0b0011001100110011,0b1001100110011001,0b1100110011001100,0b0110011001100110,
  0b0011001100110011,0b1001100110011001,0b1100110011001100,0b0110011001100110,
  0b0011001100110011,0b1001100110011001,0b1100110011001100,0b0110011001100110,

  0b0000000000000000,0b0001111001111000,0b0001111001111000,0b0100000000000010,//Smiley Face
  0b0111100000011110,0b0011111111111100,0b0001111111111000,0b0000000000000000,
  0b0000000000000000,0b0001111001111000,0b0001111001111000,0b0100000000000010,
  0b0111100000011110,0b0011111111111100,0b0001111111111000,0b0000000000000000,


  0b1111000011110000,0b0111100001111000,0b0011110000111100,0b0001111000011110,//Float
  0b0000111100001111,0b1000011110000111,0b1100001111000011,0b1110000111100001,
  0b1111000011110000,0b0111100001111000,0b0011110000111100,0b0001111000011110,
  0b0000111100001111,0b1000011110000111,0b1100001111000011,0b1110000111100001,

  0b1100110011001100,0b0110011001100110,0b0011001100110011,0b1001100110011001,//Zag
  0b0011001100110011,0b0110011001100110,0b1100110011001100,0b1001100110011001,
  0b1100110011001100,0b0110011001100110,0b0011001100110011,0b1001100110011001,
  0b0011001100110011,0b0110011001100110,0b1100110011001100,0b1001100110011001,



  0b0000111111110000,0b0011110000111100,0b1111001001001111,0b1100000110000011,//NewCircle
  0b1111001001001111,0b0011110000111100,0b0000111111110000,0b0000000000000000,
  0b0000111111110000,0b0011110000111100,0b1111001001001111,0b1100000110000011,
  0b1111001001001111,0b0011110000111100,0b0000111111110000,0b0000000000000000,


  0b1100001111000011,0b1100001111000011,0b0110011001100110,0b0011110000111100,//Double Helix
  0b0011110000111100,0b0110011001100110,0b1100001111000011,0b1100001111000011,
  0b1100001111000011,0b1100001111000011,0b0110011001100110,0b0011110000111100,
  0b0011110000111100,0b0110011001100110,0b1100001111000011,0b1100001111000011,


  0b0011001111001100,0b0111100110011110,0b1111110000111111,0b0111100110011110,// Bubbles
  0b0011001111001100,0b0111100110011110,0b1111110000111111,0b0111100110011110,
  0b0011001111001100,0b0111100110011110,0b1111110000111111,0b0111100110011110,
  0b0011001111001100,0b0111100110011110,0b1111110000111111,0b0111100110011110,

  0b1001001001001001,0b0100100100100100,0b0010010010010010,0b1001001001001001,//Move
  0b0010010010010010,0b0100100100100100,0b1001001001001001,0b0010010010010010,
  0b1001001001001001,0b0100100100100100,0b0010010010010010,0b1001001001001001,
  0b0010010010010010,0b0100100100100100,0b1001001001001001,0b0010010010010010,

  0b0011110000111100,0b0111100001111000,0b1111000011110000,0b1110000111100001,//Diag Checkers
  0b0001111000011110,0b0000111100001111,0b1000011110000111,0b1100001111000011,
  0b0011110000111100,0b0111100001111000,0b1111000011110000,0b1110000111100001,
  0b0001111000011110,0b0000111100001111,0b1000011110000111,0b1100001111000011,
};


const char led_chars[97][6] PROGMEM = {
  0x00,0x00,0x00,0x00,0x00,0x00, // space 0
  0x00,0x00,0xfa,0x00,0x00,0x00, // ! 1
  0x00,0xe0,0x00,0xe0,0x00,0x00,  // "2
  0x28,0xfe,0x28,0xfe,0x28,0x00,  // #3
  0x24,0x54,0xfe,0x54,0x48,0x00, // $4
  0xc4,0xc8,0x10,0x26,0x46,0x00, // %5
  0x6c,0x92,0xaa,0x44,0x0a,0x00, // &6
  0x00,0xa0,0xc0,0x00,0x00,0x00, // '7
  0x00,0x38,0x44,0x82,0x00,0x00,  // (8
  0x00,0x82,0x44,0x38,0x00,0x00, // )10
  0x28,0x10,0x7c,0x10,0x28,0x00, // *11
  0x10,0x10,0x7c,0x10,0x10,0x00, // +12
  0x00,0x0a,0x0c,0x00,0x00,0x00, // ,13
  0x10,0x10,0x10,0x10,0x10,0x00, // -14
  0x00,0x06,0x06,0x00,0x00,0x00, // .15
  0x04,0x08,0x10,0x20,0x40,0x00, // / 16
  0x7c,0x8a,0x92,0xa2,0x7c,0x00, // 0 17
  0x00,0x42,0xfe,0x02,0x00,0x00, // 1 18
  0x42,0x86,0x8a,0x92,0x62,0x00, // 2 9
  0x84,0x82,0xa2,0xd2,0x8c,0x00,  // 3 0
  0x18,0x28,0x48,0xfe,0x08,0x00,  // 4 1
  0xe5,0xa2,0xa2,0xa2,0x9c,0x00,  // 5 2
  0x3c,0x52,0x92,0x92,0x0c,0x00,  // 6 3
  0x80,0x8e,0x90,0xa0,0xc0,0x00,  // 7 4
  0x6c,0x92,0x92,0x92,0x6c,0x00,  // 8 5
  0x60,0x92,0x92,0x94,0x78,0x00,  // 9 6
  0x00,0x6c,0x6c,0x00,0x00,0x00,  // : 7
  0x00,0x6a,0x6c,0x00,0x00,0x00,  // ;8
  0x10,0x28,0x44,0x82,0x00,0x00,  // <9
  0x28,0x28,0x28,0x28,0x28,0x00,  // =0
  0x00,0x82,0x44,0x28,0x10,0x00,  // >1
  0x40,0x80,0x8a,0x90,0x60,0x00,  // ?2
  0x4c,0x92,0x9e,0x82,0x7c,0x00,  // @3
  0x7e,0x88,0x88,0x88,0x7e,0x00,  // A4
  0xfe,0x92,0x92,0x92,0x6c,0x00,  // B5
  0x7c,0x82,0x82,0x82,0x44,0x00,  // C6
  0xfe,0x82,0x82,0x44,0x38,0x00,  // D7
  0xfe,0x92,0x92,0x92,0x82,0x00,  // E8
  0xfe,0x90,0x90,0x90,0x80,0x00,  // F9
  0x7c,0x82,0x92,0x92,0x5e,0x00,  // G0
  0xfe,0x10,0x10,0x10,0xfe,0x00,  // H1
  0x00,0x82,0xfe,0x82,0x00,0x00,   // I2
  0x04,0x02,0x82,0xfc,0x80,0x00,  // J3
  0xfe,0x10,0x28,0x44,0x82,0x00,  // K4
  0xfe,0x02,0x02,0x02,0x02,0x00,  // L5
  0xfe,0x40,0x30,0x40,0xfe,0x00,  // M6
  0xfe,0x20,0x10,0x08,0xfe,0x00,  // N7
  0x7c,0x82,0x82,0x82,0x7c,0x00,  // O8
  0xfe,0x90,0x90,0x90,0x60,0x00,  // P9
  0x7c,0x82,0x8a,0x84,0x7a,0x00,  // Q0
  0xfe,0x90,0x98,0x94,0x62,0x00,  // R1
  0x62,0x92,0x92,0x92,0x8c,0x00,  // S2
  0x80,0x80,0xfe,0x80,0x80,0x00,  // T3
  0xfc,0x02,0x02,0x02,0xfc,0x00,  // U4
  0xf8,0x04,0x02,0x04,0xf8,0x00,  // V5
  0xfc,0x02,0x1c,0x02,0xfc,0x00,  // W6
  0xc6,0x28,0x10,0x28,0xc6,0x00,  // X7
  0xe0,0x10,0x0e,0x10,0xe0,0x00,  // Y8
  0x86,0x8b,0x92,0xa2,0xc2,0x00,  // Z9
  0x00,0xfe,0x82,0x82,0x00,0x00,  // [0
  0x00,0x00,0x00,0x00,0x00,0x00, //1 *** do not remove this empty char ***
  0x00,0x82,0x82,0xfe,0x00,0x00,	// ]2
  0x20,0x40,0x80,0x40,0x20,0x00,	// ^3
  0x02,0x02,0x02,0x02,0x02,0x00,	// _4
  0x00,0x80,0x40,0x20,0x00,0x00,	// `5
  0x04,0x2a,0x2a,0x2a,0x1e,0x00,	// a6
  0xfe,0x12,0x22,0x22,0x1c,0x00,	// b7
  0x1c,0x22,0x22,0x22,0x04,0x00,	// c8
  0x1c,0x22,0x22,0x12,0xfe,0x00,	// d9
  0x1c,0x2a,0x2a,0x2a,0x18,0x00,	// e0
  0x10,0x7e,0x90,0x80,0x40,0x00,	// f1
  0x30,0x4a,0x4a,0x4a,0x7c,0x00,	// g2
  0xfe,0x10,0x20,0x20,0x1e,0x00,	// h3
  0x00,0x22,0xbe,0x02,0x00,0x00,	// i4
  0x04,0x02,0x22,0xbc,0x00,0x00,	// j5
  0xfe,0x08,0x14,0x22,0x00,0x00,	// k6
  0x00,0x82,0xfe,0x02,0x00,0x00,	// l7
  0x3e,0x20,0x18,0x20,0x1e,0x00,	// m8
  0x3e,0x10,0x20,0x20,0x1e,0x00,	// n9
  0x1c,0x22,0x22,0x22,0x1c,0x00,	// o0
  0x3e,0x28,0x28,0x28,0x10,0x00,	// p1
  0x10,0x28,0x28,0x18,0x3e,0x00,	// q2
  0x3e,0x10,0x20,0x20,0x10,0x00,	// r3
  0x12,0x2a,0x2a,0x2a,0x04,0x00,	// s4
  0x20,0xfc,0x22,0x02,0x04,0x00,	// t5
  0x3c,0x02,0x02,0x04,0x3e,0x00,	// u6
  0x38,0x04,0x02,0x04,0x38,0x00,	// v7
  0x3c,0x02,0x0c,0x02,0x3c,0x00,	// w8
  0x22,0x14,0x08,0x14,0x22,0x00,	// x9
  0x30,0x0a,0x0a,0x0a,0x3c,0x00,	// y0
  0x22,0x26,0x2a,0x32,0x22,0x00, // z1
  0x00,0x10,0x6c,0x82,0x00,0x00,	// {2
  0x00,0x00,0xfe,0x00,0x00,0x00,	// |3
  0x00,0x82,0x6c,0x10,0x00,0x00,//96
  //  0x18,0x3c,0x7e,0xff,0x7e,0x3c,//97 we added this line and bellow


}; //4

// Principle of operation: at any given time, the LEDs depict an image or
// animation effect (referred to as the "back" image throughout this code).
// Periodically, a transition to a new image or animation effect (referred
// to as the "front" image) occurs. During this transition, a third buffer
// (the "alpha channel") determines how the front and back images are
// combined; it represents the opacity of the front image. When the
// transition completes, the "front" then becomes the "back," a new front
// is chosen, and the process repeats.
byte imgData[2][numPixels * 3], // Data for 2 strips worth of imagery
tempimgData[numPixels*3], // this is our temp strip for storing the last image
alphaMask[numPixels], // Alpha channel for compositing images
backImgIdx = 0, // Index of 'back' image (always 0 or 1)
fxIdx[3]; // Effect # for back & front images + alpha
int fxVars[3][50]; // Effect instance variables (explained later)
// Countdown to next transition
int transitionTime; // Duration (in frames) of current transition
// function prototypes, leave these be :)
void schemetest(byte idx);
void schemetestfade(byte idx);
void schemetestlong(byte idx);
void schemetestlongfade(byte idx);
void schemefade(byte idx);
void MonsterHunter(byte idx);
void wavyFlag(byte idx);// stock
void pacman(byte idx);   //bounces back from end to end and builds every time 
void POV(byte idx); //if using uno comment this out. 2k of ram is not enough! or is it?
void fans(byte idx);
void renderAlpha00(void);
void renderAlpha01(void);
void renderAlpha02(void);
void renderAlpha03(void);
byte mixColor8(byte color1, byte color2, uint8_t alpha);
void callback();
void menu();
void menurender();
void getSerial();
void findplane();
void compassread();
byte gamma(byte x);
long hsv2rgb(long h, byte s, byte v);
char fixSin(int angle);
char fixCos(int angle);

// List of image effect and alpha channel rendering functions; the code for
// each of these appears later in this file. Just a few to start with...
// simply append new ones to the appropriate list here:


// ---------------------------------------------------------------------------

void bluetoothsetup(){
  Serial.println("Setting up bluetooth module");
  //inital baud rate of the bluetooth modules we use is 9600. I think we get the best performance
  //out of 38400 baud because of the timing errors due to the prescaler. we are specifically not using nl/cr
  //Uart.begin(9600);//change uart baud to match bt default
  // Uart.print("AT+BAUD1"); //sets bluetooth uart baud at 1200
  //  Uart.print("AT+BAUD2"); //sets bluetooth uart baud at 2400
  //  Uart.print("AT+BAUD3"); //sets bluetooth uart baud at 4800
  //  Uart.print("AT+BAUD4"); //sets bluetooth uart baud at 9600
  //  Uart.print("AT+BAUD5"); //sets bluetooth uart baud at 19200
  Uart.print("AT+BAUD6"); //sets bluetooth uart baud at 38400 //set bt uart at 38400, applies on next reboot
  //  Uart.print("AT+BAUD7"); //sets bluetooth uart baud at 57600
  //  Uart.print("AT+BAUD8"); //sets bluetooth uart baud at 115200
  delay(1000);//wait a sec
  Uart.print("AT+NAMEMax's Galaxy"); //sets name seen in bt
  delay(1000);
  Uart.print("AT+PIN1337");//sets pin, act like you know
  delay(1000); 
}
void brutebluetooth(){ //mess your bluetooth chip up? not to fear. this will try all available baud rates and
  int baudrate = 6; //when finished we will have a bt chip on 38400 baud
  // Uart.print("AT+BAUD1"); //sets bluetooth uart baud at 1200
  //  Uart.print("AT+BAUD2"); //sets bluetooth uart baud at 2400
  //  Uart.print("AT+BAUD3"); //sets bluetooth uart baud at 4800
  //  Uart.print("AT+BAUD4"); //sets bluetooth uart baud at 9600
  //  Uart.print("AT+BAUD5"); //sets bluetooth uart baud at 19200
  //   Uart.print("AT+BAUD6"); //sets bluetooth uart baud at 38400 
  //  Uart.print("AT+BAUD7"); //sets bluetooth uart baud at 57600
  //  Uart.print("AT+BAUD8"); //sets bluetooth uart baud at 115200
  delay(1000);//wait a sec
  Serial.println("This may take a while");
  for(int i=0;i<10;i++){
    Uart.begin(1200);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(2400);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(4800);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(9600);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(19200);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(38400);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(57600);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
    Uart.begin(115200);
    delay(1000);
    Uart.print("AT+BAUD");
    Uart.print(baudrate);
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("done");

} 

void setup() {
  //bring up our serial connections
  Serial.begin(115200);//start serial connection through usb 
  Uart.begin(38400); //start serial connection to bluetooth module
  strip.begin();//start lpd8806 strip

  //check for demo mode flag in eeprom spot 256, set demo accordingly and
  //reset flag 
  if(EEPROM.read(256)>0){//if eeprom 256 is 1 or more
    demo=false; //disable demo mode
    EEPROM.write(256, 0);//write eeprom spot 256 to 0
  }
  else{//if eeprom 256 is 0 (1 unsigned byte in each eeprom spot)
    demo=true; //enable demo mode
    EEPROM.write(256,1);//write eeprom spot 256 to 1
  }

  //check for ir learn flag on eeprom spot 255.
  uint8_t offcounter = EEPROM.read(255);
  EEPROM.write(255, offcounter+1);
  //add one to what you find in pair flag slot
  //if the user turns the hoop on and off 3 times in a row before the 3color
  //fade finishes it puts the hoop into IR learn mode.
  //every time the 3color fade finishes it resets eeprom 255 to 0
  //so 2 consecutive interruptions is required to trigger.


  //RGB means demo is disabled, CMY means demo is enabled
  if(demo==true){//Cyan, MAGENTA and yellow fade

      for(int i=0;i<127;i++){ //fade in cyan
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0, i/2, i/2);
      }
      delay(5);
      strip.show();
    }
    for(int i=127;i>0;i--){ //fade out cyan
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0, i/2, i/2);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade in purple
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i/2, 0, i/2);
      }
      delay(5);
      strip.show();
    }
    for(int i=127;i>0;i--){ //fade out cyan
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i/2,0, i/2);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade in orange
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i/2, i/2, 0);
      }
      delay(5);
      strip.show();
    }
    for(int i=127;i>0;i--){ //fade out yellow
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i/2, i/2, 0);
      }
      delay(5);
      strip.show();
    } 

  }
  else{ //good old red green and blue.

    for(int i=0;i<127;i++){ //fade in red
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i, 0, 0);
      }
      delay(5);
      strip.show();
    }
    for(int i=127;i>0;i--){ //fade out red
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, i, 0, 0);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade in green
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0, i, 0);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade out green
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0,abs(i-127), 0);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade in blue
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0, 0, i);
      }
      delay(5);
      strip.show();
    }
    for(int i=0;i<127;i++){ //fade out blue
      for(int q=0;q<numPixels;q++){
        strip.setPixelColor(q, 0, 0, abs(i-127));
      }
      delay(5);
      strip.show();
    } 
  } 

  //delay(100000);
  uint8_t irsetupflag = EEPROM.read(255);
  Serial.print(irsetupflag);
  Serial.println(" read from EEPROM spot 255");
  if(irsetupflag==3){//if our pair flag is 2 then
    opmode=3;
    for(int q=0;q<ircsetup;q++){
      strip.setPixelColor(q,64,0,0); 
    }
    strip.setPixelColor(0,0,64,0);
    strip.show();
  }
  else{
    EEPROM.write(255,0); //otherwise we want to write eeprom spot 255 to 0  
  }                      //to reset discoverable / learn counter
  int i;
  pinMode(irrxpin, INPUT);
  pinMode(19, INPUT);
  EEPreadirc();
  /*
 if(serialoutput==true){
   Serial.println();
   Serial.println("Send a");
   Serial.println("+ to press button");
   //Serial.println("B to increase brightness, ");
   //Serial.println("b to decrease brightness, ");
   Serial.println("D to enable compass debug,");
   Serial.println("d to disable compass debug");
   Serial.println("C to + color scheme");
   Serial.println("c to - color scheme");
   Serial.println("M to enter menu");
   Serial.println("m to go back to run");
   Serial.println("Starting the I2C interface.");
   }
   */
  Wire.begin(); // Start the I2C interface.
  compass.init();
  compass.enableDefault();
  // Initialize random number generator from a floating analog input.
  randomSeed(analogRead(0));
  memset(imgData, 0, sizeof(imgData)); // Clear image data
  fxVars[backImgIdx][0] = 1; // Mark back image as initialized
  irrecv.enableIRIn();
  pinMode(19, INPUT_PULLUP);//using internal pull up resistor
  //attachInterrupt(19, buttonpress, LOW); //button 19 esternal interrupt 7
  // Timer1.initialize();
  // Timer1.attachInterrupt(callback, 1000000 / 30); //30 times/second
}

void findplane(){
  // MagnetometerScaled scaled = compass.ReadScaledAxis();
  if(abs(compass.m.x)>abs(compass.m.y)&&abs(compass.m.x)>abs(compass.m.z)) //in plane 1
  {
    if(compass.m.x>0){
      plane=1;
    }
    else{
      plane=-1;
    }
  }
  if(abs(compass.m.y)>abs(compass.m.x)&&abs(compass.m.y)>abs(compass.m.z)) //in plane 2

  {
    if(compass.m.y>0){
      plane=2;
    }
    else{
      plane=-2;
    }
  }

  if(abs(compass.m.z)>abs(compass.m.y)&&abs(compass.m.z)>abs(compass.m.x)) //in plane 3

  {
    if(compass.m.z>0){
      plane=3;
    }
    else{
      plane=-3;
    }

  }
  if(planeoutput==1){

    Serial.println();
    Serial.print("plane:");
    Serial.println(plane);

  }
}
void accelread(){
  axlast=ax;//copy old values
  aylast=ay;//to new slot
  azlast=az;//before poll
  ax= compass.a.x;//get new
  ay= compass.a.y;//values
  az= compass.a.z;
  // fxVars[idx][4]+fxVars[idx][5]+fxVars[idx][6];//sum of all axises
  // fxVars[idx][17]=fxVars[idx][14]+fxVars[idx][15]+fxVars[idx][16];//sum of all axises old
  // fxVars[idx][8]=abs(fxVars[idx][7]-fxVars[idx][17]);

  runningaverageax(abs(ax-axlast));//we are doing a running average 
  runningaverageay(abs(ay-aylast));//on the difference between polls
  runningaverageax(abs(ay-aylast));//to make the data more useable
  if(acceloutput==true){
    Serial.print("Acc:X");
    Serial.print(averageax);
    Serial.print(",Y");
    Serial.print(averageay);
    Serial.print(",Z");
    Serial.println(averageaz);
  }


}
void compassread()
{ 
  xyheadinglast = xyheading;
  xzheadinglast = xzheading;
  yzheadinglast = yzheading;
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  xyheading = atan2(compass.m.y, compass.m.x);
  xzheading = atan2(compass.m.x, compass.m.z);
  yzheading = atan2(compass.m.z, compass.m.y);
  xytravel = atan2(xyheading,xyheadinglast);
  xztravel = atan2(xzheading,xzheadinglast);
  yztravel = atan2(yzheading,yzheadinglast);
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your locatio

  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: 2Ã¯Â¿Â½ 37' W, which is 2.617 Degrees, or (which we need) 0.0456752665 radians, I will use 0.0457
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  // float declinationAngle = 0.0457;
  // heading += declinationAngle;

  // Correct for when signs are reversed.
  if(xyheading < 0)
    xyheading += 2*PI;

  // Check for wrap due to addition of declination.
  if(xyheading > 2*PI)
    xyheading -= 2*PI;

  // Convert radians to degrees for readability.
  xyheadingdegreeslast = xyheadingdegrees;
  xyheadingdegrees = xyheading * 180/M_PI;
  // runningaverage(xyheadingDegrees);


  // Correct for when signs are reversed.
  if(xzheading < 0)
    xzheading += 2*PI;

  // Check for wrap due to addition of declination.
  if(xzheading > 2*PI)
    xzheading -= 2*PI;

  // Convert radians to degrees for readability.
  xzheadingdegrees = xzheading * 180/M_PI;
  // Correct for when signs are reversed.
  if(yzheading < 0)
    yzheading += 2*PI;

  // Check for wrap due to addition of declination.
  if(yzheading > 2*PI)
    yzheading -= 2*PI;

  // Convert radians to degrees for readability.
  yzheadingdegreeslast = yzheadingdegrees;
  yzheadingdegrees = yzheading * 180/M_PI;
  // runningaverage(xyheadingDegrees);



  //xydynamic calibration
  if (xyheadingdegrees>xyheadingdegreesmax||xyheadingdegreesmax==0){

    xyheadingdegreesmax=xyheadingdegrees;

  }
  else{
    if(xyheadingdegrees<xyheadingdegreesmin||xyheadingdegreesmin==0){
      xyheadingdegreesmin=xyheadingdegrees;
    }
  }
  xyheadingdegreescalibrated = map(xyheadingdegrees,xyheadingdegreesmin,xyheadingdegreesmax,0,360);
  //xzdynamic calibration
  if (xzheadingdegrees>xzheadingdegreesmax||xzheadingdegreesmax==0){
    xzheadingdegreesmax=xzheadingdegrees;
  }
  else{
    if(xzheadingdegrees<xzheadingdegreesmin||xzheadingdegreesmin==0){

      xzheadingdegreesmin=xzheadingdegrees;
    }
  }
  xzheadingdegreescalibrated = map(xzheadingdegrees,xzheadingdegreesmin,xzheadingdegreesmax,0,360);
  //yzdynamic calibration
  if (yzheadingdegrees>yzheadingdegreesmax||yzheadingdegreesmax==0){
    yzheadingdegreesmax=yzheadingdegrees;
  }
  else{
    if(yzheadingdegrees<yzheadingdegreesmin||yzheadingdegreesmin==0){
      yzheadingdegreesmin=yzheadingdegrees;
    }
  }
  yzheadingdegreescalibrated = map(yzheadingdegrees,yzheadingdegreesmin,yzheadingdegreesmax,0,360);



  if (compassoutput==1){

    Uart.print("xy");
    Uart.println(xyheadingdegrees);
    Uart.print("xz");
    Uart.println(xzheadingdegrees);
    Uart.print("yz");
    Uart.println(yzheadingdegrees);
    //delay(250);

  }



  // Convert radians to degrees for readability.
  // float yzheadingDegrees = yzheading * 180/M_PI;


  // Output the data via the serial port.
  // Output(raw, scaled, heading, headingDegrees);

  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
  // delay(66);
  // Serial.print(xyheadingDegrees);
  // Serial.print(" xyDegrees \t");
  // Serial.print(xzheadingDegrees);
  // Serial.print(" xzDegrees \t");
  // Serial.print(yzheadingDegrees);
  // Serial.println(" yzDegrees \t");
  //figure out headingdelta
  //void runningAverage(int newval)
  /* if(count1==0){count1=1;}else{
   if(xyheadingDegrees>xyheadingDegreeslast){//indicates cw rotation or rollover from 359-0 in ccw rotation
   if(xyheadingDegreeslast>90||xyheadingDegreeslast<270){
   runningaverage(xyheadingDegrees-xyheadingDegreeslast);
   // xyheadingDegreesdelta=(xyheadingDegrees-xyheadingDegreeslast)+xyheadingDegreesdelta;
   }//indicates cw rotation w/o rollover
   else{
   runningaverage(xyheadingDegreeslast+(360-xyheadingDegrees));
   // xyheadingDegreesdelta=(xyheadingDegreeslast+(360-xyheadingDegrees))+xyheadingDegreesdelta;
   } //indicates ccw rotation with rollover
   }
   if(xyheadingDegrees<xyheadingDegreeslast){ //indicates ccw rotation or rollover from 0-359 in cw rotation
   if(xyheadingDegreeslast>90||xyheadingDegreeslast<270){
   runningaverage((xyheadingDegreeslast-xyheadingDegrees));
   // xyheadingDegreesdelta=(xyheadingDegreeslast-xyheadingDegrees)+xyheadingDegreesdelta;
   }//indicates ccw rotation w/o rollover
   else{
   runningaverage(xyheadingDegrees+(xyheadingDegreeslast-360));
   // xyheadingDegreesdelta=(xyheadingDegrees+(xyheadingDegreeslast-360))+xyheadingDegreesdelta;
   */
  //}; //indicates cw rotation with rollover
  // }; }
  /*
if(xyheadingDegreesdelta>90){
   xyheadingDegreesdelta=xyheadingDegreesdelta-90;
   count=count+1;
   xymillisdelta=xymillislast - millis();
   xymillislast=millis();
   Serial.println(xyheadingDegreesdelta );
   };
   */
  //Serial.println(average);
}

//void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
//{
// Serial.print("Raw:\t");
// Serial.print(raw.XAxis);
// Serial.print(" ");
// Serial.print(raw.YAxis);
// Serial.print(" ");
// Serial.print(raw.ZAxis);
// Serial.print(" \tScaled:\t");

// Serial.print(compass.m.x);
// Serial.print(" ");
// Serial.print(compass.m.y);
// Serial.print(" ");
// Serial.print(compass.m.z);

// Serial.print(" \tHeading:\t");
/// Serial.print(heading);
// Serial.print(" Radians \t");
// Serial.print(headingDegrees);
// Serial.println(" Degrees \t");
//}
int counter;
void mode(){
  switch(opmode){
  case 0: //normal run mode
    callback();
    break;

  case 1: //menu mode
    menurender();
    break;

  case 2://ir learn mode
    irsetup(true);
    break;
  }
}
void loop() {
  others();
  if(opmode==0){
    callback(); //generate image
    callback(); //generate image
    callback(); //generate image
    callback(); //generate image
    callback(); //generate image
  }
}
void others(){
  if(digitalRead(19)==0){
    buttonpress();
  }
  if(opmode==0||opmode==1){
    getir(); 
  }
  else{
    if(opmode==3){
      irsetup(true); 
    }  
  }
  //  getSerial();
  getUart();
  getSerial();
  compass.read();
  //  if (counter==255)calibrate(),counter=-255;
  compassread(); 
  accelread();
}

void calibrate(){
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);

  /* if(serialoutput==true&&compassdebug==true){  
   Serial.print("M min ");
   Serial.print("X: ");
   Serial.print((int)running_min.x);
   Serial.print(" Y: ");
   Serial.print((int)running_min.y);
   Serial.print(" Z: ");
   Serial.print((int)running_min.z);
   
   Serial.print(" M max ");  
   Serial.print("X: ");
   Serial.print((int)running_max.x);
   Serial.print(" Y: ");
   Serial.print((int)running_max.y);
   Serial.print(" Z: ");
   Serial.println((int)running_max.z);
   
   }
   */
  //recalculate calibration

  // Calibration values. Use the Calibrate example program to get the values for
  // your compass.

  compass.m_min.x = running_min.x; 
  compass.m_min.y = running_min.y;
  compass.m_min.z = running_min.z;
  compass.m_max.x = running_max.x;
  compass.m_max.y = running_max.y;
  compass.m_max.z = running_max.z;


}
void menurender() {
  strip.show();
  byte *backPtr    = &imgData[backImgIdx][0],
  r, g, b;
  int  i;
  for(i=0; i<numPixels; i++) {
    r = gamma(*backPtr++);
    g = gamma(*backPtr++);
    b = gamma(*backPtr++);
    strip.setPixelColor(i, r, g, b);
  }
  menu();
}
void menu() {
  byte *ptr = &imgData[backImgIdx][0];
  int type;//placeholder
  long color[3]={
    0,0,0      };
  if(type==0){//type tells us what value we are polling the user for. this 
    color[0] = red;//will choose colors and set the apropriate values
    color[1] = green;
    color[2] = blue;
  }
  if(type==1){//type tells us what value we are polling the user for. this 
    color[0] = purple;
    color[1] = yellow;
    color[2] = teal;
  }

  switch(menuphase){
  case 0:
    if(button==1){
      menuphase0=xyheadingdegreescalibrated/60;
      menuphase++;
      button=0;
      return;
    }
    else{
      for(int i=0; i<numPixels; i++) {

        if(i<=xyheadingdegreescalibrated/60){
          *ptr++ = color[0] >> 16;
          *ptr++ = color[0] >> 8;
          *ptr++ = color[0];
        }
        else{
          // for(int i=0; i<numPixels; i++) {
          *ptr++=0;
          *ptr++=0;
          *ptr++=0;
        }
      }
    }
    break;
  case 1:
    if(button==1){
      menuphase1=xyheadingdegreescalibrated/60;
      menuphase++;
      button=0;
      return;
    }
    else{
      for(int i=0; i<numPixels; i++) {
        if(i<=menuphase0){
          *ptr++ = color[0] >> 16;
          *ptr++ = color[0] >> 8;
          *ptr++ = color[0];
        }
        else{
          if(i>=menuphase0&&i<=menuphase0+(xyheadingdegreescalibrated/60)){
            *ptr++ = color[1] >> 16;
            *ptr++ = color[1] >> 8;
            *ptr++ = color[1];
          }
          else{
            *ptr++=0;
            *ptr++=0;
            *ptr++=0;
          }
        }
      }
    }
    break;
  case 2:
    if(button==1){
      menuphase2=xyheadingdegreescalibrated/60;
      menuphase++;
      button=0;
      return;
    }
    else{
      for(int i=0; i<numPixels; i++) {
        if(i<=menuphase0){
          *ptr++ = color[0] >> 16;
          *ptr++ = color[0] >> 8;
          *ptr++ = color[0];
        }
        else{
          if(i>=menuphase0&&i<=menuphase0+menuphase1){
            *ptr++ = color[1] >> 16;
            *ptr++ = color[1] >> 8;
            *ptr++ = color[1];
          }
          else{
            if(i>=menuphase0+menuphase1&&i<=menuphase0+menuphase1+(xyheadingdegreescalibrated/60)){
              *ptr++ = color[2] >> 16;
              *ptr++ = color[2] >> 8;
              *ptr++ = color[2];
            }
            else{
              *ptr++=0;
              *ptr++=0;
              *ptr++=0;
            }
          }
        }
      }
    }
    break;
  case 3: // if we are at 3 then the user just selected the last digit.
    //  Timer1.detachInterrupt();
    if(serialoutput==true){
      Serial.println(menuphase0);
      Serial.println(menuphase1);
      Serial.println(menuphase2);
    }
    uint8_t selection;

    if(menuphase1==-1&&menuphase2==-1){
      //code to calculate menu selection if only 1st digit supplied
      selection = menuphase0;
    }
    else{
      if(menuphase2==-1){
        //code to calculate menu selection if 2 digits supplied.
        selection = (menuphase0*10)+ menuphase1;
      }
      else{
        //code to calculate menu selection if all 3 digits caught here
        selection = (menuphase0*100)+(menuphase1*10)+ menuphase2;
      } 
    }
    if(serialoutput==true){
      Serial.print("selection ");
      Serial.println(selection);
    }
    if(type==0){//0 is pattern selection


    }
    //Timer1.attachInterrupt(callback, 1000000/framerate);//redirect interrupt to menu
    menuphase=0;
    break;

    /*  case 3:
     if(button==1){
     menuphase3=xyheadingdegreescalibrated/60;
     menuphase++;
     button=0;
     return;
     }
     else{
     for(int i=0; i<numPixels; i++) {
     if(i<=menuphase0){
     long color=red;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0&&i<=menuphase0+menuphase1){
     long color=magenta;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1&&i<=menuphase0+menuphase1+menuphase2){
     long color=blue;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2&&i<=menuphase0+menuphase1+menuphase2+(xyheadingdegreescalibrated/60)){
     //   if(i>=menuphase0+menuphase1&&i<=menuphase0+menuphase1+(xyheadingdegreescalibrated/60)){
     long color=teal;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     *ptr++=0;
     *ptr++=0;
     *ptr++=0;
     }
     }
     }
     }
     }  
     }
     break;
     case 4:
     if(button==1){
     menuphase4=xyheadingdegreescalibrated/60;
     menuphase++;
     button=0;
     return;
     }
     else{
     for(int i=0; i<numPixels; i++) {
     if(i<=menuphase0){
     long color=red;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0&&i<=menuphase0+menuphase1){
     long color=magenta;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1&&i<=menuphase0+menuphase1+menuphase2){
     long color=blue;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2&&i<=menuphase0+menuphase1+menuphase2+menuphase3){
     long color=teal;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2+menuphase3&&i<=menuphase0+menuphase1+menuphase2+menuphase3+(xyheadingdegreescalibrated/60)){
     long color=green;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     *ptr++=0;
     *ptr++=0;
     *ptr++=0;
     }
     }
     }
     }
     }
     }  
     }
     break;
     case 5:
     if(button==1){
     menuphase5=xyheadingdegreescalibrated/60;
     menuphase++;
     button=0;
     return;
     }
     else{
     for(int i=0; i<numPixels; i++) {
     if(i<=menuphase0){
     long color=red;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0&&i<=menuphase0+menuphase1){
     long color=magenta;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1&&i<=menuphase0+menuphase1+menuphase2){
     long color=blue;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2&&i<=menuphase0+menuphase1+menuphase2+menuphase3){
     long color=teal;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2+menuphase3&&i<=menuphase0+menuphase1+menuphase2+menuphase3+menuphase4){
     //if(i>=menuphase0+menuphase1+menuphase2+menuphase3&&i<=menuphase0+menuphase1+menuphase2+menuphase3+(xyheadingdegreescalibrated/60)){
     long color=green;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     if(i>=menuphase0+menuphase1+menuphase2+menuphase3+menuphase4&&i<=menuphase0+menuphase1+menuphase2+menuphase3+menuphase4+(xyheadingdegreescalibrated/60))
     {  
     long color=orange;
     *ptr++ = color >> 16;
     *ptr++ = color >> 8;
     *ptr++ = color;
     }
     else{
     *ptr++=0;
     *ptr++=0;
     *ptr++=0;
     }
     }
     }
     }
     }
     }
     }  
     }
     break;
     */
  }
}// //Timer1 interrupt handler. Called at equal intervals; 60 Hz by default.
void callback() {
  strip.show();

  if(menuphase!=0){
    menuphase=0;
    menuphase0=0;
    menuphase1=0;
    menuphase2=0;
  }
  // Very first thing here is to issue the strip data generated from the
  // *previous* callback. It's done this way on purpose because show() is
  // roughly constant-time, so the refresh will always occur on a uniform
  // beat with respect to the //Timer1 interrupt. The various effects
  // rendering and compositing code is not constant-time, and that
  // unevenness would be apparent if show() were called at the end.


  //  getir();

  byte frontImgIdx = 1 - backImgIdx,
  *backPtr = &imgData[backImgIdx][0],
  r, g, b;
  int i;

  // Always render back image based on current effect index:
  (*renderEffect[fxIdx[backImgIdx]])(backImgIdx);
  // Front render and composite only happen during transitions...
  if(tCounter > 0) {
    // Transition in progress
    byte *frontPtr = &imgData[frontImgIdx][0];
    int alpha, inv;

    // Render front image and alpha mask based on current effect indices...
    (*renderEffect[fxIdx[frontImgIdx]])(frontImgIdx);
    (*renderAlpha[fxIdx[2]])();


    // ...then composite front over back:
    for(i=0; i<numPixels; i++) {
      alpha = alphaMask[i] + 1; // 1-256 (allows shift rather than divide)
      inv = 257 - alpha; // 1-256 (ditto)
      // r, g, b are placed in variables (rather than directly in the
      // setPixelColor parameter list) because of the postincrement pointer
      // operations -- C/C++ leaves parameter evaluation order up to the
      // implementation; left-to-right order isn't guaranteed.
      r = gamma((*frontPtr++ * alpha + *backPtr++ * inv) >> 8);
      g = gamma((*frontPtr++ * alpha + *backPtr++ * inv) >> 8);
      b = gamma((*frontPtr++ * alpha + *backPtr++ * inv) >> 8);
      strip.setPixelColor(i, r, g, b);
    }
  }
  else {
    // No transition in progress; just show back image

      for(i=0; i<numPixels;i++) {
      // See note above re: r, g, b vars.
      r = gamma(*backPtr++);
      g = gamma(*backPtr++);
      b = gamma(*backPtr++);
      strip.setPixelColor(i, r, g, b);
    }
  }

  // Count up to next transition (or end of current one):
  if(demo==1||tCounter>=0){
    tCounter++;
  }
  if(button==1){
    tCounter=0;
    button=0;
  }

  if(tCounter == 0) { // Transition start
    if(colordemo==true){
      colorschemeselector=random(256);
    }

    if(pattern>=0){
      fxIdx[frontImgIdx]=pattern;
      pattern=-1;//
    }
    else{
      if(back==true){

        //  fxIdx[frontImgIdx]--;
        if(fxIdx[frontImgIdx]==0){
          fxIdx[frontImgIdx]=(sizeof(renderEffect) / sizeof(renderEffect[0]))-1;
        }
        else{
          fxIdx[frontImgIdx]--;
        }
        back=false;
      }
      else{
        fxIdx[frontImgIdx]++;//instead of random now its sequential
      }
    }
    if(fxIdx[frontImgIdx]>=(sizeof(renderEffect) / sizeof(renderEffect[0]))){
      fxIdx[frontImgIdx]=0;
    }

    fxIdx[2] = random((sizeof(renderAlpha) / sizeof(renderAlpha[0])));
    transitionTime = random(transitionspeed-transitionspeedvariance, transitionspeed+transitionspeedvariance); // depends on frame rate. if 240hz 120 frame = 1/2 sec
    fxVars[frontImgIdx][0] = 0; // Effect not yet initialized
    fxVars[2][0] = 0; // Transition not yet initialized
  }
  else if(tCounter >= transitionTime) { // End transition


    fxIdx[backImgIdx] = fxIdx[frontImgIdx]; // Move front effect index to back
    backImgIdx = 1 - backImgIdx; // Invert back index

      if(demo==0){ //works?
      tCounter = -1; // hold image on the edge
      button=0;
    }
    else{
      tCounter = random(-(patternswitchspeed-patternswitchspeedvariance),-(patternswitchspeed+patternswitchspeedvariance)); // Hold image ? to ? seconds
    }
  }
}
// ---------------------------------------------------------------------------
// Image effect rendering functions. Each effect is generated parametrically
// (that is, from a set of numbers, usually randomly seeded). Because both
// back and front images may be rendering the same effect at the same time
// (but with different parameters), a distinct block of parameter memory is
// required for each image. The 'fxVars' array is a two-dimensional array
// of integers, where the major axis is either 0 or 1 to represent the two
// images, while the minor axis holds 50 elements -- this is working scratch
// space for the effect code to preserve its "state." The meaning of each
// element is generally unique to each rendering effect, but the first element
// is most often used as a flag indicating whether the effect parameters have
// been initialized yet. When the back/front image indexes swap at the end of
// each transition, the corresponding set of fxVars, being keyed to the same
// indexes, are automatically carried with them.

// Simplest rendering effect: fill entire image with solid color
unsigned long usercolorscheme[8] = {
  red,orange,yellow,green,teal,blue,indigo,violet};//color scheme stored in ram 

unsigned long getschemacolor(uint8_t y){
  long color;

  if(colorschemeselector==0){
//    color = (y>7)?
    hsv2rgb((y-8)*192,255,255);//:
//    usercolorscheme[y%8];
  }
  else{
  //color = (y>7)?
  pgm_read_dword(&eightcolorschema[colorschemeselector][y%8]);//:
 // hsv2rgb((y-8)*192,255,255);
  }
  return color;
}
void schemefade(byte idx) {
  long color,color2;
  byte r,g,b,r2,g2,b2;
  if(fxVars[idx][0] == 0) {
    fxVars[idx][4]=0;//starting color
    fxVars[idx][8]=1;//starting color2
    fxVars[idx][8]=0;//alpha
    fxVars[idx][9]=0;//inverse
    fxVars[idx][10]=random(2,12)/2;
    fxVars[idx][0]=1; //init    
  }
  color = getschemacolor(fxVars[idx][4]);
  color2 = getschemacolor(fxVars[idx][5]);
  r=color >> 16;//to r
  g=color >> 8;//to g
  b=color;

  r2=color2 >> 16;//to r
  g2=color2 >> 8;//to g
  b2=color2;//to b // color = (foo >= 0) ?
  fxVars[idx][9] = 257 - abs(fxVars[idx][8]); // 1-256 (ditto)
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    *ptr++ = (r2*abs((fxVars[idx][8]))+r*fxVars[idx][9])>>8;
    *ptr++ = (g2*abs((fxVars[idx][8]))+g*fxVars[idx][9])>>8;
    *ptr++ = (b2*abs((fxVars[idx][8]))+b*fxVars[idx][9])>>8;
  }
  fxVars[idx][8]+=fxVars[idx][10];
  //fxVars[idx][8]++;
  if(fxVars[idx][8]>=255-fxVars[idx][10]){
    fxVars[idx][8]=-fxVars[idx][8];
    fxVars[idx][4]++;
  }
  if(fxVars[idx][8]<=fxVars[idx][10]&&fxVars[idx][8]>0){
    fxVars[idx][5]++;
  }
}
void schemetest(byte idx) {
  if(fxVars[idx][0] == 0) {
    byte *ptr = &imgData[idx][0];
    for(int i=0; i<numPixels; i++) {
      long color;
      color = getschemacolor(i%8); 
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
  }
}

void schemetestlongfade(byte idx) {
  long color1,color2;
  byte r1,g1,b1,r2,g2,b2;
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1] = 0;//spin opeartor
    fxVars[idx][2] = 0;//spin frame wait operator
    fxVars[idx][3] = random(5,10);//spin frame wait holder
    fxVars[idx][4]=0;//starting color
    fxVars[idx][8]=-255;//alpha
    // colorschemeselector = random(16,23);
    fxVars[idx][0]=random(60,180); //init    
  }
  if(fxVars[idx][0] == 1) {
    fxVars[idx][0]=random(60,180); //init   
  }
  // fxVars[idx][0]--;
  byte *ptr = &imgData[idx][0];
  for(int i=fxVars[idx][1]; i<numPixels; i++) {
    color1 = getschemacolor((i+fxVars[idx][4])/8);
    r1=color1 >> 16;//to r
    g1=color1 >> 8;//to g
    b1=color1;
    color2 = getschemacolor((((i+fxVars[idx][4])/8)+1));
    r2=color2 >> 16;//to r
    g2=color2 >> 8;//to g
    b2=color2;//to b
    if(abs(fxVars[idx][8])==0){
      fxVars[idx][8]=1;
    }
    *ptr++ = mixColor8(color1>>16,color2>>16,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1>>8,color2>>8,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1,color2,abs(fxVars[idx][8]));
  }
  for(int i=0; i<fxVars[idx][1]; i++) {
    color1 = getschemacolor((i+fxVars[idx][4])/8);
    r1=color1 >> 16;//to r
    g1=color1 >> 8;//to g
    b1=color1;
    color2 = getschemacolor((((i+fxVars[idx][4])/8)+1));
    r2=color2 >> 16;//to r
    g2=color2 >> 8;//to g
    b2=color2;//to b
    if(abs(fxVars[idx][8])==0){
      fxVars[idx][8]=1;
    }
    *ptr++ = mixColor8(color1>>16,color2>>16,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1>>8,color2>>8,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1,color2,abs(fxVars[idx][8]));
  }
  fxVars[idx][2]--;
  if(fxVars[idx][2]<=0){
    fxVars[idx][2]=fxVars[idx][3];

    fxVars[idx][1]++;
    if(fxVars[idx][1]>=numPixels){
      fxVars[idx][1]=0;
    }
  }
  fxVars[idx][8]++;
  if(fxVars[idx][8]==255){
    fxVars[idx][8]=-255;
  }

}
void schemetestfade(byte idx) {
  long color1,color2;
  byte r1,g1,b1,r2,g2,b2;
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=random(-16,16);
    fxVars[idx][4]=0;//starting color
    fxVars[idx][8]=-255;//alpha
    fxVars[idx][10]=random(2,6)/2;
    fxVars[idx][0]=1; //init    
  }
  byte *ptr = &imgData[idx][0];
  for(int i=abs(fxVars[idx][1]); i<numPixels; i++) {
    color1 = getschemacolor((i+fxVars[idx][4])%8);
    r1=color1 >> 16;//to r
    g1=color1 >> 8;//to g
    b1=color1;
    color2 = getschemacolor((((i+fxVars[idx][4])%8)+1));
    r2=color2 >> 16;//to r
    g2=color2 >> 8;//to g
    b2=color2;//to b
    if(abs(fxVars[idx][8])==0){
      fxVars[idx][8]=1;
    }
    *ptr++ = mixColor8(color1>>16,color2>>16,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1>>8,color2>>8,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1,color2,abs(fxVars[idx][8]));
  }
  for(int i=0; i<abs(fxVars[idx][1]); i++) {
    color1 = getschemacolor((i+fxVars[idx][4])%8);
    r1=color1 >> 16;//to r
    g1=color1 >> 8;//to g
    b1=color1;
    color2 = getschemacolor((((i+fxVars[idx][4])%8)+1));
    r2=color2 >> 16;//to r
    g2=color2 >> 8;//to g
    b2=color2;//to b
    if(abs(fxVars[idx][8])==0){
      fxVars[idx][8]=1;
    }
    *ptr++ = mixColor8(color1>>16,color2>>16,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1>>8,color2>>8,abs(fxVars[idx][8]));
    *ptr++ = mixColor8(color1,color2,abs(fxVars[idx][8]));
  }

  fxVars[idx][1]++;
  if(fxVars[idx][1]>=numPixels){
    fxVars[idx][1]=0;
  }
  fxVars[idx][8]++;
  if(fxVars[idx][8]==255){
    fxVars[idx][8]=-255;
  }
  if(fxVars[idx][8]==0){
  }
  // Serial.println(fxVars[idx][8]);

}

void schemetestlong(byte idx) {
  if(fxVars[idx][0] == 0) {
    byte *ptr = &imgData[idx][0];
    for(int i=0; i<numPixels; i++) {
      long color;
      color = getschemacolor(i/8+1); 
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
  }
}

void simpleOrbit(byte idx) {
  if(fxVars[idx][0] == 0) {
    for(int i=1;i<10;i++){
      fxVars[idx][i] =0;//spots 1-10 position
    }
    fxVars[idx][11] =1;//spots 1-10 speed
    fxVars[idx][12] =2;//speed of 10 is 1 pixel/frame
    fxVars[idx][13] =3;
    fxVars[idx][14] =4;
    fxVars[idx][15] =5;
    fxVars[idx][16] =6;
    fxVars[idx][17] =7;
    fxVars[idx][18] =8;
    fxVars[idx][19] =9;
    fxVars[idx][20] =10;
    fxVars[idx][21] = -255;//background brightness
    fxVars[idx][22] = 0;//background hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in tenth-degree units:
    fxVars[idx][0] =360*10;// init
  }
  byte *ptr = &imgData[idx][0];
  long color;
  for(int i=0; i<numPixels; i++) {
    color = hsv2rgb(fxVars[idx][22],255,127);
    for(int q=1; q<10; q++) {
      if(i==fxVars[idx][q]){
        color= getschemacolor(q);
      }
    }
    // color = getschemacolor(i%8);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }

  for(int i=1; i<10; i++){
    fxVars[idx][i] += fxVars[idx][i+10];//position += speed
    if(fxVars[idx][i]>numPixels){
      fxVars[idx][i]-=numPixels;
    }
  }
  fxVars[idx][21]++;
  fxVars[idx][22]++;
  if(fxVars[idx][22]==255){
    fxVars[idx][22]=-255;
  }
}

void onespin(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][0]=1;// init

  }
  long color;
  color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    if(i==fxVars[idx][1]){
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    //  fxVars[idx][3]+=fxVars[idx][2];
  }
  fxVars[idx][3]+=fxVars[idx][2];
}

void onespinfade(byte idx) {
  //starts with a pixelchase but instead of updating imgdata

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=6;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *ptr2 = &tempimgData[0], *ptr3 = &imgData[idx][0], *ptr4 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(i==fxVars[idx][1]){
      *ptr2++ = color >> 16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
      *ptr3++;
      *ptr3++;
      *ptr3++;
    }
    else{
      *ptr2++ = ((*ptr3++)-fxVars[idx][4]);
      *ptr2++ = ((*ptr3++)-fxVars[idx][4]);
      *ptr2++ = ((*ptr3++)-fxVars[idx][4]);
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *ptr4++;
    *ptr++ = *ptr4++;
    *ptr++ = *ptr4++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}

void accel1(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/2;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  fxVars[idx][4]=1/2;
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(random(numPixels/2)==1){
      color = hsv2rgb(random(1536),255,255);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}
void sparklefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/2;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(random(numPixels/2)==1){
      color = hsv2rgb(random(1536),255,255);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}


void schemesparklefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/2;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(random(numPixels/2)==1){
      color = getschemacolor(random(8));
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}

void schemesparklefadelong(byte idx) {
}


void accelschemesparklefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=4;//top number
    fxVars[idx][5]=5; //bottom number
    fxVars[idx][0]=1;// init
    //read accell
    // colorschemeselector = 34;
  }

  //  Serial.println((averageax+averageay+averageaz)/150);
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(i== fxVars[idx][1]){
      color = getschemacolor(0);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{

      if(random(averageax+averageay+averageaz)/150>9){
        color = getschemacolor(0);
        *tptr++ = color >> 16;
        *tptr++ = color >> 8;
        *tptr++ = color;
        *ptr2++ = color >>16;
        *ptr2++ = color >> 8;
        *ptr2++ = color;
      }
      else{
        if(random(averageax+averageay+averageaz)/150>7){
          color = getschemacolor(1);
          *tptr++ = (color >> 16)>>1;
          *tptr++ = (color >> 8)>>1;
          *tptr++ = (color)>>1;
          *ptr2++ = (color >>16)>>1;
          *ptr2++ = (color >> 8)>>1;
          *ptr2++ = (color)>>1;
        }
        else{
          if(random(averageax+averageay+averageaz)/150>1){
            color = getschemacolor(2);
            *tptr++ = (color >> 16)>>2;
            *tptr++ = (color >> 8)>>2;
            *tptr++ = (color)>>2;
            *ptr2++ = (color >>16)>>2;
            *ptr2++ = (color >> 8)>>2;
            *ptr2++ = (color)>>2;
          }
          else{

            *tptr++ = (*ptr2++ * fxVars[idx][4]/fxVars[idx][5]);
            *tptr++ = (*ptr2++ * fxVars[idx][4]/fxVars[idx][5]);
            *tptr++ = (*ptr2++ * fxVars[idx][4]/fxVars[idx][5]);
          }
        }
      }
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}

void compassschemesparklefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=17;//top number
    fxVars[idx][5]=18; //bottom number
    fxVars[idx][0]=1;// init
    //read accell

  }

  //  Serial.println((averageax+averageay+averageaz)/150);
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(random(averageax+averageay+averageaz)/150>12){
      color = getschemacolor(0);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      if(random(averageax+averageay+averageaz)/150>9){
        color = getschemacolor(1);
        *tptr++ = (color >> 16)>>1;
        *tptr++ = (color >> 8)>>1;
        *tptr++ = (color)>>1;
        *ptr2++ = (color >>16)>>1;
        *ptr2++ = (color >> 8)>>1;
        *ptr2++ = (color)>>1;
      }
      else{
        if(random(averageax+averageay+averageaz)/150>6){
          color = getschemacolor(2);
          *tptr++ = (color >> 16)>>2;
          *tptr++ = (color >> 8)>>2;
          *tptr++ = (color)>>2;
          *ptr2++ = (color >>16)>>2;
          *ptr2++ = (color >> 8)>>2;
          *ptr2++ = (color)>>2;
        }
        else{
          if(random(averageax+averageay+averageaz)/150>4){
            color = getschemacolor(3);
            *tptr++ = (color >> 16)>>3;
            *tptr++ = (color >> 8)>>3;
            *tptr++ = (color)>>3;
            *ptr2++ = (color >>16)>>3;
            *ptr2++ = (color >> 8)>>3;
            *ptr2++ = (color)>>3;
          }
          else{
            if(random(averageax+averageay+averageaz)/150>2||random(1000)==50){
              color = getschemacolor(4);
              *tptr++ = (color >> 16)>>4;
              *tptr++ = (color >> 8)>>4;
              *tptr++ = (color)>>4;
              *ptr2++ = (color >>16)>>4;
              *ptr2++ = (color >> 8)>>4;
              *ptr2++ = (color)>>4;
            }
            else{
              if(random(averageax+averageay+averageaz)/150>0){
                color = getschemacolor(5);
                *tptr++ = (color >> 16)>>5;
                *tptr++ = (color >> 8)>>5;
                *tptr++ = (color)>>5;
                *ptr2++ = (color >>16)>>5;
                *ptr2++ = (color >> 8)>>5;
                *ptr2++ = (color)>>5;
              }
              else{
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
              }
            }
          }
        }
      }
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}




void onefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=0;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/2;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(i==fxVars[idx][1]){
      color = getschemacolor(i/8);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}
void fourfade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position 1
    fxVars[idx][5]=numPixels;//position 2
    fxVars[idx][2]=random(3,6);//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/6;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(

    i==fxVars[idx][1] ||
      i==(fxVars[idx][1]+(numPixels*1/4))%numPixels||
      i==(fxVars[idx][1]+(numPixels*2/4))%numPixels||
      i==(fxVars[idx][1]+(numPixels*3/4))%numPixels||
      i==fxVars[idx][5] ||
      i==(fxVars[idx][5]+(numPixels*1/4))%numPixels||
      i==(fxVars[idx][5]+(numPixels*2/4))%numPixels||
      i==(fxVars[idx][5]+(numPixels*3/4))%numPixels


      ){
      color = getschemacolor(i/8);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    fxVars[idx][5]--;
    if(fxVars[idx][5]<=0){
      fxVars[idx][5]=numPixels; 
    }
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}
void eightfade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position 1
    fxVars[idx][5]=numPixels;//position 2
    fxVars[idx][2]=random(3,6);//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/6;//how much to drop each pixel by if not updated
    fxVars[idx][0]=1;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(

    i==fxVars[idx][1] ||
      i==(fxVars[idx][1]+(numPixels*1/4))%numPixels||
      i==(fxVars[idx][1]+(numPixels*2/4))%numPixels||
      i==(fxVars[idx][1]+(numPixels*3/4))%numPixels||
      i==fxVars[idx][5] ||
      i==(fxVars[idx][5]+(numPixels*1/4))%numPixels||
      i==(fxVars[idx][5]+(numPixels*2/4))%numPixels||
      i==(fxVars[idx][5]+(numPixels*3/4))%numPixels


      ){
      color = getschemacolor(i/8);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    fxVars[idx][5]--;
    if(fxVars[idx][5]<=0){
      fxVars[idx][5]=numPixels; 
    }
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}


void accelsparklefade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=1;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=17;//top number
    fxVars[idx][5]=18; //bottom number
    fxVars[idx][0]=1;// init
    //read accell

  }

  //  Serial.println((averageax+averageay+averageaz)/150);
  long color;
  int accelsum = averageax+averageay+averageaz;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(random(accelsum)/150>12){
      color = getschemacolor(0);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      if(random(accelsum)/150>9){
        color = getschemacolor(1);
        *tptr++ = (color >> 16)>>1;
        *tptr++ = (color >> 8)>>1;
        *tptr++ = (color)>>1;
        *ptr2++ = (color >>16)>>1;
        *ptr2++ = (color >> 8)>>1;
        *ptr2++ = (color)>>1;
      }
      else{
        if(random(accelsum)/150>6){
          color = getschemacolor(2);
          *tptr++ = (color >> 16)>>2;
          *tptr++ = (color >> 8)>>2;
          *tptr++ = (color)>>2;
          *ptr2++ = (color >>16)>>2;
          *ptr2++ = (color >> 8)>>2;
          *ptr2++ = (color)>>2;
        }
        else{
          if(random(accelsum)/150>4){
            color = getschemacolor(3);
            *tptr++ = (color >> 16)>>3;
            *tptr++ = (color >> 8)>>3;
            *tptr++ = (color)>>3;
            *ptr2++ = (color >>16)>>3;
            *ptr2++ = (color >> 8)>>3;
            *ptr2++ = (color)>>3;
          }
          else{
            if(random(accelsum)/150>2||random(1000)==50){
              color = getschemacolor(4);
              *tptr++ = (color >> 16)>>4;
              *tptr++ = (color >> 8)>>4;
              *tptr++ = (color)>>4;
              *ptr2++ = (color >>16)>>4;
              *ptr2++ = (color >> 8)>>4;
              *ptr2++ = (color)>>4;
            }
            else{
              if(random(accelsum)/150>0){
                color = getschemacolor(5);
                *tptr++ = (color >> 16)>>5;
                *tptr++ = (color >> 8)>>5;
                *tptr++ = (color)>>5;
                *ptr2++ = (color >>16)>>5;
                *ptr2++ = (color >> 8)>>5;
                *ptr2++ = (color)>>5;
              }
              else{
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
                *tptr++ = (*ptr2++)*fxVars[idx][4]/fxVars[idx][5];
              }
            }
          }
        }
      }
    }
  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}

void colorDriftmod(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=random(0,1536); //color were gonna write initally
    fxVars[idx][0] = 1; // Effect initialized
    fxVars[idx][2] =random(1,16); //increments of color drift per frame
    // fxVars[idx][2] =1; //increments of color drift per frame
  }
  byte *ptr = &imgData[idx][0];
  fxVars[idx][1]+=fxVars[idx][2];
  long color = hsv2rgb(fxVars[idx][1]%1536, 255, 255);
  for(int i=0; i<numPixels; i++) {
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}

void who(byte idx) { //spining fade taking up 7 pixels using 2 colors
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=16;//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][0]=1;// init

  }
  long color,color1;
  color = getschemacolor(0); //first color in color scheme
  color1 = getschemacolor(1); //first color in color scheme
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    if(i==fxVars[idx][1]){
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
    else{
      if(i==fxVars[idx][1]-1){
        *ptr++ = mixColor8(color>>16,color1>>16,64);
        *ptr++ = mixColor8(color>>8,color1>>8,64);
        *ptr++ = mixColor8(color,color1,64);
      }
      else{
        if(i==fxVars[idx][1]+1){
          *ptr++ = mixColor8(color1>>16,color>>16,64);
          *ptr++ = mixColor8(color1>>8,color>>8,64);
          *ptr++ = mixColor8(color1,color,64);
        }
        else{
          if(i==fxVars[idx][1]-2){
            *ptr++ = mixColor8(color>>16,color1>>16,128);
            *ptr++ = mixColor8(color>>8,color1>>8,128);
            *ptr++ = mixColor8(color,color1,128);
          }
          else{
            if(i==fxVars[idx][1]+2){
              *ptr++ = mixColor8(color1>>16,color>>16,128);
              *ptr++ = mixColor8(color1>>8,color>>8,128);
              *ptr++ = mixColor8(color1,color,128);
            }
            else{
              if(i==fxVars[idx][1]-3){
                *ptr++ = mixColor8(color>>16,color1>>16,192);
                *ptr++ = mixColor8(color>>8,color1>>8,192);
                *ptr++ = mixColor8(color,color1,192);
              }
              else{
                if(i==fxVars[idx][1]+3){
                  *ptr++ = mixColor8(color1>>16,color>>16,192);
                  *ptr++ = mixColor8(color1>>8,color>>8,192);
                  *ptr++ = mixColor8(color1,color,192);
                }
                else
                  *ptr++ = color1 >> 16;
                *ptr++ = color1 >> 8;
                *ptr++ = color1;
              }
            }
          }
        }
      } 
    }
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}

void what(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//
    fxVars[idx][2]=0;//
    fxVars[idx][3]=0;//
    fxVars[idx][4]=0;//
    fxVars[idx][5]=0;//
    fxVars[idx][6]=0;//
    fxVars[idx][7]=0;//
    fxVars[idx][8]=0;//
    fxVars[idx][9]=0;//
    fxVars[idx][10]=0;//
    fxVars[idx][0]=1;// init
  }
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    long color;
    // color = getschemacolor(i%8); 
    if (i==fxVars[idx][1]){
      color=getschemacolor(0);
    }
    else{
      if (i==fxVars[idx][2]){
        color=getschemacolor(1);
      }
      else{
        if (i==fxVars[idx][3]){
          color=getschemacolor(2);
        }
        else{
          color=black;
        }
      }
    }
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}


void blank(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1] =0;//
    fxVars[idx][2]=0;//
    fxVars[idx][3]=0;//
    fxVars[idx][4]=0;//
    fxVars[idx][5]=0;//
    fxVars[idx][6]=0;//
    fxVars[idx][7]=0;//
    fxVars[idx][8]=0;//
    fxVars[idx][9]=0;//
    fxVars[idx][10]=0;//
    fxVars[idx][0]=1;// init
  }
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    long color;
    // color = getschemacolor(i%8); 
    color=black;
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}


void compassheading(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//
    fxVars[idx][2]=0;//
    fxVars[idx][3]=0;//
    fxVars[idx][4]=0;//
    fxVars[idx][5]=0;//
    fxVars[idx][6]=0;//
    fxVars[idx][7]=0;//
    fxVars[idx][8]=0;//
    fxVars[idx][9]=0;//
    fxVars[idx][10]=0;//
    fxVars[idx][0]=1;// init
  }
  fxVars[idx][1] =map(xyheadingdegrees,0,360,0,numPixels);
  fxVars[idx][2] =map(xzheadingdegrees,0,360,0,numPixels);
  fxVars[idx][3] =map(yzheadingdegrees,0,360,0,numPixels);
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    long color;
    // color = getschemacolor(i%8); 
    if (i==fxVars[idx][1]){
      color=getschemacolor(0);
    }
    else{
      if (i==fxVars[idx][2]){
        color=getschemacolor(1);
      }
      else{
        if (i==fxVars[idx][3]){
          color=getschemacolor(2);
        }
        else{
          color=black;
        }
      }
    }
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}

void rotate(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1] =0;//
    fxVars[idx][2] =-254;
    fxVars[idx][3] = -8;
    fxVars[idx][0]=1;// init
  }
  byte *ptr = &imgData[idx][0],r,g,b,r2,g2,b2;
  r=getschemacolor(1)>>16;
  g=getschemacolor(1)>>8;
  b=getschemacolor(1);
  r2=getschemacolor(2)>>16;
  g2=getschemacolor(2)>>8;
  b2=getschemacolor(2);
  for(int i=1; i<numPixels+1; i++) {
    r =mixColor8(r,r2,abs(fxVars[idx][2]));
    g =mixColor8(g,g2,abs(fxVars[idx][2]));
    b =mixColor8(b,b2,abs(fxVars[idx][2]));
    // color = getschemacolor(i%8); 
    *ptr++ = r;
    *ptr++ = g;
    *ptr++ = b;
  }
  fxVars[idx][2]++;


  if (fxVars[idx][2]==254){
    fxVars[idx][2]= -254; 
  }
}


void compassheadingRGBFade(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//
    fxVars[idx][2]=0;//
    fxVars[idx][3]=0;//
    fxVars[idx][0]=1;// init
  }
  fxVars[idx][1] =map(xyheadingdegrees,0,360,0,255);
  fxVars[idx][2] =map(xzheadingdegrees,0,360,0,255);
  fxVars[idx][3] =map(yzheadingdegrees,0,360,0,255);
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) { 
    *ptr++ = fxVars[idx][1];
    *ptr++ = fxVars[idx][2];
    *ptr++ = fxVars[idx][3];
  }
}

void petechase(byte idx) {
  if(fxVars[idx][0] == 0) { // Initialize effect?
    fxVars[idx][1] = random(1536);
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(2 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring.  It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = random(1,35);
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][5] = fxVars[idx][1]+256;
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int  foo;
  long color, i;
  int colorX = random(2);


  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1], 255,  foo * 2 ) :
    hsv2rgb(fxVars[idx][5], 255, 254 - (foo * 2));
    *ptr++ = color >> 16; 
    *ptr++ = color >> 8; 
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];

}

void sendOnedowntheline(byte idx) {
  int i;
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//
    fxVars[idx][2]=0;//
    fxVars[idx][3]=0;//
    fxVars[idx][0]=1;// init
  }
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) { 
    *ptr++ = fxVars[idx][1];
    *ptr++ = fxVars[idx][2];
    *ptr++ = fxVars[idx][3];
  }
}

/*
void sineChase(byte idx) {
 
 if(fxVars[idx][0] == 0) {
 
 fxVars[idx][1] = random(1536); // Random hue
 // Number of repetitions (complete loops around color wheel);
 // any more than 4 per meter just looks too chaotic.
 // Store as distance around complete belt in half-degree units:
 fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
 // Frame-to-frame increment (speed) -- may be positive or negative,
 // but magnitude shouldn't be so small as to be boring. It's generally
 // still less than a full pixel per frame, making motion very smooth.
 fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
 // Reverse direction half the time.
 if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
 fxVars[idx][4] = 0; // Current position
 fxVars[idx][0] = 1; // Effect initialized
 }
 
 byte *ptr = &imgData[idx][0];
 int foo;
 long color, i;
 for(long i=0; i<numPixels; i++) {
 foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
 // Peaks of sine wave are white, troughs are black, mid-range
 // values are pure hue (100% saturated).
 color = (foo >= 0) ?
 
 *ptr++ = color >> 16;
 *ptr++ = color >> 8;
 *ptr++ = color;
 }
 fxVars[idx][4] += fxVars[idx][3];
 }
 
 */
void thingeyDrift(byte idx) {
  long i;
  uint8_t thingeynum = 3;
  if(fxVars[idx][0] == 0) {

    for(i=1;i<1+thingeynum;i++){ //1-10 thingey position!
      fxVars[idx][i]=0;
    }

    for(i=11;i<thingeynum+11;i++){ //11-20 direction/speed
      // Frame-to-frame increment (speed) -- may be positive or negative,
      // but magnitude shouldn't be so small as to be boring. It's generally
      // still less than a full pixel per frame, making motion very smooth.
      fxVars[idx][i] = random(5,60);
      // Reverse direction half the time.
      if(random(2) == 0) fxVars[idx][i] = -fxVars[idx][i]; 
    }

    for(i=21;i<21+thingeynum;i++){ //21-30 intended direction/speed
      // Frame-to-frame increment (speed) -- may be positive or negative,
      // but magnitude shouldn't be so small as to be boring. It's generally
      // still less than a full pixel per frame, making motion very smooth.
      fxVars[idx][i] = random(5,60);
      // Reverse direction half the time.
      if(random(2) == 0) fxVars[idx][i] = -fxVars[idx][i]; 
    }  
    fxVars[idx][0] = 2 * 720;// init
  }
  long foo[thingeynum];
  byte *ptr = &imgData[idx][0],r,g,b;
  for(i=0; i<numPixels ;i++) {

    for(int q=1;q<thingeynum+1;q++){  
      foo[q] = fixSin(fxVars[idx][q] + fxVars[idx][0] * i / numPixels);
      long   color = getschemacolor(8);
      r =mixColor8(r,color>>16,foo[q]*2); //bling
      g =mixColor8(g,color>>8,foo[q]*2);
      b =mixColor8(b,color,foo[q]*2);  
    }
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    //long getschemacolor(uint8_t y)


    //    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
    //    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
    //  r =mixColor8(color1>>16,color2>>16,foo*2); //bling
    //  g =mixColor8(color1>>8,color2>>8,foo*2);
    //  b =mixColor8(color1,color2,foo*2);

    *ptr++ = r;
    *ptr++ = g;
    *ptr++ = b;
  } 
  /* byte *ptr = &imgData[idx][0];
   for(int i=0; i<numPixels; i++) {
   long color;
   color = getschemacolor(i%8); 
   *ptr++ = color >> 16;
   *ptr++ = color >> 8;
   *ptr++ = color;
   }
   */
  for(i=1;i<1+thingeynum;i++){ //add position
    fxVars[idx][i] += fxVars[idx][10+i];
    if(fxVars[idx][20+i]==fxVars[idx][10+i]){ //check if intended direction is = current dirrecton
      // Frame-to-frame increment (speed) -- may be positive or negative,
      // but magnitude shouldn't be so small as to be boring. It's generally
      // still less than a full pixel per frame, making motion very smooth.
      fxVars[idx][10+i] = 4 + random(1536) / numPixels;
      // Reverse direction half the time.
      if(random(2) == 0) fxVars[idx][10+i] = -fxVars[idx][10+i]; 
    }

  }
}

void mixColor8Chase(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][10]= random(1,4);
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][12] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][13] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][14] = 0; // Current position
    fxVars[idx][0]=1;// init
  }

  //   color = (foo >= 0) ?
  //    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
  //   hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);

  byte *ptr = &imgData[idx][0],r2,g2,b2,r1,g1,b1,r,g,b;
  long color,color1,color2,t1,t2,t3,t4,foo;
  byte alpha;
  for(int i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][14] + fxVars[idx][12] * i / numPixels);
    t1 =  getschemacolor(fxVars[idx][10]);
    t2 =  getschemacolor(fxVars[idx][10]+1);     
    t3 =  getschemacolor(fxVars[idx][10]+2);
    t4 =  getschemacolor(fxVars[idx][10]+3);  
    color1 = (foo < 0) ? t1  : t2 ;
    color2 = (foo > 0) ? t3  : t4 ;
    r2=color2>>16;
    g2=color2>>8;
    b2=color2;
    //color1=black;
    r1=color1>>16;
    g1=color1>>8;
    b1=color1;
    r = mixColor8(color>>16,color2>>16,((foo-1) * 2));
    g = mixColor8(color>>8,color2>>8,((foo-1) * 2));
    b = mixColor8(color,(color2),((foo-1 )* 2));
    *ptr++ = r;
    *ptr++ = g;
    *ptr++ = b;
  }
  //  Serial.println(foo);
  fxVars[idx][14] += fxVars[idx][13];
}    
byte mixColor8(byte color1, byte color2, uint8_t alpha){
  byte inv = 257 - (alpha+1);  
  return (color1*(alpha+1)+color2*inv)>>8;
}

long mixColor24(long color1, long color2, byte alpha){
  return mixColor8(color1>>16,color2>>16,alpha),mixColor8(color1>>8,color2>>8,alpha),mixColor8(color1,color1,alpha);
}

/*
void orbit(byte idx) {
 if(fxVars[idx][0] == 0) {
 fxVars[idx][1] =numPixels*6;//
 fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
 // Frame-to-frame increment (speed) -- may be positive or negative,
 // but magnitude shouldn't be so small as to be boring. It's generally
 // still less than a full pixel per frame, making motion very smooth.
 fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
 // Reverse direction half the time.
 if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];     fxVars[idx][4]=0;//
 fxVars[idx][4] = 0; // Current position
 fxVars[idx][5]=0;//buddy0
 fxVars[idx][6]=0;//buddy1
 fxVars[idx][7]=0;//buddy2
 fxVars[idx][8]=0;//buddy3
 fxVars[idx][9]=0;//buddy4
 fxVars[idx][10]=0;//buddy 5
 fxVars[idx][0]=1;// init
 
 
 }
 long color,foo;
 
 
 
 byte *ptr = &imgData[idx][0];
 for(int i=0; i<numPixels; i++) {
 foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
 long color;
 
 
 // color = getschemacolor(i%8); 
 color = (foo >= 0) ?
 hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
 hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
 *ptr++ = color >> 16;
 *ptr++ = color >> 8;
 *ptr++ = color;
 }
 fxVars[idx][4] += fxVars[idx][3];
 }
 */

void colorDrift(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][11]=random(0,1536); //color were gonna write initally
    fxVars[idx][10] = 1; // Effect initialized
    fxVars[idx][12] =random(1,8); //increments of color drift per frame
    // fxVars[idx][2] =1; //increments of color drift per frame
  }
  byte *ptr = &imgData[idx][0];
  fxVars[idx][11]+=fxVars[idx][12];
  long colord = hsv2rgb(fxVars[idx][11], 255, 255);
  for(int i=0; i<numPixels; i++) {
    *ptr++ = colord >> 16;
    *ptr++ = colord >> 8;
    *ptr++ = colord;
  }
}

void strobe(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1] = 0; //
    fxVars[idx][2] = random(0,2); //increments of color drift per frame
    fxVars[idx][3] = 0; //strobe indicator, 0 is nothing written for the frame and anything else is write
    fxVars[idx][4] = 0; //frame counter 0-120
    fxVars[idx][5] = random(0,2); //dutycycle, 1-5 for 10-90%
    fxVars[idx][6] = random(0,5);//effect type,0 is one color strobe,1 is 2 color,2 is 3 color
    fxVars[idx][7] = random(0,1);//if 1 replace black with second color 9
    fxVars[idx][8] = 60; // strobe duty cycle value
    fxVars[idx][9] = 0; //
    fxVars[idx][0] = 1; // Effect initialized
  }
  //fxVars[idx][7]++;
  //if(fxVars[idx][7]==fxVars[idx][8]){
  // fxVars[idx][7]=0;
  // fxVars[idx][5]++;}
  byte *ptr = &imgData[idx][0];
  fxVars[idx][1]+=fxVars[idx][2];
  if(fxVars[idx][1]>1536-fxVars[idx][1]){
    fxVars[idx][1]=fxVars[idx][1]%1536;
  }
  for(int i=0; i<numPixels; i++) {
    long color;
    //color = hsv2rgb(fxVars[idx][1],255, 255);
    color = getschemacolor(fxVars[idx][1]);
    if(fxVars[idx][3]==0){

      *ptr++ = 0;
      *ptr++ = 0;
      *ptr++ = 0;
    }
    else{
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;

    }

  }
  if(fxVars[idx][3]!=0){
    fxVars[idx][1]++;
    fxVars[idx][1]%=7;
  }
  //Serial.println(fxVars[idx][1]);
  switch(abs(fxVars[idx][5])) //dutycycle=0-9
  {
  case 0://10%ducy cycle
    if(fxVars[idx][4]%2==0){
      fxVars[idx][3]=1;
    }
    else{
      fxVars[idx][3]=0;
    }
    break;

  case 1://20%ducy cycle
    if(fxVars[idx][4]%5==0){
      fxVars[idx][3]=1;
    }
    else{
      fxVars[idx][3]=0;
    }
    break;
  case 2://30%ducy cycle
    if(fxVars[idx][4]%10==0){
      fxVars[idx][3]=1;
    }
    else{
      fxVars[idx][3]=0;
    }
    break;
  case 3://40%ducy cycle
    if(fxVars[idx][4]%40==0){
      fxVars[idx][3]=1;
    }
    else{
      fxVars[idx][3]=0;
    }
    break;
  case 4://50%ducy cycle
    if(fxVars[idx][4]%50==0){
      fxVars[idx][3]=1;
    }
    else{
      fxVars[idx][3]=0;
    }
    break;
  }
  if(fxVars[idx][4]>=100){ //keep track of frames passed
    fxVars[idx][4]=1;
  }
  else{
    fxVars[idx][4]=fxVars[idx][4]+1;
  }
  if(fxVars[idx][4]%24==1){
    // fxVars[idx][5]++;
  }
  if(fxVars[idx][5]>2){
    fxVars[idx][5]=-1;
  }
  //Serial.println(fxVars[idx][5]);
}
void RandomColorsEverywhere(byte idx) {
  byte *ptr = &imgData[idx][0];
  for (int i=0;i<numPixels; i++){
    byte r = random(256), g = random(256), b = random(256);
    *ptr++ =r;
    *ptr++ =g;
    *ptr++ =b;
  }
}

void rainStrobe2at1(byte idx){
  crazycounter++;
  if(crazycounter>50){
    crazycounter=0;
  }

  if(crazycounter>25){
    fxVars[0][0]=0;
    strobe(idx);
  }
  else{
    fxVars[0][0]=0;
    rainbowChase(idx);
  }
}

void raindance(byte idx){
  if(fxVars[idx][0] == 0) {
    // Number of repetitions (complete loops around color wheel); any
    // more than 4 per meter just looks too chaotic and un-rainbow-like.
    // Store as hue 'distance' around complete belt:
    fxVars[idx][1] = (1 + random(4 * ((numPixels + 31) / 32)))*768;
    // Frame-to-frame hue increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][2] = 250;
    // Reverse speed and hue shift direction half the time.
    if(random(2) == 0) fxVars[idx][1] = -fxVars[idx][1];
    if(random(2) == 0) fxVars[idx][2] = -fxVars[idx][2];
    fxVars[idx][3] = 0; //position
    fxVars[idx][4] = 100 + random(fxVars[idx][1]*100) / numPixels;//next speed
    fxVars[idx][5] = random(300); // countdown to next change after speed match
    fxVars[idx][0] = 1; // Effect initialized
  }
  if(fxVars[idx][0] == -1) {
    if(fxVars[idx][4]>=0){

      fxVars[idx][4] =-1*( 25 + random(fxVars[idx][1]) / numPixels);
    }
    else{
      if(fxVars[idx][4]<0){
        fxVars[idx][4] = 25 + random(fxVars[idx][1]) / numPixels;
      } 
    }
    //   if(random(2) == 0) fxVars[idx][2] = -fxVars[idx][2];
    fxVars[idx][5] = random(60); // countdown to next change after speed match
    fxVars[idx][0] = 1; // Effect initialized
  }

  if(fxVars[idx][4]==fxVars[idx][2]){
    fxVars[idx][5]--;
    if(fxVars[idx][5]==0){
      fxVars[idx][0]=-1;//new speed and counter
    }
  }
  else{
    if(fxVars[idx][4]>fxVars[idx][2]){
      fxVars[idx][2]++;    
    }
    else{
      if(fxVars[idx][4]<fxVars[idx][2]){
        fxVars[idx][2]--;    
      }     
    }
  }
  byte *ptr = &imgData[idx][0];
  long color, i;
  for(i=0; i<numPixels; i++) {
    color = hsv2rgb(fxVars[idx][3] + fxVars[idx][1] * i / numPixels,
    255, 255);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][3] += fxVars[idx][2];
}
void schemetestlongrain2at1(byte idx){
  crazycounter++;
  if(crazycounter>90){
    crazycounter=0;
  }

  if(crazycounter>45){
    fxVars[0][0]=0;
    strobe(idx);
  }
  else{
    fxVars[0][0]=0;
    rainbowChase(idx);

  }

}
void schemetestrain2at1(byte idx){
  crazycounter++;
  if(crazycounter>90){
    crazycounter=0;
  }

  if(crazycounter>45){
    fxVars[0][0]=0;
    schemetest(idx);
  }
  else{
    fxVars[0][0]=0;
    rainbowChase(idx);

  }

}

void schemetest2at1(byte idx){
  crazycounter++;
  if(crazycounter>90){
    crazycounter=0;
  }

  if(crazycounter>45){
    fxVars[0][0]=0;
    schemetest(idx);
  }
  else{
    fxVars[0][0]=0;
    schemetestlong(idx);

  }

}
void strobefans2at1(byte idx){
  crazycounter++;
  if(crazycounter>120){
    crazycounter=0;
  }

  if(crazycounter>16){
    fxVars[0][0]=0;
    fans(idx);
  }
  else{
    fxVars[0][0]=0;
    strobe(idx);

  }

}
void MonsterStrobe2at1(byte idx){
  crazycounter++;
  if(crazycounter>60){
    crazycounter=0;
  }

  if(crazycounter>30){
    fxVars[0][0]=0;
    strobe(idx);
  }
  else{
    fxVars[0][0]=0;
    MonsterHunter(idx);

  }

}



void fans(byte idx) {
  if(fxVars[idx][0] == 0) {
    int i;
    fxVars[idx][1]=random(1536); //color were gonna use to cycle
    fxVars[idx][2]=numPixels/random(2,8); //using this to determine the # of sections between 2 and 8
    fxVars[idx][3]=0;//frame counter operator. starts at 1 and is incremented every frame,
    fxVars[idx][4]=0;//# of frames until next change
    fxVars[idx][6]=fxVars[idx][2]*2;//number of different levels
    fxVars[idx][5]=-fxVars[idx][6]+1;// level operator
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8]=fxVars[idx][2];// this is the number of times to cut up the 1536 increment wheel. 2=opposite colors, 3 == a triangle, 4= a square
    //using fxVars[idx][2] here makes the whole stretch minus the remainder go once around the clolr wheel
    fxVars[idx][9]=0;//
    fxVars[idx][0]=1;// Effect initialized
  }
  if(fxVars[idx][0] == -1) { //re init
  }
  byte *ptr = &imgData[idx][0];
  long color;
  for(int i=0; i<numPixels/fxVars[idx][2]; i++) {
    for(int i=0; i<fxVars[idx][2]; i++) {
      if(fxVars[idx][6]/fxVars[idx][2]*i>abs(fxVars[idx][5])){//number of levels(frames) to change over nubmer of leds gives change per pixel
        // color = hsv2rgb(fxVars[idx][1]+((1536/fxVars[idx][8])*fxVars[idx][7]), 255, 255);
        color = getschemacolor(fxVars[idx][7]);
        *ptr++ = color >> 16;
        *ptr++ = color >> 8;
        *ptr++ = color;
      }
      else{
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = 0;
      }
    }
    fxVars[idx][7]++;
    fxVars[idx][5]++; //increment level operator
    if(fxVars[idx][5]>=fxVars[idx][6]){ //if level operator == number of levels
      fxVars[idx][5]=-fxVars[idx][6]+1;
    }
  }
  for(int i=0; i<numPixels%fxVars[idx][2]; i++) {// do the same thing here, this is for the remainder
    if(fxVars[idx][6]/fxVars[idx][2]*i>abs(fxVars[idx][5])){//number of levels to change over nubmer of leds gives change per pixel
      color = hsv2rgb(fxVars[idx][1]+((1536/fxVars[idx][8])*fxVars[idx][7]),
      255, 255);
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
    else{
      *ptr++ = 0;
      *ptr++ = 0;
      *ptr++ = 0;
    }
  }
  fxVars[idx][7]=0;
}

void scrolls(byte idx) {
  byte r1,r2,g1,g2,b1,b2,alpha,color1,color2;
  if(fxVars[idx][0] == 0) {
    int i;
    fxVars[idx][1]=0;//frame counter operator
    fxVars[idx][2]=2; //change every this # frames
    fxVars[idx][3]=0;//
    fxVars[idx][4]=0;//# of frames until next change
    fxVars[idx][6]=fxVars[idx][2]*2;//number of different levels
    fxVars[idx][5]=-fxVars[idx][6]+1;// level operator
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8]=8; //top level of whatever counter
    fxVars[idx][9]=-fxVars[idx][8];
    fxVars[idx][10]=254; //top level of alpha counter
    fxVars[idx][11]=-fxVars[idx][10]; //alpha operator
    fxVars[idx][0]=1;// Effect initialized
  }
  if(fxVars[idx][0] == -1) { //re init
  }
  fxVars[idx][1]++;
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels/fxVars[idx][2]; i++) {
    for(int i=0; i<fxVars[idx][2]; i++) {
      color1 = getschemacolor(i+abs(fxVars[idx][9]));
      r1=color1>>16;
      g1=color1>>8;
      b1=color1;
      color2 = getschemacolor(i+abs(fxVars[idx][9])+1);
      r2=color2>>16;
      g2=color2>>8;
      b2=color2;

      *ptr++ = mixColor8(r1,r2,abs(fxVars[idx][11]));
      *ptr++ = mixColor8(g1,g2,abs(fxVars[idx][11]));
      *ptr++ = mixColor8(b1,b2,abs(fxVars[idx][11]));
    }
  }
  fxVars[idx][11]++;
  if(fxVars[idx][1]%fxVars[idx][2]==0){
    fxVars[idx][9]++;
    fxVars[idx][9]%=fxVars[idx][8];
  }

  if(fxVars[idx][11]==fxVars[idx][10]){
    fxVars[idx][11]=-fxVars[idx][10];
  }

  if(fxVars[idx][11]==0){
    fxVars[idx][9]++;
    fxVars[idx][9]%=fxVars[idx][8];
  }

  for(int i=0; i<numPixels%fxVars[idx][2]; i++) {// do the same thing here, this is for the remainder
    color1 = getschemacolor(i%8);
    *ptr++ = color1 >> 16;
    *ptr++ = color1 >> 8;
    *ptr++ = color1;
  }
}




void Dice(byte idx){
  findplane();
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;
    fxVars[idx][2]=1;
    fxVars[idx][3]=2;
    fxVars[idx][4]=3;
    fxVars[idx][5]=4;
    fxVars[idx][6]=5;
    fxVars[idx][7]=0;
    fxVars[idx][0]=1; //effect init
  }
  if(plane>0){
    fxVars[idx][7]=plane;
  }
  else{
    fxVars[idx][7]=abs(plane)*2;
  }
  byte *ptr = &imgData[idx][0];
  for(int i=0; i<numPixels; i++) {
    long color;
    // color = hsv2rgb(fxVars[idx][fxVars[idx][7]],255, 255);
    color = getschemacolor(fxVars[idx][7]);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}




//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************
void colorflag(byte idx){
  colorPOV(idx, 0); 
}
void testcolorPOV(byte idx){
  colorPOV(idx, 1); 
}
void PlaidPOV(byte idx){
  colorPOV(idx, 2); 
}
void SmallCirclePOV(byte idx){
  colorPOV(idx, 3); 
}
void QuadHelixPOV(byte idx){
  colorPOV(idx, 4); 
}
void WavePOV(byte idx){
  colorPOV(idx, 5); 
}
void FourWayCheckersPOV(byte idx){
  colorPOV(idx, 6); 
}
void FourColorCheckersPOV(byte idx){
  colorPOV(idx, 7); 
}
void ZigZagPOV(byte idx){
  colorPOV(idx, 8); 
}
void CrazyCirclesPOV(byte idx){
  colorPOV(idx, 9); 
}
void SpreadPOV(byte idx){
  colorPOV(idx, 10); 
}
void TimePOV(byte idx){
  colorPOV(idx, 11); 
}
void SlagPOV(byte idx){
  colorPOV(idx, 12); 
}
void AmericanFlagPOV(byte idx){
  colorPOV(idx, 13); 
}
void RingsPOV(byte idx){
  colorPOV(idx, 14); 
}
void ArrowPOV(byte idx){
  colorPOV(idx, 15); 
}
void MultiBoxPOV(byte idx){
  colorPOV(idx, 16); 
}
void NewPOV(byte idx){
  colorPOV(idx, 17); 
}
void CrossTheTPOV(byte idx){
  colorPOV(idx, 18); 
}
void TheBigDownPOV(byte idx){
  colorPOV(idx, 19); 
}
void TheBigDownSquarePOV(byte idx){
  colorPOV(idx, 20); 
}
void UpDownPOV(byte idx){
  colorPOV(idx, 21); 
}
void DoubleDimePOV(byte idx){
  colorPOV(idx, 22); 
}
void OneColorStrobe(byte idx){
  colorPOV(idx, 23); 
}
void TwoColorStrobe(byte idx){
  colorPOV(idx, 24); 
}
void FourColorStrobe(byte idx){
  colorPOV(idx, 25); 
}
void SparkleLights(byte idx){
  colorPOV(idx, 26); 
}
void Bam(byte idx){
  colorPOV(idx, 27); 
}
void IDK(byte idx){
  colorPOV(idx, 28); 
}
void colorPOV(byte idx, byte imageSelector2) {
  if(fxVars[idx][0] == 0) {

    // fxVars[idx][1]=random(32)*48; //color were gonna use to cycle
    fxVars[idx][2]=16; //either 8 or 16 (scale of 1 or 2 ), usedto determine # of pixels in height; our character table is 8 x 6
    fxVars[idx][3]=0;//frame counter operator. starts at 1 and is incremented every frame,
    fxVars[idx][4]=0;//# of frames until next change
    fxVars[idx][6]=15;//number of different levels or time. a level is incremented every x# of frames; character table is 8x6
    fxVars[idx][5]=0;// level operator gets a ++ every loop and is set to -9 when @ 10 and abs() when called so it oscillates
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8]=fxVars[idx][2];// this is the number of times to cut up the 1536 increment wheel. 2=opposite colors, 3 == a triangle, 4= a square
    fxVars[idx][9]=0;// character counter
    fxVars[idx][0]=1;// Effect initialized
  }

  // uint32_t data=pgm_read_word (&rgbImages[imageSelector2][fxVars[idx][5]]); //
  byte *ptr = &imgData[idx][0];

  for(int i=0; i<numPixels/fxVars[idx][2]; i++) {

    for(int q=0; q<fxVars[idx][2]; q++) {
      
 //     long color = (foo >= 0) ?
 //   hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
 //   hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
      long color = getschemacolor(pgm_read_byte(&rgbImages[imageSelector2][fxVars[idx][5]+(fxVars[idx][3]*16)]));
      *ptr++ = color>>16;
      *ptr++ = color>>8;
      *ptr++ = color;
       fxVars[idx][5]++;
    }
    fxVars[idx][5]=0;
    fxVars[idx][7]++;
  }
  for(int q=0; q<fxVars[idx][2]; q++) {
    long color = (getschemacolor(pgm_read_byte(&rgbImages[imageSelector2][fxVars[idx][5]+(fxVars[idx][3]*16)])));
    *ptr++ = color>>16;
    *ptr++ = color>>8;
    *ptr++ = color;
     fxVars[idx][5]++;
  }
  fxVars[idx][5]=0;
  fxVars[idx][7]=0;
 
   fxVars[idx][3]++;
  if(fxVars[idx][3]>=15){
    fxVars[idx][3]=0;

  }
  // fxVars[idx][5]++;
//  if(fxVars[idx][5]>=fxVars[idx][6]) // if level operator > level holder then increment character and check for overflow
 // {
  //  fxVars[idx][5]=0;
 // }
}
//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************

//*******************************************************************


void HeartPOV(byte idx){
  picPOV(idx, 0); 
}
void StarPOV(byte idx){
  picPOV(idx, 1); 
}
void WavyPOV(byte idx){
  picPOV(idx, 2); 
}
void MoonPOV(byte idx){
  picPOV(idx, 3); 
}
void CatPOV(byte idx){
  picPOV(idx, 4); 
}
void OooPOV(byte idx){
  picPOV(idx, 5); 
}
void MazePOV(byte idx){
  picPOV(idx, 6); 
}
void ChainsPOV(byte idx){
  picPOV(idx, 7); 
}
void MiniTriPOV(byte idx){
  picPOV(idx, 8); 
}
void FourSquare(byte idx){
  picPOV(idx, 9); 
}
void Checkerboard(byte idx){
  picPOV(idx, 10); 
}
void Slider(byte idx){
  picPOV(idx, 11); 
}
void Smiley(byte idx){
  picPOV(idx, 12); 
}
void Float(byte idx){
  picPOV(idx, 13); 
}
void Zag(byte idx){
  picPOV(idx, 14); 
}
void NewCircle(byte idx){
  picPOV(idx, 15); 
}
void DoubleHelix(byte idx){
  picPOV(idx, 16); 
}
void Bubbles(byte idx){
  picPOV(idx, 17); 
}
void Move(byte idx){
  picPOV(idx, 18); 
}
void DiagCheckers(byte idx){
  picPOV(idx, 19); 
}


void picPOV(byte idx, byte imageSelector) {
  if(fxVars[idx][0] == 0) {

    // fxVars[idx][1]=random(32)*48; //color were gonna use to cycle
    fxVars[idx][2]=16; //either 8 or 16 (scale of 1 or 2 ), usedto determine # of pixels in height; our character table is 8 x 6
    fxVars[idx][3]=0;//frame counter operator. starts at 1 and is incremented every frame,
    fxVars[idx][4]=0;//# of frames until next change
    fxVars[idx][6]=16;//number of different levels or time. a level is incremented every x# of frames; character table is 8x6
    fxVars[idx][5]=0;// level operator gets a ++ every loop and is set to -9 when @ 10 and abs() when called so it oscillates
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8] = fxVars[idx][2];// this is the number of times to cut up the 1536 increment wheel. 2=opposite colors, 3 == a triangle, 4= a square
    fxVars[idx][9]=0;// character counter
    fxVars[idx][11]=random(0,1536); //color were gonna write initally
    fxVars[idx][12] =random(1,16); //increments of color drift per frame
    fxVars[idx][0]=1;// Effect initialized

  }
  //fxVars[idx][1]=random(10000);
  // byte R,G,B;
  //      long color=hsv2rgb(fxVars[idx][1],255,255);
  //      R=color>>16;
  //      G=color>>8;
  //      B=color; 

  fxVars[idx][3]++;
  uint16_t data=pgm_read_word (&Images[imageSelector][fxVars[idx][5]]); //
  byte *ptr = &imgData[idx][0];
  fxVars[idx][11]+=fxVars[idx][12];
  long colord = hsv2rgb(fxVars[idx][11], 255, 255);
  for(int i=0; i<numPixels/fxVars[idx][2]; i++) {

    for(int q=0; q<fxVars[idx][2]; q++) {
      if((data>>q)&1){
        *ptr++ = colord >> 16;
        *ptr++ = colord >> 8;
        *ptr++ = colord;
        /// *ptr++ = color;
        // *ptr++ = color;
        // *ptr++ = color;

      }
      else{
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = 0;
      }
    }
    fxVars[idx][7]++;
  }
  for(int i=0; i<numPixels&fxVars[idx][2]-1; i++) {//this is for the remainder
    *ptr++ = 0;
    *ptr++ = 0;
    *ptr++ = 0;
  }
  // if(fxVars[idx][3]>=fxVars[idx][4]){
  //   fxVars[idx][3]=0;
  fxVars[idx][5]++;
  //  }
  if(fxVars[idx][5]>=fxVars[idx][6]) // if level operator > level holder then increment character and check for overflow
  {
    fxVars[idx][5]=0;
  }
}
void POV(byte idx) {
  const String Message[4] = {
    "CREATE ",
    "MAKE ",
    "HACK ",
    "KolaHoops.com ",
  };
  const String led_chars_index =" ! #$%&'()*+,-./0123456789:;>=<?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~~";
  if(fxVars[idx][0] == 0) {
    int i;
    fxVars[idx][1]=random(1536); //color were gonna use to cycle
    fxVars[idx][2]=16; //either 8 or 16 (scale of 1 or 2 ), used to determine # of pixels in height; our character table is 8 x 6
    fxVars[idx][3]=0;//frame counter operator. starts at 1 and is incremented every frame,
    fxVars[idx][4]=0;//# of frames until next change
    fxVars[idx][6]=6;//number of different levels or time. a level is incremented every x# of frames; character table is 8x6
    fxVars[idx][5]=0;// level operator gets a ++ every loop and is set to -9 when @ 10 and abs() when called so it oscillates
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8] = fxVars[idx][2];// this is the number of times to cut up the 1536 increment wheel. 2=opposite colors, 3 == a triangle, 4= a square
    //using fxVars[idx][2] here makes the whole stretch minus the remainder go once around the clolr wheel
    fxVars[idx][9]=0;// character counter
    fxVars[idx][10]=random(0,sizeof(Message)/7);// determines message for the message array. 0 = KolaHoops.com, 1=make,2=hack,3=build
    //  Serial.println(sizeof(Message)/7);
    // fxVars[idx][11]= random(0,10); //if greater than 5,change the message after it finishes

    fxVars[idx][0]=1;// Effect initialized
  }
  // if(fxVars[idx][0] == -1) { //re init
  // }
  fxVars[idx][3]++;
  byte *ptr = &imgData[idx][0];
  long color;
  for(int i=0; i<numPixels/fxVars[idx][2]; i++) {
    byte data=pgm_read_byte (&led_chars[led_chars_index.indexOf(Message[fxVars[idx][10]].charAt(fxVars[idx][9]))][fxVars[idx][5]]); //
    for(int i=0; i<fxVars[idx][2]; i++) {
      if((data>>(i/2))&1){
        //led_chars_index.indexOf(Message.charAt(fxVars[idx][9]))
        *ptr++ = 255;
        *ptr++ = 0;
        *ptr++ = 0;
      }
      else{
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = 0;
      }
    }
    fxVars[idx][7]++;
  }
  for(int i=0; i<numPixels%fxVars[idx][2]; i++) {//this is for the remainder
    *ptr++ = 0;
    *ptr++ = 0;
    *ptr++ = 0;
  }
  // if(fxVars[idx][3]>=fxVars[idx][4]){
  //   fxVars[idx][3]=0;
  fxVars[idx][5]++;
  //  }
  if(fxVars[idx][5]>=fxVars[idx][6]) // if level operator > level holder then increment character and check for overflow
  {
    fxVars[idx][5]=0;
    fxVars[idx][9]++;
    if(fxVars[idx][9]>=Message[fxVars[idx][10]].length()){
      fxVars[idx][9]=0;
    }
    //Serial.println(fxVars[idx][5]);
    fxVars[idx][7]=0;
  }
}




void Whacky(byte idx) {
  const String Message[15] = {
    ":.",
    "/",
    "01",
    "X",
    "!",
    "$",
    "?",
    "#",
    ":=-=",
    "!$?#@&*",
    "<>",

    "{|}",
    "[]",
    "~-^-",
    "()"

  };
  const String led_chars_index =" ! #$%&'()*+,-./0123456789:;>=<?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~~";
  if(fxVars[idx][0] == 0) {
    int i;
    fxVars[idx][1]=random(1536); //color were gonna use to cycle
    fxVars[idx][2]=8; //either 8 or 16 (scale of 1 or 2 ), used to determine # of pixels in height; our character table is 8 x 6
    fxVars[idx][3]=0;//frame counter operator. starts at 1 and is incremented every frame,
    fxVars[idx][4]=16;//# of frames until next change
    fxVars[idx][6]=6;//number of different levels or time. a level is incremented every x# of frames; character table is 8x6
    fxVars[idx][5]=0;// level operator gets a ++ every loop and is set to -9 when @ 10 and abs() when called so it oscillates
    fxVars[idx][7]=0;//using this to keep track of which section we're writing to, operator of fxVars[idx][2]. starts at 0
    fxVars[idx][8] = fxVars[idx][2];// this is the number of times to cut up the 1536 increment wheel. 2=opposite colors, 3 == a triangle, 4= a square
    //using fxVars[idx][2] here makes the whole stretch minus the remainder go once around the clolr wheel
    fxVars[idx][9]=0;// character counter
    // fxVars[idx][10]=random(0,15);// determines message for the message array. 0 = KolaHoops.com, 1=make,2=hack,3=build, 4 = a bunch of

    fxVars[idx][10]=0;
    fxVars[idx][11]=-127;//even fade counter
    fxVars[idx][12]=0;//odd fade counter
    fxVars[idx][13]=0;//rotation position
    fxVars[idx][14]=24;//rotation wait holder
    fxVars[idx][15]=0;//rotation wait operator
    fxVars[idx][16]=random(fxVars[idx][14]);//intended rotation wait holder
    fxVars[idx][17]=fxVars[idx][14];//maximum slowness
    //  fxVars[idx][13]=0;//rotation operator

    // fxVars[idx][11]= random(0,10); //if greater than 5,change the message after it finishes
    fxVars[idx][0]=600;// Effect initialized
  }
  if(fxVars[idx][0]==1){
    fxVars[idx][0]=600;// Effect initialized
    fxVars[idx][10]=random(0,15);
  }
  // if(fxVars[idx][0] == -1) { //re init
  // }
  fxVars[idx][11]++;
  fxVars[idx][12]++;
  if(fxVars[idx][11]>=255){
    fxVars[idx][11]=-255; 
  }
  if(fxVars[idx][12]>=255){
    fxVars[idx][12]=-255; 
  }
  fxVars[idx][3]++;
  byte *ptr = &imgData[idx][0];
  long color=hsv2rgb(fxVars[idx][1],255,abs(fxVars[idx][11])),color2=hsv2rgb(fxVars[idx][1]+512,255,64);
  fxVars[idx][1]++;

  for(int i=fxVars[idx][13]/fxVars[idx][2]; i<numPixels/fxVars[idx][2]; i++) {
    byte data=pgm_read_byte (&led_chars[led_chars_index.indexOf(Message[fxVars[idx][10]].charAt(fxVars[idx][9]))][fxVars[idx][5]]); //
    for(int i=0; i<fxVars[idx][2]; i++) {
      if((data>>(i/2))&1){
        //led_chars_index.indexOf(Message.charAt(fxVars[idx][9]))
        //       if(fxVars[idx][7]%2==1){
        *ptr++ = color2>>16;
        //       }else{
        //          *ptr++ = abs(fxVars[idx][12]);
        //        }
        // *ptr++ = 255;
        *ptr++ = color2>>8;
        *ptr++ = color2;
      }
      else{
        *ptr++ = color>>16;
        *ptr++ = color>>8;
        *ptr++ = color;
      }
    }
    fxVars[idx][7]++;
  }
  for(int i=0; i<fxVars[idx][13]%fxVars[idx][2]; i++) {//this is for the remainder
    *ptr++ = 0;
    *ptr++ = 0;
    *ptr++ = 0;
  }
  for(int i=0; i<fxVars[idx][13]/fxVars[idx][2]; i++) {
    byte data=pgm_read_byte (&led_chars[led_chars_index.indexOf(Message[fxVars[idx][10]].charAt(fxVars[idx][9]))][fxVars[idx][5]]); //
    for(int i=0; i<fxVars[idx][2]; i++) {
      if((data>>(i/2))&1){
        //led_chars_index.indexOf(Message.charAt(fxVars[idx][9]))
        if(fxVars[idx][7]%2==1){
          *ptr++ = abs(fxVars[idx][11]);
        }
        else{
          *ptr++ = abs(fxVars[idx][12]);
        }
        // *ptr++ = 255;
        *ptr++ = 0;
        *ptr++ = 0;
      }
      else{
        *ptr++ = color>>16;
        *ptr++ = color>>8;
        *ptr++ = color;
      }
    }
    fxVars[idx][7]++;
  }
  for(int i=0; i<fxVars[idx][13]%fxVars[idx][2]; i++) {//this is for the remainder
    *ptr++ = 0;
    *ptr++ = 0;
    *ptr++ = 0;
  }
  fxVars[idx][15]++;
  Serial.println(fxVars[idx][15]);
  if(fxVars[idx][15]>=fxVars[idx][14]){
    fxVars[idx][13]++;
    fxVars[idx][15]=0;

    if(fxVars[idx][16]>fxVars[idx][14]){
      fxVars[idx][14]++; 
    }
    else{
      if(fxVars[idx][16]<fxVars[idx][14]){
        fxVars[idx][14]--; 
      }
      else{
        if(fxVars[idx][16]==fxVars[idx][14]){
          fxVars[idx][16]=random(fxVars[idx][17]);//intended rotation wait holder
        }
      } 
    }
  }
  fxVars[idx][3]++;//increment frame wait
  if(fxVars[idx][3]>=fxVars[idx][4]){// if frame operator >= frame holder
    fxVars[idx][3]=0;//reset frame operator
    fxVars[idx][5]++;//increment the coloum, checks bellow
    //  }
    if(fxVars[idx][5]>=fxVars[idx][6]) // if level operator > level holder then increment character and check for overflow
    {
      fxVars[idx][5]=0;
      fxVars[idx][9]++;
      if((fxVars[idx][9]+1)>=Message[fxVars[idx][10]].length()){
        fxVars[idx][9]=0;
      }
      //Serial.println(fxVars[idx][5]);
      fxVars[idx][7]=0;
    }
  }
}


void blankfade(byte idx) {

  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=0;//position
    fxVars[idx][2]=random(8,16);//frame skip holder
    fxVars[idx][3]=fxVars[idx][2];//frame skip operator
    fxVars[idx][4]=1/2;//how much to drop each pixel by if not updated
    fxVars[idx][0]=0;// init

  }
  long color;
  //color = getschemacolor(0); //first color in color scheme
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(int i=0; i<numPixels; i++) {//write to temp strip so we can remember our data!
    if(i==fxVars[idx][1]){
      color=hsv2rgb(1536*i/numPixels,255,255);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >>16;
      *ptr2++ = color >> 8;
      *ptr2++ = color;
    }
    else{
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
      *tptr++ = (*ptr2++)*4/5;
    }

  }
  for(int i=0; i<numPixels; i++) {//copy temp strip to regular strip for write at end of callback
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
    *ptr++ = *tptr2++;
  }
  if(fxVars[idx][1]>=fxVars[idx][0]){//if position at limit then
    fxVars[idx][1]=0;
  }
  fxVars[idx][3]--;
  if(fxVars[idx][3]<=0){
    fxVars[idx][1]++;
    if(fxVars[idx][1]>numPixels){
      fxVars[idx][1]=0; 
    }
    fxVars[idx][3]=fxVars[idx][2];
  }
}
/*
void halfrandom(byte idx) {
 if(fxVars[idx][0]==0){
 int front =random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 int back = random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 fxVars[idx][0]=1;
 }
 numPixels = numPixelsHolder/2;//set numPixels to half; we are doing 2 renders for each frame and slapping them togeather for full strip
 byte *ptr = &imgData[idx][0], *ptr2 = &imgData[idx][numPixels*3];//
 
 // Render front image and alpha mask based on current effect indices...
 (*renderEffect[fxIdx[front]])(front);//generate 2nd half in 1st half spot
 for(int i=0;i<numPixels;i+=){
 *ptr2++ = *ptr++;// copy 1st half of imgdata to 2nd hald
 }
 // Always render back image based on current effect index:
 (*renderEffect[fxIdx[back]])(back); //generate first half
 numPixels=numPixelsHolder;
 
 }
 
 void quarterrandom(byte idx) {
 if(fxVars[idx][0]==0){
 int one =random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 int two = random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 int three = random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 int four= random((sizeof(renderEffect) / sizeof(renderEffect[0])));
 fxVars[idx][0]=1;
 
 }
 numPixels = numPixelsHolder/4;//set numPixels to half; we are doing 2 renders for each frame and slapping them togeather for full strip
 byte *ptr1a = &imgData[idx][0], *ptr1b = &imgData[idx][numPixels*3];//
 byte *ptr2a = &imgData[idx][0], *ptr2b = &imgData[idx][numPixels*3*2];//
 byte *ptr3a = &imgData[idx][0], *ptr3b = &imgData[idx][numPixels*3*3];//
 // only do 3 shifts; the 4th image lands where it needs to go
 // Render front image and alpha mask based on current effect indices...
 (*renderEffect[fxIdx[one]])(one);//generate 2nd 1/4 in 1st 1/4 spot
 for(int i=0;i<numPixels;i+=){
 *ptrb++ = *ptra++;// copy 1st 1/4 of imgdata to 2nd 1/4
 }
 (*renderEffect[fxIdx[two]])(two);//generate 2nd 1/4 in 1st 1/4 spot
 for(int i=0;i<numPixels;i+=){
 *ptr2b++ = *ptr2a++;// copy 1st 1/4 of imgdata to 3rd 1/4
 }
 (*renderEffect[fxIdx[three]])(three);//generate 2nd half in 1st half spot
 for(int i=0;i<numPixels;i+=){
 *ptr3b++ = *ptr3a++;// copy 1st 1/4 of imgdata to 4th 1/4
 }
 (*renderEffect[fxIdx[four]])(four); //generate first half in correct spot; no shifting needed
 numPixels=numPixelsHolder;// reset numpixels so nothing else catches an error
 }
 */
void pacman(byte idx) { //hsv color chase for now
  if(fxVars[idx][0] == 0) {// using hsv for pacman
    fxVars[idx][1]=0;//get new pacman color
    // fxVars[idx][2]=fxVars[idx][1]+256;//get new 2nd color
    fxVars[idx][3]=numPixels/2;//pacman position
    fxVars[idx][4]=0;//lower edge
    fxVars[idx][5]=numPixels;//upper edge
    fxVars[idx][6]=2;//wait counter if at 120 fps 12 would be 1/10 of a second
    fxVars[idx][7]=0; //wait operator
    fxVars[idx][8]=random(4); //pcaman width
    fxVars[idx][0] = 1; // Effect initialized
  }
  if(fxVars[idx][0] == -1) { //re init
    // fxVars[idx][2]=fxVars[idx][1];
    fxVars[idx][1]++;//get new pacman color
    fxVars[idx][3]=numPixels/2;//pacman position
    fxVars[idx][4]=0;//lower edge
    fxVars[idx][5]=numPixels;//upper edge
    fxVars[idx][8]=random(4); //pcaman width
    fxVars[idx][0] = 1; // Effect initialized
  }

  int i;
  byte *ptr = &imgData[idx][0];
  for(i=0; i<numPixels; i++) {
    long color;
    if(i>=abs(fxVars[idx][3])-fxVars[idx][8]&&i<=abs(fxVars[idx][3])+fxVars[idx][8]){

      // color = hsv2rgb(fxVars[idx][1], 255, 255);
      color = getschemacolor(fxVars[idx][1]+1);
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
    else{
      if(i<=fxVars[idx][4]||i>=fxVars[idx][5]){
        // color = hsv2rgb(fxVars[idx][1], 255, 255);
        color = getschemacolor(fxVars[idx][1]+1);
        *ptr++ = color >> 16;
        *ptr++ = color >> 8;
        *ptr++ = color;
      }
      else{
        // color = hsv2rgb(fxVars[idx][2], 255, 255);
        color = getschemacolor(fxVars[idx][1]);
        *ptr++ = color >> 16;
        *ptr++ = color >> 8;
        *ptr++ = color;
      }
    }
  }

  if(fxVars[idx][3]>=numPixels){
    fxVars[idx][3]=-numPixels+1;
  }
  fxVars[idx][7]++;
  if(fxVars[idx][7]==fxVars[idx][6]){
    fxVars[idx][3]++;
    fxVars[idx][7]=0;
  }

  if(fxVars[idx][4]==fxVars[idx][5]){
    fxVars[idx][0]=-1;
  }
  else{
    if(abs(fxVars[idx][3])==fxVars[idx][4]){
      fxVars[idx][4]++;
      fxVars[idx][3]=fxVars[idx][4]+1;
    }
    else{
      if(abs(fxVars[idx][3])==fxVars[idx][5]){
        fxVars[idx][5]--;
        fxVars[idx][3]=((0-1)*fxVars[idx][5])+1;
      }
    }
  }
}
void pacmanfade(byte idx) { //hsv color chase for now
  if(fxVars[idx][0] == 0) {// using hsv for pacman
    fxVars[idx][1]=0;//get new pacman color
    // fxVars[idx][2]=fxVars[idx][1]+256;//get new 2nd color
    fxVars[idx][3]=numPixels/2;//pacman position
    fxVars[idx][4]=0;//lower edge
    fxVars[idx][5]=numPixels;//upper edge
    fxVars[idx][6]=2;//wait counter if at 120 fps 12 would be 1/10 of a second
    fxVars[idx][7]=0; //wait operator
    fxVars[idx][8]=random(4); //pcaman width
    fxVars[idx][0] = 1; // Effect initialized
  }
  if(fxVars[idx][0] == -1) { //re init
    // fxVars[idx][2]=fxVars[idx][1];
    fxVars[idx][1]++;//get new pacman color
    fxVars[idx][3]=numPixels/2;//pacman position
    fxVars[idx][4]=0;//lower edge
    fxVars[idx][5]=numPixels;//upper edge
    fxVars[idx][8]=random(4); //pcaman width
    fxVars[idx][0] = 1; // Effect initialized
  }

  int i;
  byte *ptr = &imgData[idx][0], *tptr = &tempimgData[0], *ptr2 = &imgData[idx][0], *tptr2 = &tempimgData[0];
  for(i=0; i<numPixels; i++) {
    long color;
    if(i>=abs(fxVars[idx][3])-fxVars[idx][8]&&i<=abs(fxVars[idx][3])+fxVars[idx][8]){

      // color = hsv2rgb(fxVars[idx][1], 255, 255);
      color = getschemacolor(fxVars[idx][1]+1);
      *tptr++ = color >> 16;
      *tptr++ = color >> 8;
      *tptr++ = color;
      *ptr2++ = color >> 16;
      *ptr2++ = color >> 8;
      *ptr2++ = color ;
    }
    else{
      if(i<=fxVars[idx][4]||i>=fxVars[idx][5]){
        // color = hsv2rgb(fxVars[idx][1], 255, 255);
        color = getschemacolor(fxVars[idx][1]+1);
        *tptr++ = color >> 16;
        *tptr++ = color >> 8;
        *tptr++ = color;
        *ptr2++ = color >> 16;
        *ptr2++ = color >> 8;
        *ptr2++ = color ;
      }
      else{
        // color = hsv2rgb(fxVars[idx][2], 255, 255);
        *tptr++ = (*ptr2++)*4/5;
        *tptr++ = (*ptr2++)*4/5;
        *tptr++ = (*ptr2++)*4/5;
      }
    }
  }
  /*
    if(color>0){
   *tptr++ = color >> 16;
   *tptr++ = color >> 8;
   *tptr++ = color;
   *ptr2++ = color >> 16;
   *ptr2++ = color >> 8;
   *ptr2++ = color ;
   }
   else{
   *tptr++ = (*ptr2++)*4/5;
   *tptr++ = (*ptr2++)*4/5;
   *tptr++ = (*ptr2++)*4/5;
   }
   
   */

  if(fxVars[idx][3]>=numPixels){
    fxVars[idx][3]=-numPixels+1;
  }
  fxVars[idx][7]++;
  if(fxVars[idx][7]==fxVars[idx][6]){
    fxVars[idx][3]++;
    fxVars[idx][7]=0;
  }

  if(fxVars[idx][4]==fxVars[idx][5]){
    fxVars[idx][0]=-1;
  }
  else{
    if(abs(fxVars[idx][3])==fxVars[idx][4]){
      fxVars[idx][4]++;
      fxVars[idx][3]=fxVars[idx][4]+1;
    }
    else{
      if(abs(fxVars[idx][3])==fxVars[idx][5]){
        fxVars[idx][5]--;
        fxVars[idx][3]=((0-1)*fxVars[idx][5])+1;
      }
    }
  }
}

// Rainbow effect (1 or more full loops of color wheel at 100% saturation).
// Not a big fan of this pattern (it's way overused with LED stuff), but it's
// practically part of the Geneva Convention by now.
void rainbowChase(byte idx) {
  if(fxVars[idx][0] == 0) {
    // Number of repetitions (complete loops around color wheel); any
    // more than 4 per meter just looks too chaotic and un-rainbow-like.
    // Store as hue 'distance' around complete belt:
    fxVars[idx][1] = (1 + random(4 * ((numPixels + 31) / 32))) * 1536;
    // Frame-to-frame hue increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][2] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse speed and hue shift direction half the time.
    if(random(2) == 0) fxVars[idx][1] = -fxVars[idx][1];
    if(random(2) == 0) fxVars[idx][2] = -fxVars[idx][2];
    fxVars[idx][3] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }
  if(fxVars[idx][0] == -1) {
    fxVars[idx][2] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse speed and hue shift direction half the time.
    if(random(2) == 0) fxVars[idx][1] = -fxVars[idx][1];
    //   if(random(2) == 0) fxVars[idx][2] = -fxVars[idx][2];
    fxVars[idx][0] = 1; // Effect initialized
  }
  byte *ptr = &imgData[idx][0];
  long color, i;
  for(i=0; i<numPixels; i++) {
    color = hsv2rgb(fxVars[idx][3] + fxVars[idx][1] * i / numPixels,
    255, 255);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][3] += fxVars[idx][2];
}



void sineChase(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
}
void petesineChase(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][1] = random(1536); // Random hue
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
}
void colorDriftmod2(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=random(0,1536); //color were gonna write initally
    fxVars[idx][0] = 1; // Effect initialized
    fxVars[idx][2] =random(1,16); //increments of color drift per frame
    // fxVars[idx][2] =1; //increments of color drift per frame
  }
  byte *ptr = &imgData[idx][0];
  fxVars[idx][1]+=fxVars[idx][2];
  long color = hsv2rgb(fxVars[idx][1]%1536, 255, 255);
  for(int i=0; i<numPixels; i++) {
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
}
void longsinechasecolordrift(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = 180;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][5] =random(1,16); //increments of color drift per frame
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
  fxVars[idx][1] += fxVars[idx][5];
}
void colorDriftsineChase(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(foo*12, 254 - (foo * 2), 255) :
    hsv2rgb(foo*12, 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
}
void sineDance(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) :
    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
}

void rainbowsineChase(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
    // Peaks of sine wave are white, troughs are black, mid-range
    // values are pure hue (100% saturated).
    color = (foo >= 0) ?
    hsv2rgb(fxVars[idx][1] * i / numPixels, 254 - (foo * 2), 255) :
    hsv2rgb(fxVars[idx][1] * i / numPixels, 255, 254 + foo * 2);
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  fxVars[idx][4] += fxVars[idx][3];
}

void somekindaChase(byte idx) {

  if(fxVars[idx][0] == 0) {

    fxVars[idx][1] = random(1536); // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720;
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels;
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
    fxVars[idx][5] = random(0,3);
  }

  //*ptr++ = (r2*abs(fxVars[idx][8])+r*fxVars[idx][9])>>8;
  //  *ptr++ = (g2*abs(fxVars[idx][8])+g*fxVars[idx][9])>>8;
  // *ptr++ = (b2*abs(fxVars[idx][8])+b*fxVars[idx][9])>>8;

  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i,o;
  for(long i=0,o=numPixels; i<numPixels; i++,o--) {
    switch(fxVars[idx][5]){
    case 0:
      foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
      *ptr++ = 254 - (foo * 2);
      *ptr++ = foo * 2;
      *ptr++ = 0;
      break;
    case 1:  
      foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
      *ptr++ = 254 - (foo * 2);
      *ptr++ = 0;
      *ptr++ = foo * 2;
      break;
    case 2:
      foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
      *ptr++ = 0;
      *ptr++ = foo * 2;
      *ptr++ = 254 - (foo * 2);
      break;
    case 3:
      foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
      *ptr++ = foo * 2;
      *ptr++ = 254 - (foo * 2);
      *ptr++ = 0;
      break;
    case 4:
      foo = fixSin(fxVars[idx][4] + fxVars[idx][2] * i / numPixels);
      *ptr++ = 0;
      *ptr++ = 254 - (foo * 2);
      *ptr++ = foo * 2;
      break;
    }
  }
  fxVars[idx][4] += fxVars[idx][3];

}



// Data for American-flag-like colors (20 pixels representing
// blue field, stars and stripes). This gets "stretched" as needed
// to the full LED strip length in the flag effect code, below.
// Can change this data to the colors of your own national flag,
// favorite sports team colors, etc. OK to change number of elements.
/*#define AAA 255
 #define BBB 255
 #define CCC 64
 #define C_RED AAA, BBB, CCC
 #define C_GREEEN CCC, AAA, BBB
 #define C_BLUE BBB, CCC, AAA
 PROGMEM prog_uchar flagTable[] = {
 C_BLUE , C_GREEEN, C_BLUE , C_GREEEN, C_BLUE , C_GREEEN, C_BLUE,
 C_RED , C_GREEEN, C_RED , C_GREEEN, C_RED , C_GREEEN, C_RED ,
 C_GREEEN, C_RED , C_GREEEN, C_RED , C_GREEEN, C_RED };
 */

#define C_RED 160, 0, 0
#define C_WHITE 255, 255, 255
#define C_BLUE 0, 0, 100
PROGMEM prog_uchar flagTable[] = {
  C_BLUE , C_WHITE, C_BLUE , C_WHITE, C_BLUE , C_WHITE, C_BLUE,
  C_RED , C_WHITE, C_RED , C_WHITE, C_RED , C_WHITE, C_RED ,
  C_WHITE, C_RED , C_WHITE, C_RED , C_WHITE, C_RED };


// Wavy flag effect




void wavyFlag(byte idx) {
  long i, sum, s, x;
  int idx1, idx2, a, b;
  if(fxVars[idx][0] == 0) { // Initialize effect?
    fxVars[idx][1] = 720 + random(720); // Wavyness
    fxVars[idx][2] = 4 + random(10); // Wave speed
    fxVars[idx][3] = 200 + random(200); // Wave 'puckeryness'
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }
  for(sum=0, i=0; i<numPixels-1; i++) {
    sum += fxVars[idx][3] + fixCos(fxVars[idx][4] + fxVars[idx][1] *
      i / numPixels);
  }

  byte *ptr = &imgData[idx][0];
  for(s=0, i=0; i<numPixels; i++) {
    x = 256L * ((sizeof(flagTable) / 3) - 1) * s / sum;
    idx1 = (x >> 8) * 3;
    idx2 = ((x >> 8) + 1) * 3;
    b = (x & 255) + 1;
    a = 257 - b;
    *ptr++ = ((pgm_read_byte(&flagTable[idx1 ]) * a) +
      (pgm_read_byte(&flagTable[idx2 ]) * b)) >> 8;
    *ptr++ = ((pgm_read_byte(&flagTable[idx1 + 1]) * a) +
      (pgm_read_byte(&flagTable[idx2 + 1]) * b)) >> 8;
    *ptr++ = ((pgm_read_byte(&flagTable[idx1 + 2]) * a) +
      (pgm_read_byte(&flagTable[idx2 + 2]) * b)) >> 8;
    s += fxVars[idx][3] + fixCos(fxVars[idx][4] + fxVars[idx][1] *
      i / numPixels);
  }

  fxVars[idx][4] += fxVars[idx][2];
  if(fxVars[idx][4] >= 720) fxVars[idx][4] -= 720;
}

void schemestretch(byte idx) {
  //  only run once to remove motion
  if(fxVars[idx][0] == 0) { // Initialize effect?
    long i, sum, s, x;
    int idx1, idx2, a, b;
    fxVars[idx][1] = 720 + random(720); // Wavyness
    fxVars[idx][2] = 4 + random(10); // Wave speed
    fxVars[idx][3] = 200 + random(200); // Wave 'puckeryness'
    fxVars[idx][4] = 0; // Current position
    //fxVars[idx][0] = 1; // Effect initialized

    for(sum=0, i=0; i<numPixels-1; i++) {
      sum += fxVars[idx][3] + fixCos(fxVars[idx][4] + fxVars[idx][1] *
        i / numPixels);
    }

    byte *ptr = &imgData[idx][0];
    for(s=0, i=0; i<numPixels; i++) {
      //x = 256L * ((sizeof(flagTable) / 3) - 1) * s / sum; //original
      x = 256L * ((8 / 3) - 1) * s / sum;
      //x = 256L * ((7 / 3) - 1) * s / sum; //and where do we start counting?
      idx1 = (x >> 8) * 3;
      idx2 = ((x >> 8) + 1) * 3;
      b = (x & 255) + 1;
      a = 257 - b;
      *ptr++ = (((getschemacolor(idx1)>>16) * a) + ((getschemacolor(idx2)>>16) * b)) >> 8;
      *ptr++ = (((getschemacolor(idx1)>>8) * a) + ((getschemacolor(idx1)>>8) * b)) >> 8;
      *ptr++ = ((getschemacolor(idx1) * a) + ((getschemacolor(idx1) * b))) >> 8;
      s += fxVars[idx][3] + fixCos(fxVars[idx][4] + fxVars[idx][1] *
        i / numPixels);
    }

    fxVars[idx][4] += fxVars[idx][2];
    if(fxVars[idx][4] >= 720) fxVars[idx][4] -= 720;
    fxVars[idx][0] = 1; // Effect initialized
  }

}








void sineCompass(byte idx) {
  // Only needs to be rendered once, when effect is initialized:
  if(fxVars[idx][0] == 0) {
    // Serial.println("effect=04");
    // fxVars[idx][1] = random(1536); // Random hue
    fxVars[idx][1] = 1; // Random hue
    // Number of repetitions (complete loops around color wheel);
    // any more than 4 per meter just looks too chaotic.
    // Store as distance around complete belt in half-degree units:
    // fxVars[idx][2] = (1 + random(4 * ((numPixels + 31) / 32))) * 720; //original
    fxVars[idx][2] = 720; 
    // Frame-to-frame increment (speed) -- may be positive or negative,
    // but magnitude shouldn't be so small as to be boring. It's generally
    // still less than a full pixel per frame, making motion very smooth.
    //fxVars[idx][3] = 4 + random(fxVars[idx][1]) / numPixels; //original
    fxVars[idx][3] = 0; //no rotation
    // Reverse direction half the time.
    if(random(2) == 0) fxVars[idx][3] = -fxVars[idx][3];
    fxVars[idx][4] = 0; // Current position
    fxVars[idx][0] = 1; // Effect initialized
  }
  //fxVars[idx][4] = map(compass.m.x,0,360,0,720); // Current position
  byte *ptr = &imgData[idx][0];
  int foo;
  long color, i;
  for(long i=0; i<numPixels; i++) {
    foo = fixSin((compass.m.x*2) + fxVars[idx][2] * i / numPixels);
    color = (foo >= 0) ? //black?
    hsv2rgb(fxVars[idx][1], 254 - (foo * 2), 255) : //white!
    hsv2rgb(fxVars[idx][1], 255, 254 + foo * 2); //color
    *ptr++ = color >> 16;
    *ptr++ = color >> 8;
    *ptr++ = color;
  }
  // fxVars[idx][4] += fxVars[idx][3];
}


void MonsterHunter(byte idx) {
  if(fxVars[idx][0] == 0) {
    fxVars[idx][1]=random(1536);
    fxVars[idx][3]=numPixels/2;//pacman position
    fxVars[idx][2]=random(1536);//get new color
    fxVars[idx][4]=0;//position of light
    fxVars[idx][7]=random(1536);
    fxVars[idx][5]=12;//wait steps
    fxVars[idx][8]=random(1536);
    fxVars[idx][6]=0;//wait operator
    fxVars[idx][9]=random(1536); //backgtround color
    fxVars[idx][10] =random(0,16); //increments of color drift per frame
    fxVars[idx][11] =random(0,4); //determine if sparkle3, strobe2 , colordrift1 or blank0 backgorund
    fxVars[idx][13] =random(0,4); //randomly determines the with of the pchasers 1=3 wide 2=5 wide 3=7 wide
    fxVars[idx][12] =0; //strobe operator
    fxVars[idx][0] = 1; // Effect initialized
  }

  if(fxVars[idx][11]>=1){
    fxVars[idx][9]= fxVars[idx][10]+fxVars[idx][9];
    if(fxVars[idx][9]>1536){
      fxVars[idx][9]=fxVars[idx][9]%1536;
    }
  }
  fxVars[idx][12] =!fxVars[idx][12]; //?
  byte *ptr = &imgData[idx][0];
  int l;
  for(int i=0,l=numPixels; i<numPixels,l>0; i++,l--) {
    long color;
    if(i>=fxVars[idx][4]-fxVars[idx][13]&&i<=fxVars[idx][4]+fxVars[idx][13]){
      color = getschemacolor(0);
      //color = hsv2rgb(fxVars[idx][1], 255, 255);
      *ptr++ = color >> 16;
      *ptr++ = color >> 8;
      *ptr++ = color;
    }
    else{
      if(numPixels-i>=fxVars[idx][4]-fxVars[idx][13]&&numPixels-i<=fxVars[idx][4]+fxVars[idx][13]){
        //color = hsv2rgb(fxVars[idx][2], 255, 255);
        color = getschemacolor(1);
        *ptr++ = color >> 16;
        *ptr++ = color >> 8;
        *ptr++ = color;
      }
      else{
        if((i+(numPixels/2))%numPixels>=fxVars[idx][4]-fxVars[idx][13]&&(i+(numPixels/2))%numPixels<=fxVars[idx][4]+fxVars[idx][13]){
          // color = hsv2rgb(fxVars[idx][7],255, 255);
          color = getschemacolor(2);
          *ptr++ = color >> 16;
          *ptr++ = color >> 8;
          *ptr++ = color;
        }
        else{
          if(((numPixels/2)-i+numPixels)%numPixels>=fxVars[idx][4]-fxVars[idx][13]&&((numPixels/2)-i+numPixels)%numPixels<=fxVars[idx][4]+fxVars[idx][13]){
            // color = hsv2rgb(fxVars[idx][8], 255, 255);
            color = getschemacolor(3);
            *ptr++ = color >> 16;
            *ptr++ = color >> 8;
            *ptr++ = color;
          }
          else{
            if(fxVars[idx][11]==0){
              *ptr++ = 0;
              *ptr++ =0;
              *ptr++ =0;
            }

            if(fxVars[idx][11]==1){
              // color = hsv2rgb(fxVars[idx][9],128, 128);
              color = getschemacolor(4);
              *ptr++ = color >> 16;
              *ptr++ = color >> 8;
              *ptr++ = color;
            }
            if(fxVars[idx][11]==2){
              //color = hsv2rgb(fxVars[idx][9], 128, 128);
              color = getschemacolor(5);
              if(fxVars[idx][12]==0){
                *ptr++ = 0;
                *ptr++ =0;
                *ptr++ =0;
              }
              else{
                *ptr++ = color >> 16;
                *ptr++ = color >> 8;
                *ptr++ = color;
              }
            }
            if(fxVars[idx][11]==3){
              color = getschemacolor(i);
              *ptr++ = color >> 16;
              *ptr++ = color >> 8;
              *ptr++ = color;
            }
          }
        }
      }
    }
  }


  fxVars[idx][6]++;
  if(fxVars[idx][5]==fxVars[idx][6]){
    fxVars[idx][6]=0;
    fxVars[idx][4]++;
  }
  if(fxVars[idx][4]==numPixels){
    fxVars[idx][4]=0;
  }

}

// TO DO: Add more effects here...Larson scanner, etc.

// ---------------------------------------------------------------------------
// Alpha channel effect rendering functions. Like the image rendering
// effects, these are typically parametrically-generated...but unlike the
// images, there is only one alpha renderer "in flight" at any given time.
// So it would be okay to use local static variables for storing state
// information...but, given that there could end up being many more render
// functions here, and not wanting to use up all the RAM for static vars
// for each, a third row of fxVars is used for this information.

// Simplest alpha effect: fade entire strip over duration of transition.
void renderAlpha00(void) {
  byte fade = 255L * tCounter / transitionTime;
  for(int i=0; i<numPixels; i++) alphaMask[i] = fade;
}



// Straight left-to-right or right-to-left wipe
void renderAlpha01(void) {
  long x, y, b;
  if(fxVars[2][0] == 0) {
    fxVars[2][1] = random(1, numPixels); // run, in pixels
    fxVars[2][2] = (random(2) == 0) ? 255 : -255; // rise
    fxVars[2][0] = 1; // Transition initialized
  }

  b = (fxVars[2][2] > 0) ?
  (255L + (numPixels * fxVars[2][2] / fxVars[2][1])) *
    tCounter / transitionTime - (numPixels * fxVars[2][2] / fxVars[2][1]) :
  (255L - (numPixels * fxVars[2][2] / fxVars[2][1])) *
    tCounter / transitionTime;
  for(x=0; x<numPixels; x++) {
    y = x * fxVars[2][2] / fxVars[2][1] + b; // y=mx+b, fixed-point style
    if(y < 0) alphaMask[x] = 0;
    else if(y >= 255) alphaMask[x] = 255;
    else alphaMask[x] = (byte)y;
  }
}

// Dither reveal between images
void renderAlpha02(void) {
  long fade;
  int i, bit, reverse, hiWord;

  if(fxVars[2][0] == 0) {
    // Determine most significant bit needed to represent pixel count.
    int hiBit, n = (numPixels - 1) >> 1;
    for(hiBit=1; n; n >>=1) hiBit <<= 1;
    fxVars[2][1] = hiBit;
    fxVars[2][0] = 1; // Transition initialized
  }

  for(i=0; i<numPixels; i++) {
    // Reverse the bits in i for ordered dither:
    for(reverse=0, bit=1; bit <= fxVars[2][1]; bit <<= 1) {
      reverse <<= 1;
      if(i & bit) reverse |= 1;
    }
    fade = 256L * numPixels * tCounter / transitionTime;
    hiWord = (fade >> 8);
    if(reverse == hiWord) alphaMask[i] = (fade & 255); // Remainder
    else if(reverse < hiWord) alphaMask[i] = 255;
    else alphaMask[i] = 0;
  }
}

// TO DO: Add more transitions here...triangle wave reveal, etc.

// ---------------------------------------------------------------------------
// Assorted fixed-point utilities below this line. Not real interesting.

// Gamma correction compensates for our eyes' nonlinear perception of
// intensity. It's the LAST step before a pixel value is stored, and
// allows intermediate rendering/processing to occur in linear space.
// The table contains 256 elements (8 bit input), though the outputs are
// only 7 bits (0 to 127). This is normal and intentional by design: it
// allows all the rendering code to operate in the more familiar unsigned
// 8-bit colorspace (used in a lot of existing graphics code), and better
// preserves accuracy where repeated color blending operations occur.
// Only the final end product is converted to 7 bits, the native format
// for the LPD8806 LED driver. Gamma correction and 7-bit decimation
// thus occur in a single operation.
PROGMEM prog_uchar gammaTable[][255] = {
  //brightness 0
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 60, 60, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63,
  //brightness 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
  4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127,
  //brightness 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
  4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127,
  //brightness 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
  4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127,
  //brightness 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
  4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127,
  //brightness 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
  4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
  11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
  16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
  30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
  40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
  50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
  62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
  76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127,

};

// This function (which actually gets 'inlined' anywhere it's called)
// exists so that gammaTable can reside out of the way down here in the
// utility code...didn't want that huge table distracting or intimidating
// folks before even getting into the real substance of the program, and
// the compiler permits forward references to functions but not data.
inline byte gamma(byte x) {
  //  return pgm_read_byte(&gammaTable[x][2]);
  return x>>(brightness+2);
}

// Fixed-point colorspace conversion: HSV (hue-saturation-value) to RGB.
// This is a bit like the 'Wheel' function from the original strandtest
// code on steroids. The angular units for the hue parameter may seem a
// bit odd: there are 1536 increments around the full color wheel here --
// not degrees, radians, gradians or any other conventional unit I'm
// aware of. These units make the conversion code simpler/faster, because
// the wheel can be divided into six sections of 256 values each, very
// easy to handle on an 8-bit microcontroller. Math is math, and the
// rendering code elsehwere in this file was written to be aware of these
// units. Saturation and value (brightness) range from 0 to 255.
long hsv2rgb(long h, byte s, byte v) {
  byte r, g, b, lo;
  int s1;
  long v1;
  //if(h==0) s=0,v=0;
  // Hue
  h %= 1536; // -1535 to +1535
  if(h < 0) h += 1536; // 0 to +1535
  lo = h & 255; // Low byte = primary/secondary color mix
  switch(h >> 8) { // High byte = sextant of colorwheel
  case 0 :
    r = 255 ;
    g = lo ;
    b = 0 ;
    break; // R to Y
  case 1 :
    r = 255 - lo;
    g = 255 ;
    b = 0 ;
    break; // Y to G
  case 2 :
    r = 0 ;
    g = 255 ;
    b = lo ;
    break; // G to C
  case 3 :
    r = 0 ;
    g = 255 - lo;
    b = 255 ;
    break; // C to B
  case 4 :
    r = lo ;
    g = 0 ;
    b = 255 ;
    break; // B to M
  default:
    r = 255 ;
    g = 0 ;
    b = 255 - lo;
    break; // M to R
  }

  // Saturation: add 1 so range is 1 to 256, allowig a quick shift operation
  // on the result rather than a costly divide, while the type upgrade to int
  // avoids repeated type conversions in both directions.
  s1 = s + 1;
  r = 255 - (((255 - r) * s1) >> 8);
  g = 255 - (((255 - g) * s1) >> 8);
  b = 255 - (((255 - b) * s1) >> 8);

  // Value (brightness) and 24-bit color concat merged: similar to above, add
  // 1 to allow shifts, and upgrade to long makes other conversions implicit.
  v1 = v + 1;
  return (((r * v1) & 0xff00) << 8) |
    ((g * v1) & 0xff00) |
    ( (b * v1) >> 8);
}

// The fixed-point sine and cosine functions use marginally more
// conventional units, equal to 1/2 degree (720 units around full circle),
// chosen because this gives a reasonable resolution for the given output
// range (-127 to +127). Sine table intentionally contains 181 (not 180)
// elements: 0 to 180 *inclusive*. This is normal.

PROGMEM prog_char sineTable[181] = {
  0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17,
  18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34,
  35, 36, 37, 38, 39, 40, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
  67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 77, 78, 79, 80, 81,
  82, 83, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 92, 92, 93, 94,
  95, 95, 96, 97, 97, 98, 99,100,100,101,102,102,103,104,104,105,
  105,106,107,107,108,108,109,110,110,111,111,112,112,113,113,114,
  114,115,115,116,116,117,117,117,118,118,119,119,120,120,120,121,
  121,121,122,122,122,123,123,123,123,124,124,124,124,125,125,125,
  125,125,126,126,126,126,126,126,126,127,127,127,127,127,127,127,
  127,127,127,127,127
};

char fixSin(int angle) {
  angle %= 720; // -719 to +719
  if(angle < 0) angle += 720; // 0 to +719
  return (angle <= 360) ?
  pgm_read_byte(&sineTable[(angle <= 180) ?
  angle : // Quadrant 1
  (360 - angle)]) : // Quadrant 2
  -pgm_read_byte(&sineTable[(angle <= 540) ?
  (angle - 360) : // Quadrant 3
  (720 - angle)]) ; // Quadrant 4
}

char fixCos(int angle) {
  angle %= 720; // -719 to +719
  if(angle < 0) angle += 720; // 0 to +719
  return (angle <= 360) ?
  ((angle <= 180) ? pgm_read_byte(&sineTable[180 - angle]) : // Quad 1
  -pgm_read_byte(&sineTable[angle - 180])) : // Quad 2
  ((angle <= 540) ? -pgm_read_byte(&sineTable[540 - angle]) : // Quad 3
  pgm_read_byte(&sineTable[angle - 540])) ; // Quad 4
}



void buttonpress(){
  if ((millis() - lastDebounceTime) > debounceDelay) {
    uint8_t buttoncounter = 0;
    while(digitalRead(19)==LOW){
      delay(100);
      buttoncounter++;
      if(buttoncounter>100){ //this prob means the button is busted.
        return; //break while loop
        //disable button
      } 
    }
    Serial.println(buttoncounter);
    if(buttoncounter<5){//short press 
      button=1;
      Serial.println("button!");
    }
    else{
      if(buttoncounter>=5){//long press
        //longbutton=1;
        colorschemeselector++;
        //Serial.println("long button!");
      }      
    }
  }
}

void runningaverageax(int newval) {
  if(newval==0){
    return;
  }
  // subtract the last reading:
  totalax= totalax - readingsax[indexax];
  // read from the sensor:
  readingsax[indexax] = newval;
  // add the reading to the total:
  totalax= totalax + readingsax[indexax];
  // advance to the next position in the array:
  indexax = indexax + 1;
  // if we're at the end of the array...
  if (indexax >= numReadingsax)
    // ...wrap around to the beginning:
    indexax = 0;
  // calculate the average:
  averageax = totalax / numReadingsax;
  // send it to the computer as ASCII digits
  // Serial.println(average);
  // delay(1); // delay in between reads for stability
}
void runningaverageay(int newval) {
  if(newval==0){
    return;
  }
  // subtract the last reading:
  totalay= totalay - readingsay[indexay];
  // read from the sensor:
  readingsay[indexay] = newval;
  // add the reading to the total:
  totalay= totalay + readingsay[indexay];
  // advance to the next position in the array:
  indexay = indexay + 1;
  // if we're at the end of the array...
  if (indexay >= numReadingsay)
    // ...wrap around to the beginning:
    indexay = 0;
  // calculate the average:
  averageay = totalay / numReadingsay;
  // send it to the computer as ASCII digits
  // Serial.println(average);
  // delay(1); // delay in between reads for stability
}
void runningaverageaz(int newval) {
  if(newval==0){
    return;
  }
  // subtract the last reading:
  totalaz= totalaz - readingsaz[indexaz];
  // read from the sensor:
  readingsaz[indexaz] = newval;
  // add the reading to the total:
  totalaz= totalaz + readingsaz[indexaz];
  // advance to the next position in the array:
  indexaz = indexaz + 1;
  // if we're at the end of the array...
  if (indexaz >= numReadingsaz)
    // ...wrap around to the beginning:
    indexaz = 0;
  // calculate the average:
  averageaz = totalaz / numReadingsaz;
  // send it to the computer as ASCII digits
  // Serial.println(average);
  // delay(1); // delay in between reads for stability
}

void getSerial(){
  unsigned long num;
  int i;
  if( readSerialString() ) {
    //   if(serialoutput==true){
    Serial.println(serInStr);
    //    }
    char cmd = serInStr[0]; // first char is command
    char* str = serInStr;
    while( *++str == ' ' ); // got past any intervening whitespace
    num = atol(str); // the rest is arguments (maybe)
    if( cmd == 'J' ) { //
      if(serialoutput==true){  
        Serial.println(".");
      }
      for(i=0;i<8;i++){
        num = atol(str); // the rest is arguments (maybe)
        //      num=num>>8;
        usercolorscheme[i] = num;//what?

        Serial.println(num, HEX);

        while( *++str != ' ' ){ // got to intervening whitespace

        }
        while( *++str == ' ' ); // got past any intervening whitespace
        //  *++str;
        //   num = atoi(str); // the rest is arguments (maybe)

      }
      Serial.println("Read user color scheme");

    }


    if( cmd == '+' ) {
      if(serialoutput==true){ 
        Serial.println("Button recieved");
      }
      button=1;
    }
    if( cmd == 'd' ) {
      compassoutput=0;
      if(serialoutput==true){  
        Serial.println("disable compass serial output");
      }
    }
    if( cmd == 'D' ) {
      compassoutput=1;
      if(serialoutput==true){
        Serial.println("enable compass serial output");
      }
    }
    if( cmd == 'Q' ) {

      for (int i =0; i<ircsetup; i++){
        Serial.print (irc[i]);
        Serial.print(" , " );
        Serial.println (i);

      }
      Serial.println();
      for (int i =0; i<ircsetup; i++){
        Serial.print (irc2[i]);
        Serial.print(" , " );
        Serial.println (i);
      }
    }
    //int opmode; //0==normal ,1=menu,2=irsetup
    if( cmd == 'M' ) {
      if(serialoutput==true){ 
        Serial.println("Entering Menu");
      }
      opmode = 1;
    }
    if( cmd == 'm' ) {
      //Timer1.detachInterrupt();
      if(serialoutput==true){ 
        Serial.println("Woah.");
      }
      opmode=0;
    }
    if( cmd == 'I' ) {
      //Timer1.detachInterrupt();
      if(serialoutput==true){ 
        Serial.println("Entering irsetup");
      }
      opmode=2;
    }
    //  boolean serialoutput=false;// will the serial respond?
    if( cmd == 'S' ) {
      serialoutput=true;
      if(serialoutput==true){  
        Serial.print("Serial output enabled");
      }
    }
    if( cmd == 's' ) {

      if(serialoutput==true){  
        Serial.print("Serial output disabled");
        serialoutput=false;
      }
    }

    if( cmd == 'C' ) {
      colorschemeselector++;
      if(serialoutput==true){  
        Serial.print("Color Scheme ");
        Serial.println(colorschemeselector);
      }
    }
    if( cmd == 'c' ) {
      colorschemeselector--;
      if(serialoutput==true){  
        Serial.print("Color Scheme ");
        Serial.println(colorschemeselector);
      }
    }
    if( cmd == 'Z' ) { //send bluetooth config command
      //not needed for normal operation, this will be preconfigured.
      //left for learning
      if(serialoutput==true){  
        Serial.println("Sending bluetooth config commands");
        Serial.println("This will take about 3 secconds");
      }
      bluetoothsetup(); 
      Serial.println("Sent.");
    }
    if( cmd == 'z' ) { //send bluetooth config command
      brutebluetooth();
    }
    if( cmd == 'A' ) { //Enable accel output
      if(serialoutput==true){  
        Serial.println("Enable accel output");
      }
      acceloutput=true;
    }
    if( cmd == 'a' ) { //disable accel output
      if(serialoutput==true){  
        Serial.println("Disable accel output");
      }
      acceloutput=false;
    }

    serInStr[0] = 0; // say we've used the string
  }

}



void getUart(){
  long num;
  int i;
  if(readUartString()) {
    //   Serial.println(readUartString());
    // irrecv.pause();
    delay(10);
    if(uartoutput==true){
      //    Uart.println(urtInStr);
    }
    char ucmd = urtInStr[0]; // first char is command
    char* urt = urtInStr;
    while( *++urt == ' ' ); // got past any intervening whitespace
    num = atol(urt); // the rest is arguments (maybe)
    if( ucmd == 'J' ) { //
      if(serialoutput==true){  
        //     Serial.println(".");
      }
      for(i=0;i<8;i++){
        num = atol(urt); // the rest is arguments (maybe)
        //      num=num>>8;
        usercolorscheme[i] = num;//what?

        Serial.println(num, HEX);

        while( *++urt != ' ' ){ // got to intervening whitespace

        }
        while( *++urt == ' ' ); // got past any intervening whitespace
        //  *++str;
        //   num = atoi(str); // the rest is arguments (maybe)

      }
      Serial.println();
      colorschemeselector=0;
      //  Serial.println("Read user color scheme");

    }
    if( ucmd == 'P' ) {//P means the next character is a pattern we are getting.
      if(num>0){
        pattern = num;//in 
      }
      tCounter=0;//start the transition
    }
    if( ucmd == 'C' ) {//C means color scheme read through atoi comes next
      if(num>0){
        colorschemeselector = num;//in
      }
    }
    if( ucmd == 'c' ) {//C means color scheme read through atoi comes next
      if(num>0){
        colorschemeselector = num;//in
      }
    }

    if( ucmd == 'B' ) {
      brightness=num;//self explanitory.
    }
    if( ucmd == 'H' ) {//handshake. when recieved reply with 'ver#'
      Uart.print("ver");
      Uart.print(galaxyversion);
    }
    if( ucmd == 'R' ) {//re-init pattern
      fxVars[0][0]=0;
      //button=1;
    }
    if( ucmd == 'C' ) {//re-init pattern
      //   fxVars[0][0]=0;
      longbutton=1;
    }
    if( ucmd == 'A' ) {//re-init pattern
      //   fxVars[0][0]=0;
      opmode=1;
    }

    /*    if( ucmd == 'Q' ) {
     
     for (int i =0; i<ircsetup; i++){
     Uart.print (irc[i]);
     Uart.print(" , " );
     Uart.println (i);
     
     }
     Uart.println();
     for (int i =0; i<ircsetup; i++){
     Uart.print (irc2[i]);
     Uart.print(" , " );
     Uart.println (i);
     }
     }
     */
    /*    if( ucmd == 'I' ) {
     //Timer1.detachInterrupt();
     if(uartoutput==true){ 
     Uart.println("Entering irsetup");
     }
     opmode=2;
     }
     //  boolean serialoutput=false;// will the serial respond?
     */
    if( ucmd == 'P' ) {//P means pattern number read through atoi comes next

      pattern = num;//in
      button=1;
    }
    if( ucmd == 'D' ) {//D means toggle demo mode
      demo=!demo;
      if(demo==1){
        Uart.println("Demo mode enabled");
      }
      else{
        Uart.println("Demo mode disabled");
      }
    }
    //   if( ucmd == 'A' ) {//D means toggle demo mode
    //     compassoutput=!compassoutput;
    //     if(compassoutput==1){
    //       Uart.println("compass output enabled");
    //     }
    //    else{
    //       Uart.println("compass outputdisabled");
    //     }
    //   }
    urtInStr[0] = 0; // say we've used the string
    //irrecv.resume();  
  }
}

//read a string from the serial and store it in an array
//you must supply the array variable
uint8_t readSerialString()
{
  if(!Serial.available()) {
    return 0;
  }
  delay(10); // wait a little for serial data

  memset( serInStr, 0, sizeof(serInStr) ); // set it all to zero
  int i = 0;
  while (Serial.available()) {
    serInStr[i] = Serial.read(); // FIXME: doesn't check buffer overrun
    i++;
  }
  //serInStr[i] = 0; // indicate end of read string
  return i; // return number of chars read
}
uint8_t readUartString()
{
  if(!Uart.available()) {
    return 0;
  }
  delay(10); // wait a little for serial data

  memset( serInStr, 0, sizeof(serInStr) ); // set it all to zero
  int i = 0;
  while (Uart.available()) {
    urtInStr[i] = Uart.read(); // FIXME: doesn't check buffer overrun
    i++;
  }
  //serInStr[i] = 0; // indicate end of read string
  return i; // return number of chars read
}

#include <ctype.h>
uint8_t toHex(char hi, char lo)
{
  uint8_t b;
  hi = toupper(hi);
  if( isxdigit(hi) ) {
    if( hi > '9' ) hi -= 7; // software offset for A-F
    hi -= 0x30; // subtract ASCII offset
    b = hi<<4;
    lo = toupper(lo);
    if( isxdigit(lo) ) {
      if( lo > '9' ) lo -= 7; // software offset for A-F
      lo -= 0x30; // subtract ASCII offset
      b = b + lo;
      return b;
    } // else error
  } // else error
  return 0;
}
void EEPwrite(int p_address, unsigned long p_value)
{
  int i;
  byte Byte1 = ((p_value >> 0) & 0xFF);
  byte Byte2 = ((p_value >> 8) & 0xFF);
  byte Byte3 = ((p_value >> 16) & 0xFF);
  byte Byte4 = ((p_value >> 24) & 0xFF);

  EEPROM.write(p_address, Byte1);
  EEPROM.write(p_address + 1, Byte2);
  EEPROM.write(p_address + 2, Byte3);
  EEPROM.write(p_address + 3, Byte4);
  firstTwoBytes = ((Byte1 << 0) & 0xFF) + ((Byte2 << 8) & 0xFF00);
  secondTwoBytes = (((Byte3 << 0) & 0xFF) + ((Byte4 << 8) & 0xFF00));
  secondTwoBytes *= 65536; // multiply by 2 to power 16 - bit shift 24 to the left
  Serial.print("wrote ");

  Serial.println(firstTwoBytes + secondTwoBytes, DEC);

  firstTwoBytes = 0;
  secondTwoBytes = 0;
}



void EEPreadirc()
{
  int i;
  for(i=0;i<ircsetup;i++){
    byte Byte1 = EEPROM.read(i*4);
    byte Byte2 = EEPROM.read(i*4 + 1);
    byte Byte3 = EEPROM.read(i*4 + 2);
    byte Byte4 = EEPROM.read(i*4 + 3);

    firstTwoBytes = ((Byte1 << 0) & 0xFF) + ((Byte2 << 8) & 0xFF00);
    secondTwoBytes = (((Byte3 << 0) & 0xFF) + ((Byte4 << 8) & 0xFF00));
    secondTwoBytes *= 65536; // multiply by 2 to power 16 - bit shift 24 to the left


    irc[i] = firstTwoBytes + secondTwoBytes;
    if(serialoutput==true){
      Serial.print("Read code from eeprom spots ");
      Serial.print(i*4);
      Serial.print(" to ");
      Serial.print(i*4 + 3);
      Serial.print(" as ");
      Serial.print(firstTwoBytes + secondTwoBytes, DEC);
      Serial.print(" in irc spot ");
      Serial.println(i);
    }
    firstTwoBytes = 0;
    secondTwoBytes = 0;
  }
}
int i;


void irsetup(boolean feedback) {
  // irsetupflag=1;
  for(int q=0;q<ircsetup;q++){//refresh image
    if(i<q){
      strip.setPixelColor(q, 64, 0, 0);
    }
    else{
      if(i>q){
        strip.setPixelColor(q, 0, 0, 64);
      }
      else{
        if(i==q){
          strip.setPixelColor(i, 0, 64, 0);
        } 
      }
    }
  }
  strip.show();
  if (irrecv.decode(&results)) {//if we have a new ir code
    irc[i] = results.value; //add it to our ir code array
    if(serialoutput==true){   //shout it to the world
      Serial.print("got code ");
      Serial.println(results.value, DEC);
      Serial.print("Stored in slot ");
      Serial.println(i); 
    }

    strip.setPixelColor(i, 0, 0, 64);// write the current pixel to blue so the user knows to wait.
    strip.show();  //update image 
    i++;  //done with this  
    delay(1500);//needed for frequent button presses
    irrecv.resume();
    if(serialoutput==true){
      Serial.println("ready for next button");
    }
  }

  if (i == ircsetup-1){
    int i2;
    for (i = 0; i < ircsetup; i ++){
      if(serialoutput==true){  
        Serial.print("Spot ");
        Serial.print(i);
        Serial.print(" has code ");
        Serial.println(irc[i], DEC);
        Serial.println("Writing to eeprom");
      }
      i2 = (i*4);
      EEPwrite(i2,irc[i]);
    }
    delay(1000);
    if(serialoutput==true){  
      Serial.println("Ready.");
    }
    opmode=0;
    return;
  }

  delay(100);
  // irsetupflag=0;
}


void getir(){
  //Serial.println("Please press the numbers 0-9 first, then a few more? if you dont know, keep going.");
  //  Serial.println(i);
  //irsetup(true);

  /* keychain remote with flashlight
   Read code from eeprom spots 0 to 3 as 17 in irc spot 0 -
   
   Read code from eeprom spots 1 to 4 as 2064 in irc spot 1 +
   
   Read code from eeprom spots 2 to 5 as 33 in irc spot 2 down 
   
   Read code from eeprom spots 3 to 6 as 2080 in irc spot 3 up 
   
   Read code from eeprom spots 4 to 7 as 62 in irc spot 4 input
   
   Read code from eeprom spots 5 to 8 as 13 in irc spot 5 mute
   
   */
  /*  kenmore remote
   279939191 , 0
   
   279928991 , 1
   
   279937151 , 2
   
   279933071 , 3
   
   279941231 , 4
   
   279912671 , 5
   
   279949391 , 6
   
   279920831 , 7
   
   279965711 , 8
   
   279904511 , 9
   
   279961631 , 10
   
   
   Sirius codes
   Read code from eeprom spots 0 to 3 as 2155864095 in irc spot 0
   
   Read code from eeprom spots 1 to 4 as 2155847775 in irc spot 1
   
   Read code from eeprom spots 2 to 5 as 2155815135 in irc spot 2
   
   Read code from eeprom spots 3 to 6 as 2155811055 in irc spot 3
   
   Read code from eeprom spots 4 to 7 as 2155860015 in irc spot 4
   
   Read code from eeprom spots 5 to 8 as 2155851855 in irc spot 5
   
   Read code from eeprom spots 6 to 9 as 2155827375 in irc spot 6
   
   Read code from eeprom spots 7 to 10 as 2155835535 in irc spot 7
   
   Read code from eeprom spots 8 to 11 as 2155868175 in irc spot 8
   
   Read code from eeprom spots 9 to 12 as 2155809015 in irc spot 9
   
   Read code from eeprom spots 10 to 13 as 2155831455 in irc spot 10
   
   
   
   */

  if (irrecv.decode(&results)) {
    //   Serial.println(results.value);
    if(results.value==0){
      irrecv.resume();
      return;
    }
    if (results.value == irc2[0]||results.value==2065 || results.value== 17) {//pattern down
      if(serialoutput==true){
        Serial.println("recognised 0 on ir");
      }//pattern ++
      back=true;
      button=1;
      tCounter=0;
    }
    if (results.value == irc2[1]||results.value==2064 || results.value==16) {//pattern up
      if(serialoutput==true){
        Serial.println("recognised 1 on ir");
      } 
      button=1;
      tCounter=0;
      //colorschemeselector++;
    }  
    if (results.value == irc2[2]||results.value==2081 || results.value==33) {//color scheme down
      if(serialoutput==true){
        Serial.println("recognised 2 on ir");
      }
      colorschemeselector--;
      //color scheme --
    }
    if (results.value == irc2[3]||results.value==2080 || results.value==32) {//color scheme up
      if(serialoutput==true){
        Serial.println("recognised 3 on ir");
      }
      colorschemeselector++;
    }
    if (results.value == irc2[4]||results.value==2110 || results.value==62) {//re-init pattern
      if(serialoutput==true){
        Serial.println("recognised 4 on ir");
      }
      fxVars[0][0]=0;
      fxVars[1][0]=0;
    }
    if (results.value == irc2[5]||results.value==2061 || results.value==13) {//toggle brightness
      if(serialoutput==true){
        Serial.println("recognised 5 on ir");//serial message here    
      }

      if(brightness==2){
        brightness=4;
      }
      else{
        if(brightness==4){
          brightness=2;
        } 
        else{
          brightness=2;
        }
      }

      //   brightness = random(2,1)*2;
      Serial.println(brightness);
    }    
    if (results.value == irc2[6]) {
      if(serialoutput==true){
        Serial.println("recognised 6 on ir");//serial message here    

      }

      //set demo mode off
      demo =0;  
    }
    if (results.value == irc2[7]) {
      if(serialoutput==true){
        Serial.println("recognised 7 on ir");  //serial message here    
      }
      //set super fast demo mode
      demo = 1;
      patternswitchspeed = 200; //# of frames between pattern switches
      patternswitchspeedvariance = 15;//# of frames the pattern switch speed can vary+ and _ so total variance could be 2x 
      transitionspeed = 60;// # of frames transition lasts 
      transitionspeedvariance = 15;// # of frames transition lenght varies by, total var 2X, 1X in either + or -

    }
    if (results.value == irc2[8]) {
      if(serialoutput==true){
        Serial.println("recognised 8 on ir");  //serial message here    
      }
      //set medium demo mode
      demo = 1;
      patternswitchspeed = 800; //# of frames between pattern switches
      patternswitchspeedvariance = 50;//# of frames the pattern switch speed can vary+ and _ so total variance could be 2x 
      transitionspeed = 120;// # of frames transition lasts 
      transitionspeedvariance = 15;// # of frames transition lenght varies by, total var 2X, 1X in either + or -

    }
    if (results.value == irc2[9]) {
      if(serialoutput==true){
        Serial.println("recognised 9 on ir");   //serial message here    
      }
      //set slow demo mode
      demo = 1;
      patternswitchspeed = 3000; //# of frames between pattern switches
      patternswitchspeedvariance = 255;//# of frames the pattern switch speed can vary+ and _ so total variance could be 2x 
      transitionspeed = 120;// # of frames transition lasts 
      transitionspeedvariance = 15;// # of frames transition lenght varies by, total var 2X, 1X in either + or -
    }
    if (results.value == irc2[10]) {
      if(serialoutput==true){
        Serial.println("recognised 10 on ir"); //serial message here    
      }
      fxVars[0][0]=0;
      //  tCounter=-1;
      //re init
    }
    irrecv.resume();
  }
}


/*
 * Converts an RGB color value to HSV. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and v in the set [0, 1].
 *
 * @param   Number  r       The red color value
 * @param   Number  g       The green color value
 * @param   Number  b       The blue color value
 * @return  Array           The HSV representation
 */
//unsigned long rgbToHsv(byte r, byte g, byte b, double hsv[]) {
unsigned long rgbToHsv(byte r, byte g, byte b) {
  double rd = (double) r/255;
  double gd = (double) g/255;
  double bd = (double) b/255;
  double max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
  double h, s, v = max;

  double d = max - min;
  s = max == 0 ? 0 : d / max;

  if (max == min) { 
    h = 0; // achromatic
  } 
  else {
    if (max == rd) {
      h = (gd - bd) / d + (gd < bd ? 6 : 0);
    } 
    else if (max == gd) {
      h = (bd - rd) / d + 2;
    } 
    else if (max == bd) {
      h = (rd - gd) / d + 4;
    }
    h /= 6;
  }

  return h,s,v;
}

unsigned long threeway_max(double a, double b, double c) {
  return max(a, max(b, c));
}
unsigned long threeway_min(double a, double b, double c) {
  return min(a, min(b, c));
}

