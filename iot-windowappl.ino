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
 * This is a sample demonstrates particle photon with losant.
 *
 * Needed components
 * Mic MAX4466 (MAX)
 * Particle Photon (PHO)
 * SD-Card (SD)
 * 9DOF LSM9DS1 (LSM)
 *
 * Wiring
 * see assignment description of lecture
 *
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @author Vinay Kumar Puligilla
 * @author Alisa Jaekle
 * @author Pascal Walter
 * @version 1.0
 */

// This #include statement was automatically added by the Particle IDE.
#include <SparkFunLSM9DS1.h>

// This #include statement was automatically added by the Particle IDE.
#include <SdFat.h>

#include "math.h"

LSM9DS1 imu;

#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

#define LED_PIN D7
#define OPEN_PIN D3 //red
#define CLOSE_PIN D5 //green
#define TILT_PIN D4 //yellow
#define CONFIG_PIN D2
#define TICK_TIMER 100 // in milliseconds


//Window Calibration Parameters------------------------------------------------------------------------------

//Number of samples required to confirm that there is a rotation movement.
#define MAGX_SAMPLETHRESHOLD 10
#define TILT_SAMPLETHRESHOLD 250
#define ROTY_SAMPLETHRESHOLD 10

//Window Callibration parameters
#define GYRY_LH_OPENMAX  14000
#define GYRY_LH_OPENMIN	 1500
#define GYRY_RH_OPENMIN	(59429-20)
#define GYRY_RH_OPENMAX	(64500+20)

#define ACCZ_TILTMAX (63350)

//------------------------------------------------------------------------------
typedef enum STATE{CLOSE, TILTOPEN, OPEN} STATE_TYPE;

STATE_TYPE WinState = CLOSE;


struct DataTick{
	
    uint16_t accx;
    uint16_t accy;
    uint16_t accz;
    
    uint16_t magx;
    uint16_t magy;
    uint16_t magz;

    uint16_t gyrx;
    uint16_t gyry;
    uint16_t gyrz;
	float 	 abs_value;
};

bool debug = true;
bool InitialDelay = true;
bool Configstatus;

int Mag_RotXTiltOpenCntr = 0;
int Mag_RotXTiltCloseCntr = 0;
int Mag_RotXCloseCntr = 0;
int Gyr_RotYOpenCntr = 0;
int CalibrationCntr = 0;
int MAG_CLOSEMAX_calib = 0;
int MAG_CLOSEMIN_calib = 113500;
int CalibState = 1;



DataTick buffer;

