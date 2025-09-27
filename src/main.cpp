#include <Arduino.h>
#include <BleKeyboard.h>

#define BUTTON_A_PIN 2
#define BUTTON_B_PIN 3
#define LED_PIN 8

BleKeyboard bleKeyboard;

void blinkLedQuick(int times, int duration = 100)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(LED_PIN, LOW);
        delay(duration);
        digitalWrite(LED_PIN, HIGH);
        delay(duration);
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // Invertido: LED apagado por padrão

    bleKeyboard.setName("OSU-Keyboard");
    bleKeyboard.setDelay(100);
    bleKeyboard.begin();

    delay(2000);
    blinkLedQuick(3);
    Serial.println("ESP32C3 iniciado!");
}

void loop()
{
    bool currA = digitalRead(BUTTON_A_PIN);
    bool currB = digitalRead(BUTTON_B_PIN);

    if (currB == LOW)
    {
        blinkLedQuick(2, 50);
        Serial.println("Botão B");
    }

    static bool lastA = HIGH, lastB = HIGH;

    if (bleKeyboard.isConnected())
    {
        // Botão A envia 'a'
        if (lastA == HIGH && currA == LOW)
        {
            bleKeyboard.press('a');
            digitalWrite(LED_PIN, HIGH);
            Serial.println("Botão A");
        }
        else if (lastA == LOW && currA == HIGH)
        {
            bleKeyboard.release('a');
            digitalWrite(LED_PIN, LOW);
            Serial.println("Botão A solto");
        }
        lastA = currA;

        // Botão B envia 'b'
        if (lastB == HIGH && currB == LOW)
        {
            bleKeyboard.press('b');
            Serial.println("Botão B");
        }
        else if (lastB == LOW && currB == HIGH)
        {
            bleKeyboard.release('b');
            Serial.println("Botão B solto");
        }
        lastB = currB;
    }
    delay(10);
}