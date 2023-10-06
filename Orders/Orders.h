//
// Created by Kimsay Kong on 2023-09-27.
//

#ifndef WARZONE_ORDERS_H
#define WARZONE_ORDERS_H

#include <iostream>
#include <vector>

using namespace std;


class Order {
private:
    bool executed;
    string effect;
public:
    //default constructor
    Order();

    //copy constructor
    Order(const Order &order);

    //parameterized constructor
    Order(bool executed, string effect);

    virtual bool validate();
    virtual void execute();
    virtual string getName();
    void setExecuted(bool executed);
    bool getExecuted();
    void setEffect(string effect);
    string getEffect();
};

class OrdersList {
private:
    string player;
public:
    vector<Order*> ordersList;
    //default constructor
    OrdersList();

    //copy constructor
    OrdersList(const OrdersList &ordersList);

    //parameterized constructor
    OrdersList(string player, vector<Order *>& ordersList);

    //set player
    void setPlayer(string player);

    //get player
    string getPlayer();

    //get ordersList
    vector<Order*> getOrdersList();

    //set ordersList
    void setOrdersList(vector<Order*>& ordersList);

    //inserts an order at the end of the list
    void insertOrder(Order *order);

    // move order from current position to new position
    void moveOrder(int currentPosition, int newPosition);

    // remove order at position
    void removeOrder(int offset);

    void printOrders();
};

/* Deploy Class */

class Deploy : public Order {
private:
    string name;
    string territory;
    string player;
    int armies;
public:
    //default constructor
    Deploy();

    //copy constructor
    Deploy(const Deploy &deploy);

    //parameterized constructor
    Deploy(string player, string territory, int armies);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get territory
    string getTerritory();

    //get playerOrder
    string getPlayer();

    //get armies
    int getArmies();

    //set player
    void setPlayer(string player);

    //set territory
    void setTerritory(string territory);

    //set armies
    void setArmies(int armies);

    //set names
    void setName(string name);

};

/* Advance Class */
class Advance : public Order {
private:
    string name;
    string player;
    string source;
    string target;
    int armies;
public:
    //default constructor
    Advance();

    //copy constructor
    Advance(const Advance &advance);

    //parameterized constructor
    Advance(string player, string source, string target, int armies);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    string getPlayer();

    //get source
    string getSource();

    //get target
    string getTarget();

    //get armies
    int getArmies();

    //set playerOrder
    void setPlayer(string playerOrder);

    //set source
    void setSource(string source);

    //set target
    void setTarget(string target);

    //set armies
    void setArmies(int armies);

    //set names
    void setName(string name);
};

/* Bomb Class*/
class Bomb : public Order {
private:
    string name;
    string player;
    string territory;
public:
    //default constructor
    Bomb();

    //copy constructor
    Bomb(const Bomb &bomb);

    //parameterized constructor
    Bomb(string player, string territory);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    string getPlayer();

    //get territory
    string getTerritory();

    //set playerOrder
    void setPlayer(string playerOrder);

    //set territory
    void setTerritory(string territory);

    //set names
    void setName(string name);

};

/* Blockade Class*/

class Blockade : public Order {
private:
    string name;
    string player;
    string territory;
public:
    //default constructor
    Blockade();

    //copy constructor
    Blockade(const Blockade &blockade);

    //parameterized constructor
    Blockade(string player, string territory);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    string getPlayer();

    //get territory
    string getTerritory();

    //set player
    void setPlayer(string playerOrder);

    //set territory
    void setTerritory(string territory);

    //set names
    void setName(string name);

};

class Airlift : public Order {
private:
    string name;
    string player;
    string source;
    string target;
    int armies;
public:
    //default constructor
    Airlift();

    //copy constructor
    Airlift(const Airlift &airlift);

    //parameterized constructor
    Airlift(string player, string source, string target, int armies);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    string getPlayer();

    //get source
    string getSource();

    //get target
    string getTarget();

    //get armies
    int getArmies();

    //set playerOrder
    void setPlayer(string playerOrder);

    //set source
    void setSource(string source);

    //set target
    void setTarget(string target);

    //set armies
    void setArmies(int armies);

    //set names
    void setName(string name);
};

class Negotiate : public Order {
private:
    string name;
    string player1;
    string player2;
public:
    //default constructor
    Negotiate();

    //copy constructor
    Negotiate(const Negotiate &negotiate);

    //parameterized constructor
    Negotiate(string player1, string player2);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get player1
    string getPlayer1();

    //get player2
    string getPlayer2();

    //set player1
    void setPlayer1(string player1);

    //set player2
    void setPlayer2(string player2);

    //set names
    void setName(string name);

};

#endif //WARZONE_ORDERS_H
