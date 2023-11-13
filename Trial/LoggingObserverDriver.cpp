// LoggingObserverDriver.cpp

#include "Command.cpp"
#include "CommandProcessing.cpp"
#include "Orders.cpp"
#include "Orders.h"
#include "GameEngine.cpp"

#include "LoggingObserver.cpp"
#include "GameEngine.h"


void testLoggingObserver() {
    // Create instances of your classes
	

    // Create a LogObserver and attach it to all subjects
    LogObserver logObserver("gamelog.txt");

    CommandProcessor commandProcessor;
    commandProcessor.attach(&logObserver);
    commandProcessor.saveCommand("loadmap Canada.map");

    OrdersList orderList;
    Order order;

    orderList.attach(&logObserver);
    orderList.insertOrder(&order);

    // Test Order::execute()
    order.attach(&logObserver);
    order.execute();

    GameEngine* game;
    game->attach(&logObserver);
	//Instantiating all states that our game object will transition to and from.
	State* start = game->newState("start");
	State* map_loaded = game->newState("load_map"); //maploaded
    game->addTransition(start, map_loaded, "loadmap");

}

int main() {
    // Call the testLoggingObserver function
    testLoggingObserver();

    return 0;
}
