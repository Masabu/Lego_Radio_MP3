#include <Arduino.h>
#include "ButtonController.h"

// Pin definitions
const int BUTTON_UP_PIN = D2;    // GPIO5
const int BUTTON_DOWN_PIN = D4;  // GPIO7
const int LED_UP_PIN = D3;       // GPIO6
const int LED_DOWN_PIN = D5;     // GPIO8

// Volume range: 0-21 (matches ESP32-audioI2S setVolume range)
const int VOLUME_MIN = 0;
const int VOLUME_MAX = 21;

// Create button controller for volume
ButtonController volumeControl(
    BUTTON_UP_PIN, 
    BUTTON_DOWN_PIN,
    LED_UP_PIN, 
    LED_DOWN_PIN,
    VOLUME_MIN, 
    VOLUME_MAX
);

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=====================================");
    Serial.println("LEGO Radio - Button Test");
    Serial.println("=====================================");
    
    volumeControl.begin();
    volumeControl.setValue(10);  // Start at middle volume
    
    Serial.print("Starting value: ");
    Serial.println(volumeControl.getValue());
    Serial.println("-------------------------------------");
}

void loop() {
    volumeControl.update();
    
    // Check if volume changed - here you would update the audio player
    if (volumeControl.hasChanged()) {
        int volume = volumeControl.getValue();
        
        // TODO: Add audio player volume control here
        // audio.setVolume(volume);
        
        Serial.print("Volume set to: ");
        Serial.println(volume);
    }
}
