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

#ifndef IoTEcoSys_SEN09088_Lig_H 
#define IoTEcoSys_SEN09088_Lig_H 

#include "application.h"
#include "math.h"

class IoTEcoSys_SEN09088_Lig {
	private:
		uint8_t _analog_pin_id;

	public:
		IoTEcoSys_SEN09088_Lig(uint8_t pin);
		bool init();
		int32_t getLigVal();
};
#endif


