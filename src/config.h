#include <Arduino.h>
#include <Configuration.h>

#ifndef MYCONFIG_H
#define MYCONFIG_H

class MyConfig : public Configuration
{
private:
public:
    int DHT_PIN = GPIO_NUM_23;
    
    static const int KEYS5_PIN = GPIO_NUM_39;

    MyConfig() : Configuration()
    {
        HOSTNAME = "Test Keypad v1";
        LCD_ADDRESS = 0x3F;
        LCD_COLS = 16;
        LCD_ROWS = 2;

        LCD_SDA = GPIO_NUM_21;
        LCD_SCL = GPIO_NUM_22;
    }

    static int getValue(const char *key, int defaultValue = 0)
    {
        if (key == "KEYS5_PIN")
        {
            return MyConfig::KEYS5_PIN;
        }
        return Configuration::getValue(key, defaultValue);
    }
};

#endif
