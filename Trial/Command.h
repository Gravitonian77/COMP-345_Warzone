#pragma once

#include <string>
#include "LoggingObserver.h"  // Include the Observer-related headers


class Command : public Subject, public ILoggable {
public:
    std::string command;
    std::string effect;

    Command(std::string cmd);
    Command(const Command& other);  // Copy constructor
    Command& operator=(const Command& other);  // Assignment operator
    friend std::ostream& operator<<(std::ostream& os, const Command& command);  // Stream insertion operator

    void saveEffect(std::string eff);

    std::string stringToLog() const override; 

    std::string getCommand() const 
    {
        return command;
    }
    
    ~Command();  // Destructor
};
