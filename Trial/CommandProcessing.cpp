#include "CommandProcessing.h"

CommandProcessor::CommandProcessor() = default;

CommandProcessor::CommandProcessor(const CommandProcessor& other) {
    // Implement copy constructor logic if needed
}

CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other) {
    if (this != &other) {
        // Implement assignment operator logic if needed
    }
    return *this;
}

CommandProcessor::~CommandProcessor() {
    // Implement destructor logic if needed
}

void CommandProcessor::readCommand() {
    std::string inputCmd;
    std::cout << "Enter command: ";
    getline(std::cin, inputCmd);
    if (!inputCmd.empty()) {
        saveCommand(inputCmd);
    }
}

void CommandProcessor::saveCommand(std::string cmd)
{
    Command* newCommand = new Command(cmd);
    commands.push_back(newCommand); 
    Notify(this);
}

Command* CommandProcessor::getCommand() {
    if (!commands.empty()) {
        Command* cmd = commands.front();
        commands.erase(commands.begin());
        return cmd;
    }
    return nullptr;
}

bool CommandProcessor::validate(std::string cmd) {
    return true;
}

std::string CommandProcessor::stringToLog() const {
    return "CommandProcessor: Command Save"; // If any Item Print + "Item"
}
