#include "ButtonController.h"

ButtonController::ButtonController(int upButtonPin, int downButtonPin,
                                   int upLedPin, int downLedPin,
                                   int minValue, int maxValue)
    : _upButtonPin(upButtonPin)
    , _downButtonPin(downButtonPin)
    , _upLedPin(upLedPin)
    , _downLedPin(downLedPin)
    , _minValue(minValue)
    , _maxValue(maxValue)
    , _value(minValue)
    , _valueChanged(false)
    , _debounceDelay(30)
    , _upButtonState(HIGH)
    , _lastUpButtonState(HIGH)
    , _lastUpDebounceTime(0)
    , _downButtonState(HIGH)
    , _lastDownButtonState(HIGH)
    , _lastDownDebounceTime(0)
{
}

void ButtonController::begin() {
    pinMode(_upButtonPin, INPUT_PULLUP);
    pinMode(_downButtonPin, INPUT_PULLUP);
    pinMode(_upLedPin, OUTPUT);
    pinMode(_downLedPin, OUTPUT);
    
    digitalWrite(_upLedPin, LOW);
    digitalWrite(_downLedPin, LOW);
    
    Serial.println("ButtonController initialized");
    Serial.print("Value range: ");
    Serial.print(_minValue);
    Serial.print(" - ");
    Serial.println(_maxValue);
}

void ButtonController::update() {
    int readingUp = digitalRead(_upButtonPin);
    int readingDown = digitalRead(_downButtonPin);
    
    // Process UP button
    if (processButton(readingUp, _upButtonState, _lastUpButtonState, 
                      _lastUpDebounceTime, _upLedPin)) {
        if (_value < _maxValue) {
            _value++;
            _valueChanged = true;
            Serial.print("UP pressed! Value: ");
            Serial.println(_value);
        } else {
            Serial.println("UP pressed - already at maximum");
        }
    }
    
    // Process DOWN button
    if (processButton(readingDown, _downButtonState, _lastDownButtonState,
                      _lastDownDebounceTime, _downLedPin)) {
        if (_value > _minValue) {
            _value--;
            _valueChanged = true;
            Serial.print("DOWN pressed! Value: ");
            Serial.println(_value);
        } else {
            Serial.println("DOWN pressed - already at minimum");
        }
    }
}

bool ButtonController::processButton(int reading, int& buttonState, 
                                      int& lastButtonState,
                                      unsigned long& lastDebounceTime, 
                                      int ledPin) {
    bool pressed = false;
    
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > _debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            
            if (buttonState == LOW) {
                // Button pressed
                digitalWrite(ledPin, HIGH);
                pressed = true;
            } else {
                // Button released
                digitalWrite(ledPin, LOW);
            }
        }
    }
    
    lastButtonState = reading;
    return pressed;
}

int ButtonController::getValue() const {
    return _value;
}

void ButtonController::setValue(int value) {
    _value = constrain(value, _minValue, _maxValue);
    _valueChanged = true;
}

void ButtonController::setDebounceDelay(unsigned long delay) {
    _debounceDelay = delay;
}

bool ButtonController::hasChanged() {
    if (_valueChanged) {
        _valueChanged = false;
        return true;
    }
    return false;
}
