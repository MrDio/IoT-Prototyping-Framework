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

#include "IOT-ECOSYS_LSM9DS1_Acc_Gyr_Mag.h"


LSM9DS1 imu;

#define LSM9DS1_M	0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6B // Would be 0x6A if SDO_AG is LOW

IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::IoTEcoSys_LSM9DS1_Acc_Gyr_Mag(bool debug=true) {
    _debug = debug;
}

//! The init function inits the LSM9DS1 IMU
/*!
  \return bool true if init was successfull; false if init failed. 
/*!
*/
bool IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::init(){
    // Before initializing the IMU, there are a few settings
    // we may need to adjust. Use the settings struct to set
    // the device's communication mode and addresses:
    imu.settings.device.commInterface = IMU_MODE_I2C;
    imu.settings.device.mAddress = LSM9DS1_M;
    imu.settings.device.agAddress = LSM9DS1_AG;

    // Try to initialise and warn if we couldn't detect the chip
    if (!imu.begin())
    {
        if(_debug){
            Particle.publish("[Debug] Oops ... unable to initialize the LSM9DS1. Check your wiring!", 0);        
        }
        return 0;
    }
    if(_debug){
        Particle.publish("[Debug] LSM9DS1 ready", 1);        
    }
    return 1;
}

//! The fetch function touches the LSM9DS1 IMU sensors
/*!
  \return bool true if fetch was successfull; false if fetch failed. 
/*!
*/
bool IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::read() {
    return imu.readTemp() && imu.readMag() && imu.readAccel() && imu.readGyro();
}


// -- raw values ---------------------------------------

//! Returns the x raw value of the acc
/*!
  \return acc x acceleration value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccRaw_X() {
    return imu.ax;
}

//! Returns the y raw value of the acc
/*!
  \return acc y acceleration value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccRaw_Y() {
    return imu.ay;
}

//! Returns the z raw value of the acc
/*!
  \return acc z acceleration value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccRaw_Z() {
    return imu.az;
}

//! Returns the x raw value of the mag
/*!
  \return mag x magnetometer value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagRaw_X() {
    return imu.mx;
}

//! Returns the y raw value of the mag
/*!
  \return mag y magnetometer value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagRaw_Y() {
    return imu.my;
}

//! Returns the z raw value of the mag
/*!
  \return mag z magnetometer value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagRaw_Z() {
    return imu.mz;
}

//! Returns the x raw value of the gyr
/*!
  \return mag x gyroscope value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrRaw_X() {
    return imu.gx;
}

//! Returns the y raw value of the gyr
/*!
  \return mag y gyroscope value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrRaw_Y() {
    return imu.gy;
}

//! Returns the z raw value of the gyr
/*!
  \return mag z gyroscope value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrRaw_Z() {
    return imu.gz;
}

// -- calc values ---------------------------------------

//! Returns the x value of the acc
/*!
  \return acc x acceleration value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccVal_X() {
    return imu.calcAccel(imu.ax);
}

//! Returns the y value of the acc
/*!
  \return acc y acceleration value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccVal_Y() {
    return imu.calcAccel(imu.ay);
}

//! Returns the z value of the acc
/*!
  \return acc z acceleration value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getAccVal_Z() {
    return imu.calcAccel(imu.az);
}

//! Returns the x value of the mag
/*!
  \return mag x magnetometer value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagVal_X() {
    return imu.calcMag(imu.mx);
}

//! Returns the y value of the mag
/*!
  \return mag y magnetometer value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagVal_Y() {
    return imu.calcMag(imu.my);
}

//! Returns the z value of the mag
/*!
  \return mag z magnetometer value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getMagVal_Z() {
    return imu.calcMag(imu.mz);
}

//! Returns the x value of the gyr
/*!
  \return mag x gyroscope value in x direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrVal_X() {
    return imu.calcGyro(imu.gx);
}

//! Returns the y value of the gyr
/*!
  \return mag y gyroscope value in y direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrVal_Y() {
    return imu.calcGyro(imu.gy);
}

//! Returns the z value of the gyr
/*!
  \return mag z gyroscope value in z direction
*/
uint16_t IoTEcoSys_LSM9DS1_Acc_Gyr_Mag::getGyrVal_Z() {
    return imu.calcGyro(imu.gz);
}


