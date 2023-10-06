#pragma once 

#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"

#include <vector>
#include <iostream>
using namespace std;

class Territory;
class Orders;
class OrdersList;
class Hand;



class Player {
private:
    // Attributes
    static int nextPlayerNumber;
    int* playerNumber; 
    vector<Territory*> myTerritories;
    Hand* myCards;                             
    OrdersList* myOrders;    

public:

    //Constructors 
    Player();
    Player(std::vector<Territory *> territories, Hand* cards, OrdersList* orders);
    Player(const Player& player);
    
    //Destructor
    ~Player();

    //Accesors
    int getPlayerNumber() const;
    vector<Territory *> getMyTerritories() const; 
    Hand* getCards() const; 
    OrdersList* getOrders() const; 

    // Add territory to the player's list
    void addTerritory(Territory* territory);

    //Assignment operator
    Player& operator=(const Player& other);

    //Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Player& player);

    //Methods Required
    vector<Territory*> ToDefend();
    vector<Territory*> ToAttack();
    void issueOrder(string orderDescription);


};

int Player::nextPlayerNumber = 1;
