#ifndef GarageDoorRelay_h
#define GarageDoorRelay_h

#include "Arduino.h"
#include <RBD_Timer.h>
#include "Cover_Core.h"

namespace Cover {
  class GarageDoorRelay
  {
    public:
      GarageDoorRelay(int relayPin, int relayEngageTime);
      void setup();
      boolean loop();
      void setState(State state);
      void setCommand(Command command);
    private:
      int _relayPin;
      int _relayEngagedTime;
      void open();
      void close();
      void stop();
      void fireRelay();
      boolean _newCommandAvailable=false;
      Command _currentCommand=CommandUnknown;
      State _lastState=StateUnknown;
      State _currentState=StateUnknown;
      RBD::Timer _relayTimer;
      boolean _relayOn=false;
  };
}
#endif