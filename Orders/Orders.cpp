//
// Created by Kimsay Kong on 2023-09-27.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "Orders.h"

using namespace std;

/*---------------------------------Implementation of Orders Class---------------------------------*/
//default constructor
Order::Order() {
    executed = false;
    effect = "";
}

//copy constructor
Order::Order(const Order &order) {
    executed = order.executed;
    effect = order.effect;
}

//parameterized constructor
Order::Order(bool executed, string effect) {
    this->executed = executed;
    this->effect = effect;
}

//validate method
bool Order::validate() {
    return true;
}

//execute method
void Order::execute() {
    executed = true;
}

//get name method
string Order::getName() {
    return "Order";
}

//set executed method
void Order::setExecuted(bool executed) {
    this->executed = executed;
}

//get executed method
bool Order::getExecuted() {
    return executed;
}

//set effect method
void Order::setEffect(string effect) {
    this->effect = effect;
}

//get effect method
string Order::getEffect() {
    return effect;
}


/*---------------------------------Implementation of OrdersList Class--------------------------------- */
//copy constructor
OrdersList::OrdersList(const OrdersList &ordersList) {
    player = ordersList.player;
    this->ordersList = ordersList.ordersList;
}

//parameterized constructor
OrdersList::OrdersList(Player* player, vector<Order *> &ordersList) {
    this->player = player;
    this->ordersList = ordersList;
}

//get ordersList method
vector<Order *> OrdersList::getOrdersList() {
    return ordersList;
}

//set ordersList method
void OrdersList::setOrdersList(vector<Order *> &ordersList) {
    this->ordersList = ordersList;
}

//insert order method
void OrdersList::insertOrder(Order *order) {
    ordersList.push_back(order);
}

//move order method
void OrdersList::moveOrder(int currentPosition, int newPosition) {
    Order *temp = ordersList[currentPosition];
    ordersList.erase(ordersList.begin() + currentPosition);
    ordersList.insert(ordersList.begin() + newPosition, temp);
}

//remove order method
void OrdersList::removeOrder(int offset) {
    ordersList.erase(ordersList.begin() + offset);
}

void OrdersList::removeOrder(Order* order){
    ordersList.erase(remove(ordersList.begin(),ordersList.end(),order),ordersList.end());
}

//print orders method
void OrdersList::printOrders() {
    for (int i = 0; i < ordersList.size(); i++) {
        cout << ordersList[i]->getName() << " ";
    }
    cout << endl;
}

/*---------------------------------Implementation of Deploy Class---------------------------------*/
//default constructor
Deploy::Deploy() {
    name = "Deploy";
    target = nullptr;
    player = nullptr;
    numberOfArmies = 0;
}

//copy constructor
Deploy::Deploy(const Deploy &deploy) {
    name = deploy.name;
    target = deploy.target;
    player = deploy.player;
    numberOfArmies = deploy.numberOfArmies;
}

