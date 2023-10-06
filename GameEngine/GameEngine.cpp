#include <iostream>
#include "GameEngine.h"

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
