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
 * This is a library for DHT11.
 * 
 * Needed components
 * Humidity & Temperature Sensor DHT11 (DHT)
 * Particle Photon (PHO)
 * 
 * Wiring
 * PHO (D2) - DHT (DATA)
 * PHO (GND) - DHT (GND)
 * PHO (VIN) - DHT (+5V)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */ 
 
#ifndef IoTEcoSys_DHT11_Hum_Tem_H
#define IoTEcoSys_DHT11_Hum_Tem_H

#include "application.h"
#include "math.h"

class IoTEcoSys_DHT11_Hum_Tem
{
private:
    uint8_t _digital_pin_id;
    uint8_t _us;
    uint8_t _status;
    uint8_t _temperature;
    uint8_t _humidity;
    
public:
    IoTEcoSys_DHT11_Hum_Tem(uint8_t pin);
    uint8_t checkdelay(uint8_t us, uint8_t status);
    
    void read();
    bool init();
    
    uint8_t getHumVal();
    uint8_t getTemVal();
};
#endif


