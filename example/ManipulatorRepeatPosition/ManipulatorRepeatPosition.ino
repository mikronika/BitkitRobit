/*
 * Этот пример демонстрирует режим сохранения и повторения. 
 * Для запоминания текущего состояния используйте кнопку SW1. 
 * Манипулятор может запомнить до 10 положений, которые контроллер воспроизводит при нажатии кнопки SW2. 
 * Чтобы сбросить все сохранения и начать программировать новую последовательность — нажмите кнопку SW3.
 */

// Библиотека для управления манипулятором
#include "BitkitRobit.h"

// Создаём объект для работы с манипулятором
BitkitRobit robit;

void setup() {
    Serial.begin(9600);
    // Инициализация манипулятора
    robit.begin();
    // Устанавливаем шаг/чувствительность энкодеров
    robit.setStep(2, 3, 3, 5);
    // Устанавливаем предельные границы для сервоприводов
    robit.setRange(0, 180, 0, 180, 0, 180, 0, 180);
    // Устанавливаем начальное положение манипулятора
    robit.setPosition(45, 90, 90, 90);
}

void loop() {
    // Обновляем данные работы с манипулятором
    robit.update();
    // Если нажали на кнопку SW1
    if (!robit.digitalRead(ManipulatorButton::SW1)) {
        // Мигаем быстро два раза светодиодами LED1 и LED2
        bool stateLed = false;
        for (int i = 0; i < 5; i++) {
            robit.digitalWrite(ManipulatorLed::LED1, stateLed);
            robit.digitalWrite(ManipulatorLed::LED2, stateLed);
            stateLed = !stateLed;
            delay(200);
        }
        // Сохраняем текущее состояние сервоприводов на манипуляторе
        robit.savePosition(ManipulatorPositionNumber::POSITION1);
        // Если нажали на кнопку SW2
    } else if (!robit.digitalRead(ManipulatorButton::SW2)) {
        // Включаем светодиоды LED1 и LED2
        robit.digitalWrite(ManipulatorLed::LED1, HIGH);
        robit.digitalWrite(ManipulatorLed::LED2, HIGH);
        // Загружаем текущее состояние сервоприводов на манипуляторе
        robit.loadPosition(ManipulatorPositionNumber::POSITION1);
        // Выключаем светодиоды LED1 и LED2
        robit.digitalWrite(ManipulatorLed::LED1, LOW);
        robit.digitalWrite(ManipulatorLed::LED2, LOW);
        // Если нажали на кнопку SW3
    } else if (!robit.digitalRead(ManipulatorButton::SW3)) {
        // Мигаем медленно три раза светодиодами LED1 и LED2
        bool stateLed = false;
        for (int i = 0; i < 7; i++) {
            robit.digitalWrite(ManipulatorLed::LED1, stateLed);
            robit.digitalWrite(ManipulatorLed::LED2, stateLed);
            stateLed = !stateLed;
            delay(500);
        }
        // Очищаем память
        robit.clearPositions();
    }
}