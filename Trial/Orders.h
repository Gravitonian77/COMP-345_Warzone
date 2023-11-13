//
// Created by Kimsay Kong on 2023-09-27.
//

#ifndef WARZONE_ORDERS_H
#define WARZONE_ORDERS_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Map.h"

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

    // stream insertion operator
    friend ostream& operator<<(ostream& out, const Order& order);
};

class OrdersList {
private:
    Player* player;
public:
    vector<Order*> ordersList;
    //default constructor
    OrdersList();

    //copy constructor
    OrdersList(const OrdersList &ordersList);

    //parameterized constructor
    OrdersList(Player* player, vector<Order *>& ordersList);

    // stream insertion operator
    friend ostream& operator<<(ostream& out, const OrdersList& ordersList);

    //set player
    void setPlayer(Player player);

    //get player
    Player getPlayer();

    //get ordersList
    vector<Order*> getOrdersList();

    //set ordersList
    void setOrdersList(vector<Order*>& ordersList);

    //inserts an order at the end of the list
    void insertOrder(Order* order);

    // move order from current position to new position
    void moveOrder(int currentPosition, int newPosition);

    // remove order at position
    void removeOrder(int offset);
    void removeOrder(Order* order);

    void printOrders();
};

/* Deploy Class */
class Deploy : public Order {
private:
    string name = "Deploy";
    Territory* target;
    Player* player;
    int numberOfArmies;
public:
    //default constructor
    Deploy();

    //copy constructor
    Deploy(const Deploy &deploy);

    //parameterized constructor
    Deploy(Player* player, Territory* target, int armies);

    //destructors
    ~Deploy();

    // stream insertion operator
    friend ostream& operator<<(ostream& out, const Deploy& deploy);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer();

    //get target
    Territory* getTarget();

    //get armies
    int getArmies();

    // get executed
    //bool getExecuted();

    //set playerOrder
    void setPlayer(Player* playerOrder);

    //set target
    void setTarget(Territory* target);

    //set armies
    void setArmies(int armies);

    //set names
    void setName(string name);
};

/* Advance Class */
class Advance : public Order {
private:
    string name = "Advance";
    Player* player;
    Territory* source;
    Territory* target;
    int numberOfArmies;
public:
    //default constructor
    Advance();

    //copy constructor
    Advance(const Advance &advance);

    //parameterized constructor
    Advance(Player* player, Territory* source, Territory* target, int numberOfArmies);

    //destructors
    ~Advance();

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Advance& advance);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer();

    //get source
    Territory* getSource();

    //get target
    Territory* getTarget();

    //get armies
    int getArmies();

    //set playerOrder
    void setPlayer(Player* playerOrder);

    //set source
    void setSource(Territory* source);

    //set target
    void setTarget(Territory* target);

    //set armies
    void setArmies(int armies);

    //set names
    void setName(string name);
};

/* Bomb Class*/
class Bomb : public Order {
private:
    string name="Bomb";
    Player* player;
    Territory* target;
public:
    //default constructor
    Bomb();

    //copy constructor
    Bomb(const Bomb &bomb);

    //parameterized constructor
    Bomb(Player* player, Territory* target);

    //destructors
    ~Bomb();

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Bomb& bomb);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer();

    //get target
    Territory* getTarget();

    //set playerOrder
    void setPlayer(Player* playerOrder);

    //set target
    void setTarget(Territory* target);

    //set names
    void setName(string name);

};

/* Blockade Class*/

class Blockade : public Order {
private:
    string name = "Blockade";
    Player* player;
    Territory* target;
public:
    //default constructor
    Blockade();

    //copy constructor
    Blockade(const Blockade &blockade);

    //parameterized constructor
    Blockade(Player* player, Territory* target);

    //destructors
    ~Blockade();

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Blockade& blockade);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer();

    //get target
    Territory* getTarget();

    //set playerOrder
    void setPlayer(Player* playerOrder);

    //set target
    void setTarget(Territory* target);

    //set names
    void setName(string name);
};

class Airlift : public Order {
private:
    string name = "Airlift";
    Player* player;
    Territory* source;
    Territory* target;
    int NumberOfArmies;
public:
    //default constructor
    Airlift();

    //copy constructor
    Airlift(const Airlift &airlift);

    //parameterized constructor
    Airlift(Player* player, Territory* source, Territory* target, int numberOfArmies);

    //destructors
    ~Airlift();

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Airlift& airlift);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer();

    //get source
    Territory* getSource();

    //get target
    Territory* getTarget();

    //get armies
    int getNumberOfArmies();

    //set playerOrder
    void setPlayer(Player* playerOrder);

    //set source
    void setSource(Territory* source);

    //set target
    void setTarget(Territory* target);

    //set armies
    void setNumberOfArmies(int armies);

    //set names
    void setName(string name);
};

class Negotiate : public Order {
private:
    string name = "Negotiate";
    Player* player1;
    Player* player2;
public:
    //default constructor
    Negotiate();

    //copy constructor
    Negotiate(const Negotiate &negotiate);

    //parameterized constructor
    Negotiate(Player* player1, Player* player2);

    //destructors
    ~Negotiate();

    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Negotiate& negotiate);

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get playerOrder
    Player* getPlayer1();

    //get playerOrder
    Player* getPlayer2();

    //set player1
    void setPlayer1(Player* player1);

    //set player2
    void setPlayer2(Player* player2);

    //set names
    void setName(string name);
};

#endif //WARZONE_ORDERS_H
