#include <Configuration.h>

#ifndef MYCONFIG_H
#define MYCONFIG_H

class MyConfig : public Configuration
{
private:
public:
    int DHT_PIN = GPIO_NUM_23;
    int KEYS5_PIN = GPIO_NUM_39;

    MyConfig() : Configuration()
    {
        HOSTNAME = "TestFrameworkESP32";
        LCD_ADDRESS = 0x3F;
        LCD_COLS = 16;
        LCD_ROWS = 2;

        int LCD_SDA = GPIO_NUM_21;
        int LCD_SCL = GPIO_NUM_22;
    }
};

#endif
