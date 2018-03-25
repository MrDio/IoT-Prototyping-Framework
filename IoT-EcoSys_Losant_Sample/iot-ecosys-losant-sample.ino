
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
 * This is the sample dashboard of team e:
 * https://app.losant.com/dashboards/59de849dd2033400064dc378
 * 
 * Needed components
 * Mic MAX4466 (MAX)
 * Particle Photon (PHO)
 * 
 * Wiring
 * PHO (A0) - MAX (OUT)
 * PHO (GND) - MAX (GND)
 * PHO (3,3) - MAX (VCC)
 * 
 * @author Dionysios Satikidis (dionysios.satikidis@gmail.com)
 * @version 1.0
 */ 

// This #include statement was automatically added by the Particle IDE.
#include <SparkJson.h>

// This #include statement was automatically added by the Particle IDE.
#include <MQTT.h>

// Credentials for losant - see access keys
#define LOSANT_BROKER "broker.losant.com"
#define LOSANT_DEVICE_ID "<your device ID>"
#define LOSANT_ACCESS_KEY "<your access key>"
#define LOSANT_ACCESS_SECRET "<your access secret key>"

// Topic used to subscribe to Losant commands.
String MQTT_TOPIC_COMMAND =
    String::format("losant/%s/command", LOSANT_DEVICE_ID);

// Topic used to publish state to Losant.
String MQTT_TOPIC_STATE =
    String::format("losant/%s/state", LOSANT_DEVICE_ID);

// The Photon's onboard LED.
int LED = D7;

// Callback signature for MQTT subscriptions.
void callback(char* topic, byte* payload, unsigned int length);

// MQTT client.
MQTT client(LOSANT_BROKER, 1883, callback);

// Toggles the LED on/off whenever "toggle" command is received.
bool ledValue = false;

void callback(char* topic, byte* payload, unsigned int length) {
    
    // Parse the command payload.
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& command = jsonBuffer.parseObject((char*)payload);

    Serial.println("Command received:");
    command.printTo(Serial);
    Serial.println();
    
    // If the command's name is "toggle", flip the LED.
    if(String(command["name"].asString()).equals(String("toggle"))) {
        ledValue = !ledValue;
        digitalWrite(LED, ledValue ? HIGH : LOW);
        Serial.println("Toggling LED");
    }
}

void setup() {
    Serial.begin(9600);
    while(!Serial) { }

    pinMode(LED, OUTPUT);
}

// Connects to the Losant MQTT broker.
void connect() {

    Serial.print("Connecting to Losant...");

    while(!client.isConnected()) {
        client.connect(
            LOSANT_DEVICE_ID,
            LOSANT_ACCESS_KEY,
            LOSANT_ACCESS_SECRET);

        if(client.isConnected()) {
            Serial.println("connected!");
            client.subscribe(MQTT_TOPIC_COMMAND);
        }
        else {
            Serial.print(".");
            delay(500);
        }
    }
}

// Used to only send light value and micro value once a second.
int lastUpdate = millis();

void loop() {
    
    // check if connected to losant
    if (!client.isConnected()) {
        connect();
    }

    // Loop the MQTT client.
    client.loop();

    int now = millis();

    // Publish state every second.
    if(now - lastUpdate > 1000) {
        lastUpdate = now;
        
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        JsonObject& lightState = jsonBuffer.createObject();
        JsonObject& microState = jsonBuffer.createObject();

        // Build the json payload:
        // { "data" : { "light" : val }}
        int light = analogRead(A1);
        lightState["light"] = light;
        root["data"] = lightState;

        // Get JSON string.
        char buffer[200];
        root.printTo(buffer, sizeof(buffer));

        // Send JSON via MQTT to losant
        client.publish(MQTT_TOPIC_STATE, buffer);
        
        // Build the json payload:
        // { "data" : { "micro" : val }}
        int micro = analogRead(A0);
        microState["micro"] = micro;
        root["data"] = microState;
        
        // Get JSON string.
        root.printTo(buffer, sizeof(buffer));

        // Send JSON via MQTT to losant
        client.publish(MQTT_TOPIC_STATE, buffer);
    }
}

