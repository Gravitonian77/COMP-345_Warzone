#pragma once

#include "Map.h"
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
class Orders;
class OrdersList;

class Player {
private:
    // Attributes
    static int nextPlayerNumber;
    int playerNumber;
    vector<Territory*> myTerritories; 
	OrdersList* myOrdersList;
	int reinforcementPool; 
	Hand* myHand; 

public:
    // Constructors
    Player();
    Player(vector<Territory*> territories, OrdersList* ordersList, Hand* hand); // Updated constructor
    Player(const Player& player);

    // Destructor
    ~Player();

    // Accessors
    int getPlayerNumber() const;
    int getReinforcementPool() const;
    vector<Territory*> getMyTerritories() const;
    OrdersList* getMyOrdersList() const;
    Hand* getMyHand() const; 
	
    // Mutators
    void setReinforcementPool(int pool);
    void setMyTerritories(vector<Territory*>& newTerritories);
    void setMyOrdersList(OrdersList* newOrdersList);
    void setMyHand(Hand* newHand);

    // Add/Remove territory to the player's list
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);

    // Assignment operator
    Player& operator=(const Player& other);

    // Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Player& player);

    // Methods Required
    vector<Territory*> ToDefend();
    vector<Territory*> ToAttack();
    void issueOrder(Order* order); 
};
