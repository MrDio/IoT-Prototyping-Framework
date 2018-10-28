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


// analog pin A0 for microphone
IoTEcoSys_NeoPIXEL_Ring ring(16);

void setup(){
    ring.init();    
}

// Uncomment to test the NeoPixel ring
void loop() {
  ring.neoRingFillClockWise(500, 100, "blue");
  ring.neoRingCounterClockWise(10,30, "blue");
  ring.neoRingDoubleCounterClockWise(10, 20, "blue");
}