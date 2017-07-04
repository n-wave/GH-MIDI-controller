#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller
{
  public:
    Controller();
    virtual ~Controller();
    virtual void execute() = 0;
    virtual void updateAction(uint32_t) = 0;
    virtual void setParameter(uint16_t) = 0;
    virtual uint16_t getParameter() = 0;
    virtual void setConfiguration(uint8_t[]) = 0;
};

#endif
