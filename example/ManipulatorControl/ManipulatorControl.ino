/*
 * Этот пример демонстрирует ручной режим управления робо-рукой.
 * Энкодеры ENC1-ENC4 рулят суставами манипулятора S1-S4.
 * В консоль выводятся текущие углы сервоприводов.
 */

// Библиотека для работы манипулятора
#include "BitkitRobit.h"

// Создаём объект для работы с манипулятором
BitkitRobit robit;

void setup() {
    // Открываем Serial-порт
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
    // Получаем значения с каждого сустава и выводим в консоль
    uint8_t val1, val2, val3, val4;
    robit.getPosition(val1, val2, val3, val4);
    Serial.print(val1);
    Serial.print("\t");
    Serial.print(val2);
    Serial.print("\t");
    Serial.print(val3);
    Serial.print("\t");
    Serial.println(val4);
}