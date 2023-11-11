//
// Created by Kimsay Kong on 2023-09-27.
//
#include <iostream>
#include "Orders.h"

using namespace std;

/* Implementation of Orders Class */

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


/* Implementation of OrdersList Class */

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

/* Implementation of Deploy Class */
//parameterized constructor
Deploy::Deploy(Player *player, Territory *target, int numberOfArmies) {
    this -> name = "Deploy";
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

//validate method
bool Deploy::validate() {
    if (target==nullptr){
        cout<< "Deploy order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Deploy order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the territory belongs to the player
    if (target->getOwner() != player){
        cout<< "Deploy order is invalid because the target territory does not belong to the player" << endl;
        return false;
    }

    // check if the number of armies is greater than 0
    if (numberOfArmies <= 0){
        cout<< "Deploy order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }
    cout<< "Deploy order is valid" << endl;
    return true;
}

//execute method
void Deploy::execute() {
    if (validate()){
        int numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
        target->setNumberOfArmies(numberOfArmies);
        setExecuted(true);
        setEffect("Deploy order has been executed");
    }
}

/* Implementation of Advance Class */
//parameterized constructor
Advance::Advance(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Advance";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

//validate method
bool Advance::validate() {
    if (source==nullptr){
        cout<< "Advance order is invalid because the source territory is null" << endl;
        return false;
    }
    if (target==nullptr){
        cout<< "Advance order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Advance order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the source territory belongs to the player
    if (source->getOwner() != player){
        cout<< "Advance order is invalid because the source territory does not belong to the player" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (target->getOwner() == player){
        cout<< "Advance order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    // check if the source territory is adjacent to the target territory
    bool isAdjacent = false;
    for (Territory* adjacentTerritory : source->getAdjacentTerritories()) {
        if (adjacentTerritory == target) {
            isAdjacent = true;
            break;
        }
    }
    if (!isAdjacent){
        cout<< "Advance order is invalid because the source territory is not adjacent to the target territory" << endl;
        return false;
    }

    // check if the number of armies is greater than 0
    if (numberOfArmies <= 0) {
        cout << "Advance order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }

    // check if the number of armies is greater than the number of armies in the source territory
    if (numberOfArmies > source->getNumberOfArmies()) {
        cout << "Advance order is invalid because the number of armies is greater than the number of armies in the source territory" << endl;
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

/* Implementation of Bomb Class */
//parameterized constructor
Bomb::Bomb(Player *player, Territory *target) {
    this -> name = "Bomb";
    this -> target = target;
    this -> player = player;
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

/* Implementation of Blockade Class */
//parameterized constructor
Blockade::Blockade(Player *player, Territory *target) {
    this -> name = "Blockade";
    this -> target = target;
    this -> player = player;
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

/* Implementation of Airlift Class */
//parameterized constructor
Airlift::Airlift(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Airlift";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> NumberOfArmies = numberOfArmies;
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

/* Implementation of Negotiate Class */
//parameterized constructor
Negotiate::Negotiate(Player *sourcePlayer, Player *targetPlayer) {
    this->name = "Negotiate";
    this->sourcePlayer = sourcePlayer;
    this->targetPlayer = targetPlayer;
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

/* free function to test orders lists */
void testOrdersLists(){
//    cout << "------------------------" << endl;
//    cout << "Testing OrdersList class" << endl;
//    cout << "------------------------" << endl;
//    cout << endl;
//
//    cout << "Creating an empty OrdersList" << endl;
//    OrdersList *ordersList = new OrdersList();
//    cout << endl;
//
//    Order *order1 = new Deploy("territory1", "player1", 1);
//    Order *order2 = new Advance("territory2", "territory3", "player2", 2);
//    Order *order3 = new Bomb("territory4", "player3");
//    Order *order4 = new Blockade("territory5", "player4");
//    Order *order5 = new Airlift("territory6", "territory7", "player5", 3);
//    Order *order6 = new Negotiate("player6", "player7");
//
//    cout << "Validate the Deploy Class : ";
//    cout << order1->validate();
//    cout << endl;
//
//    cout << "Execute the Deploy Class : " ;
//    order1->execute();
//    cout << order1->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Advance Class : ";
//    cout << order2->validate();
//    cout << endl;
//
//    cout << "Execute the Advance Class : " ;
//    order2->execute();
//    cout << order2->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Bomb Class : ";
//    cout << order3->validate();
//    cout << endl;
//
//    cout << "Execute the Bomb Class : " ;
//    order3->execute();
//    cout << order3->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Blockade Class : ";
//    cout << order4->validate();
//    cout << endl;
//
//    cout << "Execute the Blockade Class : " ;
//    order4->execute();
//    cout << order4->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Airlift Class : ";
//    cout << order5->validate();
//    cout << endl;
//
//    cout << "Execute the Airlift Class : " ;
//    order5->execute();
//    cout << order5->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Negotiate Class : ";
//    cout << order6->validate();
//    cout << endl;
//
//    cout << "Execute the Negotiate Class : " ;
//    order6->execute();
//    cout << order6->getExecuted();
//    cout << endl;
//
//    cout << "Inserting 6 orders into the OrdersList" << endl;
//    ordersList->insertOrder(order1);
//    ordersList->insertOrder(order2);
//    ordersList->insertOrder(order3);
//    ordersList->insertOrder(order4);
//    ordersList->insertOrder(order5);
//    ordersList->insertOrder(order6);
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Removing the second order from the OrdersList..." ;
//    ordersList->removeOrder(1);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Moving the first order to the third position in the OrdersList...";
//    ordersList->moveOrder(1, 2);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Delete second order to the OrdersList...";
//    ordersList->removeOrder(1);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Delete the whole OrdersList..." << endl;
//    delete ordersList;
//    cout << endl;
//    cout << endl;
}





