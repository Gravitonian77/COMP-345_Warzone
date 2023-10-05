#include <iostream>
#include "GameEngine.h"

State::State() = default;
State::State(std::string& state) {
	this->stateName = stateName;
}

State::State(State &anotherState) {
	this->stateName = anotherState.stateName;
}

State &State::operator=(const State &state) {
	if(this != &state)
		this->stateName = state.stateName;

	return *this;
}

ostream &operator<<(ostream& out, const State& state) {
	out << "Current State: " << state.stateName << endl;
	return out;
}

void State::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
}

void State::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
}

/*LoadState::LoadState() = default;

void LoadState::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
}

void LoadState::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
}

void MapState::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
}

void MapState::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
}

void PlayerState::onEnter(GameEngine *engine) {
	engine->setCurrentState(this);
}

void PlayerState::onExit(GameEngine *engine) {
	engine->setCurrentState(nullptr);
}

void PlayerState::addPlayer(Player *) {
	cout << "player added";
}

void OrderState::validate() {
	cout << "validated";
}

*/








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

ostream &operator<<(ostream& out, const GameEngine& game){
	out << "State: " << game.getCurrentState() << " Transition: " << game.getTransition();
	return out;
}

void GameEngine::setCurrentState(State *state) {
	this->currentState = state;
}

State *GameEngine::getCurrentState() const {
	return this->currentState;
}

void GameEngine::changeState(string& command) {
	//change current state if newState is not the final state
	if(transitions.find(command) != transitions.end()) {
		currentState->onExit(this);
		currentState = transitions[command].second;
		currentState->onEnter(this);
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

	if(transitions.find(command) != transitions.end()){
		//changeState(command);

		if(command == "loadmap"){
			setMap(map);
		}else if(command == "validatemap"){
			cout << "validated";
		}else if(command == "addplayer"){

		}else if(command == "assigncountries"){

		}else if(command == "issueorder"){

		}else if(command == "endissueorders"){

		}else if(command == "execorder"){

		}else if(command == "endexecorders"){

		}else if(command == "win"){

		}else if(command == "end"){

		}else if(command == "play"){

		}

	}else
		cout << "not working";

}

State* GameEngine::newState(std::string stateName) {
	State * state = new State(stateName);
	return state;
}
