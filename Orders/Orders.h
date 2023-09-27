//
// Created by Kimsay Kong on 2023-09-27.
//

#ifndef WARZONE_ORDERS_H
#define WARZONE_ORDERS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Order {
public:
    string description;
    Order *next;

    //default constructor
    Order() {
        description = "";
        next = NULL;
    }

    //parameterized constructor
    Order(string description) {
        this->description = description;
        next = NULL;
    }
    bool validate(string description);

    string execute(string description);
};

class OrdersList {
    Order *head;
public:
    OrdersList(){
        head = NULL;
    }

    //inserts an order at the end of the list
    void insertOrder(string descirption);

    void moveOrder(int currentPosition, int newPosition);

    void removeOrder(int nodeOffset);

    void printOrders();
};

#endif //WARZONE_ORDERS_H
