#pragma once

#include "Cards.h"
#include "Orders.h"
#include "GameEngine.h"

#include <vector>
#include <list>
#include <iostream>

using namespace std;

// Forward declaration
class Territory;
class Hand;
class OrdersList;
class GameEngine;

class Player {
private:
    // Attributes
    static int nextPlayerNumber;
    int playerNumber;
    vector<Territory*> myTerritories; 
	OrdersList* myOrdersList;
	int reinforcementPool; 
	Hand* myHand; 
    GameEngine* myGameEngine;

public:
    // Constructors
    Player();
    Player(vector<Territory*> territories, OrdersList* ordersList, Hand* hand);
    Player(const Player& player);

    // Destructor
    ~Player();

    // Accessors
    int getPlayerNumber() const;
    int getReinforcementPool() const;
    vector<Territory*> getMyTerritories() const;
    OrdersList* getMyOrdersList() const;
    Hand* getMyHand() const; 
    GameEngine* getMyGameEngine()const;

	
    // Mutators
    void setReinforcementPool(int pool);
    void setMyTerritories(vector<Territory*>& newTerritories);
    void setMyOrdersList(OrdersList* newOrdersList);
    void setMyHand(Hand* newHand);
    void setGameEngine(GameEngine* game);

    // Owns territory
    bool ownsTerritory(string territoryName);

    // Add/Remove territory to the player's list
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);

    // Assignment operator
    Player& operator=(const Player& other);

    // Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Player& player);

    // Methods Required
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(); 
};
