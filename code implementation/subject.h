#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "residencetype.h"

class Observer;

class Subject {
   protected:
    std::vector<Observer *> observers;

   public:
    void attach(Observer *o);
    virtual void notifyObservers() = 0;
};

#endif