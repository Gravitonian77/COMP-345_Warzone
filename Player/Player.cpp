#include "Player.h"
#include <iostream>
using namespace std;

#include "Map.cpp"
#include "Orders.cpp"
#include "Cards.cpp"

int Player::nextPlayerNumber = 1;

// Constructors
Player::Player() 
    : playerNumber(nextPlayerNumber++), 
      myTerritories(), 
      myOrdersList(new OrdersList()), 
      reinforcementPool(0), 
      myHand(new Hand()) 
{}


Player::Player(vector<Territory*> territories, OrdersList* ordersList, Hand* hand)
    : playerNumber(nextPlayerNumber++),
      myTerritories(), // initialize to an empty vector
      myOrdersList(new OrdersList(*ordersList)), // deep copy orders list
      myHand(new Hand(*hand)) // deep copy hand
{
    // Deep copy each territory
    for (Territory* territory : territories) {
        myTerritories.push_back(new Territory(*territory));
    }
}

Player::Player(const Player& player)
    : playerNumber(nextPlayerNumber++), 
      myTerritories(), // Create an empty vector for territories
      myOrdersList(new OrdersList(*(player.myOrdersList))), // Deep copy of orders list
      reinforcementPool(player.reinforcementPool), // Copy reinforcement pool value
      myHand(new Hand(*(player.myHand))) // Deep copy of hand
{
    // Deep copy each territory
    for (Territory* territory : player.myTerritories) {
        myTerritories.push_back(new Territory(*territory));
    }
}


// Destructor
Player::~Player() {
    for (auto& territory : myTerritories) {
        if (territory != nullptr) {
            delete territory;
            territory = nullptr;
        }
    }
    myTerritories.clear();

    if (myOrdersList != nullptr) {
        delete myOrdersList;
        myOrdersList = nullptr;
    }

    if (myHand != nullptr) {
        delete myHand;
        myHand = nullptr;
    }
}



// Accessors
int Player::getPlayerNumber() const {
    return playerNumber;
}

int Player::getReinforcementPool() const{
    return reinforcementPool;
}

vector<Territory*> Player::getMyTerritories() const {
    return myTerritories;
}

OrdersList* Player::getMyOrdersList() const{
    return myOrdersList;
}

Hand* Player::getMyHand() const {
    return myHand;
}


// Mutators
void Player::setReinforcementPool(int pool){
    reinforcementPool = pool;
}

void  Player::setMyTerritories(vector<Territory*>& newTerritories){
    myTerritories = newTerritories;
}

void Player::setMyOrdersList(OrdersList* newOrdersList){
    myOrdersList = newOrdersList;
}

void Player::setMyHand(Hand *newHand){
    myHand = newHand;
}


// Add territory
void Player::addTerritory(Territory* territory) {
    myTerritories.push_back(territory);
    territory->setPlayer(this);
    cout << "Territory " << territory->getTerritoryName() << " was assigned to player " << getPlayerNumber() << "\n";
}


// Remove territory
void Player::removeTerritory(Territory* territory) {
    auto it = std::find(myTerritories.begin(), myTerritories.end(), territory);
    if (it != myTerritories.end()) {
        // Territory found, print its name
        cout << "Territory " << (*it)->getTerritoryName() << " was removed from player " << getPlayerNumber() << "\n";
        // Remove the territory
        myTerritories.erase(it);
    } else {
        // Territory not found, print a different message if needed
        cout << "Territory not found in player's territory list.\n";
    }
}


Player& Player::operator=(const Player& other) {
    if (this != &other) {
        // Deep copy of hand and orders list
        Hand* newHand = nullptr;
        OrdersList* newOrdersList = nullptr;
        if (other.myHand) {
            newHand = new Hand(*(other.myHand));
        }
        if (other.myOrdersList) {
            newOrdersList = new OrdersList(*(other.myOrdersList));
        }

        // Clean up existing resources
        delete myHand;
        delete myOrdersList;

       
        vector<Territory*> newTerritories;
        for (Territory* territory : other.myTerritories) {
            newTerritories.push_back(new Territory(*territory)); // Deep copy each territory
        }

        // Delete the old territories if you have ownership
        for (Territory* territory : myTerritories) {
            delete territory;
        }

        
        myHand = newHand;
        myOrdersList = newOrdersList;
        myTerritories = newTerritories;

        reinforcementPool = other.reinforcementPool;

        // Note: playerNumber is unique and not copied
    }
    return *this;
}


//Stream Insertion Operator
ostream& operator<<(ostream& out, const Player& player) {
    out << "Player Number: " << player.getPlayerNumber() << endl;

    out << "Territories: ";
    for (const Territory* territory : player.getMyTerritories()) {
        out << territory->getTerritoryName() << ", ";
    }
    out << endl;

    out << "Cards: ";
    for (const Card* card : player.getMyHand()->getCards()) {
        out << card->getType() << ", ";
    }
    out << endl;

    out << "Orders: ";
    for (const Order* order : player.getMyOrdersList()->getOrdersList()) {
        out << order->getEffect() << ", ";
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



void Player::issueOrder(Order* order) {
    if (order != nullptr) {
        // Check for the specific type of order, you may need dynamic_cast here if you have derived classes
        if (order->getEffect() == "Deploy" || order->getEffect() == "Advance" || 
            order->getEffect() == "Bomb" || order->getEffect() == "Blockade" || 
            order->getEffect() == "Airlift" || order->getEffect() == "Negotiate") {
            myOrdersList->insertOrder(order);
        } else {
            cout << "The order: " << order->getEffect() << " is not recognized." << endl;
        }
    } else {
        cout << "The order pointer is null." << endl;
    }
}


void testPlayers() {

    cout << "---------------------- Start of Player -------------- \n";
    // Create the map 
    Map* gameMap = mapLoader::createMapFromConquestFile("Canada.map");

    // Players
    Player* p1 = new Player();
    OrdersList* playerOrders = new OrdersList();
    Hand* playerHand = new Hand();

    // add territories
    Territory* territory1 = gameMap->getContinent()[0]->getTerritories()[0]; // 1,548,116,Northern Islands,2,12
    Territory* territory2 = gameMap->getContinent()[0]->getTerritories()[1]; // 2,510,124,Northern Islands,1,3
    p1->addTerritory(territory1);
    p1->addTerritory(territory2);
   
    // add hand
    playerHand->addCard(new Card(CardType::BOMB));
    playerHand->addCard(new Card(CardType::BLOCKADE));
    p1->setMyHand(playerHand);

    // add orders
    playerOrders->insertOrder(new Order(false, "Deploy"));
    playerOrders->insertOrder(new Order(false, "Bomb"));
    playerOrders->insertOrder(new Order(false, "Airlift"));
    p1->setMyOrdersList(playerOrders);

    cout << endl << *p1 << endl;

    // invalid orders
    Order* order1 = new Order(false, "Attack");
    p1->issueOrder(order1);

    // valid order
    Order* order2 = new Order(false, "Blockade");
    p1->issueOrder(order2);

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

    // Remove a territory and print which one was removed
    cout << "Removing territory: ";
    p1->removeTerritory(territory1);

    cout << "\nCopy Constructor \n";
    Player* p2 = new Player(*p1);

    cout << endl << *p2 << endl;


   cout << "---------------------- End of Player -------------- \n";

    // Release memory
    delete p1;
    p1 = nullptr;
    delete gameMap;
    gameMap = nullptr;
    
}
