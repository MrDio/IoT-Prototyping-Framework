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
 * This is a sample demonstrates particle photon with IFTTT.
 * 
 * Needed components
 * IFTTT
 * Particle PHO
 * LED White LW
 * LED Green LG
 * LED Red LR
 * 
 * PHO.D6 - LG
 * PHO.D5 - LR
 * PHO.D4 - LW
 * 
 * PHO.GND - LG
 * PHO.GND - LR
 * PHO.GND - LW
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */

// Function header
int ledFunction(String color);


int greenLed = D6;
int redLed = D5;
int whiteLed = D4;

bool isWhiteOn = false;
bool isRedOn = false;
bool isGreenOn = false;

void setup() {
    // register callThisFunction on particle cloud
    Particle.function("ledFunction", ledFunction);
    
    pinMode(greenLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(whiteLed, OUTPUT);
}

void loop() {
  
}

int ledFunction(String color){
    if(color == "white"){
        if(isWhiteOn){
            digitalWrite(whiteLed, LOW);
            isWhiteOn=false;
        }else{
            digitalWrite(whiteLed, HIGH);
            isWhiteOn=true;
        }
    }else if(color == "red"){
        if(isRedOn){
            digitalWrite(redLed, LOW);
            isRedOn=false;
        }else{
            digitalWrite(redLed, HIGH);
            isRedOn=true;
        }
    }else if(color == "green"){
        if(isGreenOn){
            digitalWrite(greenLed, LOW);
            isGreenOn=false;
        }else{
            digitalWrite(greenLed, HIGH);
            isGreenOn=true;
        }
    }else if(color == "all"){
       digitalWrite(greenLed, HIGH);
       digitalWrite(whiteLed, HIGH);
       digitalWrite(redLed, HIGH);
    }else{
        digitalWrite(whiteLed, HIGH);
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, HIGH); 
    }
}
