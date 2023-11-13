#pragma once

#include <vector>
#include "Command.h"

class CommandProcessor : public Subject, public ILoggable {
private:
    std::vector<Command*> commands; // Stores the commands

public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor& other);  // Copy constructor
    CommandProcessor& operator=(const CommandProcessor& other);  // Assignment operator
    ~CommandProcessor();  // Destructor

    void readCommand(); // Reads a command from the console
    void saveCommand(std::string cmd); // Saves a command to the list
    Command* getCommand(); // Retrieves and removes the next command from the list
    std::string stringToLog() const override; // Creates a string for logging

    bool validate(std::string cmd); // Validates a command
};
