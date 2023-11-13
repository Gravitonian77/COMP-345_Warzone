#pragma once

#include <fstream>
#include "CommandProcessing.h"

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    std::ifstream inputFile;

public:
    FileCommandProcessorAdapter(std::string fileName);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);  // Copy constructor
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);  // Assignment operator
    ~FileCommandProcessorAdapter();  // Destructor

    void readCommand();
};
