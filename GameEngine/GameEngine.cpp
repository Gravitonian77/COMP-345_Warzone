#include <iostream>
#include "GameEngine.h"
#include "Map.h"

State::State() = default;
State::State(std::string& state) {
	this->stateName = &state;
}

string* State::getStateName() const{
	return stateName;
}

State::State(State &anotherState) {
	this->stateName = anotherState.stateName;
}

State &State::operator=(const State &state) {
	if(this != &state)
		this->stateName = state.stateName;

	return *this;
}

ostream &operator<<(ostream& out, const State &state) {

		if((state.getStateName()) != nullptr) {
			out << "Current State: " << (*state.getStateName()) << endl;
		} else{
			out << "statename is null";
		}
	return out;
}

void State::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
	cout << "State changed\n";
}

void State::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
	cout << "Changing states...\n";
}


Transition::Transition() = default;
Transition::Transition(State *fromState, State *toState, std::string *command) {
	this->from = fromState;
	this->to = toState;
	this->command = command;
}

Transition::Transition(const Transition &transition) {
	this->from = transition.from;
	this->to = transition.to;
	this->command = transition.command;
}

Transition &Transition::operator=(const Transition &transition) {
	if(this != &transition){
		this->to = transition.to;
		this->from = transition.from;
		this->command = transition.command;
	}
	return *this;
}

ostream &operator<<(ostream& out, const Transition& transition){
	out << "Transitioning from: " << transition.from << ", to: " << transition.to <<endl;
	return out;
}


GameEngine::GameEngine() = default;
GameEngine::GameEngine(State *initialState, std::pair<State*, State*> transitions) {
	this->currentState = initialState;
	//this ->transitions = transitions;
}

GameEngine::GameEngine(const GameEngine &game) {
	this->currentState = game.currentState;
	this->transitions = game.transitions;
}

GameEngine &GameEngine::operator=(const GameEngine &game) {
	if(this!= &game){
		this->currentState = game.currentState;
		this->transitions = game.transitions;
	}
	return *this;
}

/*ostream &operator<<(ostream& out, const GameEngine& game){
	out << "State: " << game.getCurrentState() << " Transition: " << game.getTransition();
	return out;
}*/

void GameEngine::setCurrentState(State *state) {
	this->currentState = state;
	//this->currentState->stateName = state->stateName;
}

State *GameEngine::getCurrentState() const {
	return this->currentState;
}

void GameEngine::changeState(string& command) {
	//change current state if newState is not the final state

	if((transitions.find(command) != transitions.end()) && (transitions.find(command)->second.second->getStateName())) {
		currentState->onExit(this);
		cout<< "debug: " << *transitions[command].second;//to //A -> B ; B
		setCurrentState(transitions[command].second);
		currentState->onEnter(this);
		cout <<  *currentState;
	}

}

void GameEngine::addTransition(State *from, State *to, string command) {
	transitions[command].first = from;
	transitions[command].second = to;
}

map<std::string, std::pair<State*, State*>> GameEngine::getTransition() const {
	return transitions;
}

void GameEngine::setMap(Map *pMap) {
	this->map = pMap;
}

Map *GameEngine::getMap() {
	return this->map;
}

void GameEngine::startGame() {
	string command;
	std::cout << "Enter a command: ";
	std::cin >> command;
	processCommand(command);
}

void GameEngine::processCommand(std::string command) {
	string stateNow = *getCurrentState()->getStateName();
	if(transitions.find(command) != transitions.end()){
		//currentState = new State(command);

		if(command == "loadmap" && ((stateNow == "start") || (stateNow == "load_map"))){

			changeState(command);
			//setMap(mapLoader::createMapFromConquestFile(""));

		}else if(command == "validatemap" && (stateNow == "load_map")){

			changeState(command);

		}else if(command == "addplayer" && ((stateNow == "map_validated") || (stateNow == "players_added"))){

			changeState(command);

		}else if(command == "assigncountries" && (stateNow == "players_added")){
			cout << "previous state = " << stateNow << endl;
			changeState(command);
			stateNow = *getCurrentState()->getStateName();
			cout << "current state = " << stateNow <<endl;
		}else if(command == "issueorder" && ((stateNow == "assign_ref") || (stateNow == "issue_orders"))){

			changeState(command);

		}else if(command == "endissueorders" && (stateNow == "issue_orders")){

			changeState(command);

		}else if(command == "execorder" && (stateNow == "execute_orders")){

			changeState(command);

		}else if(command == "endexecorders" && (stateNow == "execute_orders")){

			changeState(command);

		}else if(command == "win" && (stateNow == "execute_orders")){

			changeState(command);

		}else if(command == "end"){

			changeState(command);

		}else if(command == "play" && stateNow == "win"){
			changeState(command);
		}else{
			cout << "This is not a valid transition. Please enter a valid state to transition to. \n";
		}

	}else
		cout << "not working";

}

State* GameEngine::newState(std::string stateName) {
	State * state = new State(stateName);
	return state;
}
