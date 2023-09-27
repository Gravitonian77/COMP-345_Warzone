//
// Created by Kimsay Kong on 2023-09-27.
//
#include "Orders.h"
#include <iostream>

using namespace std;

// insert order node to orders list
void OrdersList::insertOrder(string description) {
    // Create the new order node
    Order *newOrder = new Order(description);

    // Assign to head if list is empty
    if (head == NULL) {
        head = newOrder;
        return;
    }

    // Find the last node
    Order *last = head;
    while (last->next != NULL) {
        last = last->next;
    }

    // Insert the new order
    last->next = newOrder;
}

// remove order node from orders list
void OrdersList::removeOrder(int nodeOffset){
    Order *temp1 = head, *temp2 = NULL;
    int ListLen = 0;
    if(head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    // Find the length of the list
    while(temp1 != NULL) {
        temp1 = temp1->next;
        ListLen++;
    }

    // Check if the node to be deleted is within the list
    if(nodeOffset > ListLen) {
        cout << "Node to be deleted is out of range" << endl;
        return;
    }

    // declare temp 1
    temp1 = head;

    //Deleting the first node
    if(nodeOffset == 1) {
        head = temp1->next;
        delete temp1;
        return;
    }

    // Traverse to the node at position nodeOffset
    for(int i = 0; i < nodeOffset - 1; i++) {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    // Change the pointers to delete the node
    temp2->next = temp1->next;
    delete temp1;
};

void OrdersList::moveOrder(int currentPosition, int newPosition){
    // Declare head node and temp node
    Order *temp1 = head, *temp2 = NULL;
    int ListLen = 0;
    // Check if the list is empty
    if(head == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    // Find the length of the list
    while(temp1 != NULL) {
        temp1 = temp1->next;
        ListLen++;
    }

    // check current position and new position is valid position
    if(currentPosition > ListLen || newPosition > ListLen) {
        cout << "Node to be moved is out of range" << endl;
        return;
    }

    // get the node at current position
    temp1 = head;
    for(int i = 0; i < currentPosition - 1; i++) {
        temp1 = temp1->next;
    }

    // get the node at new position
    temp2 = head;
    for(int i = 0; i < newPosition - 1; i++) {
        temp2 = temp2->next;
    }

    // switch the node
    string temp = temp1->description;
    temp1->description = temp2->description;
    temp2->description = temp;
}

void OrdersList::printOrders(){
    // Check if the list is empty
    if(head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    // Declare temp
    Order *temp = head;

    // Traverse the list and print the orders
    while(temp != NULL) {
        cout << temp->description << " ";
        temp = temp->next;
    }
}

bool Order::validate(string description) {
    // array of commands
    string commands[6] = {"Deploy", "Advance", "Bomb", "Blockade", "Airlift", "Negotiate"};
    //check if the command is valid
    for (int i = 0; i < 6; i++) {
        if (description == commands[i]) {
            return true;
        }
    }
    return false;
}

string Order::execute(string description) {
    return description;
}








