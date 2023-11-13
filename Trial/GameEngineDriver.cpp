#include "GameEngine.h"

/**
 * G++ COMPILING
 * g++ GameEngineDriver.cpp Player.cpp CommandProcessing.cpp LoggingObserver.cpp Command.cpp -o t
 * 
*/


void testStartUpPhase()
{
    
    GameEngine* game = new GameEngine();

    game->startupPhase();

}

int main()
{
    
    testStartUpPhase();
    
    return 0;
}