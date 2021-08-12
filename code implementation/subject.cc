#include "subject.h"

void Subject::attach(const std::shared_ptr<Observer> &o) {
    observers.emplace_back(o);
}