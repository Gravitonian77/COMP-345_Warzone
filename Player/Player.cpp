#include "Player.h"
#include <iostream>
using namespace std;

#include "Map.cpp"
#include "Orders.cpp"
#include "Cards.cpp"

int Player::nextPlayerNumber = 0;

// Constructors
Player::Player() : playerNumber(nextPlayerNumber++) {}


Player::Player(vector<Territory*> territories, OrdersList* ordersList, Hand* hand)
    : playerNumber(nextPlayerNumber++),
      myTerritories(territories),
      myOrdersList(ordersList),
      myHand(hand) 
{}

Player::Player(const Player& player)
    : playerNumber(nextPlayerNumber++), 
      myTerritories(player.myTerritories),
      myOrdersList(player.myOrdersList), 
      reinforcementPool(player.reinforcementPool), 
      myHand(player.myHand) 
{}


// Destructor
Player::~Player() {
    for (auto& territory : myTerritories) {
        if (territory != nullptr) {
            delete territory;
            territory = nullptr;
        }
    }
    myTerritories.clear();

    if (myOrdersList != nullptr) {
        delete myOrdersList;
        myOrdersList = nullptr;
    }

    if (myHand != nullptr) {
        delete myHand;
        myHand = nullptr;
    }
}



// Accessors
int Player::getPlayerNumber() const {
    return playerNumber;
}

int Player::getReinforcementPool() const{
    return reinforcementPool;
}

vector<Territory*> Player::getMyTerritories() const {
    return myTerritories;
}

OrdersList* Player::getMyOrdersList() const{
    return myOrdersList;
}

Hand* Player::getMyHand() const {
    return myHand;
}

GameEngine* Player::getMyGameEngine() const{
    return myGameEngine;
}

// Mutators
void Player::setReinforcementPool(int pool){
    reinforcementPool = pool;
}

void  Player::setMyTerritories(vector<Territory*>& newTerritories){
    myTerritories = newTerritories;
}

void Player::setMyOrdersList(OrdersList* newOrdersList){
    myOrdersList = newOrdersList;
}

void Player::setMyHand(Hand *newHand){
    myHand = newHand;
}

void Player::setGameEngine(GameEngine* newGameEngine){
    myGameEngine = newGameEngine;
}

// Owns territory
bool Player::ownsTerritory(string territoryName){
    for (Territory* t : myTerritories) {
        if (t->getTerritoryName() == territoryName) {return true;}
    }
    return false;
}

// Add territory
void Player::addTerritory(Territory* territory) {
    myTerritories.push_back(territory);
    territory->setPlayer(this);
    cout << "Territory " << territory->getTerritoryName() << " was assigned to player " << getPlayerNumber() << "\n";
}


// Remove territory
void Player::removeTerritory(Territory* territory) {
    auto it = std::find(myTerritories.begin(), myTerritories.end(), territory);
    if (it != myTerritories.end()) {
        // Territory found, print its name
        cout << "Territory " << (*it)->getTerritoryName() << " was removed from player " << getPlayerNumber() << "\n";
        // Remove the territory
        myTerritories.erase(it);
    } else {
        // Territory not found, print a different message if needed
        cout << "Territory not found in player's territory list.\n";
    }
}


Player& Player::operator=(const Player& other) {
    if (this != &other) {
        // Deep copy of hand and orders list
        Hand* newHand = nullptr;
        OrdersList* newOrdersList = nullptr;
        if (other.myHand) {
            newHand = new Hand(*(other.myHand));
        }
        if (other.myOrdersList) {
            newOrdersList = new OrdersList(*(other.myOrdersList));
        }
        // Clean up existing resources
        delete myHand;
        delete myOrdersList;

        vector<Territory*> newTerritories;
        for (Territory* territory : other.myTerritories) {
            newTerritories.push_back(new Territory(*territory)); // Deep copy each territory
        }
        // Delete the old territories if you have ownership
        for (Territory* territory : myTerritories) {
            delete territory;
        }
        myHand = newHand;
        myOrdersList = newOrdersList;
        myTerritories = newTerritories;
        reinforcementPool = other.reinforcementPool;
    }
    return *this;
}

