//
// Created by Kimsay Kong on 2023-09-27.
//

#ifndef WARZONE_ORDERS_H
#define WARZONE_ORDERS_H

#include <iostream>
using namespace std;

class Order {
private:
    bool executed = false;
    string effect;
    Order *next;
public:
    //default constructor
    Order();

    //copy constructor
    Order(const Order &order);

    //parameterized constructor
    Order(string description);

    //destructor
    ~Order() {
        delete next;
    }

    virtual bool validate();
    virtual void execute();
    virtual string getName();
    void setExecuted(bool executed);
    bool getExecuted();
    void setEffect(string effect);
    string getEffect();
    void setNext(Order *next);
    Order *getNext();
};

class OrdersList {
private:
    Order *head;
public:
    //default constructor
    OrdersList();

    //copy constructor
    OrdersList(const OrdersList &ordersList);

    //destructor
    ~OrdersList() {
        delete head;
    }

    //set head
    void setHead(Order *head);

    //get head
    Order *getHead();

    //inserts an order at the end of the list
    void insertOrder(Order *order);

    // move order from current position to new position
    void moveOrder(int currentPosition, int newPosition);

    // remove order at position
    void removeOrder(int offset);

    void printOrders();
};

class Deploy : public Order {
private:
    string name = "Deploy";
    string territory;
    int armies;
public:
    //default constructor
    Deploy();

    //copy constructor
    Deploy(const Deploy &deploy);

    //parameterized constructor
    Deploy(string territory, int armies);

    //destructor
    ~Deploy() {
        delete this;
    }

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get territory
    string getTerritory();

    //get armies
    int getArmies();

    //set territory
    void setTerritory(string territory);

    //set armies
    void setArmies(int armies);
};

class Advance : public Order {
private:
    string name = "Advance";
    string source;
    string target;
    int armies;
public:
    //default constructor
    Advance();

    //copy constructor
    Advance(const Advance &advance);

    //parameterized constructor
    Advance(string source, string target, int armies);

    //destructor
    ~Advance() {
        delete this;
    }

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get source
    string getSource();

    //get target
    string getTarget();

    //get armies
    int getArmies();

    //set source
    void setSource(string source);

    //set target
    void setTarget(string target);

    //set armies
    void setArmies(int armies);
};

class Bomb : public Order {
private:
    string name = "Bomb";
    string territory;
public:
    //default constructor
    Bomb();

    //copy constructor
    Bomb(const Bomb &bomb);

    //parameterized constructor
    Bomb(string territory);

    //destructor
    ~Bomb() {
        delete this;
    }

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get territory
    string getTerritory();

    //set territory
    void setTerritory(string territory);

};

class Blockade : public Order {
private:
    string name = "Blockade";
    string territory;
public:
    //default constructor
    Blockade();

    //copy constructor
    Blockade(const Blockade &blockade);

    //parameterized constructor
    Blockade(string territory);

    //destructor
    ~Blockade() {
        delete this;
    }

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get territory
    string getTerritory();

    //set territory
    void setTerritory(string territory);

};

class Airlift : public Order {
private:
    string name= "Airlift";
    string source;
    string target;
    int armies;
public:
    //default constructor
    Airlift();

    //copy constructor
    Airlift(const Airlift &airlift);

    //parameterized constructor
    Airlift(string source, string target, int armies);

    //destructor
    ~Airlift() {
        delete this;
    }

    //validate order
    bool validate();

    //execute order
    void execute();

    //get name
    string getName();

    //get source
    string getSource();

    //get target
    string getTarget();

    //get armies
    int getArmies();

    //set source
    void setSource(string source);

    //set target
    void setTarget(string target);

    //set armies
    void setArmies(int armies);
};

class Negotiate : public Order {
private:
    string name = "Negotiate";
    string player1;
    string player2;
public:
    //default constructor
    Negotiate();

    //copy constructor
    Negotiate(const Negotiate &negotiate);

    //parameterized constructor
    Negotiate(string player1, string player2);

    //destructor
    ~Negotiate() {
        delete this;
    }

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
};

#endif //WARZONE_ORDERS_H
