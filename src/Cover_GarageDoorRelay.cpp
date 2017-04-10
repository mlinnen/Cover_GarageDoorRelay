#include "Arduino.h"
#include "Cover_GarageDoorRelay.h"

namespace Cover
{
  GarageDoorRelay::GarageDoorRelay(int relayPin, int relayEngageTime)
  {
    _relayPin = relayPin;
    _relayEngagedTime = relayEngageTime;
  }

  void GarageDoorRelay::setup()
  {
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, HIGH);
    _relayTimer.setTimeout(_relayEngagedTime);
  }

  boolean GarageDoorRelay::loop()
  {
    if (_relayTimer.isExpired() && _relayOn)
    {
      _relayOn = false;
      digitalWrite(_relayPin, HIGH);
    }
    // This is the service loop that is called from the main program and will update the state of this component.
    if (_newCommandAvailable)
    {
      Serial.println("Executing Command");
      if (_currentCommand == CommandOpen)
        open();
      else if (_currentCommand == CommandClose)
        close();
      else if (_currentCommand == CommandStop)
        stop();
      else
        Serial.println("Unknown Command");
      _newCommandAvailable = false;
    }

    _lastState = _currentState;

    return true;
  }

  void GarageDoorRelay::setState(State state)
  {
    _currentState = state;
  }

  void GarageDoorRelay::setCommand(Command command)
  {
    _currentCommand = command;
    _newCommandAvailable = true;
  }

  void GarageDoorRelay::stop()
  {
    // If the cover is currently opening or closing then stop it
    if (_lastState == StateClosing || _lastState == StateOpening)
    {
      Serial.println("Cmd Stop Cover");
      fireRelay();
    }
    else
    {
      Serial.println("Unable to Stop");
    }
  }

  void GarageDoorRelay::open()
  {
    // If the cover is not already open then open it
    if (_lastState == StateClosed || _lastState == StateClosing || _lastState == StateUnknown)
    {
      Serial.println("Cmd Open Cover");
      fireRelay();
    }
    else
    {
      Serial.println("Unable to Open");
    }
  }

  void GarageDoorRelay::close()
  {
    // If the cover is not already closed then close it
    if (_lastState == StateOpen || _lastState == StateOpening || _lastState == StateUnknown)
    {
      Serial.println("Cmd Close Cover");
      fireRelay();
    }
    else
    {
      Serial.println("Unable to Close");
    }
  }

  void GarageDoorRelay::fireRelay()
  {
    digitalWrite(_relayPin, LOW);
    _relayOn = true;
    _relayTimer.restart();
  }
}
