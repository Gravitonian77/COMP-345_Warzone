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
    vector<Territory *> getMyTerritories() const; // Accessor to return territories
    Hand* getCards() const; // Accessor to return cards
    OrdersList* getOrders() const; // Accessor to return orders

    //Assignment operator
    Player& operator=(const Player& other);

    //Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Player& player);

    //Methods Required
    vector<Territory*> ToDefend();
    vector<Territory*> ToAttack();
    void issueOrder(const string& orderDescription);

};

int Player::nextPlayerNumber = 1;  // Initialize the static member

