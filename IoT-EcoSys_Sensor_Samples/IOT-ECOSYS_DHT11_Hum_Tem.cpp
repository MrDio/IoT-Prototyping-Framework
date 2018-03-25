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

#include "IOT-ECOSYS_DHT11_Hum_Tem.h"

// Constructor inits humidity & temperature sensor pin related to input pin (default is pin 2)
/*!
  \param pin digital pin on particle photon 
  \return obj insctance of class
*/
IoTEcoSys_DHT11_Hum_Tem::IoTEcoSys_DHT11_Hum_Tem(uint8_t pin=2) {
	_digital_pin_id = pin;
	if(_digital_pin_id == 0){
	    #define HT_PIN 0
	}else if(_digital_pin_id == 1){
	    #define HT_PIN 1
	}else if(_digital_pin_id == 2){
	    #define HT_PIN 2
	}else if(_digital_pin_id == 3){
	    #define HT_PIN 3
	}else if(_digital_pin_id == 4){
	    #define HT_PIN 4
	}else if(_digital_pin_id == 5){
	    #define HT_PIN 5
	}else{
	    #define HT_PIN 2
	}
}

//! The init function - nothing to do in this class
/*!
*/
bool IoTEcoSys_DHT11_Hum_Tem::init(){
    return true;
}

//! The init function - nothing to do in this class
/*!
  \Check the duration of a specific level status on the data line 
*/
uint8_t IoTEcoSys_DHT11_Hum_Tem::checkdelay(uint8_t us, uint8_t status)
{
    _us = us;
    _status = status;
    pinMode(_digital_pin_id, INPUT);
    unsigned long t = micros();
    while(digitalRead(_digital_pin_id) == _status) // Wait for a status variation
        if ((micros() - t) > _us) return 1;  // or a timeout
    return 0;
}

/*!
  \Read sensor data and check for errors
*/
void IoTEcoSys_DHT11_Hum_Tem::read()
{
 

    uint8_t bytes[5]; // input buffer
    uint8_t cnt = 7;
    uint8_t idx = 0;
    uint8_t chksum;
    unsigned long t;
    
    _digital_pin_id = HT_PIN;

    // Initialize the buffer
    for (uint8_t i=0; i< 5; i++) bytes[i] = 0;

    // Verify if the data line is busy
    if (!checkdelay(100, HIGH)) Particle.publish(String("Sensor status: "), String("Data line busy!")); // Data line busy

    // Send Start signal
    pinMode(HT_PIN, OUTPUT);
    digitalWrite(HT_PIN, LOW);
    delay(18);
    digitalWrite(HT_PIN, HIGH);
    delayMicroseconds(40);

    // Wait the Acknowledge signal
     if (checkdelay(100, LOW)) Particle.publish(String("Sensor status: "), String("Timeout!")); // Timeout
     if (checkdelay(100, HIGH)) Particle.publish(String("Sensor status: "), String("Timeout!")); // Timeout
    

    // Read data output from the sensor
    for (int i=0; i<40; i++)
    {
        if (checkdelay(60, LOW)) Particle.publish(String("Sensor status: "), String("Timeout!")); // Timeout
        t = micros();
        if (checkdelay(80, HIGH)) Particle.publish(String("Sensor status: "), String("Timeout!")); // Timeout

 	if ((micros() - t) > 40) bytes[idx] += (1 << cnt); // bit 1 received

 	if (cnt == 0)   // end of the byte
 	{
 	    cnt = 7;    // reset at MSB
 	    idx++;      // point to next byte
 	}
 	else cnt--;
    }

    // Update variables
    // bytes[1] and bytes[3] are allways zero
    _humidity    = bytes[0];
    _temperature = bytes[2];

    // Verify the Checksum value
    chksum = bytes[0] + bytes[2];
    if (chksum != bytes[4]) Particle.publish(String("Sensor status: "), String("Checksum error!")); // Checksum error
}

/*!
  \return humVal the value of the digital read pin 
*/
uint8_t IoTEcoSys_DHT11_Hum_Tem::getHumVal(){
    return _humidity;
}

/*!
  \return temVal the value of the digital read pin 
*/
uint8_t IoTEcoSys_DHT11_Hum_Tem::getTemVal(){
    return _temperature;
}


