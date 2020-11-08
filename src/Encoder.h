#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"

class Encoder {
public:
    Encoder(uint8_t pinA, uint8_t pinB);
    void begin();
    void setStep(uint8_t step);
    uint8_t getStep() const;
    void setRange(uint8_t minValue, uint8_t maxValue);
    void getRange(uint8_t& minValue, uint8_t& maxValue);
    void setPosition(uint8_t value);
    uint8_t getPosition() const;
    void update();

private:
    uint8_t _pinA, _pinB;
    uint8_t _minValue, _maxValue;
    uint8_t _step;
    uint8_t _position;
    bool _moveEncoder;
};

#endif // __ENCODER_H__
