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

#ifndef IoTEcoSys_Max4466_Mic_H
#define IoTEcoSys_Max4466_Mic_H

#include "application.h"
#include "math.h"

class IoTEcoSys_Max4466_Mic {
	private:
		uint8_t _analog_pin_id;

	public:
		IoTEcoSys_Max4466_Mic(uint8_t pin);
		bool init();
		int32_t getMicVal();
};
#endif


