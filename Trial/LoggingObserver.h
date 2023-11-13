// LoggingObserver.h

#ifndef LOGGING_OBSERVER_H
#define LOGGING_OBSERVER_H

#include <iostream>
#include <fstream>
#include <vector>

// Forward declarations
class Subject;


// ILoggable interface
class ILoggable {
public:
    virtual ~ILoggable() {}
    virtual std::string stringToLog() const = 0;
};


// Observer interface
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(ILoggable* subject) = 0;
};

// LogObserver class
class LogObserver : public Observer {
public:
    LogObserver(const std::string& logFileName);
    void update(ILoggable* subject) override;
    void writeToLogFile(const std::string& logEntry);

private:
    std::string logFileName;
};


// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void Notify(ILoggable * subject);
private:
    std::vector<Observer*> observers;

};





#endif // LOGGING_OBSERVER_H
