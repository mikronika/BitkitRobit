#ifndef __BITKIT_ROBIT_H__
#define __BITKIT_ROBIT_H__

#include "Arduino.h"
#include "Encoder.h"
#include <Servo.h>

// Пины светодиодов
constexpr uint8_t LED1_PIN = 12;
constexpr uint8_t LED2_PIN = 13;

// Пины кнопок
constexpr uint8_t BUTTON1_PIN = 3;
constexpr uint8_t BUTTON2_PIN = 2;
constexpr uint8_t BUTTON3_PIN = A5;
constexpr uint8_t BUTTON4_PIN = A4;

// Пины сервоприводов
constexpr uint8_t SERVO1_PIN = 5;
constexpr uint8_t SERVO2_PIN = 6;
constexpr uint8_t SERVO3_PIN = 9;
constexpr uint8_t SERVO4_PIN = 10;

// Пины энкодеров
constexpr uint8_t ENCODER1_PIN_A = 4;
constexpr uint8_t ENCODER1_PIN_B = 7;
constexpr uint8_t ENCODER2_PIN_A = 8;
constexpr uint8_t ENCODER2_PIN_B = 11;
constexpr uint8_t ENCODER3_PIN_A = A0;
constexpr uint8_t ENCODER3_PIN_B = A1;
constexpr uint8_t ENCODER4_PIN_A = A2;
constexpr uint8_t ENCODER4_PIN_B = A3;

// Позиции сервоприводов по умолчанию
// При таких данных манипулятор в среднем положении по всем суставам
constexpr uint8_t DEFAULT_VAL1 = 45;
constexpr uint8_t DEFAULT_VAL2 = 90;
constexpr uint8_t DEFAULT_VAL3 = 90;
constexpr uint8_t DEFAULT_VAL4 = 90;

// Шаг/чувствительность энкодеров по умолчанию
constexpr uint8_t DEFAULT_STEP = 1;

// Максимальный и минимальный угол поворота каждого из сервоприводов по умолчанию
constexpr uint8_t DEFAULT_MIN_VAL = 0;
constexpr uint8_t DEFAULT_MAX_VAL = 180;

// Класс светодиодов
enum class ManipulatorLed { LED1 = 1, LED2 = 2 };

// Класс кнопок
enum class ManipulatorButton { SW1 = 1, SW2 = 2, SW3 = 3, SW4 = 4 };

// Метки для хранения положения манипулятора
enum class ManipulatorPositionNumber {
    POSITION1 = 1,
    POSITION2 = 2,
    POSITION3 = 3,
    POSITION4 = 4,
    POSITION5 = 5,
    POSITION6 = 6,
    POSITION7 = 7,
    POSITION8 = 8,
    POSITION9 = 9,
    POSITION10 = 10
};

// Стуктура для хранения всех четырёх данных суставов
struct ManipulatorPositionValues {
    uint8_t value1;
    uint8_t value2;
    uint8_t value3;
    uint8_t value4;
};

class BitkitRobit {
public:
    BitkitRobit();
    void begin(uint8_t value1 = DEFAULT_VAL1, uint8_t value2 = DEFAULT_VAL2,
               uint8_t value3 = DEFAULT_VAL3, uint8_t value4 = DEFAULT_VAL4);
    void digitalWrite(ManipulatorLed led, bool value);
    bool digitalRead(ManipulatorButton sw);
    void setStep(uint8_t step1, uint8_t step2, uint8_t step3, uint8_t step4);
    void getStep(uint8_t& step1, uint8_t& step2, uint8_t& step3,
                 uint8_t& step4);
    void setRange(uint8_t minValue1, uint8_t maxValue1, uint8_t minValue2,
                  uint8_t maxValue2, uint8_t minValue3, uint8_t maxValue3,
                  uint8_t minValue4, uint8_t maxValue4);
    void getRange(uint8_t& minValue1, uint8_t& maxValue1, uint8_t& minValue2,
                  uint8_t& maxValue2, uint8_t& minValue3, uint8_t& maxValue3,
                  uint8_t& minValue4, uint8_t& maxValue4);
    void setPosition(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4);
    void getPosition(uint8_t& value1, uint8_t& value2, uint8_t& value3,
                     uint8_t& value4);
    void savePosition(ManipulatorPositionNumber positionNumber);
    void loadPosition(ManipulatorPositionNumber positionNumber);
    void clearPositions();
    void update();

private:
    ManipulatorPositionValues _positionValues[10];
    Encoder _encoder1, _encoder2, _encoder3, _encoder4;
    Servo _servo1, _servo2, _servo3, _servo4;
    void _servoAttachSmooth(Servo servo, uint8_t pin, uint8_t value);
    void _servoWriteSmooth(Servo servo, uint8_t valueStart, uint8_t valueEnd);
};

#endif // __BITKIT_ROBIT_H__
