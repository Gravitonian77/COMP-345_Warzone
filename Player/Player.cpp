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

void testPlayers() {
    // Create the map 
    Map* gameMap = mapLoader::createMapFromConquestFile("Canada.map");

    // Players
    Player* p1 = new Player();
    p1->addTerritory(gameMap->getContinent()[0]->getTerritories()[0]); // 1,548,116,Northern Islands,2,12
    p1->addTerritory(gameMap->getContinent()[0]->getTerritories()[1]); // 2,510,124,Northern Islands,1,3

    Player* p2 = new Player();
    p2->addTerritory(gameMap->getContinent()[0]->getTerritories()[2]); // 3,487,139,Northern Islands,2,4
    p2->addTerritory(gameMap->getContinent()[0]->getTerritories()[3]); // 4,463,136,Northern Islands,3,5

    cout << endl << *p1 << endl;
    cout << *p2 << endl;

    // P1 territories to attack
    cout << "Player " << p1->getPlayerNumber() << " can attack territories: ";
    vector<Territory*> toAttackp1 = p1->ToAttack();
    for (Territory* t : toAttackp1) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // P1 territories to defend
    cout << "Player " << p1->getPlayerNumber() << " can defend territories: ";
    vector<Territory*> toDefendp1 = p1->ToDefend();
    for (Territory* t : toDefendp1) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // P2 territories to attack
    cout << "Player " << p2->getPlayerNumber() << " can attack territories: ";
    vector<Territory*> toAttackp2 = p2->ToAttack();
    for (Territory* t : toAttackp2) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // P2 territories to defend
    cout << "Player " << p2->getPlayerNumber() << " can defend territories: ";
    vector<Territory*> toDefendp2 = p2->ToDefend();
    for (Territory* t : toDefendp2) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl << endl;

    // Add orders to players
    p1->issueOrder("Attack Territory  12 3");   // valid
    p1->issueOrder("Defend Territory 2");       // valid
    p1->issueOrder("Move to Territory  12 3");  // invalid

    p2->issueOrder("Attack territory 2 5");     // valid
    p2->issueOrder("Defend Territory 3 4");     // valid
    p2->issueOrder("Move to Territory  2 5");  // invalid
    
    // Display orders
    cout << "\nPlayer " << p1->getPlayerNumber() << " has orders: ";
    for (const string& order : p1->getOrders()) {
        cout << order << ", ";
    }
    cout << endl;

    cout << "Player " << p2->getPlayerNumber() << " has orders: ";
    for (const string& order : p2->getOrders()) {
        cout << order << ", ";
    }
    cout << endl;

    // Release memory
    delete p1;
    delete p2;
}
