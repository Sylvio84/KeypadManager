#include <Configuration.h>
#include <EventManager.h>
#include <ezAnalogKeypad.h>

class KeyPadManager
{
private:
    ezAnalogKeypad keypad;
    static EventManager *eventManager; // Pointeur vers EventManager

public:
    KeyPadManager(Configuration config, EventManager &eventMgr);
    void init();
    void loop();
    void readKeypad();
};