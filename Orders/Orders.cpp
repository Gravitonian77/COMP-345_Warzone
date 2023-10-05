//
// Created by Kimsay Kong on 2023-09-27.
//
#include "Orders.h"
#include <iostream>

using namespace std;

//default constructor
Order::Order() {
    executed = false;
    effect = "";
    next = nullptr;
}

//copy constructor
Order::Order(const Order &order) {
    executed = order.executed;
    effect = order.effect;
    next = order.next;
}

//parameterized constructor
Order::Order(string description) {
    executed = false;
    effect = description;
    next = nullptr;
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

//set next method
void Order::setNext(Order *next) {
    this->next = next;
}

//get next method
Order *Order::getNext() {
    return next;
}

//default constructor
OrdersList::OrdersList() {
    head = nullptr;
}

//copy constructor
OrdersList::OrdersList(const OrdersList &ordersList) {
    head = ordersList.head;
}

//set head method
void OrdersList::setHead(Order *head) {
    this->head = head;
}

//get head method
Order *OrdersList::getHead() {
    return head;
}

//insert order method
void OrdersList::insertOrder(Order *order) {
    if (head == nullptr) {
        head = order;
    } else {
        Order *temp = head;
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }
        temp->setNext(order);
    }
}

//remove order method
void OrdersList::removeOrder(int position) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        Order *temp = head;
        Order *prev = nullptr;
        int count = 0;
        while (temp != nullptr) {
            if (count == position) {
                if (prev == nullptr) {
                    head = temp->getNext();
                } else {
                    prev->setNext(temp->getNext());
                }
                temp->setNext(nullptr);
                delete temp;
                break;
            }
            prev = temp;
            temp = temp->getNext();
            count++;
        }
    }
}

//move order method
void OrdersList::moveOrder(int currentPosition, int newPosition) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        Order *temp = head;
        Order *prev = nullptr;
        int count = 0;
        while (temp != nullptr) {
            if (count == currentPosition) {
                if (prev == nullptr) {
                    head = temp->getNext();
                } else {
                    prev->setNext(temp->getNext());
                }
                temp->setNext(nullptr);
                break;
            }
            prev = temp;
            temp = temp->getNext();
            count++;
        }
        if (temp == nullptr) {
            cout << "Position not found" << endl;
        } else {
            if (newPosition == 0) {
                temp->setNext(head);
                head = temp;
            } else {
                Order *temp2 = head;
                Order *prev2 = nullptr;
                int count2 = 0;
                while (temp2 != nullptr) {
                    if (count2 == newPosition) {
                        if (prev2 == nullptr) {
                            head = temp;
                        } else {
                            prev2->setNext(temp);
                        }
                        temp->setNext(temp2);
                        break;
                    }
                    prev2 = temp2;
                    temp2 = temp2->getNext();
                    count2++;
                }
                if (temp2 == nullptr) {
                    cout << "Position not found" << endl;
                }
            }
        }
    }
}

//print orders method
void OrdersList::printOrders() {
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        Order *temp = head;
        while (temp != nullptr) {
            cout << temp->getName() << " ";
            temp = temp->getNext();
        }
    }
}

//default constructor
Deploy::Deploy() : Order() {
    territory = "";
    armies = 0;
}

//copy constructor
Deploy::Deploy(const Deploy &deploy) : Order(deploy) {
    territory = deploy.territory;
    armies = deploy.armies;
}

//parameterized constructor
Deploy::Deploy(string territory, int armies) : Order("Deploy") {
    this->territory = territory;
    this->armies = armies;
}

//validate method
bool Deploy::validate() {
    return true;
}

//execute method
void Deploy::execute() {
    Order::execute();
}

//get name method
string Deploy::getName() {
    return name;
}

//get territory method
string Deploy::getTerritory() {
    return territory;
}

//get armies method
int Deploy::getArmies() {
    return armies;
}

//set territory method
void Deploy::setTerritory(string territory) {
    this->territory = territory;
}

//set armies method
void Deploy::setArmies(int armies) {
    this->armies = armies;
}

//default constructor
Advance::Advance() : Order() {
    source = "";
    target = "";
    armies = 0;
}

//copy constructor
Advance::Advance(const Advance &advance) : Order(advance) {
    source = advance.source;
    target = advance.target;
    armies = advance.armies;
}

//parameterized constructor
Advance::Advance(string source, string target, int armies) : Order("Advance") {
    this->source = source;
    this->target = target;
    this->armies = armies;
}

//validate method
bool Advance::validate() {
    return true;
}

//execute method
void Advance::execute() {
    Order::execute();
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

//get armies method
int Advance::getArmies() {
    return armies;
}

//set source method
void Advance::setSource(string source) {
    this->source = source;
}

//default constructor
Bomb::Bomb() : Order() {
    territory = "";
}

//copy constructor
Bomb::Bomb(const Bomb &bomb) : Order(bomb) {
    territory = bomb.territory;
}

//parameterized constructor
Bomb::Bomb(string territory) : Order("Bomb") {
    this->territory = territory;
}

//validate method
bool Bomb::validate() {
    return true;
}

//execute method
void Bomb::execute() {
    Order::execute();
}

//get name method
string Bomb::getName() {
    return name;
}

//get territory method
string Bomb::getTerritory() {
    return territory;
}

//set territory method
void Bomb::setTerritory(string territory) {
    this->territory = territory;
}

//default constructor
Blockade::Blockade() : Order() {
    territory = "";
}

//copy constructor
Blockade::Blockade(const Blockade &blockade) : Order(blockade) {
    territory = blockade.territory;
}

//parameterized constructor
Blockade::Blockade(string territory) : Order("Blockade") {
    this->territory = territory;
}

//validate method
bool Blockade::validate() {
    return true;
}

//execute method
void Blockade::execute() {
    Order::execute();
}

//get name method
string Blockade::getName() {
    return name;
}

//get territory method
string Blockade::getTerritory() {
    return territory;
}

//set territory method
void Blockade::setTerritory(string territory) {
    this->territory = territory;
}

//default constructor
Airlift::Airlift() : Order() {
    source = "";
    target = "";
    armies = 0;
}

//copy constructor
Airlift::Airlift(const Airlift &airlift) : Order(airlift) {
    source = airlift.source;
    target = airlift.target;
    armies = airlift.armies;
}

//parameterized constructor
Airlift::Airlift(string source, string target, int armies) : Order("Airlift") {
    this->source = source;
    this->target = target;
    this->armies = armies;
}

//validate method
bool Airlift::validate() {
    return true;
}

//execute method
void Airlift::execute() {
    Order::execute();
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

//get armies method
int Airlift::getArmies() {
    return armies;
}

//default constructor
Negotiate::Negotiate() : Order() {
    player1 = "";
    player2 = "";
}

//copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate) {
    player1 = negotiate.player1;
    player2 = negotiate.player2;
}

//parameterized constructor
Negotiate::Negotiate(string player1, string player2) : Order("Negotiate") {
    this->player1 = player1;
    this->player2 = player2;
}

//validate method
bool Negotiate::validate() {
    return true;
}

//execute method
void Negotiate::execute() {
    Order::execute();
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