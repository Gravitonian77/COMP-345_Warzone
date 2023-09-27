//
// Created by Kimsay Kong on 2023-09-27.
//
#include "Orders.cpp"
using namespace std;

int main() {
    OrdersList ordersList;
    ordersList.insertOrder("Deploy");
    ordersList.insertOrder("Advance");
    ordersList.insertOrder("Bomb");
    ordersList.insertOrder("Blockade");
    ordersList.insertOrder("Airlift");
    ordersList.insertOrder("Negotiate");
    cout << "Orders List: " << endl;
    ordersList.printOrders();
    cout << endl;
    ordersList.removeOrder(3);
    cout << "Remove Node at position 3: " << endl;
    ordersList.printOrders();
    cout << endl;
    ordersList.moveOrder(1, 3);
    cout << "Move Node from position 1 to position 3: " << endl;
    ordersList.printOrders();
    cout << endl;
    return 0;
}