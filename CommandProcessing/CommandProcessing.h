#pragma once

#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class Command{

    private:
        string command;
        string effect;
    
    public:
        Command(string cmd);
        void saveEffect(const string& eff);
        string getCommand() const;
        string getEffect() const;
};

class CommandProcessor{

    private:
        std::vector<Command*> commands;

    public:
        Command* getCommand();
        void validate(Command* cmd);
        void readCommand();
        void saveCommand(const string& input);

};

class FileCommandProcessorAdapter : public CommandProcessor{

    private:
        ifstream file;

    public:
        FileCommandProcessorAdapter(const string& filename);

        void readCommand();
    

};
