#include "BitkitRobit.h"

BitkitRobit::BitkitRobit()
    : _encoder1(ENCODER1_PIN_A, ENCODER1_PIN_B)
    , _encoder2(ENCODER2_PIN_A, ENCODER2_PIN_B)
    , _encoder3(ENCODER3_PIN_A, ENCODER3_PIN_B)
    , _encoder4(ENCODER4_PIN_A, ENCODER4_PIN_B) { }

void BitkitRobit::begin(uint8_t value1, uint8_t value2, uint8_t value3,
                        uint8_t value4) {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    ::digitalWrite(LED1_PIN, LOW);
    ::digitalWrite(LED2_PIN, LOW);
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);
    _encoder1.begin();
    _encoder2.begin();
    _encoder3.begin();
    _encoder4.begin();
    _encoder1.setPosition(value1);
    _encoder2.setPosition(value2);
    _encoder3.setPosition(value3);
    _encoder4.setPosition(value4);
    _servoAttachSmooth(_servo1, SERVO1_PIN, value1);
    _servoAttachSmooth(_servo2, SERVO2_PIN, value2);
    _servoAttachSmooth(_servo3, SERVO3_PIN, value3);
    _servoAttachSmooth(_servo4, SERVO4_PIN, value4);
    clearPositions();
    setStep(DEFAULT_STEP, DEFAULT_STEP, DEFAULT_STEP, DEFAULT_STEP);
    setRange(DEFAULT_MIN_VAL, DEFAULT_MAX_VAL, DEFAULT_MIN_VAL, DEFAULT_MAX_VAL,
             DEFAULT_MIN_VAL, DEFAULT_MAX_VAL, DEFAULT_MIN_VAL,
             DEFAULT_MAX_VAL);
}

void BitkitRobit::digitalWrite(ManipulatorLed led, bool value) {
    switch (led) {
    case ManipulatorLed::LED1: {
        ::digitalWrite(LED1_PIN, value);
        break;
    }
    case ManipulatorLed::LED2: {
        ::digitalWrite(LED2_PIN, value);
        break;
    }
    default: {
    } break;
    }
}

bool BitkitRobit::digitalRead(ManipulatorButton sw) {
    bool stateButton;
    switch (sw) {
    case ManipulatorButton::SW1: {
        stateButton = ::digitalRead(BUTTON1_PIN);
        break;
    }
    case ManipulatorButton::SW2: {
        stateButton = ::digitalRead(BUTTON2_PIN);
        break;
    }
    case ManipulatorButton::SW3: {
        stateButton = ::digitalRead(BUTTON3_PIN);
        break;
    }
    case ManipulatorButton::SW4: {
        stateButton = ::digitalRead(BUTTON4_PIN);
        break;
    }
    default: {
    } break;
    }
    return stateButton;
}

void BitkitRobit::setStep(uint8_t step1, uint8_t step2, uint8_t step3,
                          uint8_t step4) {
    _encoder1.setStep(step1);
    _encoder2.setStep(step2);
    _encoder3.setStep(step3);
    _encoder4.setStep(step4);
}

void BitkitRobit::getStep(uint8_t& step1, uint8_t& step2, uint8_t& step3,
                          uint8_t& step4) {
    step1 = _encoder1.getStep();
    step2 = _encoder2.getStep();
    step3 = _encoder3.getStep();
    step4 = _encoder4.getStep();
}

void BitkitRobit::setRange(uint8_t minValue1, uint8_t maxValue1,
                           uint8_t minValue2, uint8_t maxValue2,
                           uint8_t minValue3, uint8_t maxValue3,
                           uint8_t minValue4, uint8_t maxValue4) {
    _encoder1.setRange(minValue1, maxValue1);
    _encoder2.setRange(minValue2, maxValue2);
    _encoder3.setRange(minValue3, maxValue3);
    _encoder4.setRange(minValue4, maxValue4);
}

void BitkitRobit::getRange(uint8_t& minValue1, uint8_t& maxValue1,
                           uint8_t& minValue2, uint8_t& maxValue2,
                           uint8_t& minValue3, uint8_t& maxValue3,
                           uint8_t& minValue4, uint8_t& maxValue4) {
    _encoder1.getRange(minValue1, maxValue1);
    _encoder2.getRange(minValue2, maxValue2);
    _encoder3.getRange(minValue3, maxValue3);
    _encoder4.getRange(minValue4, maxValue4);
}

