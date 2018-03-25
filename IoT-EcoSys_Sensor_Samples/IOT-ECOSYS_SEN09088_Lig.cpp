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
 * This is a library for SEN09088.
 * 
 * Needed components
 * Mini Photocell  SEN09088 (LIG)
 * Particle Photon (PHO)
 * Resistor 10kΩ (RES)
 * 
 * Wiring
 * PHO (A1) - LIG (GND)
 * RES (POSITIVE) - LIG (GND)
 * PHO (GND) - RES (NEGATIVE)
 * PHO (VIN) - LIG (VCC)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */ 

#include "IOT-ECOSYS_SEN09088_Lig.h"

// Constructor inits lightsensor pin related to input pin (default is pin 1)
/*!
  \param pin analog pin on particle photon 
  \return obj insctance of class
*/
IoTEcoSys_SEN09088_Lig::IoTEcoSys_SEN09088_Lig(uint8_t pin=1) {
	_analog_pin_id = pin;
	if(_analog_pin_id == 0){
	    #define LIGHTSENSOR_PIN A0
	}else if(_analog_pin_id == 1){
	    #define LIGHTSENSOR_PIN A1
	}else if(_analog_pin_id == 2){
	    #define LIGHTSENSOR_PIN A2
	}else if(_analog_pin_id == 3){
	    #define LIGHTSENSOR_PIN A3
	}else if(_analog_pin_id == 4){
	    #define LIGHTSENSOR_PIN A4
	}else if(_analog_pin_id == 5){
	    #define LIGHTSENSOR_PIN A5
	}else{
	    #define LIGHTSENSOR_PIN A1
	}
}

//! The init function - nothing to do in this class
/*!
*/
bool IoTEcoSys_SEN09088_Lig::init(){
    return true;
}

//! The init function - nothing to do in this class
/*!
  \return ligVal the value of the analog read pin 
*/
int32_t IoTEcoSys_SEN09088_Lig::getLigVal() {
	return analogRead(LIGHTSENSOR_PIN);
}


