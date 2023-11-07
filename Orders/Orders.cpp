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

//print orders method
void OrdersList::printOrders() {
    for (int i = 0; i < ordersList.size(); i++) {
        cout << ordersList[i]->getName() << " ";
    }
    cout << endl;
}

/* Implementation of Deploy Class */

// stream insertion operator
ostream& operator<<(ostream& out, const Deploy& deploy) {
    out << "Deploy Order Executed: " << (deploy.getExecuted ? "Yes" : "No") << ", Effect: " << deploy.effect;
    return out;
}

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
        int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
        source->setNumberOfArmies(numberOfArmies);
        target->setNumberOfArmies(this->numberOfArmies);
        target->setPlayer(player);
        setExecuted(true);
        setEffect("Advance order has been executed");
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
    if (target==nullptr){
        cout<< "Bomb order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Bomb order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (target->getOwner() == player){
        cout<< "Bomb order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    cout<< "Bomb order is valid" << endl;
    return true;
}

//execute method
void Bomb::execute() {
    if (validate()){
        target->setNumberOfArmies(0);
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
    if (target==nullptr){
        cout<< "Blockade order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Blockade order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (target->getOwner() != player){
        cout<< "Blockade order is invalid because the target territory does not belong to the player" << endl;
        return false;
    }

    cout<< "Blockade order is valid" << endl;
    return true;
}

//execute method
void Blockade::execute() {
    if (validate()){
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
    if (getTarget()==nullptr){
        cout<< "Airlift order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getSource()==nullptr){
        cout<< "Airlift order is invalid because the source territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Airlift order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the source territory belongs to the player
    if (getSource()->getOwner() != getPlayer()){
        cout<< "Airlift order is invalid because the source territory does not belong to the player" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (getTarget()->getOwner() == getPlayer()){
        cout<< "Airlift order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    // check if the source territory is adjacent to the target territory
    bool isAdjacent = false;
    for (Territory* adjacentTerritory : getSource()->getAdjacentTerritories()) {
        if (adjacentTerritory == getTarget()) {
            isAdjacent = true;
            break;
        }
    }

    if (!isAdjacent){
        cout<< "Airlift order is invalid because the source territory is not adjacent to the target territory" << endl;
        return false;
    }

    // check if the number of armies is greater than 0
    if (getNumberOfArmies() <= 0) {
        cout << "Airlift order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }

    // check if the number of armies is greater than the number of armies in the source territory
    if (getNumberOfArmies() > getSource()->getNumberOfArmies()) {
        cout << "Airlift order is invalid because the number of armies is greater than the number of armies in the source territory" << endl;
        return false;
    }

    cout<< "Airlift order is valid" << endl;
    return true;
}

//execute method
void Airlift::execute() {
    if (validate()){
        int numberOfArmies = getSource()->getNumberOfArmies()-getNumberOfArmies();
        getSource()->setNumberOfArmies(numberOfArmies);
        getTarget()->setNumberOfArmies(getNumberOfArmies());
        getTarget()->setPlayer(getPlayer());
        setExecuted(true);
        setEffect("Airlift order has been executed");
    }
}

/* Implementation of Negotiate Class */

//parameterized constructor
Negotiate::Negotiate(Player *player1, Player *player2) {
    this -> name = "Negotiate";
    this -> player1 = player1;
    this -> player2 = player2;
}

//validate method
bool Negotiate::validate() {
    if (player1==nullptr){
        cout<< "Negotiate order is invalid because the player1 is null" << endl;
        return false;
    }
    if (player2==nullptr){
        cout<< "Negotiate order is invalid because the player2 is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Negotiate order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the player1 is the same as player2
    if (player1 == player2){
        cout<< "Negotiate order is invalid because the player1 is the same as player2" << endl;
        return false;
    }

    cout<< "Negotiate order is valid" << endl;
    return true;
}

//execute method
void Negotiate::execute() {
    if (validate()){
        setExecuted(true);
        setEffect("Negotiate order has been executed");
    }
}

/* free function to test orders lists */
//void testOrdersLists(){
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
//}





