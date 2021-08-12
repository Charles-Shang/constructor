#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "subject.h"

class Vertices;

class Observer {
   public:
    // update the availability of building residence for neighbour vertices
    virtual void notify() = 0;
    virtual ~Observer() = default;  // destructor
};

#endif
