#include <Arduino.h>
#include <BleKeyboard.h>

#define BUTTON_Z_PIN 0
#define BUTTON_X_PIN 1
#define BUTTON_C_PIN 2
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

    pinMode(BUTTON_Z_PIN, INPUT_PULLUP);
    pinMode(BUTTON_X_PIN, INPUT_PULLUP);
    pinMode(BUTTON_C_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    bleKeyboard.setName("OSU-Keyboard");
    bleKeyboard.setDelay(0);
    bleKeyboard.begin();

    blinkLedQuick(3);
}

bool pressZ = false;
bool pressX = false;
bool pressC = false;

void loop()
{
    if (!bleKeyboard.isConnected())
    {
        // Se desconectar enquanto uma tecla está marcada como pressionada,
        // garantir que as teclas sejam liberadas para evitar stuck keys.
        if (pressZ || pressX || pressC)
        {
            bleKeyboard.releaseAll();
            pressZ = pressX = pressC = false;
        }
        return;
    }

    bool currZ = digitalRead(BUTTON_Z_PIN) == LOW;
    bool currX = digitalRead(BUTTON_X_PIN) == LOW;
    bool currC = digitalRead(BUTTON_C_PIN) == LOW;

    // Botão Z
    if (currZ && !pressZ)
    {
        bleKeyboard.press('z');
        pressZ = true;
    }
    else if (!currZ && pressZ)
    {
        bleKeyboard.release('z');
        pressZ = false;
    }

    // Botão X
    if (currX && !pressX)
    {
        bleKeyboard.press('x');
        pressX = true;
    }
    else if (!currX && pressX)
    {
        bleKeyboard.release('x');
        pressX = false;
    }

    // Botão C
    if (currC && !pressC)
    {
        bleKeyboard.press('c');
        pressC = true;
    }
    else if (!currC && pressC)
    {
        bleKeyboard.release('c');
        pressC = false;
    }

    delay(5);
}