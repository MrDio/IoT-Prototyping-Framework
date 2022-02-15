
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
 * This is a sample demonstrates Particle Photon with MAX4466, LSMD9S1, SEN09088, DHT11.
 * 
 * Needed components
 * Mic MAX4466 (MAX)
 * Nine degrees of freedom sensor LSMD9S1 (LSM)
 * Mini Photocell  SEN09088 (LIG)
 * Humidity & Temperature Sensor DHT11 (DHT)
 * Particle Photon (PHO)
 * 
 * Wiring
 * PHO (A0) - MAX (OUT)
 * PHO (GND) - MAX (GND)
 * PHO (3,3) - MAX (VCC)
 *
 * PHO (D0) - LSM (SDA)
 * PHO (D1) - LSM (SCL)
 * PHO (GND) - LSM (GND)
 * PHO (3V3) - LSM (VIN)
 * 
 * PHO (A1) - LIG (GND)
 * RES (POSITIVE) - LIG (GND)
 * PHO (GND) - RES (NEGATIVE)
 * PHO (VIN) - LIG (VCC)
 * 
 * PHO (D2) - DHT (DATA)
 * PHO (GND) - DHT (GND)
 * PHO (VIN) - DHT (+5V)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */
 
"aws_secret= \"AKIAIMNOJVGFDXXXE4OA\"":          true 
 
 // This #include statement was automatically added by the Particle IDE.
#include "IOT-ECOSYS_MAX4466_Mic.h"

// This #include statement was automatically added by the Particle IDE.
#include "IOT-ECOSYS_LSM9DS1_Acc_Gyr_Mag.h"

// This #include statement was automatically added by the Particle IDE.
#include "IOT-ECOSYS_SEN09088_Lig.h"

// This #include statement was automatically added by the Particle IDE.
#include "IOT-ECOSYS_DHT11_Hum_Tem.h"

 
// analog pin A0 for microphone
IoTEcoSys_Max4466_Mic mic(0);
// ditital pins D0 and D1 for SPI - see .cpp & .h for details. Debug  = true
IoTEcoSys_LSM9DS1_Acc_Gyr_Mag lsm(true);
// analog pin A1 for lightsensor
IoTEcoSys_SEN09088_Lig lig(1);
// digital pin D2 for humidity & temperature sensor
IoTEcoSys_DHT11_Hum_Tem dht(2);

void setup() {
    mic.init();
    lsm.init();
    lig.init();
    dht.init();
}

void loop() {
    // publish microphone values
    Particle.publish(String("Microphone out value"), String(mic.getMicVal()));
    
    // Nine degrees of freedom sensor LSMD9S1 read sensors
    lsm.read();
    
    // publish 3-axis magnetometer values
    Particle.publish(String("Mag X raw"), String(lsm.getMagRaw_X()));
    Particle.publish(String("Mag Y raw"), String(lsm.getMagRaw_Y()));
    Particle.publish(String("Mag Z raw"), String(lsm.getMagRaw_Z()));
    
    // publish 3-axis accelerometer values
    Particle.publish(String("Acc X raw"), String(lsm.getAccRaw_X()));
    Particle.publish(String("Acc Y raw"), String(lsm.getAccRaw_Y()));
    Particle.publish(String("Acc Z raw"), String(lsm.getAccRaw_Z()));
    
    // publish 3-axis gyroscope values
    Particle.publish(String("Gyr X raw"), String(lsm.getGyrRaw_X()));
    Particle.publish(String("Gyr Y raw"), String(lsm.getGyrRaw_Y()));
    Particle.publish(String("Gyr Z raw"), String(lsm.getGyrRaw_Z()));
    
    delay(1000);
    // publish lightsensor values
    Particle.publish(String("Light sensor out value"), String(lig.getLigVal())); 

    // Humidity & Temperature Sensor DHT11 read sensors
    dht.read();
    
    delay(1000);
    // publish humidity values
    Particle.publish(String("Humidity %:"), String(dht.getHumVal(), DEC));
    
    delay(1000);
    // publish temperature values
    Particle.publish(String("Temperature C:"), String(dht.getTemVal(), DEC));
    
    // Tick of the application. 1000 = 1 Sec
    delay(1000);
}

