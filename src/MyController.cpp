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

    int temperatureInterval = timeManager.setIntervalObj(this, std::bind(&MyController::readTemperature, this), dht.getMinimumSamplingPeriod());
}

void MyController::loop()
{
    MainController::loop();
    keypadManager.loop();
}

void MyController::processKey(String key)
{
    Serial.println("Keypad => " + key);
    displayManager.printLine(1, key);
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
}