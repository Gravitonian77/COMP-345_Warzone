//
// Created by Kimsay Kong on 2023-09-27.
//
#include "Orders.cpp"
using namespace std;

int main() {

    //create orders
    Deploy *deploy = new Deploy("Deploy",1);
    Advance *advance = new Advance("Canada","USA",2);
    Bomb *bomb = new Bomb("USA");
    Blockade *blockade = new Blockade("USA");
    Airlift *airlift = new Airlift("Canada","USA",3);
    Negotiate *negotiate = new Negotiate("Canada","USA");

    //create orders list
    OrdersList *ordersList = new OrdersList();

    //insert orders to orders list
    ordersList->insertOrder(deploy);
    ordersList->insertOrder(advance);
    ordersList->insertOrder(bomb);
    ordersList->insertOrder(blockade);
    ordersList->insertOrder(airlift);
    ordersList->insertOrder(negotiate);

    //print orders list
    cout << "Orders List:" << " ";
    ordersList->printOrders();
    cout << endl;

    //move orders
    cout << "Move orders From position 1 to 3:" << " ";
    ordersList->moveOrder(1,3);
    ordersList->printOrders();
    cout << endl;

    //remove orders
    cout << "Remove orders at position 0:" << " ";
    ordersList->removeOrder(0);
    ordersList->printOrders();
    cout << endl;

}