#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include <Arduino.h>
#include <MainController.h>
#include <Configuration.h>
#include <vector>
#include "config.h"
#include <KeyPadManager.h>

#include <DHT.h>
#include <ezAnalogKeypad.h>

class MyController : public MainController
{
private:
    MyConfig *myConfig;
    DHT dht;
    KeyPadManager keypadManager;

public:
    MyController(MyConfig &config);

    void init() override;
    void loop() override;

    void processEvent(String type, String action, std::vector<String> params) override;
    void processMQTT(String topic, String value) override;
    void processKey(String key);

    void readTemperature();
    void displayTime();
};

#endif
