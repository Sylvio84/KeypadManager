#include "MyController.h"

MyController::MyController(MyConfig &config) : MainController(config),
                                               myConfig(&config),
                                               keypadManager(config, eventManager)
{
}

void MyController::init()
{
    MainController::init();
    displayManager.printLine(0, "Init done!");
    Serial.println("Init done!");

    dht.setup(myConfig->DHT_PIN);

    keypadManager.init();
    eventManager.registerCallback("KeyPad", [this](String action, std::vector<String> params)
                                  { this->processKey(action); });

    // int temperatureInterval = timeManager.setIntervalObj(this, std::bind(&MyController::readTemperature, this), dht.getMinimumSamplingPeriod());
    // int timeInterval = timeManager.setIntervalObj(this, std::bind(&MyController::displayTime, this), 1000);
}

void MyController::loop()
{
    MainController::loop();
    keypadManager.loop();
}

void MyController::processKey(String key)
{
    Serial.println("Keypad => " + key);
    // displayManager.printLine(1, key);
    if (key == "U")
    {
        displayManager.clear();
        readTemperature();
    }
    if (key == "D")
    {
        displayManager.clear();
        displayTime();
    }
    if (key == "L")
    {
        displayManager.clear();
        String ip = wiFiManager.retrieveIP();
        displayManager.printLine(0, "IP Address:");
        displayManager.printLine(1, ip);
    }
    if (key == "R")
    {
        displayManager.clear();
        String ssid = wiFiManager.retrieveSSID();
        displayManager.printLine(0, "WiFI SSID:");
        displayManager.printLine(1, ssid);
    }
    if (key == "S")
    {
        displayManager.clear();
        displayManager.printLine(0, "Welcome on ");
        displayManager.printLine(1, hostname);
    }
}

void MyController::processEvent(String type, String action, std::vector<String> params)
{
    // Serial.println("Event received: " + type + " " + action);
    MainController::processEvent(type, action, params);

    if (type == "MQTT")
    {
        if (action == "Connected")
        {
            mqttManager.publish("abris_velo/" + String(hostname), "Connected");
            mqttManager.subscribe("abris_velo/lampe");
        }
        else if (action == "Message")
        {
            displayManager.printLine(0, "Message MQTT" + params[0] + " = " + params[1]);
        }
    }
}

void MyController::processMQTT(String topic, String value)
{
    // Serial.println("*** Received MQTT message *** " + topic + " = " + value);
    if (topic == "abris_velo/lampe")
    {
        Serial.println("Lampe = " + value);
        if (value == "1")
        {
            displayManager.printLine(1, "Lampe allumee");
        }
        else
        {
            displayManager.printLine(1, "Lampe eteinte");
        }
    }
}

void MyController::readTemperature()
{
    float temp = dht.getTemperature();
    float hum = dht.getHumidity();

    if (isnan(temp))
    {
        Serial.println("Erreur de lecture du capteur DHT !");
        return;
    }

    Serial.println("Température: " + String(temp) + " °C");
    Serial.println("Humidité: " + String(hum) + " %");
    displayManager.printLine(0, "Temp.: " + String(temp) + " " + "\xDF" + "C");
    displayManager.printLine(1, "Humidity: " + String(hum) + " %");
}

void MyController::displayTime()
{
    String datetime = timeManager.getFormattedDateTime("%d/%m/%Y %H:%M:%S");
    Serial.println("Time: " + datetime);
    String date = timeManager.getFormattedDateTime("%d/%m/%Y");
    String time = timeManager.getFormattedDateTime("%H:%M:%S");
    displayManager.printLine(0, date);
    displayManager.printLine(1, time);
}