//Stream Insertion Operator
ostream& operator<<(ostream& out, const Player& player) {
    out << "Player Number: " << player.getPlayerNumber() << endl;

    out << "Territories: ";
    for (const Territory* territory : player.getMyTerritories()) {
        out << territory->getTerritoryName() << ", ";
    }
    out << endl;

    out << "Cards: ";
    for (const Card* card : player.getMyHand()->getCards()) {
        out << card->getType() << ", ";
    }
    out << endl;

    out << "Orders: ";
    for (Order* order : player.getMyOrdersList()->getOrdersList()) {
        out << order->getEffect() << ", ";
    }
    out << endl;

    return out;
}
// Methods Required
vector<Territory*> Player::toDefend() {
    vector<Territory*> territoriesToDefend;
    // Iterate through the player's territories
    for (Territory* myTerritory : myTerritories) {
        bool needsDefending = false;
        // Check each adjacent territory
        for (Territory* adjacentTerritory : myTerritory->getAdjacentTerritories()) {
            // If the adjacent territory does not belong to the player, it needs to be defended
            if (adjacentTerritory->getOwner() != myTerritory->getOwner() && adjacentTerritory->getOwner() != nullptr) {
                needsDefending = true;
                break; // No need to check other adjacent territories for this territory
            }
        }
        // If this territory needs defending, add it to the list
        if (needsDefending) {
            territoriesToDefend.push_back(myTerritory);
        }
    }
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesToAttack;
    // Iterate through the player's territories
    for (Territory* myTerritory : myTerritories) {
        // Check each adjacent territory
        for (Territory* adjacentTerritory : myTerritory->getAdjacentTerritories()) {
            // If the adjacent territory is owned by a different player, it can be attacked
            if (adjacentTerritory->getOwner() != this) {
                territoriesToAttack.push_back(adjacentTerritory);
            }
        }
    }
    return territoriesToAttack;
}

