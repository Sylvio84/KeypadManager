#include <Arduino.h>
#include "config.h"
#include "MyController.h"
#include <ezAnalogKeypad.h>

MyConfig config;
MyController myController(config);

ezAnalogKeypad keypad(config.KEYS5_PIN);

void setup()
{
    myController.init();
}

void loop()
{
    myController.loop();
}
