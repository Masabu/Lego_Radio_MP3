#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>

class ButtonController {
public:
    // Constructor
    ButtonController(int upButtonPin, int downButtonPin, 
                     int upLedPin, int downLedPin,
                     int minValue = 0, int maxValue = 21);
    
    // Initialize pins
    void begin();
    
    // Call this in loop() - handles debouncing and updates
    void update();
    
    // Get current counter value
    int getValue() const;
    
    // Set counter value (clamped to min/max)
    void setValue(int value);
    
    // Set debounce delay in milliseconds
    void setDebounceDelay(unsigned long delay);
    
    // Check if value changed since last check
    bool hasChanged();

private:
    // Pin assignments
    const int _upButtonPin;
    const int _downButtonPin;
    const int _upLedPin;
    const int _downLedPin;
    
    // Value limits
    const int _minValue;
    const int _maxValue;
    
    // Current value
    int _value;
    
    // Change tracking
    bool _valueChanged;
    
    // Debounce settings
    unsigned long _debounceDelay;
    
    // UP button state
    int _upButtonState;
    int _lastUpButtonState;
    unsigned long _lastUpDebounceTime;
    
    // DOWN button state
    int _downButtonState;
    int _lastDownButtonState;
    unsigned long _lastDownDebounceTime;
    
    // Helper method to handle single button
    bool processButton(int reading, int& buttonState, int& lastButtonState, 
                       unsigned long& lastDebounceTime, int ledPin);
};

#endif