//
// Created by garvi on 2023-09-22.
//

#ifndef UNTITLED_GAMEENGINE_H
#define UNTITLED_GAMEENGINE_H

#include<iostream>
#include <map>
using namespace std;

class GameEngine;
class Player;
class Map;
class Orders;
class State;
class Transition;

class State{
public:
	string* stateName;
	State();
	State(string& state);
	State(State &anotherState);
	State& operator = (const State& state);
	friend ostream& operator<<(ostream& out, const State& state);
	~State() ;

	void onEnter(GameEngine* engine) ;
	void onExit(GameEngine* engine);
};



class Transition{
private:
	State* from;
	State* to;
	string* command;

public:
	Transition();
	Transition(State* fromState, State* toState, string* command);
	Transition(const Transition& transition);
	~Transition();
	Transition& operator = (const Transition& transition);
	friend ostream& operator<<(ostream& out, const Transition& transition);
	State* getToState() const;
};

class GameEngine{

private:
	//meEngine(State *initialState, std::map<State *, Transition *, string &> transitions);

	State* currentState;
	map<std::string, std::pair<State*, State*>> transitions;
	Map* map;
	Player* player;
	Orders* order;

public:
	GameEngine();
	GameEngine(State* initialState, std::pair<State*, State*> transitions);
	GameEngine(const GameEngine& game);
	~GameEngine();
	GameEngine& operator = (const GameEngine& game);
	friend  ostream&  operator << (ostream& out, const GameEngine& game);
	void addTransition(State* from, State *to, string command);
	void changeState(string& command);
	void startGame();
	void processCommand(string command);
	void setMap(Map* pMap);
	Map* getMap();
	State* newState(string stateName);

	void issueOrders(Orders*);
	State * getCurrentState() const;
	void setCurrentState(State* state);
	std::map<std::string, std::pair<State*, State*>> getTransition() const;


};

#endif //UNTITLED_GAMEENGINE_H

