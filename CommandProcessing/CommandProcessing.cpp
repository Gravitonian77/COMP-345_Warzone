#include "CommandProcessing.h"
#include <fstream>

Command::Command(string cmd){
    command = cmd;
    effect = "";
}

void Command::saveEffect(const std::string& eff) {
        effect = eff;
}

string Command::getCommand() const {
        return command;
    }

string Command::getEffect() const{
    return effect;
}

Command* CommandProcessor::getCommand(){

    if (!commands.empty()) {
            Command* cmd = commands.back();
            commands.pop_back();
            return cmd;
        }
    return nullptr;

}

void CommandProcessor::readCommand(){
    string input;
    getline(cin, input);
    saveCommand(input);
}

void CommandProcessor::saveCommand(const string& input){
     commands.push_back(new Command(input));
}

void CommandProcessor::validate(Command* cmd){

}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string& filename) 
    : file(filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}

void FileCommandProcessorAdapter::readCommand(){
    if (file.is_open() && !file.eof()) {
        string line;
        getline(file, line);
        saveCommand(line);
    }
}
