// #include "CommandProcessing.h"
// #include "FileCommandProcessorAdapter.h"
// #include "GameEngine.h"
// #include <iostream>
// #include <cstdlib>
// #include <string>
#include "Command.cpp"
#include "CommandProcessing.cpp"
#include "FileCommandProcessorAdapter.cpp"
#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>
#include <cstdlib>

/**
 * G++ TO DO
 * g++ CommandProcessingDriver.cpp LoggingObserver.cpp Player.cpp -o t
 * 
*/


void testCommandProcessor() {
    // // Create a GameEngine object for command validation
    // GameEngine* game = new GameEngine(); 
    // // Instantiate all states that the game object will transition to and from.
    // // ... (State initialization as per your existing logic)

    // // Instantiate CommandProcessor for console input
    // CommandProcessor commandProcessor;
    // std::cout << "Enter commands, type 'end' to switch to file input:" << std::endl << std::flush;
    
    // // Read and process commands from the console
    // std::string consoleCommand;
    // do {
    //     commandProcessor.readCommand(); // Read command from the console
    //     Command* cmd = commandProcessor.getCommand(); // Get the next command
    //     //cout << cmd->command << endl;
        
    //     if (cmd == nullptr || cmd->command == "end") {
    //         delete cmd; // Free memory allocated for command
    //         break; // Break if 'end' command is entered to switch to file input
    //     }
        
    //     // Validate and execute command
    //     if (game->validCommand(cmd->command)) {
    //         std::cout << "Valid Command: " << cmd->command << std::endl;
    //         // Execute command here or handle further
    //     } else {
    //         std::cout << "Invalid Command: " << cmd->command << std::endl;
    //     }
        
    //     delete cmd; // Free memory allocated for the command
    // } while (true);
    
    // // Now switch to file input using FileCommandProcessorAdapter
    // FileCommandProcessorAdapter fileAdapter("commands.txt");
    // std::cout << "Reading commands from file: commands.txt" << std::endl;
    // fileAdapter.readCommand(); // Read all commands from the file
    
    // // Process commands read from the file
    // Command* fileCommand;
    // while ((fileCommand = fileAdapter.getCommand()) != nullptr) {
    //     // Validate and execute file command
    //     if (fileAdapter.validate(fileCommand->command)) {
    //         std::cout << "Valid Command from file: " << fileCommand->command << std::endl;
    //         // Execute command here or handle further
    //     } else {
    //         std::cout << "Invalid Command from file: " << fileCommand->command << std::endl;
    //     }
    //     delete fileCommand; // Free memory allocated for the command
    // }

    // delete game; // Clean up GameEngine object




    // Part 1: Test CommandProcessor with console input
    CommandProcessor consoleProcessor;
    std::cout << "Testing CommandProcessor with console input:" << std::endl;
    consoleProcessor.readCommand();
    Command* consoleCmd = consoleProcessor.getCommand();
    if (consoleCmd) {
        // Validate and execute the command
        // For demonstration, assume all console commands are valid
        std::cout << "Executing command: " << consoleCmd->getCommand() << std::endl;
        delete consoleCmd;
    }

    // Part 2: Test FileCommandProcessorAdapter with file input
    std::string fileName = "commands.txt"; // Replace with your actual file name
    FileCommandProcessorAdapter fileProcessor(fileName);
    std::cout << "Testing FileCommandProcessorAdapter with file input:" << std::endl;
    fileProcessor.readCommand();
    Command* fileCmd = fileProcessor.getCommand();
    while (fileCmd) {
        // Validate and execute the command
        // For demonstration, assume all file commands are valid
        std::cout << "Executing command: " << fileCmd->getCommand() << std::endl;
        delete fileCmd;
        fileCmd = fileProcessor.getCommand();
    }

    // Part 3: Demonstrate command validation
    // This part depends on your game's state and command validation logic
    // For demonstration, assume a simple validation
    std::cout << "Demonstrating command validation:" << std::endl;
    std::string testCommand = "invalidCommand";
    if (consoleProcessor.validate(testCommand)) {
        std::cout << "Command is valid." << std::endl;
    } else {
        std::cout << "Command is invalid." << std::endl;
    }
}


int main() {
    testCommandProcessor(); // Test command processing
    return 0;
}
