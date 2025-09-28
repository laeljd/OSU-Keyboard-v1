#include <Arduino.h>
#include <BleKeyboard.h>

#define BUTTON_A_PIN 0
#define BUTTON_B_PIN 1
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

    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(BUTTON_C_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    bleKeyboard.setName("OSU-Keyboard");
    bleKeyboard.setDelay(0);
    bleKeyboard.begin();

    blinkLedQuick(3);
}

bool pressA = false;
bool pressB = false;
bool pressC = false;

void loop()
{
    if (!bleKeyboard.isConnected())
        return;

    bool currA = digitalRead(BUTTON_A_PIN) == LOW;
    bool currB = digitalRead(BUTTON_B_PIN) == LOW;
    bool currC = digitalRead(BUTTON_C_PIN) == LOW;

    // Botão A
    if (currA && !pressA)
    {
        bleKeyboard.write('a');
        pressA = true;
    }
    else if (!currA && pressA)
    {
        pressA = false;
    }

    // Botão B
    if (currB && !pressB)
    {
        bleKeyboard.write('b');
        pressB = true;
    }
    else if (!currB && pressB)
    {
        pressB = false;
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