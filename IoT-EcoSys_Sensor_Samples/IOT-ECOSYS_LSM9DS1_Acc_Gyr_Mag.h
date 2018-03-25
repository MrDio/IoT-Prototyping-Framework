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
 * This is a library for LSMD9S1.
 * 
 * Needed components
 * Nine degrees of freedom sensor LSMD9S1 (LSM)
 * Particle Photon (PHO)
 * 
 * Wiring
 * PHO (D0) - LSM (SDA)
 * PHO (D1) - LSM (SCL)
 * PHO (GND) - LSM (GND)
 * PHO (3V3) - LSM (3V3)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */ 

#ifndef IoTEcoSys_LSM9DS1_Acc_Gyr_Mag_H
#define IoTEcoSys_LSM9DS1_Acc_Gyr_Mag_H

// This #include statement was automatically added by the Particle IDE
#include <SparkFunLSM9DS1.h>

#include "application.h"
#include "math.h"

class IoTEcoSys_LSM9DS1_Acc_Gyr_Mag {
	private:
		bool _debug;

	public:
	    IoTEcoSys_LSM9DS1_Acc_Gyr_Mag(bool debug);
		bool init();
		bool read();
		
		uint16_t getAccRaw_X();
		uint16_t getAccRaw_Y();
		uint16_t getAccRaw_Z();
		
		uint16_t getMagRaw_X();
		uint16_t getMagRaw_Y();
		uint16_t getMagRaw_Z();
		
		uint16_t getGyrRaw_X();
		uint16_t getGyrRaw_Y();
		uint16_t getGyrRaw_Z();

		uint16_t getAccVal_X();
		uint16_t getAccVal_Y();
		uint16_t getAccVal_Z();
		
		uint16_t getMagVal_X();
		uint16_t getMagVal_Y();
		uint16_t getMagVal_Z();
		
		uint16_t getGyrVal_X();
		uint16_t getGyrVal_Y();
		uint16_t getGyrVal_Z();
};
#endif


