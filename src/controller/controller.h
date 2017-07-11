#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <Arduino.h>
#include "../testing/configuration.h"

class Controller
{
  public:
    Controller();
    Controller(const int* data);

    virtual ~Controller();
    virtual void execute() = 0;
    virtual void update(const uint32_t* time) = 0;

    virtual void setParameter(const uint16_t *value) = 0;
    virtual uint16_t getParameter() = 0;
    virtual boolean setConfiguration(const int* data) = 0;

#ifdef DEBUG
    virtual void printContents() = 0;
#endif /* DEBUG */

};

#endif /* SRC_CONTROLLER_CONTROLLER_H */
