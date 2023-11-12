// LoggingObserver.cpp
#include "LoggingObserver.h"
#include <iostream>

Subject::~Subject() {
    // Destructor content if needed, like cleaning up observers if they are dynamically allocated
}

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Subject::notify() {
    for (Observer* observer : observers) {
        observer->update(this);
    }
}

void LogObserver::update(const ILoggable* subject) {
    std::ofstream logFile("gamelog.txt", std::ios::app);
    if (!logFile) {
        std::cerr << "Error: Unable to open gamelog.txt for writing." << std::endl;
        return;
    }
    logFile << subject->stringToLog() << std::endl;
}
