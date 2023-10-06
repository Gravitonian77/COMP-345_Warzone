// MainDriver.cpp
#include "Cards/Cards.h"
#include "Orders/Orders.cpp"
#include "Player/Player.cpp"
#include "Map/Map.cpp"


// testPlayers()
void testPlayers() {
    
    // Create the map using your mapLoader class
    Map* gameMap = mapLoader::createMapFromConquestFile("Canada.map");

    // Players
    Player* p1 = new Player();;
    p1->addTerritory(gameMap->getContinent()[0]->getTerritories()[0]); //1,548,116,Northern Islands,2,12
    p1->addTerritory(gameMap->getContinent()[0]->getTerritories()[1]); //2,510,124,Northern Islands,1,3

    Player* p2 = new Player();
    p2->addTerritory(gameMap->getContinent()[0]->getTerritories()[2]); //3,487,139,Northern Islands,2,4
    p2->addTerritory(gameMap->getContinent()[0]->getTerritories()[3]); //4,463,136,Northern Islands,3,5

    cout <<endl << *p1 << endl;
    cout << *p2 << endl;

    // P1 territories to attack
    cout <<"Player "<< p1->getPlayerNumber() << " can attack territories: "; 
    vector<Territory*> toAttackp1 = p1->ToAttack();
    for (Territory* t : toAttackp1) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // P1 territories to defend
    cout <<"Player "<< p1->getPlayerNumber() << " can defend territories: "; 
    vector<Territory*> toDefendp1 = p1->ToDefend();
    for (Territory* t : toDefendp1) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

     // P2 territories to attack
    cout <<"Player "<< p2->getPlayerNumber() << " can attack territories: ";
    vector<Territory*> toAttackp2 = p2->ToAttack();
    for (Territory* t : toAttackp2) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // P2 territories to defend
     cout <<"Player "<< p2->getPlayerNumber() << " can defend territories: ";
    vector<Territory*> toDefendp2 = p2->ToDefend();
    for (Territory* t : toDefendp2) {
        cout << t->getTerritoryName() << " ";
    }
    cout << endl;

    // Release memory
    delete p1;
    delete p2;
}
// Function to test the Card classes
void testCards() {
    Deck deck;
    Hand hand;

    // Draw cards from the deck and add them to the hand.
    for (int i = 0; i < 5; ++i) {
        Card drawnCard = deck.draw();
        hand.addCard(drawnCard);
    }

    // Play all cards in the hand.
    hand.playAll();
}

int main() {
    testPlayers();
    testCards();
    testOrdersLists();
    return 0;
}
