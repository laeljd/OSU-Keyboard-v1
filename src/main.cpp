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
    bleKeyboard.setDelay(0);
    bleKeyboard.begin();

    blinkLedQuick(3);
}

bool pressA = false;
bool pressB = false;

void loop()
{
    if (!bleKeyboard.isConnected())
        return;

    bool currA = digitalRead(BUTTON_A_PIN) == LOW;
    bool currB = digitalRead(BUTTON_B_PIN) == LOW;

    // Botão A
    if (currA && !pressA)
    {
        bleKeyboard.write('a');
        pressA = true;

        Serial.println("Botão A");
    }
    else if (!currA && pressA)
    {
        pressA = false;
        Serial.println("Botão A solto");
    }

    // Botão B
    if (currB && !pressB)
    {
        bleKeyboard.write('b');
        pressB = true;

        digitalWrite(LED_PIN, LOW);
    }
    else if (!currB && pressB)
    {
        pressB = false;
        digitalWrite(LED_PIN, HIGH);
    }

    delay(10);
}