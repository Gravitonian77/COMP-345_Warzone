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
    
    cout << "\nPlease enter the case number (1-5) for the demonstrations of testGameLoop." << endl;
    cout << "\ncase 1: 2 players with no cards. Player 0 has all territories in the map while player 2 has none." << endl;
    cout << "case 2: 2 players with no cards. Player 0 has 1 territory player 2 has 0." << endl;
    cout << "case 3: 2 players with no cards. Player 0 has 1 continent of 12 territories player 2 has 1 territory." << endl;
    cout << "case 4: 2 players and both players have all cards and 1 territory each." << endl;
    cout << "case 5: 2 players and both players have 1 territory each." << endl;   

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

        gameEng->reinforcementPhase();
        gameEng->changeState(command);
        gameEng->mainGameLoop();
    }
    else if(input == 2){

        cout <<"Case 2 has been selected."<<endl << endl;
        p0->addTerritory(gameMap->getTerritoryByName("1"));

	gameEng->reinforcementPhase();
        gameEng->changeState(command);
        gameEng->mainGameLoop();

    }
    else if(input == 3){
        cout <<"Case 3 has been selected."<<endl << endl;
        p0->addTerritory(gameMap->getTerritoryByName("1"));

        //Assigning a bonus of 3 units to continent
        gameMap->getContinent()[0]->setArmyBonus(4);
        
        //Assigning territories to both players
        vector<Territory*> p0Territories =  gameMap->getContinent()[0]->getTerritories();
        p0->setMyTerritories(p0Territories);
        cout << endl;
	    
	gameEng->reinforcementPhase();
        gameEng->changeState(command);
        gameEng->mainGameLoop();

    }
    else if(input == 4){
        cout <<"Case 4 has been selected."<<endl << endl;

        // Add territories
        p0->addTerritory(gameMap->getTerritoryByName("1"));
        p1->addTerritory(gameMap->getTerritoryByName("2"));

        // Add Cards
        p0->getMyHand()->addCard(new Card(CardType::BOMB));
        p0->getMyHand()->addCard(new Card(CardType::REINFORCEMENT));
        p0->getMyHand()->addCard(new Card(CardType::BLOCKADE));
        p0->getMyHand()->addCard(new Card(CardType::AIRLIFT));
        p0->getMyHand()->addCard(new Card(CardType::DIPLOMACY));
        
        p1->getMyHand()->addCard(new Card(CardType::BOMB));
        p1->getMyHand()->addCard(new Card(CardType::REINFORCEMENT));
        p1->getMyHand()->addCard(new Card(CardType::BLOCKADE));
        p1->getMyHand()->addCard(new Card(CardType::AIRLIFT));
        p1->getMyHand()->addCard(new Card(CardType::DIPLOMACY));

	gameEng->reinforcementPhase();
        gameEng->changeState(command);
        gameEng->mainGameLoop();

    }
    else if(input == 5){

        cout <<"Case 5 has been selected."<<endl << endl;

        // Add territories
        p0->addTerritory(gameMap->getTerritoryByName("1"));
        p1->addTerritory(gameMap->getTerritoryByName("2"));

	gameEng->reinforcementPhase();
        gameEng->changeState(command);
        gameEng->mainGameLoop();
    }
    else{
        cout << "You did not enter a valid option." <<endl << "Program will end." << endl;
        exit(0);
    }
    
    // Release memory
    delete p0, p1, p2;
    p0, p1, p2 = nullptr;

}

int main (){
    testMainGameLoop();
    return 0;
}
