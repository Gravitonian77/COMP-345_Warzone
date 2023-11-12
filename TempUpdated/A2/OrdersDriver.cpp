//
// Created by Kimsay Kong on 2023-09-27.
//

#include "Orders.cpp"


using namespace std;

int main() {
    // Initialize the Quebec territory
    Territory* quebec = new Territory();
    quebec->setTerritoryName("Quebec");

    // Initialize the Ontario territory
    Territory* ontario = new Territory();
    ontario->setTerritoryName("Ontario");

    // Initialize the Alberta territory
    Territory* alberta = new Territory();
    alberta->setTerritoryName("Alberta");

    // Initialize the British Columbia territory
    Territory* britishColumbia = new Territory();
    britishColumbia->setTerritoryName("British Columbia");

    // Initialize the Manitoba territory
    Territory* manitoba = new Territory();
    manitoba->setTerritoryName("Manitoba");

    // Initialize the Saskatchewan territory
    Territory* saskatchewan = new Territory();
    saskatchewan->setTerritoryName("Saskatchewan");

    // add adjacent territories to the Quebec territory
    quebec->getAdjacentTerritories().push_back(ontario);

    // add adjacent territories to the Ontario territory
    ontario->getAdjacentTerritories().push_back(quebec);
    ontario->getAdjacentTerritories().push_back(manitoba);

    // add adjacent territories to the Alberta territory
    alberta->getAdjacentTerritories().push_back(britishColumbia);
    alberta->getAdjacentTerritories().push_back(saskatchewan);

    // add adjacent territories to the British Columbia territory
    britishColumbia->getAdjacentTerritories().push_back(alberta);

    // add adjacent territories to the Manitoba territory
    manitoba->getAdjacentTerritories().push_back(ontario);
    manitoba->getAdjacentTerritories().push_back(saskatchewan);

    // add adjacent territories to the Saskatchewan territory
    saskatchewan->getAdjacentTerritories().push_back(alberta);
    saskatchewan->getAdjacentTerritories().push_back(manitoba);

    // Initialize the player

    Player* player1 = new Player();
    player1->addTerritory(quebec);
    player1->addTerritory(ontario);
    player1->setReinforcementPool(10);

    Player* player2 = new Player();
    player2->addTerritory(alberta);
    player2->addTerritory(britishColumbia);
    player2->setReinforcementPool(10);

    Player* player3 = new Player();
    player3->addTerritory(manitoba);
    player3->addTerritory(saskatchewan);
    player3->setReinforcementPool(10);

    // Initialize the orders
    player1->setMyOrdersList(new OrdersList());
    player2->setMyOrdersList(new OrdersList());
    player3->setMyOrdersList(new OrdersList());

    // Deploy orders
    player1->getMyOrdersList()->insertOrder(new Deploy(player1, quebec, 5));
    player1->getMyOrdersList()->insertOrder(new Deploy(player1, ontario, 5));
    player2->getMyOrdersList()->insertOrder(new Deploy(player2, alberta, 5));
    player2->getMyOrdersList()->insertOrder(new Deploy(player2, britishColumbia, 5));
    player3->getMyOrdersList()->insertOrder(new Deploy(player3, manitoba, 5));
    player3->getMyOrdersList()->insertOrder(new Deploy(player3, saskatchewan, 5));

    // Advance orders
    player1->getMyOrdersList()->insertOrder(new Advance(player1, quebec, ontario, 2));
    player1->getMyOrdersList()->insertOrder(new Advance(player1, ontario, manitoba, 2));
}