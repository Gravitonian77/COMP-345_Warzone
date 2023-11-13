// LoggingObserver.cpp

#include "LoggingObserver.h"
#include <iostream>
#include <fstream>
#include <algorithm> // Include the algorithm header

// Subject Implementation
void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Subject::Notify(ILoggable* subject) {
    for (Observer* observer : observers) {
        observer->update(subject);
    }
}



// Log Observer Implementation
LogObserver::LogObserver(const std::string& logFileName) {
    // This is the body of the constructor (not explicitly provided in the original one)
    this->logFileName = logFileName; // Initialize the member variable with the value of the parameter
}

void LogObserver::update(ILoggable* subject) {
    writeToLogFile("Subject updated: " + subject->stringToLog());
}

void LogObserver::writeToLogFile(const std::string& logEntry) {
    std::ofstream logFile(logFileName, std::ios_base::app);
    if (logFile.is_open()) {
        logFile << logEntry << "\n";
        logFile.close();
    } else {
        std::cerr << "Unable to open log file: " << logFileName << "\n";
    }
}
