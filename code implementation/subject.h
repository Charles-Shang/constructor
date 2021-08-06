#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <memory>
#include <vector>
#include "residencetype.h"

class Observer;

class Subject {
   protected:
    std::vector<std::shared_ptr<Observer>> observers;

   public:
    void attach(const std::shared_ptr<Observer> &o);
    virtual void notifyObservers() = 0;
};

#endif