void BitkitRobit::setPosition(uint8_t value1, uint8_t value2, uint8_t value3,
                              uint8_t value4) {
    uint8_t preValue1, preValue2, preValue3, preValue4;
    getPosition(preValue1, preValue2, preValue3, preValue4);
    uint8_t minValue1, maxValue1, minValue2, maxValue2, minValue3, maxValue3,
        minValue4, maxValue4;
    getRange(minValue1, maxValue1, minValue2, maxValue2, minValue3, maxValue3,
             minValue4, maxValue4);
    if (value1 < minValue1) {
        value1 = minValue1;
    } else if (value1 > maxValue1) {
        value1 = maxValue1;
    }

    if (value2 < minValue2) {
        value2 = minValue2;
    } else if (value2 > maxValue2) {
        value2 = maxValue2;
    }

    if (value3 < minValue3) {
        value3 = minValue3;
    } else if (value3 > maxValue3) {
        value3 = maxValue3;
    }

    if (value4 < minValue4) {
        value4 = minValue4;
    } else if (value4 > maxValue4) {
        value4 = maxValue4;
    }

    _servoWriteSmooth(_servo1, preValue1, value1);
    _servoWriteSmooth(_servo2, preValue2, value2);
    _servoWriteSmooth(_servo3, preValue3, value3);
    _servoWriteSmooth(_servo4, preValue4, value4);
    _encoder1.setPosition(value1);
    _encoder2.setPosition(value2);
    _encoder3.setPosition(value3);
    _encoder4.setPosition(value4);
}

void BitkitRobit::getPosition(uint8_t& value1, uint8_t& value2, uint8_t& value3,
                              uint8_t& value4) {
    value1 = _encoder1.getPosition();
    value2 = _encoder2.getPosition();
    value3 = _encoder3.getPosition();
    value4 = _encoder4.getPosition();
}

void BitkitRobit::savePosition(ManipulatorPositionNumber positionNumber) {
    _positionValues[static_cast<int>(positionNumber)].value1
        = _encoder1.getPosition();
    _positionValues[static_cast<int>(positionNumber)].value2
        = _encoder2.getPosition();
    _positionValues[static_cast<int>(positionNumber)].value3
        = _encoder3.getPosition();
    _positionValues[static_cast<int>(positionNumber)].value4
        = _encoder4.getPosition();
}

void BitkitRobit::loadPosition(ManipulatorPositionNumber positionNumber) {
    uint8_t value1, value2, value3, value4;
    value1 = _positionValues[static_cast<int>(positionNumber)].value1;
    value2 = _positionValues[static_cast<int>(positionNumber)].value2;
    value3 = _positionValues[static_cast<int>(positionNumber)].value3;
    value4 = _positionValues[static_cast<int>(positionNumber)].value4;
    if (value1 == 0 && value2 == 0 && value3 == 0 && value4 == 0) {
        return;
    }
    setPosition(value1, value2, value3, value4);
}

void BitkitRobit::clearPositions() {
    memset(_positionValues, 0, sizeof(_positionValues));
}

void BitkitRobit::update() {
    _encoder1.update();
    _encoder2.update();
    _encoder3.update();
    _encoder4.update();
    _servo1.write(_encoder1.getPosition());
    _servo2.write(_encoder2.getPosition());
    _servo3.write(_encoder3.getPosition());
    _servo4.write(_encoder4.getPosition());
    delay(10);
}

void BitkitRobit::_servoAttachSmooth(Servo servo, uint8_t pin, uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        servo.attach(pin);
        servo.write(value);
        delay(50);
        servo.detach();
        delay(200);
    }
    servo.attach(pin);
}

void BitkitRobit::_servoWriteSmooth(Servo servo, uint8_t valueStart,
                                    uint8_t valueEnd) {
    if (valueStart < valueEnd) {
        for (uint8_t pos = valueStart; pos <= valueEnd; pos++) {
            servo.write(pos);
            delay(50);
        }
    } else if (valueStart > valueEnd) {
        for (uint8_t pos = valueStart; pos >= valueEnd; pos--) {
            servo.write(pos);
            delay(50);
        }
    }
}