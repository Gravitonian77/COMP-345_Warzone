#include "GameEngine.h"

void testGameStates(){

	GameEngine* game = new GameEngine();

	State* start = game->newState("start");
	State* map_loaded = game->newState("load_map");
	State* map_validated = game->newState("map_validated");
	State* players_added = game->newState("players_added");
	State* assign_reinforcements = game->newState("assign_reinforcements");
	State* issue_orders = game->newState("issue_orders");
	State* execute_orders = game->newState("execute_orders");
	State* win = game->newState("win");

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
	game->addTransition(execute_orders, assign_reinforcements, "endexecorder");
	game->addTransition(execute_orders, win, "win");
	game->addTransition(win, start, "play");
	game->setCurrentState(start);
	game->startGame();

}

int main(){
	testGameStates();
}
