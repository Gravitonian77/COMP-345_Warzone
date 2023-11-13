#include "FileCommandProcessorAdapter.h"
#include <iostream>
#include <cstdlib>

FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string fileName) {
    inputFile.open(fileName);
    if (!inputFile.is_open()) {
        std::cout << "Error: Unable to open file " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other) {
    // Implement copy constructor logic if needed
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other) {
    if (this != &other) {
        // Implement assignment operator logic if needed
    }
    return *this;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    inputFile.close();
    // Implement destructor logic if needed
}

void FileCommandProcessorAdapter::readCommand() {
    std::string cmd;
    while (inputFile >> cmd) {
        saveCommand(cmd);
    }
}