void setup() {
	
	int ConfigPinstatus;

    Serial.begin(115200);
    // register the Particle function
    Particle.function("checkStatus", checkStatus);

    // Wait for USB Serial
    pinMode(LED_PIN, OUTPUT);
    pinMode(OPEN_PIN, OUTPUT);
    pinMode(CLOSE_PIN, OUTPUT);
    pinMode(TILT_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    if(debug){
        Particle.publish("[Debug] Setup start","1", 1);
    }

    // Before initializing the IMU, there are a few settings
    // we may need to adjust. Use the settings struct to set
    // the device's communication mode and addresses:
    imu.settings.device.commInterface = IMU_MODE_I2C;
    imu.settings.device.mAddress = LSM9DS1_M;
    imu.settings.device.agAddress = LSM9DS1_AG;

    // Try to initialise and warn if we couldn't detect the chip
    if (!imu.begin())
    {
        if(debug){
            Particle.publish("[Debug] Oops ... unable to initialize the LSM9DS0. Check your wiring!","0",0);
        }
        while (1);
    }
    if(debug){
        Particle.publish("[Debug] LSM9DS1 ready","1", 1);
    }

    if(debug){
        Particle.publish("[Debug] Setup done...","1", 1);
    }
    
    ConfigPinstatus = digitalRead(CONFIG_PIN);
    if (ConfigPinstatus == HIGH)
    {
    	Configstatus = HIGH;
    	Particle.publish("[Debug] Configuration status","Window Handle: Right side", 1);
    }
    else
    {
    	Configstatus = LOW;
    	Particle.publish("[Debug] Configuration status","Window Handle: Left side", 1);
    }
}

void loop() {
	
	if (InitialDelay == true)
	{
		delay(6000);// Initial delay is added to ensure that the sensor data is stablized before calibration process begins
		InitialDelay = false;
	}

    imu.readGyro();
    imu.readMag();
    imu.readAccel();
    
    buffer.accx=imu.ax;
    buffer.accy=imu.ay;
    buffer.accz=imu.az;

    buffer.magx=imu.mx;
    buffer.magy=imu.my;
    buffer.magz=imu.mz;
	/*Absolute position value is calculated*/
	buffer.abs_value = sqrt((pow(buffer.magx,2)) + (pow(buffer.magy,2)) + (pow(buffer.magz,2)));

    buffer.gyrx=imu.gx;
    buffer.gyry=imu.gy;
    buffer.gyrz=imu.gz;
	
	
	if (CalibState == 1)
	{
		/*All LEDS are set to high, indicating that the calibration process is active*/
		digitalWrite(OPEN_PIN, HIGH);
		digitalWrite(TILT_PIN, HIGH);
		digitalWrite(CLOSE_PIN, HIGH);
		if (CalibrationCntr <= 200)
		{
			if (buffer.abs_value > MAG_CLOSEMAX_calib)
			{
				MAG_CLOSEMAX_calib = buffer.abs_value;
			}
			else if (buffer.abs_value < MAG_CLOSEMIN_calib)
			{
				MAG_CLOSEMIN_calib = buffer.abs_value;
			}
			CalibrationCntr++;
		}
		else
		{
			CalibrationCntr = 0;
			Particle.publish("[Debug] Window Calibration State","Calibrated", 1);
			Particle.publish("[Debug] Window Calibration Values", "MAG_CLOSEMAX:" + String(MAG_CLOSEMAX_calib) + "MAG_CLOSEMIN:" + String(MAG_CLOSEMIN_calib), 1);
			CalibState = 0;
			/*All LEDS are set to low, indicating that the calibration process is completed*/
			digitalWrite(OPEN_PIN, LOW);
			digitalWrite(TILT_PIN, LOW);
			digitalWrite(CLOSE_PIN, LOW);
		}

	}
	else{
	
		CalibrationCntr = 0;
		switch(WinState){
			case(CLOSE)://close
			{
				if (((Configstatus == HIGH) && ((buffer.gyry > GYRY_RH_OPENMIN) && (buffer.gyry < GYRY_RH_OPENMAX))) || ((Configstatus == LOW) && ((buffer.gyry < GYRY_LH_OPENMAX)) && (buffer.gyry > GYRY_LH_OPENMIN)))
				{
					if (Gyr_RotYOpenCntr <= ROTY_SAMPLETHRESHOLD)
					{
						Gyr_RotYOpenCntr++;
					}
					if (Gyr_RotYOpenCntr >= ROTY_SAMPLETHRESHOLD)
					{
						WinState = OPEN;
						digitalWrite(OPEN_PIN, HIGH);
						digitalWrite(CLOSE_PIN, LOW);
						Gyr_RotYOpenCntr = 0;
						Mag_RotXTiltOpenCntr = 0;
						Particle.publish("[Debug] Window State","OPEN", 1);
						delay(TICK_TIMER);// publish takes time therfore wait for 100ms
					}
				}
				else if (buffer.accz <= ACCZ_TILTMAX)
				{
					if (Mag_RotXTiltOpenCntr <= TILT_SAMPLETHRESHOLD)
					{
						Mag_RotXTiltOpenCntr++;
					}
					if (Mag_RotXTiltOpenCntr >= TILT_SAMPLETHRESHOLD) // check for the rotation around x axis for confirmation
					{
						WinState = TILTOPEN;
						digitalWrite(TILT_PIN, HIGH);
						digitalWrite(CLOSE_PIN, LOW);
						Mag_RotXTiltOpenCntr = 0;
						Gyr_RotYOpenCntr = 0;// counters must be set to zero to avoid accumilation of disturbances
						Particle.publish("[Debug] Window state","TILT OPEN", 1);
						delay(TICK_TIMER);// publish takes time therfore wait for 100ms
					}
				}
			}
			case(TILTOPEN)://tilt open
			{
				if (((buffer.abs_value >= MAG_CLOSEMIN_calib) && (buffer.abs_value <= MAG_CLOSEMAX_calib)))
				{
					if (Mag_RotXTiltCloseCntr <= MAGX_SAMPLETHRESHOLD)
					{
						Mag_RotXTiltCloseCntr++;
					}
					if (Mag_RotXTiltCloseCntr >= MAGX_SAMPLETHRESHOLD) // check for the rotation around x axis for confirmation
					{
						WinState = CLOSE;
						digitalWrite(TILT_PIN, LOW);
						digitalWrite(CLOSE_PIN, HIGH);
						Mag_RotXTiltCloseCntr = 0;
						Particle.publish("[Debug] Window state","CLOSE", 1);
						delay(TICK_TIMER);// publish takes time therfore wait for 100ms
					}
				}
			}
			case(OPEN): //open
			{
				if (((buffer.abs_value >= MAG_CLOSEMIN_calib) && (buffer.abs_value <= MAG_CLOSEMAX_calib)))
				{
					if (Mag_RotXCloseCntr <= MAGX_SAMPLETHRESHOLD)
					{
						Mag_RotXCloseCntr++;
					}
					if (Mag_RotXCloseCntr >= MAGX_SAMPLETHRESHOLD)
					{
						WinState = CLOSE;
						digitalWrite(OPEN_PIN, LOW);
						digitalWrite(CLOSE_PIN, HIGH);
						Mag_RotXCloseCntr = 0;
						Particle.publish("[Debug] Window state","CLOSE", 1);
						delay(TICK_TIMER);// publish takes time therfore wait for 100ms
					}
				}
			}
		}
	
	}
}


// this function automatically shows up in IFTTT
int checkStatus(String command)
{
	switch(WinState){
		case(OPEN)://close
		{
			Particle.publish("OPEN", "OPEN", 1);
			return 1;
		}
		case(TILTOPEN)://tilt
		{
			Particle.publish("TILT", "TILT", 1);
			return 1;
		}   
	}
    return -1;
}

