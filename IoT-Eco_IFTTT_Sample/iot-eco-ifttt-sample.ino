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
 * Particle
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */

void setup() {
    // nothing to set up
}

void loop() {
   // for IFTTT just a simple event publish is working. Dont forget connecting device to IFTTT and IFTTT to particle-cloud.
   Particle.publish("sample-event",1);
   // wait 10 sec
   delay(10000);
}