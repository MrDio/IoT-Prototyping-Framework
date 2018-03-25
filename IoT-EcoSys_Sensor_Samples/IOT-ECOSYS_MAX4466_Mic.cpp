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
 * This is a library for MAX4466.
 * 
 * Needed components
 * Mic MAX4466 (MAX)
 * Particle Photon (PHO)
 * 
 * Wiring
 * PHO (A0) - MAX (OUT)
 * PHO (GND) - MAX (GND)
 * PHO (3V3) - MAX (VCC)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */ 

#include "IOT-ECOSYS_MAX4466_Mic.h"

// Constructor inits microphone pin related to input pin (default is pin 0)
/*!
  \param pin analog pin on particle photon 
  \return obj insctance of class
*/
IoTEcoSys_Max4466_Mic::IoTEcoSys_Max4466_Mic(uint8_t pin=0) {
	_analog_pin_id = pin;
	if(_analog_pin_id == 0){
	    #define MICROPHONE_PIN A0
	}else if(_analog_pin_id == 1){
	    #define MICROPHONE_PIN A1
	}else if(_analog_pin_id == 2){
	    #define MICROPHONE_PIN A2
	}else if(_analog_pin_id == 3){
	    #define MICROPHONE_PIN A3
	}else if(_analog_pin_id == 4){
	    #define MICROPHONE_PIN A4
	}else if(_analog_pin_id == 5){
	    #define MICROPHONE_PIN A5
	}else{
	    #define MICROPHONE_PIN A0
	}
}

//! The init function - nothing to do in this class
/*!
*/
bool IoTEcoSys_Max4466_Mic::init(){
    return true;
}

//! The init function - nothing to do in this class
/*!
  \return micVal the value of the analog read pin 
*/
int32_t IoTEcoSys_Max4466_Mic::getMicVal() {
	return analogRead(MICROPHONE_PIN);
}


