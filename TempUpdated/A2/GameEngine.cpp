#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "GameEngine.h"
#include "Player.h"


class Player;


//Implementation of State class

// Default constructor
State::State() = default;

// Parameterized constructor initializing stateName with provided state
State::State(std::string& state) {
	this->stateName = &state;
}

// Getter method to retrieve the state name
string* State::getStateName() const{
	return stateName;
}

// Copy constructor to create a new State object with the same stateName as anotherState
State::State(State &anotherState) {
	this->stateName = anotherState.stateName;
}

// Overloaded assignment operator to assign the stateName of one State object to another
State &State::operator=(const State &state) {
	if(this != &state)
		this->stateName = state.stateName;

	return *this;
}

// Overloaded stream insertion operator to output the stateName
ostream &operator<<(ostream& out, const State &state) {

		if((state.getStateName()) != nullptr) {
			out << "Current State: " << (*state.getStateName()) << endl;
		} else{
			out << "statename is null";
		}
	return out;
}

// Method to set the current state of the engine and display a message
void State::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
	cout << "State changed\n";
}

// Method to reset the current state of the engine and display a message
void State::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
	cout << "Changing states...\n";
}


//Implementation of GameEngine class

// Default constructor
GameEngine::GameEngine() = default;

// Parameterized constructor initializing currentState and transitions
GameEngine::GameEngine(State *initialState, std::pair<State*, State*> transitions) {
	this->currentState = initialState;
}

// Copy constructor to create a new GameEngine object with the same currentState and transitions as game
GameEngine::GameEngine(const GameEngine &game) {
	this->currentState = game.currentState;
	this->transitions = game.transitions;
}

// Overloaded assignment operator to assign the currentState and transitions of one GameEngine object to another
GameEngine &GameEngine::operator=(const GameEngine &game) {
	if(this!= &game){
		this->currentState = game.currentState;
		this->transitions = game.transitions;
	}
	return *this;
}

// Overloaded stream insertion operator to output the current state and transitions
ostream &operator<<(ostream& out, const GameEngine& game){

	string s = *game.getCurrentState()->getStateName();
	out << "State: " << s << " Transition from: " << game.getTransition().at(s).first << " to: " << game.getTransition().at(s).second;
	return out;

}

// Method to set the current state of the engine
void GameEngine::setCurrentState(State *state) {
	this->currentState = state;
}

// Getter method to retrieve the current state of the engine
State *GameEngine::getCurrentState() const {
	return this->currentState;
}

// Method to add a transition from one state to another based on a command
void GameEngine::addTransition(State *from, State *to, string command) {
	transitions[command].first = from;
	transitions[command].second = to;
}

// Getter method to retrieve the transitions of the engine
map<std::string, std::pair<State*, State*>> GameEngine::getTransition() const {
	return transitions;
}

// Method to change the current state of the engine based on a command
void GameEngine::changeState(string& command) {

	//change current state if newState is not the final state
	if((transitions.find(command) != transitions.end()) && (transitions.find(command)->second.second->getStateName())) {
		currentState->onExit(this);
		setCurrentState(transitions[command].second);
		currentState->onEnter(this);
		cout << "\n" <<*currentState;
	}

}

// Method to start the game and accept a command from the user
void GameEngine::startGame() {
	string command;
	std::cout << "Enter a command: ";
	std::cin >> command;
	processCommand(command);
}

// Method to process a command and transition to the appropriate state
void GameEngine::processCommand(std::string command) {

	cout << *currentState;
	string stateNow = *getCurrentState()->getStateName();   //For checking the current state

	if(transitions.find(command) != transitions.end()){

		if(stateNow == "start" && command == "loadmap"){

			changeState(command);

		}else if(stateNow == "load_map" && (command == "validatemap" || command == "loadmap")){

			changeState(command);

		}else if(stateNow == "map_validated" && command == "addplayer"){

			changeState(command);

		}else if(stateNow == "players_added" && (command == "addplayer" || command == "assigncountries")){

			changeState(command);

		}else if(stateNow == "assign_ref" && command == "issueorder"){

			changeState(command);

		}else if(stateNow == "issue_orders" && (command == "issueorder" || command == "endissueorders")){

			changeState(command);

		}else if(stateNow == "execute_orders" && (command == "execorder" || command == "endexecorders") || (command == "win")){

			changeState(command);

		}else if(command == "play" && stateNow == "win"){

			changeState(command);

		}else if(command == "end"){

			exit(0);

		}else{
			cout << "This is not a valid transition. Please enter a valid state to transition to. \n";
		}

	}else
		cout << "Invalid input.\n";

}

