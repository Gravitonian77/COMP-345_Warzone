#include "Player.cpp"


void testMainGameLoop(){


    cout << "\n---------------------- Start of testMainGameLoop -------------- " << endl;
    
    GameEngine * gameEng = new GameEngine();

    //Instantiating all states that our game object will transition to and from.
	State* start = gameEng->newState("start");
	State* map_loaded = gameEng->newState("load_map");
	State* map_validated = gameEng->newState("map_validated");
	State* players_added = gameEng->newState("players_added");
	State* assign_reinforcements = gameEng->newState("assign_ref");
	State* issue_orders = gameEng->newState("issue_orders");
	State* execute_orders = gameEng->newState("execute_orders");
	State* win = gameEng->newState("win");
    State* end = gameEng->newState("end");

    //Mapping all the transitions with their respective commands.
	gameEng->addTransition(start, map_loaded, "loadmap");
	gameEng->addTransition(map_loaded, map_loaded, "loadmap");
	gameEng->addTransition(map_loaded, map_validated, "validatemap");
	gameEng->addTransition(map_validated, players_added, "addplayer");
	gameEng->addTransition(players_added, players_added, "addplayer");
	gameEng->addTransition(players_added, assign_reinforcements, "assigncountries");
	gameEng->addTransition(assign_reinforcements, issue_orders, "issueorder");
	gameEng->addTransition(issue_orders, issue_orders, "issueorder");
	gameEng->addTransition(issue_orders, execute_orders, "endissueorders");
	gameEng->addTransition(execute_orders, execute_orders, "execorder");
	gameEng->addTransition(execute_orders, assign_reinforcements, "endexecorders");
	gameEng->addTransition(execute_orders, win, "win");
	gameEng->addTransition(win, start, "play");
	gameEng->addTransition(win, end, "end");
	gameEng->setCurrentState(start);

    // Create the map 
    Map* gameMap = mapLoader::createMapFromConquestFile("Canada.map");
    gameEng->setMap(gameMap);

    // Create players
    Player* p0 = new Player();
    Player* p1 = new Player();
    Player* p2 = new Player();

    // OrdersList for players
    p0->setMyOrdersList(new OrdersList); p1->setMyOrdersList(new OrdersList); p2->setMyOrdersList(new OrdersList);

    // Hand for players
    p0->setMyHand(new Hand()); p1->setMyHand(new Hand()); p2->setMyHand(new Hand());
    
    // Game for players
    p0->setGameEngine(gameEng); p1->setGameEngine(gameEng); p2->setGameEngine(gameEng);

    gameEng->addPlayer(p0); gameEng->addPlayer(p1);
    

    // Showing different cases
    // case 1: Player 1 has 3 territories and 2  has 12 territories ---> p1 should get 1 additional unit and p2 2 additional units
    // case 2: Player 1 has 1 continent and player 2 has 6 territories --> Continent 1 will have bonus of 3 units

    cout << "\nPlease enter the case number for the demonstrations of testGameLoop" << endl;
    cout << "\ncase 1: 2 players with no cards. Player 0 has all territories in the map, player 2 has 0" << endl;
    cout << "case 2: 2 players with no cards. Player 0 has 1 territory player 2 has 0." << endl;
    cout << "case 3: 2 players with no cards. Player 0 has 1 continent of 12 territories player 2 has 1 territory." << endl;  
    // cout << "case 3: 2 players. Player 0 has 1 territory and player 2 has 0" << endl; 
    // cout << "case 4: 2 players. Player 0 has all territories in map except 1. Player 1 has last territory "<< endl; // show(6)

    string command = "assigncountries";
    int input = 0;
    cin >> input;
    cout << endl;

    if(input == 1){

        cout <<"Case 1 has been selected."<<endl << endl;
        // Assigning territories to both players
        vector<Territory*> p0Territories = gameEng->getMap()->getTerritory();
        p0->setMyTerritories(p0Territories);
        cout << endl;

        gameEng->changeState(command);
        gameEng->mainGameLoop();
    }
    else if(input == 2){

        cout <<"Case 2 has been selected."<<endl << endl;
        p0->addTerritory(gameMap->getTerritoryByName("1"));

        gameEng->changeState(command);
        gameEng->mainGameLoop();

    }
    else if(input == 3){

    }

    

    // switch (input){
    //     case 1:
    //         cout <<"Case 1 has been selected."<<endl << endl;
    //             gameEng->addPlayer(p2);
    //             // Assigning territories to both players
    //             p0->addTerritory(gameMap->getTerritoryByName("1"));
    //             p0->addTerritory(gameMap->getTerritoryByName("2"));
    //             p0->addTerritory(gameMap->getTerritoryByName("3"));
    //             cout << endl;

    //             p1->addTerritory(gameMap->getTerritoryByName("4"));
    //             p1->addTerritory(gameMap->getTerritoryByName("5"));
    //             p1->addTerritory(gameMap->getTerritoryByName("6"));
    //             p1->addTerritory(gameMap->getTerritoryByName("7"));
    //             p1->addTerritory(gameMap->getTerritoryByName("8"));
    //             p1->addTerritory(gameMap->getTerritoryByName("9"));
    //             cout << endl;

    //             // p2->addTerritory(gameMap->getTerritoryByName("10"));
    //             // cout << endl;

    //             //Reinforcement pool is 20
    //             // p0->setReinforcementPool(20);
    //             // p1->setReinforcementPool(20);
    //             // p2->setReinforcementPool(20);
    //             gameEng->changeState(command);

    //             gameEng->mainGameLoop();
    //             // gameEng->reinforcementPhase();

    //             // cout<< "Player " << p0->getPlayerNumber() << " has a reinforcement pool of " << p0->getReinforcementPool() << endl;
    //             // cout<< "Player " << p1->getPlayerNumber() << " has a reinforcement pool of " << p1->getReinforcementPool() << endl;
    //             // cout<< "Player " << p2->getPlayerNumber() << " has a reinforcement pool of " << p2->getReinforcementPool() << endl;

                
    //     break;
    //     case 2:
    //         cout <<"Case 2 has been selected."<<endl << endl;
            
    //         // Assigning a bonus of 3 units to continent
    //         gameMap->getContinent()[0]->setArmyBonus(3);

    //         // Assigning territories to both players
    //         vector<Territory*> p0Territories =  gameMap->getContinent()[0]->getTerritories();
    //         p0->setMyTerritories(p0Territories);
    //         cout << endl;

    //         p1->addTerritory(gameMap->getTerritoryByName("13"));
    //         p1->addTerritory(gameMap->getTerritoryByName("14"));
    //         p1->addTerritory(gameMap->getTerritoryByName("15"));
    //         cout << endl;

    //         gameEng->reinforcementPhase();

    //         cout<< "Player " << p0->getPlayerNumber() << " has a reinforcement pool of " << p0->getReinforcementPool() << endl;
    //         cout<< "Player " << p1->getPlayerNumber() << " has a reinforcement pool of " << p1->getReinforcementPool() << endl;

    //     break;
    // }

    // Release memory
    delete p0, p1, p2;
    p0, p1, p2 = nullptr;

    // delete gameEng; --> no destructor is defined so can't delete
    // gameEng = nullptr;

}

int main (){
    testMainGameLoop();
    return 0;
}