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

bool pressZ = false;
bool pressX = false;
bool pressC = false;

// Debounce (non-blocking)
const unsigned long DEBOUNCE_MS = 3; // adjust if you want more/less sensitive

// per-button state
bool lastReadZ = HIGH;
bool lastReadX = HIGH;
bool lastReadC = HIGH;
bool stableZ = false;
bool stableX = false;
bool stableC = false;
unsigned long lastDebounceZ = 0;
unsigned long lastDebounceX = 0;
unsigned long lastDebounceC = 0;

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

    // initialize stable states with current reading
    lastReadZ = digitalRead(BUTTON_Z_PIN);
    lastReadX = digitalRead(BUTTON_X_PIN);
    lastReadC = digitalRead(BUTTON_C_PIN);
    stableZ = (lastReadZ == LOW);
    stableX = (lastReadX == LOW);
    stableC = (lastReadC == LOW);
    pressZ = stableZ;
    pressX = stableX;
    pressC = stableC;
}

void loop()
{
    if (!bleKeyboard.isConnected())
    {
        // If disconnected while a key is marked as pressed,
        // ensure keys are released to avoid stuck keys.
        if (pressZ || pressX || pressC)
        {
            bleKeyboard.releaseAll();
            pressZ = pressX = pressC = false;
        }
        // still processes readings to keep states coherent, but returning early is acceptable
        return;
    }

    // current readings (LOW = pressed)
    int rZ = digitalRead(BUTTON_Z_PIN);
    int rX = digitalRead(BUTTON_X_PIN);
    int rC = digitalRead(BUTTON_C_PIN);
    unsigned long now = millis();

    // --- button Z debounce ---
    if (rZ != lastReadZ)
    {
        lastDebounceZ = now;
        lastReadZ = rZ;
    }
    else if ((now - lastDebounceZ) >= DEBOUNCE_MS)
    {
        bool pressed = (rZ == LOW);
        if (pressed != stableZ)
        {
            stableZ = pressed;
            if (stableZ && !pressZ) // transition to pressed
            {
                bleKeyboard.press('z');
                pressZ = true;
            }
            else if (!stableZ && pressZ) // transition to released
            {
                bleKeyboard.release('z');
                pressZ = false;
            }
        }
    }

    // --- button X debounce ---
    if (rX != lastReadX)
    {
        lastDebounceX = now;
        lastReadX = rX;
    }
    else if ((now - lastDebounceX) >= DEBOUNCE_MS)
    {
        bool pressed = (rX == LOW);
        if (pressed != stableX)
        {
            stableX = pressed;
            if (stableX && !pressX)
            {
                bleKeyboard.press('x');
                pressX = true;
            }
            else if (!stableX && pressX)
            {
                bleKeyboard.release('x');
                pressX = false;
            }
        }
    }

    // --- button C debounce ---
    if (rC != lastReadC)
    {
        lastDebounceC = now;
        lastReadC = rC;
    }
    else if ((now - lastDebounceC) >= DEBOUNCE_MS)
    {
        bool pressed = (rC == LOW);
        if (pressed != stableC)
        {
            stableC = pressed;
            if (stableC && !pressC)
            {
                bleKeyboard.press('c');
                pressC = true;
            }
            else if (!stableC && pressC)
            {
                bleKeyboard.release('c');
                pressC = false;
            }
        }
    }

    // no delay to avoid blocking — loop runs continuously
}