// Method to create a new state with a given name
State* GameEngine::newState(std::string stateName) {
	State * state = new State(stateName);
	return state;
}

Map* GameEngine::getMap(){ // saq
	return map;
}
vector <Player*> GameEngine::getPlayers(){ // saq
	return players;
}
void GameEngine::setMap(Map* newMap){
	this->map = newMap;
}

void GameEngine::addPlayer(Player* player){
	players.push_back(player);
}
void GameEngine::removePlayer(Player* player){
	players.erase(remove(players.begin(), players.end(), player), players.end());
}
/*
 numberOfArmies = (territoriesOwned/3) rounded down
 Continent control bonus is added to the numberOfarmies
 Player gets either 3 armies OR or numberOfArmies + continent control bonus
*/
void GameEngine::reinforcementPhase() {
	for (Player* p : players) {
		int numberOfArmies = floor(p->toDefend().size() / 3); 
		p->setReinforcementPool(max(3, p->getReinforcementPool() + numberOfArmies + map->continentControlBonus(p)));
	}
}

void GameEngine::issueOrderPhase() { // Orders issued for every player in the game 
	for (Player* p : players) {
            p->issueOrder();    
	}
}

void GameEngine::executeOrderPhase(){
	for (Player* p : players){
        OrdersList* playerOrders = p->getMyOrdersList();
        vector<Order*> ordersToExecute;		
		for(Order* o: p->getMyOrdersList()->getOrdersList()){
			if (o->getName() == "Deploy"){ // game engine executes all deploy orders before any other orders
				ordersToExecute.push_back(o);
			}
		}
		for(Order* o: ordersToExecute){
			o->execute();
			playerOrders->removeOrder(o);
		}
	}
}
void GameEngine::mainGameLoop(){ // This loop continues until a player has all territories
	
	bool playerOwnsAll = false;
	int numOfTerritoriesInMap = map->getTerritory().size();

	do{
		for (Player* p : players) {
			// Remove player if they have no territories
			if (p->toDefend().empty()){
				cout << "Since player " << p->getPlayerNumber() << " has 0 territories, this player will be removed." << endl;
				removePlayer(p);
			}
			// Check if a player in the game has all territories, if yes, then that player wins the game
			if(p->toDefend().size() == numOfTerritoriesInMap){
				playerOwnsAll = true;
				cout<< "Player " << p->getPlayerNumber() << " has control of all territories in the game. This player wins." << endl;
				string command = "win";
				changeState(command);
				return;
			}
			// if any player doesn't own all territories, continue the game
			if(!playerOwnsAll) {

			string command = "endexecorders";	
			changeState(command); // when orders are done excuting, start reinforcement phase
			reinforcementPhase();

			command = "issueorder";
			changeState(command); // start issue order after reinforcement phase
			issueOrderPhase();

			command = "execorder";
			changeState(command); // exeCute orders after they have been issued
			executeOrderPhase();
			}
		}
	}while(!playerOwnsAll); // loop ends when one player has all territories in the game 


}


void testGameStates(){

	//Instantiating a GameEngine object to run the game
	GameEngine* game = new GameEngine();

	//Instantiating all states that our game object will transition to and from.
	State* start = game->newState("start");
	State* map_loaded = game->newState("load_map");
	State* map_validated = game->newState("map_validated");
	State* players_added = game->newState("players_added");
	State* assign_reinforcements = game->newState("assign_ref");
	State* issue_orders = game->newState("issue_orders");
	State* execute_orders = game->newState("execute_orders");
	State* win = game->newState("win");
	State* end = game->newState("end");

	//Mapping all the transitions with their respective commands.
	game->addTransition(start, map_loaded, "loadmap");
	game->addTransition(map_loaded, map_loaded, "loadmap");
	game->addTransition(map_loaded, map_validated, "validatemap");
	game->addTransition(map_validated, players_added, "addplayer");
	game->addTransition(players_added, players_added, "addplayer");
	game->addTransition(players_added, assign_reinforcements, "assigncountries");
	game->addTransition(assign_reinforcements, issue_orders, "issueorder");
	game->addTransition(issue_orders, issue_orders, "issueorder");
	game->addTransition(issue_orders, execute_orders, "endissueorders");
	game->addTransition(execute_orders, execute_orders, "execorder");
	game->addTransition(execute_orders, assign_reinforcements, "endexecorders");
	game->addTransition(execute_orders, win, "win");
	game->addTransition(win, start, "play");
	game->addTransition(win, end, "end");
	game->setCurrentState(start);

	while(*game->getCurrentState()->getStateName() != "end") {
		game->startGame();
	}
}
