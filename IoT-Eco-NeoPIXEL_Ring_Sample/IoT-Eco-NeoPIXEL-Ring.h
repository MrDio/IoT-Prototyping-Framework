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
 
  
#ifndef IoTEcoSys_NeoPIXEL_Ring_H
#define IoTEcoSys_NeoPIXEL_Ring_H

// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

#include "application.h"
#include "math.h"

class IoTEcoSys_NeoPIXEL_Ring
{
private:

public:
    IoTEcoSys_NeoPIXEL_Ring(int pixel);
    IoTEcoSys_NeoPIXEL_Ring();
    bool init();
    int setGlRGB( String color);
    void neoRingClockWise(int circles, int del, String color);
    void neoRingFillClockWise(int showuptime, int del, String color);
    void neoRingDoubleCounterClockWise(int circles, int del, String color);
    void neoRingCounterClockWise(int circles, int del, String color);
    void changeColor(uint32_t color);
};
#endif



 
 