// LoggingObserver.h
#pragma once

#include <vector>
#include <string>
#include <fstream>

// ILoggable interface
class ILoggable {
public:
    virtual ~ILoggable() = default;
    virtual std::string stringToLog() const = 0;
};

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const ILoggable* subject) = 0;
};

// Subject interface
class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject();
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
};

// LogObserver concrete class
class LogObserver : public Observer {
public:
    void update(const ILoggable* subject) override;
};
