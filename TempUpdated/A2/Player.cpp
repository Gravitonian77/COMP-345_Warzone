#include "Player.h"
#include <iostream>
using namespace std;

#include "Map.cpp"
#include "Orders.cpp"
#include "Cards.cpp"
#include "gameEngine.cpp" 

int Player::nextPlayerNumber = 0;

// Constructors
Player::Player() : playerNumber(nextPlayerNumber++),reinforcementPool(0) {}


Player::Player(vector<Territory*> territories, OrdersList* ordersList, Hand* hand)
    : playerNumber(nextPlayerNumber++),
      reinforcementPool(0),
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

// Returns the list of players that the player has agreements with
vector<Player*> Player::getAgreements() const {
    return agreements;
}

bool Player::hasAgreement(Player *player) const
{
    return std::find(agreements.begin(), agreements.end(), player) != agreements.end();
}

// add a player to the list of players that the player has agreements with
void Player::addAgreement(Player* player) {
    agreements.push_back(player);
}

// remove a player from the list of players that the player has agreements with
void Player::removeAgreement(Player* player) {
    auto it = std::find(agreements.begin(), agreements.end(), player);
    if (it != agreements.end()) {
        // Player found, print its number
        cout << "Player " << (*it)->getPlayerNumber() << " was removed from player " << getPlayerNumber() << "'s list of agreements.\n";
        // Remove the player
        agreements.erase(it);
    } else {
        // Player not found, print a different message if needed
        cout << "Player not found in player's list of agreements.\n";
    }
}


// Mutators
void Player::setReinforcementPool(int pool){
    reinforcementPool = pool;
}

void  Player::setMyTerritories(vector<Territory*>& newTerritories){
    myTerritories = newTerritories;
    for(Territory* t: newTerritories){
          cout << "Territory " << t->getTerritoryName() << " was assigned to player " << getPlayerNumber() << "\n";
    }
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

vector<Territory*> Player::toDefend() {
    return myTerritories;
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
    cout << "-----------------------------------------------------" << endl;
    cout << "\tIssuing orders for player " << getPlayerNumber() << endl;
    cout << "-----------------------------------------------------\n" << endl;
    
    cout << "\t--- Deploy Phase Starts ---" << endl;
    if(!myTerritories.empty()){
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
			cout << "Enter number of armies you want to deploy at territory " << territorytoDeploy <<": ";
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
			cout << "The territory to deploy at "<< territorytoDeploy << " does not belong to you." << endl;
		}
    }
    }
    else{
        cout << "\nYou do not have any territories so deploy phase will end.\n" << endl;
    }

    cout << "\t--- Deploy Phase Ends ---" << endl;
    cout << "\n\t--- Advance Phase Starts ---" << endl;
    if(!myTerritories.empty()){

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

                // Reminder of Territories player has
                cout << "\nTerritories you own: " << endl;
                for (Territory* territory : getMyTerritories()) {
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
                            cout << "You entered an invalid number. You only have " << sourceTerr->getNumberOfArmies() << " army units available in territory " << sourceTerr->getTerritoryName() << endl;
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
                            cout << "You entered an invalid number. You only have " << sourceTerrForAttack->getNumberOfArmies() << "army units avilable in territory " << sourceTerrForAttack->getTerritoryName() << endl;
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
                cout << "You entered an incorrect option. You can only choose option 1 or 2." << endl;
            }
            // Ask player if he wants to advance
            cout << "Do you want to issue advance orders?" << endl; 
            cout << "Enter \"yes\" if you want to advance; otherwise, advance phase ends." << endl;
            cin >> input;
            cout << endl;
        }
    }
    else{
        cout << "\nYou do not have any territories so advance phase will end." << endl;
    }

    cout << "\n\t--- Advance Phase Ends ---" << endl;
    cout << "\n\t--- Card Phase Starts ---" << endl;
    
    int cardsInHand = playerHand->getCards().size();
    // Confirm if player has cards
    if (cardsInHand > 0){
        // list cards
        cout << "\nCards in hand:" << endl << endl;
        for(int i=0; i < cardsInHand; i++){
            cout << "Index " << i << " has card of type " << *playerHand->getCards().at(i) << endl;
        }
        // Prompt which card to use
        cout << "\nEnter the index of the card to use ";
        int cardInd;
        cin >> cardInd;
        cout << endl;

        auto it = playerHand->getCards().begin();  
        int offset = cardInd;                       

        // validate correct index was entered; otherwise prompt user again until correct index entered
        while(cardInd < 0 || cardInd >= cardsInHand){
            cout << "Wrong card index! You can only choose from 0 to " << cardsInHand - 1<< endl;
            cin >> cardInd;
            cout << endl;
        }
        // Pointer for the card
        Card* cardPoint = *(it+offset);             

		// Cases for each type of card to be played and its required input
		if (*(cardPoint->getType()) == CardType::BOMB) { //cardName == "Bomb"
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
		else if (*(cardPoint->getType()) == CardType::REINFORCEMENT) {
			cout << "You chose REINFORCEMENT card. Reinforcement order has been issued. " << endl;
			cardPoint->play();
		}
		else if (*(cardPoint->getType()) == CardType::BLOCKADE) {
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
		else if (*(cardPoint->getType()) == CardType::AIRLIFT) {
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
		else if (*(cardPoint->getType()) == CardType::DIPLOMACY) { 
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
			cout << "Diplomacy order issued!" << endl;
		}
    }
    else{
        cout<< "\nYou do not have any cards. Card Phase wil end."  << endl;
    }
    cout << "\n\t--- Card Phase Ends ---" << endl;
    cout << "\nPlayer " << getPlayerNumber() << " turn is over" << endl;
} // issueOrder