void Player::issueOrder(){
    
    Hand* playerHand = this->getMyHand();
	OrdersList* playerOrders = this->getMyOrdersList();
    GameEngine* gameEng = this->getMyGameEngine();
    
    // Start of issuing orders
    cout << "\nIssuing orders for player " << getPlayerNumber() << ":" << endl;
    cout << "-----------------------------------------------------\n" << endl;
    
    cout << "--- Deploy Phase Starts ---" << endl;

    //Territories to defend
    cout << "\nTerritories to defend: " << endl;
    for (Territory* territory : getMyTerritories()) {
        cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies"<< endl;
    }
    cout << endl;

    // continue deploying until reinforcement pool is empty
    while (getReinforcementPool() > 0) {

        // Size of player's reinforcement pool
		cout << "Player " << getPlayerNumber() << "'s has reinforcement pool of " << getReinforcementPool() << endl << endl;

        // Prompt the user to choose territory to defend
		cout << "Enter the number of your territory you want to deploy armies to: ";
		string territorytoDeploy;
		cin >> territorytoDeploy;
		cout << endl;

        // If player owns territory to deploy at, then deploy
        if (ownsTerritory(territorytoDeploy)) {

			// number of armies to deploy
			cout << "Enter number of armies you want to deploy at territory: " << territorytoDeploy;
			int armiesToDeploy;
			cin >> armiesToDeploy;
			cout << endl;

            // Assume user enters good number
            // Add a deploy order to the player's list of orders            
            myOrdersList->insertOrder(new Deploy(this, gameEng->getMap()->getTerritoryByName(territorytoDeploy), armiesToDeploy));
            
            // Sets the reinforcement pool with whatever is left after the user's input
            setReinforcementPool(getReinforcementPool() - armiesToDeploy);
            cout << armiesToDeploy << " armies were deployed to territory "<< territorytoDeploy  << endl;
            
        }
        // Player does not own territory to deploy at
		else {
			cout << "The territory to deploy at"<< territorytoDeploy << " does not belong to you." << endl;
		}

    }

    cout << "--- Deploy Phase Ends ---" << endl;
    cout << "\n--- Advance Phase Starts ---" << endl;

    // Ask player if he wants to advance
	cout << "\nDo you want to issue advance orders? " << endl
	<< "Enter \"yes\" if you want to advance; otherwise, advance phase ends. ";

    string input;
	cin >> input;
	cout << endl;

    // player enters "y"
    while (input == "yes") {

		// Player can either defend his territories or attack enemies
		cout << "Please enter 1 or 2" << endl;
		cout << "1 - Move your armies from their territories to defend another adjacent territory? " << endl;
		cout << "2 - Move your armies from their territories to attack an adjacent enemy territory? " << endl;
		int option;
		cin >> option;
		cout << endl;

        if (option == 1){

            // Reminder of Territories to defend
            cout << "\nTerritories to defend: " << endl;
            for (Territory* territory : toDefend()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies"<< endl;
            }      
            cout << endl;

            // Enter source territory
            cout << "Enter the number of the source territory: ";
            string source;
            cin >> source;
            cout << endl;

            // Verify if source entered belongs to player
            if (ownsTerritory(source)){
                // Enter target territory
                cout << "Enter the number of the target territory: ";
                string target;
                cin >> target;
                cout << endl;

                // Verify is target entered belongs to player
                if (ownsTerritory(target)) {
                    
                    // Enter armies to move to target
 					cout << "Enter the number of armies to move to target: ";
					int armiestoTarget;
					cin >> armiestoTarget;
					cout << endl;

                    // pointers for source and target territories
                    Territory* sourceTerr = gameEng->getMap()->getTerritoryByName(source);
                    Territory* targetTerr = gameEng->getMap()->getTerritoryByName(target);

                    // Validate if source territory has enough army units to move to target
                    if (armiestoTarget <= sourceTerr->getNumberOfArmies()){
                        cout<< "Moving " << armiestoTarget << " army units from territory" <<sourceTerr->getTerritoryName() << " to  territory. "
                        << targetTerr->getTerritoryName() << endl;

                        // Add to players' orderlist
                        playerOrders->insertOrder(new Advance(this, sourceTerr, targetTerr, armiestoTarget));
                    }
                    // armiesToTarget is larger than armies available in source
                    else{
                        cout << "You entered an invalid number. You only have " << sourceTerr->getNumberOfArmies() << "army units avilable in territory " << sourceTerr->getTerritoryName();
                    }
                }
                else{
                    cout << "The target territory "<< target << " does not belong to you." << endl;
                }
            }
			else {
				cout << "The source territory "<< source << " does not belong to you." << endl;
			}
        }
        else if (option == 2){
            // Reminder of Territories to defend
            cout << "\nTerritories to defend: " << endl;
            for (Territory* territory : toDefend()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies."<< endl;
            }      
            cout << endl;

            // Reminder of Territories to attack
            cout << "\nTerritories to attack: " << endl;
            for (Territory* territory : toAttack()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies."<< endl;
            }      
            cout << endl;

            // Enter source territory for attack
			cout << "Enter the number of the source territory for attack: ";
			string sourceForAttack;
			cin >> sourceForAttack;
			cout << endl;

            // Validate that player owns source
            if (ownsTerritory(sourceForAttack)){

                cout << "Enter the number of the target territory: ";
                string targetForAttack;
                cin >> targetForAttack;
                cout << endl;

                // pointers for source and target territories
                Territory* sourceTerrForAttack = gameEng->getMap()->getTerritoryByName(sourceForAttack);
                Territory* targetTerrForAttack = gameEng->getMap()->getTerritoryByName(targetForAttack);

                // Validate if targetTerr is adjacent to any of player's territories
                bool targetisAdjacent;
                for (auto it : toAttack()) {
				if (it == targetTerrForAttack) {
					targetisAdjacent = true;
					}
				}

				if (targetisAdjacent){
					cout << "Enter the number of armies to move to target: ";;
					int armiesToTargetTerr;
					cin >> armiesToTargetTerr;
					cout << endl;
                    if (armiesToTargetTerr <= sourceTerrForAttack->getNumberOfArmies()){
                        cout<< "Moving " << armiesToTargetTerr << " army units from territory" <<sourceTerrForAttack->getTerritoryName() << " to  territory "
                        << targetTerrForAttack->getTerritoryName() << endl;

                        // Add to players' orderlist
                        playerOrders->insertOrder(new Advance(this, sourceTerrForAttack, targetTerrForAttack, armiesToTargetTerr));
                    }
                    else{
                        cout << "You entered an invalid number. You only have " << sourceTerrForAttack->getNumberOfArmies() << "army units avilable in territory " << sourceTerrForAttack->getTerritoryName();
                    }
                }
                else{
                     cout << "The target territory "<< targetTerrForAttack->getTerritoryName() << " cannot be attacked because it is not adjacent." << endl;
                }
            }
            else{
                cout << "The source territory "<< sourceForAttack << " does not belong to you." << endl;
            }
         }
         // Player did not enter 1 or 2
         else{
            cout << "You entered an incorrect option. You can only choose option 1 or 2.";
         }
        // Ask player if he wants to advance
	    cout << "Do you want to issue advance orders?" << endl
	    << "Enter \"yes\" if you want to advance; otherwise, advance phase ends. ";
        cin >> input;
        cout << endl;
    }
    cout << "\n--- Advance Phase Ends ---" << endl;
    cout << "\n--- Card Phase Starts ---" << endl;
 
    int cardsInHand = playerHand->getCards().size();
    // Confirm if player has cards
    if (cardsInHand > 0){
        // list cards
        cout << "Cards in hand" << endl;
        for(int i=0; i < cardsInHand; i++){
            cout << "Index " << i << " has card of type " << playerHand->getCards().at(i)->getCardTypeName() << endl;
        }
        // Prompt which card to use
        cout << "Enter the index of the card to use ";
        int cardInd;
        cin >> cardInd;
        cout << endl;

        // validate correct index was entered; otherwise prompt user again until correct index entered
        while(cardInd < 0 || cardInd >= cardsInHand){
            cout << "Wrong card index! You can only choose from 0 to " << cardsInHand - 1;
            cin >> cardInd;
            cout << endl;
        }
        // Pointer for the card
        Card* cardPoint = playerHand->getCards().at(cardInd);
        
        string cardName = cardPoint->getCardTypeName();

		// Cases for each type of card to be played and its required input
		if (cardName == "Bomb") {
			cout << "You chose BOMB card " << endl;
            cout << "Please enter the name(number) of territory you want to BOMB from the list below: " << endl;

			// Territories to Attack
			cout << "\nTerritories that can be attacked:" << endl;
			for (auto it : toAttack()) {
				cout << "Territory " << it->getTerritoryName() << " has an army of " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Prompt for enemy territory name(number)
			string enemyTerritory;
			cin >> enemyTerritory;
			cout << endl;

			// pointer for enemy territoty
            Territory* enemyTerr = gameEng->getMap()->getTerritoryByName(enemyTerritory);

			cardPoint->play();
			cout << "BOMB order has been issued!";
		}
		else if (cardName == "Reinforcement") {
			cout << "You chose REINFORCEMENT card. Reinforcement order has been issued. " << endl;
			cardPoint->play();
		}
		else if (cardName == "Blockade") {
			cout << "You chose BLOCKADE card. " << endl;
            cout << "Please enter the territory number to blockade from the list below: " << endl;

			// Territories to defend
            cout << "\nTerritories to defend: " << endl;
            for (Territory* territory : toDefend()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies."<< endl;
            }      
            cout << endl;

			// Enter blockade territory
			string territoryBlockade;
			cin >> territoryBlockade;
			cout << endl;

			// Pointer for blockade territory
			Territory* terrBlockade = gameEng->getMap()->getTerritoryByName(territoryBlockade);
			cardPoint->play();

			cout << "Blockade order issued!";
		}
		else if (cardName == "Airlift") {
			cout << "You chose AIRLIFT card" << endl;
            cout << "Please enter the territory number that the airlift will orginate from in the list below " << endl;

			// Territories to defend
            cout << "\nTerritories to defend: " << endl;
            for (Territory* territory : toDefend()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies"<< endl;
            }      
            cout << endl;

			// Enter source for airlift
			string airliftTerritory1;
			cin >> airliftTerritory1;
			cout << endl;

			// Pointer for source of airlift
			Territory* airliftTerr1 = gameEng->getMap()->getTerritoryByName(airliftTerritory1);

			cout <<"Please enter the territory number that the airlift will go to from the list below. " << endl;

			// Territories to defend
            cout << "\nTerritories to defend: " << endl;
            for (Territory* territory : toDefend()) {
                cout <<"Territory " << territory->getTerritoryName() << " has " << territory->getNumberOfArmies() << " armies"<< endl;
            }      
            cout << endl;

			// Enter target for airlift
			string airliftTerritory2;
			cin >> airliftTerritory2;
			cout << "Enter the number of armies you want to airlift: " << endl;
			int armiesToAirlift;
            cin >> armiesToAirlift;
			cout << endl;

            // Pointer for target of airlift
			Territory* airliftTerr2 = gameEng->getMap()->getTerritoryByName(airliftTerritory2);

			cardPoint->play();
			cout << "Airlift order issued!";
		}
		else if (cardName == "Diplomacy") { 
			cout << "You chose DIPLOMACY card" << endl;
			cout << "With which player number do you want to negotiate? Select the player number from list below:" << endl;

			// Show list of players
			cout << "\nList of players in the game:" << endl;
			for (int i = 0; i < gameEng->getPlayers().size(); i++) {
				cout << "Player " << i << endl;
                //cout << "Player " << myGameEngine->players.at(i)->getPlayerNumber() << endl;
			}
			cout << endl;

			// Enter other player's number
			int playerNumber;
			cin >> playerNumber;
			cout << endl;

            // Pointer for second player
			Player* secondPlayer = gameEng->getPlayers().at(playerNumber);

			cardPoint->play();
			cout << "Diplomacy order issued!";
		}
    }
    else{
        cout<< "You do not have any cards. Card Phase is over.";
    }
    cout << "\n--- Card Phase Ends ---" << endl;
    cout << "\nPlayer " << getPlayerNumber() << " turn is over" << endl;
} // issueOrder


// void testPlayers2(){

//     cout << "---------------------- Start of Player -------------- \n";
//     // Create the map 
//     Map* gameMap = mapLoader::createMapFromConquestFile("Canada.map");

//    // GameEngine* gameEngine = new GameEngine();
//    // gameEngine->setMap (gameMap);

//     // Players
//     Player* p1 = new Player();
//     OrdersList* playerOrders = new OrdersList();
//     Hand* playerHand = new Hand();

//     Player* p2 = new Player();
//     OrdersList* playerOrders2 = new OrdersList();
//     Hand* playerHand2 = new Hand();

//     //p1->setGameEngine(gameEngine);

//     // add territories
//     Territory* territory1 = gameMap->getContinent()[0]->getTerritories()[0]; // 1,548,116,Northern Islands,2,12
//     Territory* territory2 = gameMap->getContinent()[0]->getTerritories()[1]; // 2,510,124,Northern Islands,1,3
//     Territory* territory3 = gameMap->getContinent()[0]->getTerritories()[2]; // 1,548,116,Northern Islands,2,12
//     Territory* territory4 = gameMap->getContinent()[0]->getTerritories()[3]; // 2,510,124,Northern Islands,1,3
//     p1->addTerritory(territory1);
//     p1->addTerritory(territory2);
//     p2->addTerritory(territory3);
//     p2->addTerritory(territory4);
   
//     // // add hand
//     playerHand->addCard(new Card(CardType::BOMB));
//     playerHand->addCard(new Card(CardType::BLOCKADE));
//     p1->setMyHand(playerHand);

//     playerHand2->addCard(new Card(CardType::BOMB));
//     playerHand2->addCard(new Card(CardType::BLOCKADE));
//     p2->setMyHand(playerHand2);

//     cout << "hello"; // WORKS
//     // // Add order
//     p1->issueOrder();
//     p2->issueOrder();

// }
