#include "Player.h"
#include <iostream>
using namespace std;


// Constructors
Player::Player() : playerNumber (new int(nextPlayerNumber++)), myCards(nullptr), myOrders(nullptr) {}

Player::Player(vector<Territory *> territories, Hand* cards, OrdersList* orders)
    : playerNumber (new int(nextPlayerNumber++)),myTerritories(territories), myCards(cards), myOrders(orders) {}

Player::Player(const Player& player)
    : playerNumber (new int(nextPlayerNumber++)),myTerritories(player.myTerritories), myCards(player.myCards), myOrders(player.myOrders) {}

// Destructor
Player::~Player() {

     delete playerNumber;   
    // Clean up dynamically allocated territories
    for (Territory* t : myTerritories) {
        delete t;
        t = nullptr;
    }
    myTerritories.clear();

    // Clean up dynamically allocated cards
    delete myCards;
    myCards = nullptr;

    // Clean up dynamically allocated orders
    delete myOrders;
    myOrders = nullptr;
}

// Accessors
int Player::getPlayerNumber() const{
    return *playerNumber;
}
vector<Territory *> Player::getMyTerritories() const {
    return myTerritories;
}

Hand* Player::getCards() const {
    return myCards;
}

OrdersList* Player::getOrders() const {
    return myOrders;
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this; // Check if same player
    }

    // Copy myTerritories 
    for (int i = 0; i < other.myTerritories.size(); i++) {
       this->myTerritories.push_back(new Territory(*(other.myTerritories[i])));
    }

    // Copy cards 
    delete myCards;
    myCards = new Hand(*other.myCards);

    // Copy orders
    delete myOrders;
    myOrders = new OrdersList(*other.myOrders);

    return *this;
}

//Stream Insertion Operator
ostream& operator<<(ostream& out, const Player& player) {
    out << "My Territories: ";
    for (const Territory* territory : player.getMyTerritories()) {
        out << territory->getTerritoryName() << ", ";
    }
    out << endl;
    
    out << "Cards: " << player.getCards() << endl;
    
    out << "Orders: " << player.getOrders() << endl;

    return out;
}


// Methods Required
vector<Territory*> Player::ToDefend() {
    vector<Territory*> territoriesToDefend;

    // Iterate through the player's territories
    for (Territory* myTerritory : myTerritories) {
        bool needsDefending = false;
        // Check each adjacent territory
        for (Territory* adjacentTerritory : myTerritory->getAdjacentTerritories()) {
            // If the adjacent territory does not belong to the player, it needs to be defended
            if (adjacentTerritory->getOwner() != myTerritory->getOwner()) {
                needsDefending = true;
                break; // No need to check other adjacent territories for this territory
            }
        }

        // If this territory needs defending, add it to the list
        if (needsDefending) {
            territoriesToDefend.push_back(myTerritory);
        }
    }

    return territoriesToDefend;
}


vector<Territory*> Player::ToAttack() {
    vector<Territory*> territoriesToAttack;

    // Iterate through the player's territories
    for (Territory* myTerritory : myTerritories) {
        // Check each adjacent territory
        for (Territory* adjacentTerritory : myTerritory->getAdjacentTerritories()) {
            // If the adjacent territory is not owned by the player, it can be attacked
            if (adjacentTerritory->getOwner() != myTerritory->getOwner()) {
                territoriesToAttack.push_back(adjacentTerritory);
            }
        }
    }

    return territoriesToAttack;
}

void Player::issueOrder(const string& orderDescription) {
    // Create an Order object
    Order* newOrder = new Order(orderDescription);

    // Add Order object to the player's list of orders
    myOrders->insertOrder(orderDescription);
    
}

