/*
 * Этот пример демонстрирует проверку тактовых кнопок и светодиодов.
 * При клике на каждую кнопку, будет происходить соответствующее действие.
 */

// Библиотека для управления манипулятором
#include "BitkitRobit.h"

// Создаём объект для работы с манипулятором
BitkitRobit robit;

void setup() {
    // Инициализация манипулятора
    robit.begin();
}

void loop() {
    // Если нажали на кнопку SW1
    if (!robit.digitalRead(ManipulatorButton::SW1)) {
        // Включаем светодиод LED1
        robit.digitalWrite(ManipulatorLed::LED1, HIGH);
        // Если нажали на кнопку SW2
    } else if (!robit.digitalRead(ManipulatorButton::SW2)) {
        // Выключаем светодиод LED1
        robit.digitalWrite(ManipulatorLed::LED1, LOW);
        // Если нажали на кнопку SW3
    } else if (!robit.digitalRead(ManipulatorButton::SW3)) {
        // Включаем светодиод LED2
        robit.digitalWrite(ManipulatorLed::LED2, HIGH);
        // Если нажали на кнопку SW4
    } else if (!robit.digitalRead(ManipulatorButton::SW4)) {
        // Выключаем светодиод LED2
        robit.digitalWrite(ManipulatorLed::LED2, LOW);
    }
}
