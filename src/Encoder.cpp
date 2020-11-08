#include "Encoder.h"
#include "Arduino.h"

Encoder::Encoder(uint8_t pinA, uint8_t pinB) {
    _pinA = pinA;
    _pinB = pinB;
}

void Encoder::begin() {
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
}

void Encoder::setStep(uint8_t step) { _step = step; }

uint8_t Encoder::getStep() const { return _step; }

void Encoder::setRange(uint8_t minValue, uint8_t maxValue) {
    _minValue = minValue;
    _maxValue = maxValue;
}

void Encoder::getRange(uint8_t& minValue, uint8_t& maxValue) {
    minValue = _minValue;
    maxValue = _maxValue;
}

void Encoder::setPosition(uint8_t position) { _position = position; }

uint8_t Encoder::getPosition() const { return _position; }

void Encoder::update() {
    bool statePinA = digitalRead(_pinA);
    bool statePinB = digitalRead(_pinB);

    if (statePinA && statePinB) {
        _moveEncoder = true;
    } else if (!statePinA && !statePinB) {
        _moveEncoder = true;
    }
    if (_moveEncoder) {
        if (statePinA && !statePinB) {
            if (_position > _minValue) {
                _position -= _step;
                _moveEncoder = false;
            }
        }
        if (!statePinA && statePinB) {
            if (_position < _maxValue) {
                _position += _step;
                _moveEncoder = false;
            }
        }
    }
}
