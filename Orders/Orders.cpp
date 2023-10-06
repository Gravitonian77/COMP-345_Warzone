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


//default constructor
OrdersList::OrdersList() {
    player = "";
    this->ordersList = vector<Order *>();
}

//copy constructor
OrdersList::OrdersList(const OrdersList &ordersList) {
    player = ordersList.player;
    this->ordersList = ordersList.ordersList;
}

//parameterized constructor
OrdersList::OrdersList(string player, vector<Order *> &ordersList) {
    this->player = player;
    this->ordersList = ordersList;
}

//set player method
void OrdersList::setPlayer(string player) {
    this->player = player;
}

//get player method
string OrdersList::getPlayer() {
    return player;
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

//default constructor
Deploy::Deploy() {
    this -> name = "Deploy";
    this -> territory = "";
    this -> player = "";
    this -> armies = 0;
}

//copy constructor
Deploy::Deploy(const Deploy &deploy) {
    this -> name = deploy.name;
    this -> territory = deploy.territory;
    this -> player = deploy.player;
    this -> armies = deploy.armies;
}

//parameterized constructor
Deploy::Deploy(string territory, string player, int armies) {
    this -> name = "Deploy";
    this -> territory = territory;
    this -> player = player;
    this -> armies = armies;
}

//validate method
bool Deploy::validate() {
    if (player!= "" && territory != "" && armies > 0){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Deploy::execute() {
    if (validate()){
        setExecuted(true);
    }
    else{
        setExecuted(false);
    }
}

//get name method
string Deploy::getName() {
    return name;
}

//get territory method
string Deploy::getTerritory() {
    return territory;
}

//get player method
string Deploy::getPlayer() {
    return player;
}

//get armies method
int Deploy::getArmies() {
    return armies;
}

//set territory method
void Deploy::setTerritory(string territory) {
    this -> territory = territory;
}

//set player method
void Deploy::setPlayer(string player) {
    this -> player = player;
}

//set armies method
void Deploy::setArmies(int armies) {
    this -> armies = armies;
}

//set name method
void Deploy::setName(string name) {
    this -> name = name;
}

/* Implementation of Advance Class */

//default constructor
Advance::Advance() {
    this -> name = "Advance";
    this -> source = "";
    this -> target = "";
    this -> player = "";
    this -> armies = 0;
}

//copy constructor
Advance::Advance(const Advance &advance) {
    this -> name = advance.name;
    this -> source = advance.source;
    this -> target = advance.target;
    this -> player = advance.player;
    this -> armies = advance.armies;
}

//parameterized constructor
Advance::Advance(string source, string target, string player, int armies) {
    this -> name = "Advance";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> armies = armies;
}

//validate method
bool Advance::validate() {
    if (player!= "" && source != "" && target != "" && armies > 0){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Advance::execute() {
    if (validate()){
        setExecuted(true);
    }
    else{
        setExecuted(false);
    }
}

//get name method
string Advance::getName() {
    return name;
}

//get source method
string Advance::getSource() {
    return source;
}

//get target method
string Advance::getTarget() {
    return target;
}

//get player method
string Advance::getPlayer() {
    return player;
}

//get armies method
int Advance::getArmies() {
    return armies;
}

//set source method
void Advance::setSource(string source) {
    this -> source = source;
}

//set target method
void Advance::setTarget(string target) {
    this -> target = target;
}

//set player method
void Advance::setPlayer(string player) {
    this -> player = player;
}

//set armies method
void Advance::setArmies(int armies) {
    this -> armies = armies;
}

//set name method
void Advance::setName(string name) {
    this -> name = name;
}

/* Implementation of Bomb Class */

//default constructor
Bomb::Bomb() {
    this -> name = "Bomb";
    this -> territory = "";
    this -> player = "";
}

//copy constructor
Bomb::Bomb(const Bomb &bomb) {
    this -> name = bomb.name;
    this -> territory = bomb.territory;
    this -> player = bomb.player;
}

//parameterized constructor
Bomb::Bomb(string territory, string player) {
    this -> name = "Bomb";
    this -> territory = territory;
    this -> player = player;
}

//validate method
bool Bomb::validate() {
    if (player!= "" && territory != ""){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Bomb::execute() {
    if (validate()){
        setExecuted(true);
    }
    else{
        setExecuted(false);
    }
}

//get name method
string Bomb::getName() {
    return name;
}

//get territory method
string Bomb::getTerritory() {
    return territory;
}

//get player method
string Bomb::getPlayer() {
    return player;
}

//set territory method
void Bomb::setTerritory(string territory) {
    this -> territory = territory;
}

//set player method
void Bomb::setPlayer(string player) {
    this -> player = player;
}

//set name method
void Bomb::setName(string name) {
    this -> name = name;
}

/* Implementation of Blockade Class */

//default constructor
Blockade::Blockade() {
    this -> name = "Blockade";
    this -> territory = "";
    this -> player = "";
}

//copy constructor
Blockade::Blockade(const Blockade &blockade) {
    this -> name = blockade.name;
    this -> territory = blockade.territory;
    this -> player = blockade.player;
}

//parameterized constructor
Blockade::Blockade(string territory, string player) {
    this -> name = "Blockade";
    this -> territory = territory;
    this -> player = player;
}

//validate method
bool Blockade::validate() {
    if (player!= "" && territory != ""){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Blockade::execute() {
    if (validate()){
        setExecuted(true);
    }
    else{
        setExecuted(false);
    }
}

//get name method
string Blockade::getName() {
    return name;
}

//get territory method
string Blockade::getTerritory() {
    return territory;
}

//get player method
string Blockade::getPlayer() {
    return player;
}

//set territory method
void Blockade::setTerritory(string territory) {
    this -> territory = territory;
}

//set player method
void Blockade::setPlayer(string player) {
    this -> player = player;
}

//set name method
void Blockade::setName(string name) {
    this -> name = name;
}

/* Implementation of Airlift Class */

//default constructor
Airlift::Airlift() {
    this -> name = "Airlift";
    this -> source = "";
    this -> target = "";
    this -> player = "";
    this -> armies = 0;
}

//copy constructor
Airlift::Airlift(const Airlift &airlift) {
    this -> name = airlift.name;
    this -> source = airlift.source;
    this -> target = airlift.target;
    this -> player = airlift.player;
    this -> armies = airlift.armies;
}

//parameterized constructor
Airlift::Airlift(string source, string target, string player, int armies) {
    this -> name = "Airlift";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> armies = armies;
}

//validate method
bool Airlift::validate() {
    if (player!= "" && source != "" && target != "" && armies > 0){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Airlift::execute() {
    if (validate()){
        setExecuted(true);
    }
    else{
        setExecuted(false);
    }
}

//get name method
string Airlift::getName() {
    return name;
}

//get source method
string Airlift::getSource() {
    return source;
}

//get target method
string Airlift::getTarget() {
    return target;
}

//get player method
string Airlift::getPlayer() {
    return player;
}

//get armies method
int Airlift::getArmies() {
    return armies;
}

//set source method
void Airlift::setSource(string source) {
    this -> source = source;
}

//set target method
void Airlift::setTarget(string target) {
    this -> target = target;
}

//set player method
void Airlift::setPlayer(string player) {
    this -> player = player;
}

//set armies method
void Airlift::setArmies(int armies) {
    this -> armies = armies;
}

//set name method
void Airlift::setName(string name) {
    this -> name = name;
}

/* Implementation of Negotiate Class */

//default constructor
Negotiate::Negotiate() {
    this -> name = "Negotiate";
    this -> player1 = "";
    this -> player2 = "";
}

//copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) {
    this -> name = negotiate.name;
    this -> player1 = negotiate.player1;
    this -> player2 = negotiate.player2;
}

//parameterized constructor
Negotiate::Negotiate(string player1, string player2) {
    this -> name = "Negotiate";
    this -> player1 = player1;
    this -> player2 = player2;
}

//validate method
bool Negotiate::validate() {
    if (player1!= "" && player2 != ""){
        return true;
    }
    else{
        return false;
    }
}

//execute method
void Negotiate::execute() {
    if (validate()){
        setExecuted(true);
    }
    else {
        setExecuted(false);
    }
}

//get name method
string Negotiate::getName() {
    return name;
}

//get player1 method
string Negotiate::getPlayer1() {
    return player1;
}

//get player2 method
string Negotiate::getPlayer2() {
    return player2;
}

//set player1 method
void Negotiate::setPlayer1(string player1) {
    this -> player1 = player1;
}

//set player2 method
void Negotiate::setPlayer2(string player2) {
    this -> player2 = player2;
}

//set name method
void Negotiate::setName(string name) {
    this -> name = name;
}

/* free function to test orders lists */
void testOrdersLists(){
    cout << "------------------------" << endl;
    cout << "Testing OrdersList class" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    cout << "Creating an empty OrdersList" << endl;
    OrdersList *ordersList = new OrdersList();
    cout << endl;

    Order *order1 = new Deploy("territory1", "player1", 1);
    Order *order2 = new Advance("territory2", "territory3", "player2", 2);
    Order *order3 = new Bomb("territory4", "player3");
    Order *order4 = new Blockade("territory5", "player4");
    Order *order5 = new Airlift("territory6", "territory7", "player5", 3);
    Order *order6 = new Negotiate("player6", "player7");

    cout << "Validate the Deploy Class : ";
    cout << order1->validate();
    cout << endl;

    cout << "Execute the Deploy Class : " ;
    order1->execute();
    cout << order1->getExecuted();
    cout << endl;

    cout << "Validate the Advance Class : ";
    cout << order2->validate();
    cout << endl;

    cout << "Execute the Advance Class : " ;
    order2->execute();
    cout << order2->getExecuted();
    cout << endl;

    cout << "Validate the Bomb Class : ";
    cout << order3->validate();
    cout << endl;

    cout << "Execute the Bomb Class : " ;
    order3->execute();
    cout << order3->getExecuted();
    cout << endl;

    cout << "Validate the Blockade Class : ";
    cout << order4->validate();
    cout << endl;

    cout << "Execute the Blockade Class : " ;
    order4->execute();
    cout << order4->getExecuted();
    cout << endl;

    cout << "Validate the Airlift Class : ";
    cout << order5->validate();
    cout << endl;

    cout << "Execute the Airlift Class : " ;
    order5->execute();
    cout << order5->getExecuted();
    cout << endl;

    cout << "Validate the Negotiate Class : ";
    cout << order6->validate();
    cout << endl;

    cout << "Execute the Negotiate Class : " ;
    order6->execute();
    cout << order6->getExecuted();
    cout << endl;

    cout << "Inserting 6 orders into the OrdersList" << endl;
    ordersList->insertOrder(order1);
    ordersList->insertOrder(order2);
    ordersList->insertOrder(order3);
    ordersList->insertOrder(order4);
    ordersList->insertOrder(order5);
    ordersList->insertOrder(order6);
    cout << endl;

    cout << "Printing the OrdersList: ";
    ordersList->printOrders();
    cout << endl;
    cout << endl;

    cout << "Removing the second order from the OrdersList..." ;
    ordersList->removeOrder(1);
    cout << endl;
    cout << endl;

    cout << "Printing the OrdersList: ";
    ordersList->printOrders();
    cout << endl;
    cout << endl;

    cout << "Moving the first order to the third position in the OrdersList...";
    ordersList->moveOrder(1, 2);
    cout << endl;
    cout << endl;

    cout << "Printing the OrdersList: ";
    ordersList->printOrders();
    cout << endl;
    cout << endl;

    cout << "Delete second order to the OrdersList...";
    ordersList->removeOrder(1);
    cout << endl;
    cout << endl;

    cout << "Printing the OrdersList: ";
    ordersList->printOrders();
    cout << endl;
    cout << endl;

    cout << "Delete the whole OrdersList..." << endl;
    delete ordersList;
    cout << endl;
    cout << endl;
}





