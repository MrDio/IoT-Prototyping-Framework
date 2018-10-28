/*
 *  This file is a sample application, based
 *  on the IoT Prototyping Framework (IoTPF)

    This application and IoTPF is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    IoTPF is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU v3 General Public License for more details.

    Released under GNU v3

    You should have received a copy of the GNU General Public License
    along with IoTPF.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This is a sample demonstrates Particle Photon with NeoPIXEL Ring (16 LED).
 * 
 * Needed components
 * NeoPIXEL Ring (NEO)
 * Particle Photon (PHO)
 * 
 * Wiring
 * 
 * PHO (D2) - NEO (Data Input)
 * PHO (GND) - NEO (GND)
 * PHO (3V3) - NEO (5V)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */
 
 // This #include statement was automatically added by the Particle IDE.
#include "IoT-Eco-NeoPIXEL-Ring.h"


// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define PIXEL_PIN D2
#define PIXEL_COUNT 16
#define PIXEL_TYPE SK6812RGBW
#define BRIGHTNESS 250 // 0 - 255

Adafruit_NeoPixel _ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
int p1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int p2[] = {8,9,10,11,12,13,14,15,16,0,1,2,3,4,5,6,7};
int gl_red = 0;
int gl_green = 0;
int gl_blue = 0;

// Constructor inits NeoPIXEL-Ring related to pixels (default is pin 2)
/*!
  \param pixels amount of pixels on ring
  \return obj insctance of class
*/
IoTEcoSys_NeoPIXEL_Ring::IoTEcoSys_NeoPIXEL_Ring() {
}

IoTEcoSys_NeoPIXEL_Ring::IoTEcoSys_NeoPIXEL_Ring(int pixel) {
}

//! The init function - nothing to do in this class
/*!
*/
bool IoTEcoSys_NeoPIXEL_Ring::init(){
    Serial.begin(9600);

    _ring.setBrightness(BRIGHTNESS);
    _ring.begin();
    _ring.show(); // Initialize all pixels to 'off'
    return true;
}


// Set RGB
/*!
  \param color red, green, blue, white or off
  \return int err = 0, else = 1
*/
int IoTEcoSys_NeoPIXEL_Ring::setGlRGB( String color) {
  if(color == "red") {
    gl_green = 0;
    gl_red = 255;
    gl_blue = 0;
    //ring.Color(0, 255, 0); // GRB
  }
  else if(color == "green") {
    gl_green = 255;
    gl_red = 0;
    gl_blue = 0;
    //ring.Color(255, 0, 0); // GRB
  }
  else if(color == "blue") {
    gl_green = 0;
    gl_red = 0;
    gl_blue = 255;
    //ring.Color(0, 0, 255);
  }
  else if(color == "white") {
    gl_green = 0;
    gl_red = 0;
    gl_blue = 0;
    _ring.Color(gl_green, gl_red, gl_blue, 255); // GRB+W
  }
  else if(color == "off") {
    gl_green = 0;
    gl_red = 0;
    gl_blue = 0;
    _ring.Color(gl_green, gl_red, gl_blue); // GRB+W
  }
}


// NeoPIXEL ring rotate clockwise
/*!
  \param circles amount of circles to animate
  \param del delay in ms
  \param color red, green, blue, white or off
*/
void IoTEcoSys_NeoPIXEL_Ring::neoRingClockWise(int circles, int del, String color){

    for(int c=0;c<circles;c++){
       setGlRGB("off");
       changeColor(_ring.Color(gl_green, gl_red, gl_blue)); // GRB
       _ring.show();
       for(int i=0;i<16;i++){
          setGlRGB(color);
         _ring.setPixelColor(15-p1[i],_ring.Color(gl_green, gl_red, gl_blue));
          if(i > -1){
            _ring.setPixelColor(15-(p1[i]-1),_ring.Color(0, 0, 0));
          }
          _ring.show();
          delay(del);  
      }
    }
    changeColor(_ring.Color(0, 0, 0)); // GRB
    _ring.show();
}

// NeoPIXEL ring fill clockwise
/*!
  \param showuptime time to showup in ms
  \param del delay in ms
  \param color red, green, blue, white or off
*/
void IoTEcoSys_NeoPIXEL_Ring::neoRingFillClockWise(int showuptime, int del, String color){
    changeColor(_ring.Color(0, 0, 0)); // GRB
    _ring.show();
       for(int i=0;i<16;i++){
          setGlRGB(color);
          _ring.setPixelColor(15-p1[i],_ring.Color(gl_green, gl_red, gl_blue));
          if(i > -1){
          }
          _ring.show();
          delay(del);  
      }
    delay(showuptime);
    changeColor(_ring.Color(0, 0, 0)); // GRB
    _ring.show();
}

// NeoPIXEL ring double counter clockwise
/*!
  \param circles amount of circles to animate
  \param del delay in ms
  \param color red, green, blue, white or off
*/
void IoTEcoSys_NeoPIXEL_Ring::neoRingDoubleCounterClockWise(int circles, int del, String color){

    for(int c=0;c<circles;c++){
       changeColor(_ring.Color(0, 0, 0)); // GRB
       _ring.show();
       for(int i=0;i<16;i++){
          setGlRGB(color);
          _ring.setPixelColor(p1[i],_ring.Color(gl_green, gl_red, gl_blue));
          _ring.setPixelColor(p2[i],_ring.Color(gl_green, gl_red, gl_blue));
          if(i > -1){
            setGlRGB("off");
            _ring.setPixelColor(p1[i]-1,_ring.Color(gl_green, gl_red, gl_blue));
            _ring.setPixelColor(p2[i]-1,_ring.Color(gl_green, gl_red, gl_blue));
          }
          _ring.show();
          delay(del);  
      } 
    }
    changeColor(_ring.Color(0, 0, 0)); // GRB
    _ring.show();
}

// NeoPIXEL ring double clockwise
/*!
  \param circles amount of circles to animate
  \param del delay in ms
  \param color red, green, blue, white or off
*/
void IoTEcoSys_NeoPIXEL_Ring::neoRingCounterClockWise(int circles, int del, String color){

    for(int c=0;c<circles;c++){
       changeColor(_ring.Color(0, 0, 0)); // GRB
       _ring.show();
       for(int i=0;i<16;i++){
          setGlRGB(color); 
          _ring.setPixelColor(p1[i],_ring.Color(gl_green, gl_red, gl_blue));
          if(i > -1){
            setGlRGB("off");
            _ring.setPixelColor(p1[i]-1,_ring.Color(gl_green, gl_red, gl_blue));
          }
          _ring.show();
          delay(del);  
      } 
    }
    changeColor(_ring.Color(0, 0, 0)); // GRB
    _ring.show();
}


// NeoPIXEL ring change color
/*!
  \param color color to change
*/

void IoTEcoSys_NeoPIXEL_Ring::changeColor(uint32_t color) {
  for(uint16_t i=0; i < _ring.numPixels(); i++) {
    _ring.setPixelColor(i, color);
    _ring.show();
  }
}


 
 