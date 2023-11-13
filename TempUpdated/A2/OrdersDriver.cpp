//
// Created by Kimsay Kong on 2023-09-27.
//

#include "Player.cpp"


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
    quebec->addAdjTerritory(ontario);

    // add adjacent territories to the Ontario territory
    ontario->addAdjTerritory(quebec);
    ontario->addAdjTerritory(alberta);

    // add adjacent territories to the Alberta territory
    alberta->addAdjTerritory(britishColumbia);
    alberta->addAdjTerritory(saskatchewan);

    // add adjacent territories to the British Columbia territory
    britishColumbia->addAdjTerritory(alberta);

    // add adjacent territories to the Manitoba territory
    manitoba->addAdjTerritory(ontario);
    manitoba->addAdjTerritory(saskatchewan);

    // add adjacent territories to the Saskatchewan territory
    saskatchewan->addAdjTerritory(alberta);
    saskatchewan->addAdjTerritory(manitoba);

    // Initialize the player

    Player* player1 = new Player();
    player1->addTerritory(quebec);
    player1->addTerritory(ontario);
    player1->setReinforcementPool(20);

    Player* player2 = new Player();
    player2->addTerritory(alberta);
    player2->addTerritory(britishColumbia);
    player2->setReinforcementPool(20);

    Player* player3 = new Player();
    player3->addTerritory(manitoba);
    player3->addTerritory(saskatchewan);
    player3->setReinforcementPool(10);

    // Initialize the orders
    Deploy* deploy1 = new Deploy(player1, quebec, 20);
    cout << "Testing the deploy order: " << endl;
    cout << "Player 1's reinforcement pool before excute: " << player1->getReinforcementPool() << endl;
    cout << "Quebec's army size before execute: " << quebec->getNumberOfArmies() << endl;
    deploy1->execute();
    cout << "Player 1's reinforcement pool: " << player1->getReinforcementPool() << endl;
    cout << "Quebec's army size: " << quebec->getNumberOfArmies() << endl;

    Deploy* deploy2 = new Deploy(player2, alberta, 20);
    deploy2->execute();

    // Testing on advance order
    Advance* advance1 = new Advance(player1, quebec, ontario, 10);
    cout << "Testing the advance order: " << endl;
    cout << "Quebec's army size before execute: " << quebec->getNumberOfArmies() << endl;
    cout << "Ontario's army size before execute: " << ontario->getNumberOfArmies() << endl;
    advance1->execute();
    cout << "Quebec's army size: " << quebec->getNumberOfArmies() << endl;
    cout << "Ontario's army size: " << ontario->getNumberOfArmies() << endl;

    // Testing on bomb order
    Bomb* bomb1 = new Bomb(player1, ontario);
    cout << "Testing the bomb order: " << endl;
    cout << "Ontario's army size before execute: " << ontario->getNumberOfArmies() << endl;
    bomb1->execute();
    cout << "Ontario's army size: " << ontario->getNumberOfArmies() << endl;

    Bomb* bomb2 = new Bomb(player1, alberta);
    cout << "Testing the bomb order: " << endl;
    cout << "Alberta's army size before execute: " << alberta->getNumberOfArmies() << endl;
    bomb2->execute();
    cout << "Alberta's army size: " << alberta->getNumberOfArmies() << endl;

    // Testing on blockade order
    Blockade* blockade1 = new Blockade(player1, ontario);
    cout << "Testing the blockade order: " << endl;
    cout << "Ontario's army size before execute: " << ontario->getNumberOfArmies() << endl;
    blockade1->execute();
    cout << "Ontario's army size: " << ontario->getNumberOfArmies() << endl;
    cout << "Ontario's owner: " << ontario->getOwner() << endl;

    // Testing on airlift order
    Airlift* airlift1 = new Airlift(player2, alberta, britishColumbia, 5);
    cout << "Testing the airlift order: " << endl;
    cout << "Alberta's army size before execute: " << alberta->getNumberOfArmies() << endl;
    cout << "British Columbia's army size before execute: " << britishColumbia->getNumberOfArmies() << endl;
    airlift1->execute();
    cout << "Alberta's army size: " << alberta->getNumberOfArmies() << endl;
    cout << "British Columbia's army size: " << britishColumbia->getNumberOfArmies() << endl;

    // Testing on negotiate order
    Negotiate* negotiate1 = new Negotiate(player1, player2);
    cout << "Testing the negotiate order: " << endl;
    cout << "Player 1's agreements before execute: " << player1->getAgreements().size() << endl;
    cout << "Player 2's agreements before execute: " << player2->getAgreements().size() << endl;
    negotiate1->execute();
    cout << "Player 1's agreements: " << player1->getAgreements().size() << endl;
    cout << "Player 2's agreements: " << player2->getAgreements().size() << endl;
}