//parameterized constructor
Deploy::Deploy(Player *player, Territory *target, int numberOfArmies) {
    this -> name = "Deploy";
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

// destructor
Deploy::~Deploy() {
    delete target;
    delete player;
}

//stream insertion operator overloading for Deploy class
ostream &operator<<(ostream &out, const Deploy &deploy) {
    out << deploy.name << " " << deploy.target << " " << deploy.player << " " << deploy.numberOfArmies;
    return out;
}

//validate method
bool Deploy::validate() {
    // If the target territory does not belong to the player that issued the order,
    // the order is invalid.
    if (target->getOwner() != player){
        cout<< "Deploy order is invalid because the target territory does not belong to the player" << endl;
        return false;
    }
    cout<< "Deploy order is valid" << endl;
    return true;
}

//execute method
void Deploy::execute() {
    if (validate()){
        // If the target territory belongs to the player that issued the deploy order,
        // the selected number of army units is added to the number of army units on that territory
        player->setReinforcementPool(player->getReinforcementPool()-this->numberOfArmies);
        int numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
        target->setNumberOfArmies(numberOfArmies);
        setExecuted(true);
        setEffect("Deploy order has been executed");
    }
}

//get name
string Deploy::getName() {
    return name;
}

//get player
Player *Deploy::getPlayer() {
    return player;
}

//get target
Territory *Deploy::getTarget() {
    return target;
}

//get armies
int Deploy::getArmies() {
    return numberOfArmies;
}

//set player
void Deploy::setPlayer(Player *player) {
    this->player = player;
}

//set target
void Deploy::setTarget(Territory *target) {
    this->target = target;
}

//set armies
void Deploy::setArmies(int armies) {
    this->numberOfArmies = armies;
}

//set name
void Deploy::setName(string name) {
    this->name = name;
}

/*---------------------------------Implementation of Advance Class---------------------------------*/
//default constructor
Advance::Advance() {
    name = "Advance";
    source = nullptr;
    target = nullptr;
    player = nullptr;
    numberOfArmies = 0;
}

//copy constructor
Advance::Advance(const Advance &advance) {
    name = advance.name;
    source = advance.source;
    target = advance.target;
    player = advance.player;
    numberOfArmies = advance.numberOfArmies;
}

//parameterized constructor
Advance::Advance(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Advance";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

// destructor
Advance::~Advance() {
    delete source;
    delete target;
    delete player;
}

//stream insertion operator overloading for Advance class
ostream &operator<<(ostream &out, const Advance &advance) {
    out << advance.name << " " << advance.source << " " << advance.target << " " << advance.player << " " << advance.numberOfArmies;
    return out;
}

//validate method
bool Advance::validate() {
    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if (source->getOwner() != player){
        cout<< "Advance order is invalid because the source territory does not belong to the player" << endl;
        return false;
    }

    //If the target territory is not adjacent to the source territory, the order is invalid.
    bool targetAdjacent = false;
    for (Territory* adjacentTerritory : source->getAdjacentTerritories()) {
        if (adjacentTerritory == target) {
            targetAdjacent = true;
            break;
        }
    }
    if (!targetAdjacent){
        cout<< "Advance order is invalid because the target territory is not adjacent to the source territory" << endl;
        return false;
    }


    cout<< "Advance order is valid" << endl;
    return true;

}

//execute method
void Advance::execute() {
    if (validate()){
        // If the source and target territory both belong to the player that issued the order,
        // the army units are moved from the source to the target territory.
        if(target->getOwner() == player && source->getOwner() == player){
            int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
            source->setNumberOfArmies(numberOfArmies);
            numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
            target->setNumberOfArmies(numberOfArmies);
            setExecuted(true);
            setEffect("Advance order has been executed");
        }
        //If the target territory belongs to another player than the player that issued
        // the advance order, an attack is simulated when the order is executed.
        // An attack is simulated by the following battle simulation mechanism:
        else if(source->getOwner() == player && target->getOwner()!=player){
            Player* enemy = target->getOwner();
            //Each attacking army unit involved has 60% chances of killing one defending army.
            //At the same time, each defending army unit has 70% chances of killing one attacking
            //army unit.
            int attackingArmy = this->numberOfArmies;
            int defendingArmy = target->getNumberOfArmies();
            int attackingArmyLost = 0;
            int defendingArmyLost = 0;
            for(int i = 0; i < attackingArmy; i++){
                int random = rand() % 100 + 1;
                if(random <= 60){
                    defendingArmyLost++;
                }
            }
            for(int i = 0; i < defendingArmy; i++){
                int random = rand() % 100 + 1;
                if(random <= 70){
                    attackingArmyLost++;
                }
            }
            //If the attacker loses all its army units, the attack fails and no army units are moved.
            if(attackingArmyLost == attackingArmy){
                setEffect("The advance call was not executed since the attacker loses all its army units\n");
                cout << getEffect() << endl;
            }
            //If the defender loses all its army units, the attack succeeds and the attacker moves all its army units to the conquered territory.
            else if(defendingArmyLost == defendingArmy){
                int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
                source->setNumberOfArmies(numberOfArmies);
                numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
                target->setNumberOfArmies(numberOfArmies);
                target->setPlayer(player);
                enemy->removeTerritory(target);
                player->addTerritory(target);
                setExecuted(true);
                setEffect("Advance order has been executed");
            }
            //If both players have army units left, the attack succeeds and the attacker moves the remaining army units to the conquered territory.
            else{
                int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
                source->setNumberOfArmies(numberOfArmies);
                numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
                target->setNumberOfArmies(numberOfArmies);
                target->setPlayer(player);
                enemy->removeTerritory(target);
                player->addTerritory(target);
                setExecuted(true);
                setEffect("Advance order has been executed");
            }
        }
        else{
            setEffect("The advance call was not executed since it was invalid\n");
            cout << getEffect() << endl;
        }
    }
}

//get name
string Advance::getName() {
    return name;
}

//get player
Player *Advance::getPlayer() {
    return player;
}

//get source
Territory *Advance::getSource() {
    return source;
}

//get target
Territory *Advance::getTarget() {
    return target;
}

//get armies
int Advance::getArmies() {
    return numberOfArmies;
}

//set player
void Advance::setPlayer(Player *player) {
    this->player = player;
}

//set source
void Advance::setSource(Territory *source) {
    this->source = source;
}

//set target
void Advance::setTarget(Territory *target) {
    this->target = target;
}

//set armies
void Advance::setArmies(int armies) {
    this->numberOfArmies = armies;
}

//set name
void Advance::setName(string name) {
    this->name = name;
}

/*---------------------------------Implementation of Bomb Class---------------------------------*/

//default constructor
Bomb::Bomb() {
    name = "Bomb";
    target = nullptr;
    player = nullptr;
}

//copy constructor
Bomb::Bomb(const Bomb &bomb) {
    name = bomb.name;
    target = bomb.target;
    player = bomb.player;
}

//parameterized constructor
Bomb::Bomb(Player *player, Territory *target) {
    this -> name = "Bomb";
    this -> target = target;
    this -> player = player;
}

// destructor
Bomb::~Bomb() {
    delete target;
    delete player;
}

//stream insertion operator overloading for Bomb class
ostream &operator<<(ostream &out, const Bomb &bomb) {
    out << bomb.name << " " << bomb.target << " " << bomb.player;
    return out;
}

//validate method
bool Bomb::validate() {
    // If the target belongs to the player that issued the order, the order is invalid.
    if (target->getOwner()== this->player)
    {
        cout<< "Bomb order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    // If the target territory is not adjacent to one of the territory owned by the
    // player issuing the order, then the order is invalid.
    bool targetAdjacent = false;
    for (Territory* adjacentTerritory : target->getAdjacentTerritories()) {
        if (adjacentTerritory->getOwner() == this->player) {
            targetAdjacent = true;
            break;
        }
    }
    if (!targetAdjacent){
        cout<< "Bomb order is invalid because the target territory is not adjacent to one of the territory owned by the player issuing the order" << endl;
        return false;
    }
    cout<< "Bomb order is valid" << endl;
    return true;
}

//execute method
void Bomb::execute() {
    if (validate()){
        // A bomb order targets a territory owned by another player than the one issuing the order. Its result is
        // to remove half of the army units from this territory.
        int numberOfArmies = target->getNumberOfArmies()/2;
        target->setNumberOfArmies(numberOfArmies);
        setExecuted(true);
        setEffect("Bomb order has been executed");
    }
}

//get name
string Bomb::getName() {
    return name;
}

//get player
Player *Bomb::getPlayer() {
    return player;
}

//get target
Territory *Bomb::getTarget() {
    return target;
}

//set player
void Bomb::setPlayer(Player *player) {
    this->player = player;
}

//set target
void Bomb::setTarget(Territory *target) {
    this->target = target;
}

//set name
void Bomb::setName(string name) {
    this->name = name;
}

/*---------------------------------Implementation of Blockade Class---------------------------------*/

//default constructor
Blockade::Blockade() {
    name = "Blockade";
    target = nullptr;
    player = nullptr;
}

//copy constructor
Blockade::Blockade(const Blockade &blockade) {
    name = blockade.name;
    target = blockade.target;
    player = blockade.player;
}

//parameterized constructor
Blockade::Blockade(Player *player, Territory *target) {
    this -> name = "Blockade";
    this -> target = target;
    this -> player = player;
}

// destructor
Blockade::~Blockade() {
    delete target;
    delete player;
}

//stream insertion operator overloading for Blockade class
ostream &operator<<(ostream &out, const Blockade &blockade) {
    out << blockade.name << " " << blockade.target << " " << blockade.player;
    return out;
}

//validate method
bool Blockade::validate() {
    //If the target territory belongs to an enemy player, the order is declared invalid.
    if (target->getOwner() != this->player){
        cout<< "Blockade order is invalid because the target territory does not belongs to the player" << endl;
        return false;
    }

    cout<< "Blockade order is valid" << endl;
    return true;
}

//execute method
void Blockade::execute() {
    if (validate()){
        //A blockade order targets a territory that belongs to the player issuing the order.
        //Its effect is to double the number of army units on the territory and to transfer
        //the ownership of the territory to the Neutral player.
        int numberOfArmies = target->getNumberOfArmies()*2;
        target->setNumberOfArmies(numberOfArmies);
        target->setPlayer(nullptr);
        setExecuted(true);
        setEffect("Blockade order has been executed");
    }
}

//get name
string Blockade::getName() {
    return name;
}

//get player
Player *Blockade::getPlayer() {
    return player;
}

//get target
Territory *Blockade::getTarget() {
    return target;
}

//set player
void Blockade::setPlayer(Player *player) {
    this->player = player;
}

//set target
void Blockade::setTarget(Territory *target) {
    this->target = target;
}

//set name
void Blockade::setName(string name) {
    this->name = name;
}

/*---------------------------------Implementation of Airlift Class---------------------------------*/

//default constructor
Airlift::Airlift() {
    name = "Airlift";
    source = nullptr;
    target = nullptr;
    player = nullptr;
    NumberOfArmies = 0;
}

//copy constructor
Airlift::Airlift(const Airlift &airlift) {
    name = airlift.name;
    source = airlift.source;
    target = airlift.target;
    player = airlift.player;
    NumberOfArmies = airlift.NumberOfArmies;
}

//parameterized constructor
Airlift::Airlift(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Airlift";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> NumberOfArmies = numberOfArmies;
}

// destructor
Airlift::~Airlift() {
    delete source;
    delete target;
    delete player;
}

//stream insertion operator overloading for Airlift class
ostream &operator<<(ostream &out, const Airlift &airlift) {
    out << airlift.name << " " << airlift.source << " " << airlift.target << " " << airlift.player << " " << airlift.NumberOfArmies;
    return out;
}

//validate method
bool Airlift::validate() {
    // If the source or target territory does not belong to the player that issued the order, the order is invalid.
    if (source->getOwner() != player || target->getOwner() != player){
        cout<< "Airlift order is invalid because the source or target territory does not belong to the player" << endl;
        return false;
    }
    cout<< "Airlift order is valid" << endl;
    return true;
}

//execute method
void Airlift::execute() {
    if (validate()){
        // If both the source and target territories belong to the player that issue the airlift
        // order, then the selected number of army units is moved from the source to the target territory.
        if (target->getOwner()==this->player && source->getOwner() == this->player){
            int numberOfArmies = getSource()->getNumberOfArmies()-getNumberOfArmies();
            getSource()->setNumberOfArmies(numberOfArmies);
            getTarget()->setNumberOfArmies(getNumberOfArmies());
            getTarget()->setPlayer(getPlayer());
            setExecuted(true);
            setEffect("Airlift order has been executed");
        }
    }
}

//get name
string Airlift::getName() {
    return name;
}

//get player
Player *Airlift::getPlayer() {
    return player;
}

//get source
Territory *Airlift::getSource() {
    return source;
}

//get target
Territory *Airlift::getTarget() {
    return target;
}

//get armies
int Airlift::getNumberOfArmies() {
    return NumberOfArmies;
}

//set player
void Airlift::setPlayer(Player *player) {
    this->player = player;
}

//set source
void Airlift::setSource(Territory *source) {
    this->source = source;
}

//set target
void Airlift::setTarget(Territory *target) {
    this->target = target;
}

//set armies
void Airlift::setNumberOfArmies(int armies) {
    this->NumberOfArmies = armies;
}

//set name
void Airlift::setName(string name) {
    this->name = name;
}

/*---------------------------------Implementation of Negotiate Class---------------------------------*/

//default constructor
Negotiate::Negotiate() {
    name = "Negotiate";
    sourcePlayer = nullptr;
    targetPlayer = nullptr;
}

//copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) {
    name = negotiate.name;
    sourcePlayer = negotiate.sourcePlayer;
    targetPlayer = negotiate.targetPlayer;
}

//parameterized constructor
Negotiate::Negotiate(Player *sourcePlayer, Player *targetPlayer) {
    this->name = "Negotiate";
    this->sourcePlayer = sourcePlayer;
    this->targetPlayer = targetPlayer;
}

// destructor
Negotiate::~Negotiate() {
    delete sourcePlayer;
    delete targetPlayer;
}

//stream insertion operator overloading for Negotiate class
ostream &operator<<(ostream &out, const Negotiate &negotiate) {
    out << negotiate.name << " " << negotiate.sourcePlayer << " " << negotiate.targetPlayer;
    return out;
}

//validate method
bool Negotiate::validate() {
    // If the target is the player issuing the order, then the order is invalid.
    if (this->targetPlayer == this->sourcePlayer){
        cout<< "Negotiate order is invalid because the target is the player issuing the order" << endl;
        return false;
    }
    cout<< "Negotiate order is valid" << endl;
    return true;
}

//execute method
void Negotiate::execute() {
    if (validate()){
        // If the target is an enemy player, then the effect is that any attack that may be
        // declared between territories of the player issuing the negotiate order and the
        // target player will result in an invalid order.
        setExecuted(true);
        setEffect("Negotiate order has been executed");
    }
}

//get name
string Negotiate::getName() {
    return name;
}

//get player
Player *Negotiate::getSourcePlayer() {
    return sourcePlayer;
}

//get target
Player *Negotiate::getTargetPlayer() {
    return targetPlayer;
}

//set player
void Negotiate::setSourcePlayer(Player *sourcePlayer) {
    this->sourcePlayer = sourcePlayer;
}

//set target
void Negotiate::setTargetPlayer(Player *targetPlayer) {
    this->targetPlayer = targetPlayer;
}

//set name
void Negotiate::setName(string name) {
    this->name = name;
}

/*---------------------------free function to test orders lists--------------------------------*/
void testOrdersLists(){
    cout << "------------------------" << endl;
    cout << "Testing OrdersList class" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    // load map



}





