#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <memory>
#include <vector>

class Observer;

class Subject {
   protected:
    // vector list of shared pointer of observers
    std::vector<std::shared_ptr<Observer>> observers;

   public:
    // attach the shared pointer observer with with neighbor o
    void attach(const std::shared_ptr<Observer> &o);
    // notify all neighbour to update the availability of building residences
    virtual void notifyObservers() = 0;
};

#endif