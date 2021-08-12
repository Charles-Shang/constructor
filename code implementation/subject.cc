#include "subject.h"

// below for testing
#include <iostream>

void Subject::attach(const std::shared_ptr<Observer> &o) {
    observers.emplace_back(o);
}