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
        return;

    bool currZ = digitalRead(BUTTON_Z_PIN) == LOW;
    bool currX = digitalRead(BUTTON_X_PIN) == LOW;
    bool currC = digitalRead(BUTTON_C_PIN) == LOW;

    // Botão Z
    if (currZ && !pressZ)
    {
        bleKeyboard.write('z');
        pressZ = true;
    }
    else if (!currZ && pressZ)
    {
        pressZ = false;
    }

    // Botão X
    if (currX && !pressX)
    {
        bleKeyboard.write('x');
        pressX = true;
    }
    else if (!currX && pressX)
    {
        pressX = false;
    }

    // Botão C
    if (currC && !pressC)
    {
        bleKeyboard.write('c');
        pressC = true;
    }
    else if (!currC && pressC)
    {
        pressC = false;
    }

    delay(5);
}