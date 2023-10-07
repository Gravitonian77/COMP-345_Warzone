#include "Player.h"
#include <iostream>
using namespace std;


int Player::nextPlayerNumber = 1;

// Constructors
Player::Player() : playerNumber(new int(nextPlayerNumber++)) {}

Player::Player(vector<Territory*> territories, const list<string>& cards, const list<string>& orders)
    : playerNumber(new int(nextPlayerNumber++)), myTerritories(territories), myCards(cards), myOrders(orders) {}

Player::Player(const Player& player)
    : playerNumber(new int(nextPlayerNumber++)), myTerritories(player.myTerritories), myCards(player.myCards), myOrders(player.myOrders) {}

// Destructor
Player::~Player() {
    delete playerNumber;

    for (Territory* t : myTerritories) {
        delete t;
        t = nullptr;
    }
    myTerritories.clear();
}

// Accessors
int Player::getPlayerNumber() const {
    return *playerNumber;
}

vector<Territory*> Player::getMyTerritories() const {
    return myTerritories;
}

list<string> Player::getCards() const {
    return myCards;
}

list<string> Player::getOrders() const {
    return myOrders;
}

// Add territory
void Player::addTerritory(Territory* territory) {
    myTerritories.push_back(territory);

    territory->setPlayer(this);
    cout << "Territory " << territory->getTerritoryName() << " was assigned to player " << *territory->getOwner()->playerNumber << "\n";
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this;
    }

    // Copy myTerritories
    for (Territory* t : myTerritories) {
        delete t;
    }
    myTerritories.clear();
    for (Territory* t : other.myTerritories) {
        myTerritories.push_back(new Territory(*t));
    }

    // Copy cards
    myCards = other.myCards;

    // Copy orders
    myOrders = other.myOrders;

    return *this;
}

// Stream Insertion Operator
ostream& operator<<(ostream& out, const Player& player) {
    out << "Player Number: " << player.getPlayerNumber() << endl;

    out << "My Territories: ";
    for (const Territory* territory : player.getMyTerritories()) {
        out << territory->getTerritoryName() << ", ";
    }
    out << endl;

    out << "Cards: ";
    for (const string& card : player.getCards()) {
        out << card << ", ";
    }
    out << endl;

    out << "Orders: ";
    for (const string& order : player.getOrders()) {
        out << order << ", ";
    }
    out << endl;

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
            if (adjacentTerritory->getOwner() != myTerritory->getOwner() && adjacentTerritory->getOwner() != nullptr) {
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
            // If the adjacent territory is owned by a different player, it can be attacked
            if (adjacentTerritory->getOwner() != this) {
                territoriesToAttack.push_back(adjacentTerritory);
            }
        }
    }

    return territoriesToAttack;
}

void Player::issueOrder(const string& order) {
    // Order is either to Attack or to Defend
    if (order.find("Attack") != string::npos || order.find("Defend") != string::npos) {
        myOrders.push_back(order);
    } else {
        cout << "The order: " << order << " is invalid. Order must be either Attack or Defend." << endl;
    }
}



