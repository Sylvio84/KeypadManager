#include <Arduino.h>
#include "config.h"
#include "../include/KeyPadManager.h"

EventManager *KeyPadManager::eventManager = nullptr;

KeyPadManager::KeyPadManager(Configuration config, EventManager &eventMgr) : keypad(MyConfig::getValue("KEYS5_PIN"))
{
    if (!eventManager)
    {
        eventManager = &eventMgr;
    }
}

void KeyPadManager::init()
{
    keypad.setNoPressValue(4095);
    keypad.setDebounceTime(100);
    keypad.registerKey(1, 0);    // Left
    keypad.registerKey(2, 1889); // Right
    keypad.registerKey(3, 446);  // Up
    keypad.registerKey(4, 1112); // Down
    keypad.registerKey(5, 3115); // Select
}

void KeyPadManager::loop()
{
    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastMillis >= 100)
    {
        lastMillis = currentMillis;
        readKeypad();
    }
}

void KeyPadManager::readKeypad()
{
    static const char *eventNames[] = {"X", "L", "R", "U", "D", "S"};

    unsigned char key = keypad.getKey();
    if (key > 0 && key < sizeof(eventNames) / sizeof(eventNames[0]))
    {
        //Serial.println("Debug KeyPad: " + key);
        eventManager->triggerEvent("KeyPad", eventNames[key], {});
    }
}