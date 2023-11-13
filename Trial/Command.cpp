#include "Command.h"
#include <iostream>
#include <cstdlib>

Command::Command(std::string cmd) : command(cmd) {}

Command::Command(const Command& other) : command(other.command), effect(other.effect) {}

Command& Command::operator=(const Command& other) {
    if (this != &other) {
        command = other.command;
        effect = other.effect;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Command& command) {
    os << "Command: " << command.command << ", Effect: " << command.effect;
    return os;
}

void Command::saveEffect(std::string eff) {
    effect = eff;
    Notify(this);  // Notify observers when the effect is saved
}

std::string Command::stringToLog() const {
    return "Command: " + command + ", Effect: " + effect;
}

Command::~Command() {
    // Implement destructor logic if needed
}


