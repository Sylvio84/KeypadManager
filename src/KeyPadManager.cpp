#include <Arduino.h>
#include "config.h"
#include "../include/KeyPadManager.h"

EventManager *KeyPadManager::eventManager = nullptr;

KeyPadManager::KeyPadManager(Configuration config, EventManager &eventMgr) : keypad(MyConfig::getValue("KEYS5_PIN"))
{
    if (eventManager == nullptr)
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
    if (millis() % 100 == 0)
    {
        readKeypad();
    }
}

void KeyPadManager::readKeypad()
{
    unsigned char key = keypad.getKey();
    if (key)
    {
        String event = "X";
        if (key == 1)
        {
            event = "L";
        }
        else if (key == 2)
        {
            event = "R";
        }
        else if (key == 3)
        {
            event = "U";
        }
        else if (key == 4)
        {
            event = "D";
        }
        else if (key == 5)
        {
            event = "S";
        }
        // Serial.println("Debug KeyPad: " + event);
        eventManager->triggerEvent("KeyPad", event, {});
    }
}