//
// Created by garvi on 2023-09-22.
//

#ifndef UNTITLED_GAMEENGINE_H
#define UNTITLED_GAMEENGINE_H

#include<iostream>
#include <map>
using namespace std;

class GameEngine;
class State;


class State{
private:
	//State name
	string* stateName;

public:

	//default constructor
	State();

	//Parametrized constructor
	State(string& state);

	//copy constructor
	State(State &anotherState);

	//assignment operator
	State& operator = (const State& state);

	//stream insertion operator
	friend ostream& operator<<(ostream& out, const State& state);

	//destructor
	~State() ;

	//State name getter
	string* getStateName() const;

	//Exit and Enter functions for transitioning between states
	void onEnter(GameEngine* engine) ;
	void onExit(GameEngine* engine);
};



class GameEngine{

private:

	//State object
	State* currentState;

	//Map for mapping commands with transitioning states
	map<std::string, std::pair<State*, State*>> transitions;

public:

	//default constructor
	GameEngine();

	//parametrized constructor
	GameEngine(State* initialState, std::pair<State*, State*> transitions);

	//copy constructor
	GameEngine(const GameEngine& game);

	//assignment operator
	GameEngine& operator = (const GameEngine& game);

	//stream insertion operator
	friend  ostream&  operator << (ostream& out, const GameEngine& game);

	//destructor
	~GameEngine();

	//Current state getter
	State * getCurrentState() const;

	//Current state setter
	void setCurrentState(State* state);

	//Transition map getter
	std::map<std::string, std::pair<State*, State*>> getTransition() const;

	//Transition map setter
	void addTransition(State* from, State *to, string command);

	//
	void changeState(string& command);
	void startGame();
	void processCommand(string command);
	State* newState(string stateName);

};

#endif //UNTITLED_GAMEENGINE_H

class GameEngineDriver{

	void testGameStates();

};
