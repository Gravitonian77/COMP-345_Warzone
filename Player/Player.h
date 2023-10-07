#pragma once

#include "Map.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

class Territory;

class Player {
private:
    // Attributes
    static int nextPlayerNumber;
    int* playerNumber;
    vector<Territory*> myTerritories;
    list<string> myCards;    
    list<string> myOrders;   

public:
    // Constructors
    Player();
    Player(vector<Territory*> territories, const list<string>& cards, const list<string>& orders); // Updated constructor
    Player(const Player& player);

    // Destructor
    ~Player();

    // Accessors
    int getPlayerNumber() const;
    vector<Territory*> getMyTerritories() const;
    list<string> getCards() const;
    list<string> getOrders() const;

    // Add territory to the player's list
    void addTerritory(Territory* territory);

    // Assignment operator
    Player& operator=(const Player& other);

    // Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Player& player);

    // Methods Required
    vector<Territory*> ToDefend();
    vector<Territory*> ToAttack();
    void issueOrder(const string& order); // Updated method to accept a string
};
