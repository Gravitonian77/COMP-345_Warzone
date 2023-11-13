//
// Created by Kimsay Kong on 2023-09-27.
//
#include <iostream>
#include <vector> // needed in github
#include <algorithm> // needed in github
#include "Orders.h"

using namespace std;

/*---------------------------------Implementation of Orders Class---------------------------------*/

//default constructor
Order::Order() {
    executed = false;
    effect = "";
}

//copy constructor
Order::Order(const Order &order) {
    executed = order.executed;
    effect = order.effect;
}

//parameterized constructor
Order::Order(bool executed, string effect) {
    this->executed = executed;
    this->effect = effect;
}

//validate method
bool Order::validate() {
    // add your validation logic here
    return true; // replace with your actual validation result
}

//execute method
void Order::execute() {}

//get name method
string Order::getName() {
    return "Order";
}

//set executed method
void Order::setExecuted(bool executed) {
    this->executed = executed;
}

//get executed method
bool Order::getExecuted() {
    return executed;
}

//set effect method
void Order::setEffect(string effect) {
    this->effect = effect;
}

//get effect method
string Order::getEffect() {
    return effect;
}


/*---------------------------------Implementation of OrdersList Class--------------------------------- */

//default Constructor
OrdersList::OrdersList(){
    Order();
    player = new Player();
}


//copy constructor
OrdersList::OrdersList(const OrdersList &ordersList) {
    player = ordersList.player;
    this->ordersList = ordersList.ordersList;
}

//parameterized constructor
OrdersList::OrdersList(Player* player, vector<Order *> &ordersList) {
    this->player = player;
    this->ordersList = ordersList;
}

//get ordersList method
vector<Order *> OrdersList::getOrdersList() {
    return ordersList;
}

//set ordersList method
void OrdersList::setOrdersList(vector<Order *> &ordersList) {
    this->ordersList = ordersList;
}

//insert order method
void OrdersList::insertOrder(Order *order) {
    ordersList.push_back(order);
}

//move order method
void OrdersList::moveOrder(int currentPosition, int newPosition) {
    Order *temp = ordersList[currentPosition];
    ordersList.erase(ordersList.begin() + currentPosition);
    ordersList.insert(ordersList.begin() + newPosition, temp);
}

//remove order method
void OrdersList::removeOrder(int offset) {
    ordersList.erase(ordersList.begin() + offset);
}
void OrdersList::removeOrder(Order* order){ // saq
    ordersList.erase(remove(ordersList.begin(),ordersList.end(),order),ordersList.end());
}
//print orders method
void OrdersList::printOrders() {
    for (int i = 0; i < ordersList.size(); i++) {
        cout << ordersList[i]->getName() << " ";
    }
    cout << endl;
}

/*---------------------------------Implementation of Deploy Class---------------------------------*/
//default constructor
Deploy::Deploy() {
    Order();
    player = new Player();
    target = new Territory();
    numberOfArmies = 0;
}

//copy constructor
Deploy::Deploy(const Deploy &deploy) {
    player = deploy.player;
    target = deploy.target;
    numberOfArmies = deploy.numberOfArmies;
}

//parameterized constructor
Deploy::Deploy(Player *player, Territory *target, int numberOfArmies) {
    this -> name = "Deploy";
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

//destroyer
Deploy::~Deploy() {
    delete player;
    delete target;
}

//stream insertion operator overloading for Deploy class
ostream &operator<<(ostream &output, const Deploy &deploy) {
    output << "Deploy order: " << deploy.name << " " << deploy.player << " " << deploy.target << " " << deploy.numberOfArmies << endl;
    return output;
}

//validate method
bool Deploy::validate() {
    if (target==nullptr){
        cout<< "Deploy order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Deploy order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the number of armies is greater than 0
    if (numberOfArmies <= 0){
        cout<< "Deploy order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }
    // If the target territory does not belong to the player that issued the order,
    // the order is invalid.
    if (target->getOwner() != player){
        cout<< "Deploy order is invalid because the target territory does not belong to the player" << endl;
        return false;
    }

    cout<< "Deploy order is valid" << endl;
    return true;
}

//execute method
void Deploy::execute() {
    if (validate()){
        // If the target territory belongs to the player that issued the deploy order,
        // the selected number of army units is added to the number of army units on that territory
        player->setReinforcementPool(player->getReinforcementPool()-this->numberOfArmies);
        int numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
        target->setNumberOfArmies(numberOfArmies);
        setExecuted(true);
        setEffect("Deploy order has been executed");
    }
}

string Deploy::getName(){
    return name;
}

Player* Deploy::getPlayer(){
    return player;
}

Territory* Deploy::getTarget(){
    return target;
}

int Deploy::getArmies(){
    return numberOfArmies;
}

void Deploy::setPlayer(Player* player){
    this->player = player;
}

void Deploy::setTarget(Territory* target){
    this->target = target;
}

void Deploy::setArmies(int armies){
    this->numberOfArmies = armies;
}

void Deploy::setName(string name){
    this->name = name;
}

/*---------------------------------Implementation of Advance Class---------------------------------*/
//default constructor
Advance::Advance() {
    Order();
    player = new Player();
    source = new Territory();
    target = new Territory();
    numberOfArmies = 0;
}

//copy constructor
Advance::Advance(const Advance &advance) {
    player = advance.player;
    source = advance.source;
    target = advance.target;
    numberOfArmies = advance.numberOfArmies;
}

//parameterized constructor
Advance::Advance(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Advance";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> numberOfArmies = numberOfArmies;
}

//destroyer
Advance::~Advance() {
    delete player;
    delete source;
    delete target;
}

//stream insertion operator overloading for Advance class
ostream &operator<<(ostream &output, const Advance &advance) {
    output << "Advance order: " << advance.name << " " << advance.player << " " << advance.source << " " << advance.target << " " << advance.numberOfArmies << endl;
    return output;
}

//validate method
bool Advance::validate() {
    if (source==nullptr){
        cout<< "Advance order is invalid because the source territory is null" << endl;
        return false;
    }
    if (target==nullptr){
        cout<< "Advance order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Advance order is invalid because it has already been executed" << endl;
        return false;
    }

    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if (source->getOwner() != player){
        cout<< "Advance order is invalid because the source territory does not belong to the player" << endl;
        return false;
    }

    //If the target territory is not adjacent to the source territory, the order is invalid.
    bool targetAdjacent = false;
    for (auto* adjacentTerritory : source->getAdjacentTerritories()) {
        if (adjacentTerritory == target) {
            targetAdjacent = true;
            break;
        }
    }
    if (!targetAdjacent){
        cout<< "Advance order is invalid because the target territory is not adjacent to the source territory" << endl;
        return false;
    }
    // check if the number of armies is greater than 0
    if (numberOfArmies <= 0) {
        cout << "Advance order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }

    // check if the number of armies is greater than the number of armies in the source territory
    if (numberOfArmies > source->getNumberOfArmies()) {
        cout << "Advance order is invalid because the number of armies is greater than the number of armies in the source territory" << endl;
        return false;
    }

    cout<< "Advance order is valid" << endl;
    return true;

}

//execute method
void Advance::execute() {
    if (validate()){
        // If the source and target territory both belong to the player that issued the order,
        // the army units are moved from the source to the target territory.
        if(target->getOwner() == player && source->getOwner() == player){
            int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
            source->setNumberOfArmies(numberOfArmies);
            numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
            target->setNumberOfArmies(numberOfArmies);
            setExecuted(true);
            setEffect("Advance order has been executed");
        }
        //If the target territory belongs to another player than the player that issued
        // the advance order, an attack is simulated when the order is executed.
        // An attack is simulated by the following battle simulation mechanism:
        else if(source->getOwner() == player && target->getOwner()!=player){
            Player* enemy = target->getOwner();
            //Each attacking army unit involved has 60% chances of killing one defending army.
            //At the same time, each defending army unit has 70% chances of killing one attacking
            //army unit.
            int attackingArmy = this->numberOfArmies;
            int defendingArmy = target->getNumberOfArmies();
            int attackingArmyLost = 0;
            int defendingArmyLost = 0;
            for(int i = 0; i < attackingArmy; i++){
                int random = rand() % 100 + 1;
                if(random <= 60){
                    defendingArmyLost++;
                }
            }
            for(int i = 0; i < defendingArmy; i++){
                int random = rand() % 100 + 1;
                if(random <= 70){
                    attackingArmyLost++;
                }
            }
            //If the attacker loses all its army units, the attack fails and no army units are moved.
            if(attackingArmyLost == attackingArmy){
                setEffect("The advance call was not executed since the attacker loses all its army units\n");
                cout << getEffect() << endl;
            }
            //If the defender loses all its army units, the attack succeeds and the attacker moves all its army units to the conquered territory.
            else if(defendingArmyLost == defendingArmy){
                int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
                source->setNumberOfArmies(numberOfArmies);
                numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
                target->setNumberOfArmies(numberOfArmies);
                target->setPlayer(player);
                enemy->removeTerritory(target);
                player->addTerritory(target);
                setExecuted(true);
                setEffect("Advance order has been executed");
            }
            //If both players have army units left, the attack succeeds and the attacker moves the remaining army units to the conquered territory.
            else{
                int numberOfArmies = source->getNumberOfArmies()-this->numberOfArmies;
                source->setNumberOfArmies(numberOfArmies);
                numberOfArmies = target->getNumberOfArmies()+this->numberOfArmies;
                target->setNumberOfArmies(numberOfArmies);
                target->setPlayer(player);
                enemy->removeTerritory(target);
                player->addTerritory(target);
                setExecuted(true);
                setEffect("Advance order has been executed");
            }
        }
        else{
            setEffect("The advance call was not executed since it was invalid\n");
            cout << getEffect() << endl;
        }
    }
}
string Advance::getName(){
    return name;
}

Player* Advance::getPlayer(){
    return player;
}
Territory* Advance::getSource(){
    return source;
}
Territory* Advance::getTarget(){
    return target;
}
int Advance::getArmies(){
    return numberOfArmies;
}

void Advance::setPlayer(Player* player){
    this->player = player;
}
void Advance::setSource(Territory* source){
    this->source = source;
}
void Advance::setTarget(Territory* target){
    this->target = target;
}
void Advance::setArmies(int armies){
    this->numberOfArmies = armies;
}

void Advance::setName(string name){
    this->name = name;
}

/*---------------------------------Implementation of Bomb Class---------------------------------*/
//default constructor
Bomb::Bomb() {
    Order();
    player = new Player();
    target = new Territory();
}

//copy constructor
Bomb::Bomb(const Bomb &bomb) {
    player = bomb.player;
    target = bomb.target;
}


//parameterized constructor
Bomb::Bomb(Player *player, Territory *target) {
    this -> name = "Bomb";
    this -> target = target;
    this -> player = player;
}

//destroyer
Bomb::~Bomb() {
    delete player;
    delete target;
}

//stream insertion operator overloading for Bomb class
ostream &operator<<(ostream &output, const Bomb &bomb) {
    output << "Bomb order: " << bomb.name << " " << bomb.player << " " << bomb.target << endl;
    return output;
}

//validate method
bool Bomb::validate() {
    if (target==nullptr){
        cout<< "Bomb order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Bomb order is invalid because it has already been executed" << endl;
        return false;
    }

    // If the target belongs to the player that issued the order, the order is invalid.
    if (target->getOwner()== this->player)
    {
        cout<< "Bomb order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    // If the target territory is not adjacent to one of the territory owned by the
    // player issuing the order, then the order is invalid.
    bool isAdjacent = false;
    for (Territory* adjacentTerritory : target->getAdjacentTerritories()) {
        if (adjacentTerritory->getOwner() == player) {
            isAdjacent = true;
            break;
        }
    }
    if (!isAdjacent)
    {
        cout<< "Bomb order is invalid because the target territory is not adjacent to one of the territory owned by the player issuing the order" << endl;
        return false;
    }
    

    cout<< "Bomb order is valid" << endl;
    return true;
}

//execute method
void Bomb::execute() {
    if (validate()){
        // A bomb order targets a territory owned by another player than the one issuing the order. Its result is
        // to remove half of the army units from this territory.
        int numberOfArmies = target->getNumberOfArmies()/2;
        target->setNumberOfArmies(numberOfArmies);
        setExecuted(true);
        setEffect("Bomb order has been executed");
    }
}
string Bomb::getName(){
    return name;
}

Player* Bomb::getPlayer(){
    return player;
}

Territory* Bomb::getTarget(){
    return target;
}

void Bomb::setPlayer(Player* player){
    this->player = player;
}

void Bomb::setTarget(Territory* target){
    this->target = target;
}

void Bomb::setName(string name){
    this->name = name;
}

/*---------------------------------Implementation of Blockade Class---------------------------------*/
//default constructor
Blockade::Blockade() {
    Order();
    player = new Player();
    target = new Territory();
}

//copy constructor
Blockade::Blockade(const Blockade &blockade) {
    player = blockade.player;
    target = blockade.target;
}

//parameterized constructor
Blockade::Blockade(Player *player, Territory *target) {
    this -> name = "Blockade";
    this -> target = target;
    this -> player = player;
}

//destroyer
Blockade::~Blockade() {
    delete player;
    delete target;
}

//stream insertion operator overloading for Blockade class
ostream &operator<<(ostream &output, const Blockade &blockade) {
    output << "Blockade order: " << blockade.name << " " << blockade.player << " " << blockade.target << endl;
    return output;
}

//validate method
bool Blockade::validate() {
    if (target==nullptr){
        cout<< "Blockade order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Blockade order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (target->getOwner() != player){
        cout<< "Blockade order is invalid because the target territory does not belong to the player" << endl;
        return false;
    }

    cout<< "Blockade order is valid" << endl;
    return true;
}

//execute method
void Blockade::execute() {
    if (validate()){
        //A blockade order targets a territory that belongs to the player issuing the order.
        //Its effect is to double the number of army units on the territory and to transfer
        //the ownership of the territory to the Neutral player.
        int numberOfArmies = target->getNumberOfArmies()*2;
        target->setNumberOfArmies(numberOfArmies);
        target->setPlayer(nullptr);
        setExecuted(true);
        setEffect("Blockade order has been executed");
    }
}

string Blockade::getName(){
    return name;
}

Player* Blockade::getPlayer(){
    return player;
}

Territory* Blockade::getTarget(){
    return target;
}

void Blockade::setPlayer(Player* player){
    this->player = player;
}

void Blockade::setTarget(Territory* target){
    this->target = target;
}

void Blockade::setName(string name){
    this->name = name;
}

/*---------------------------------Implementation of Airlift Class---------------------------------*/
//default constructor
Airlift::Airlift() {
    Order();
    player = new Player();
    source = new Territory();
    target = new Territory();
    NumberOfArmies = 0;
}

//copy constructor
Airlift::Airlift(const Airlift &airlift) {
    player = airlift.player;
    source = airlift.source;
    target = airlift.target;
    NumberOfArmies = airlift.NumberOfArmies;
}

//parameterized constructor
Airlift::Airlift(Player *player, Territory *source, Territory *target, int numberOfArmies) {
    this -> name = "Airlift";
    this -> source = source;
    this -> target = target;
    this -> player = player;
    this -> NumberOfArmies = numberOfArmies;
}

//destroyer
Airlift::~Airlift() {
    delete player;
    delete source;
    delete target;
}

//stream insertion operator overloading for Airlift class
ostream &operator<<(ostream &output, const Airlift &airlift) {
    output << "Airlift order: " << airlift.name << " " << airlift.player << " " << airlift.source << " " << airlift.target << " " << airlift.NumberOfArmies << endl;
    return output;
}

//validate method
bool Airlift::validate() {
    if (getTarget()==nullptr){
        cout<< "Airlift order is invalid because the target territory is null" << endl;
        return false;
    }
    if (getSource()==nullptr){
        cout<< "Airlift order is invalid because the source territory is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Airlift order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the source territory belongs to the player
    if (getSource()->getOwner() != getPlayer()){
        cout<< "Airlift order is invalid because the source territory does not belong to the player" << endl;
        return false;
    }

    // check if the target territory belongs to the player
    if (getTarget()->getOwner() != getPlayer()){
        cout<< "Airlift order is invalid because the target territory belongs to the player" << endl;
        return false;
    }

    // check if the number of armies is greater than 0
    if (getNumberOfArmies() <= 0) {
        cout << "Airlift order is invalid because the number of armies is less than or equal to 0" << endl;
        return false;
    }

    // check if the number of armies is greater than the number of armies in the source territory
    if (getNumberOfArmies() > getSource()->getNumberOfArmies()) {
        cout << "Airlift order is invalid because the number of armies is greater than the number of armies in the source territory" << endl;
        return false;
    }

    cout<< "Airlift order is valid" << endl;
    return true;
}

//execute method
void Airlift::execute() {
    if (validate()){
        // If both the source and target territories belong to the player that issue the airlift
        // order, then the selected number of army units is moved from the source to the target territory.
        if (target->getOwner()==this->player && source->getOwner() == this->player){
            int numberOfArmies = getSource()->getNumberOfArmies()-getNumberOfArmies();
            getSource()->setNumberOfArmies(numberOfArmies);
            getTarget()->setNumberOfArmies(getNumberOfArmies());
            getTarget()->setPlayer(getPlayer());
            setExecuted(true);
            setEffect("Airlift order has been executed");
        }
    }
}

string Airlift::getName(){
    return name;
}

Player* Airlift:: getPlayer(){
    return player;
}
Territory* Airlift::getSource(){
    return source;
}

Territory* Airlift::getTarget(){
    return target;
}
int Airlift::getNumberOfArmies(){
    return NumberOfArmies;
}

void Airlift::setPlayer(Player* player){
    this->player = player;
}

void Airlift::setSource(Territory* source){
    this->source = source;
}

void Airlift::setTarget(Territory* target){
    this->target = target;
}

void Airlift::setNumberOfArmies(int armies){
    this->NumberOfArmies = armies;
}

void Airlift::setName(string name){
    this->name = name;
}

/*---------------------------------Implementation of Negotiate Class---------------------------------*/
//default constructor
Negotiate::Negotiate() {
    Order();
    player1 = new Player();
    player2 = new Player();
}

//copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) {
    player1 = negotiate.player1;
    player2 = negotiate.player2;
}

//parameterized constructor
Negotiate::Negotiate(Player *player1, Player *player2) {
    this -> name = "Negotiate";
    this -> player1 = player1;
    this -> player2 = player2;
}

//destroyer
Negotiate::~Negotiate() {
    delete player1;
    delete player2;
}

//validate method
bool Negotiate::validate() {
    if (player1==nullptr){
        cout<< "Negotiate order is invalid because the player1 is null" << endl;
        return false;
    }
    if (player2==nullptr){
        cout<< "Negotiate order is invalid because the player2 is null" << endl;
        return false;
    }
    if (getExecuted()){
        cout<< "Negotiate order is invalid because it has already been executed" << endl;
        return false;
    }

    // check if the player1 is the same as player2
    if (player1 == player2){
        cout<< "Negotiate order is invalid because the player1 is the same as player2" << endl;
        return false;
    }

    cout<< "Negotiate order is valid" << endl;
    return true;
}

//execute method
void Negotiate::execute() {
    if (validate()){
        // add plays to the agreements list
        player1->addAgreement(player2);
        player2->addAgreement(player1);
        setExecuted(true);
        setEffect("Negotiate order has been executed");
    }
}

string Negotiate::getName(){
    return name;
}

Player* Negotiate::getPlayer1(){
    return player1;
}

Player* Negotiate::getPlayer2(){
    return player2;
}

void Negotiate::setPlayer1(Player* player1){
    this->player1 = player1;
}

void Negotiate::setPlayer2(Player* player2){
    this->player2 = player2;
}

void Negotiate::setName(string name){
    this->name = name;
}

/* free function to test orders lists */
//void testOrdersLists(){
//    cout << "------------------------" << endl;
//    cout << "Testing OrdersList class" << endl;
//    cout << "------------------------" << endl;
//    cout << endl;
//
//    cout << "Creating an empty OrdersList" << endl;
//    OrdersList *ordersList = new OrdersList();
//    cout << endl;
//
//    Order *order1 = new Deploy("territory1", "player1", 1);
//    Order *order2 = new Advance("territory2", "territory3", "player2", 2);
//    Order *order3 = new Bomb("territory4", "player3");
//    Order *order4 = new Blockade("territory5", "player4");
//    Order *order5 = new Airlift("territory6", "territory7", "player5", 3);
//    Order *order6 = new Negotiate("player6", "player7");
//
//    cout << "Validate the Deploy Class : ";
//    cout << order1->validate();
//    cout << endl;
//
//    cout << "Execute the Deploy Class : " ;
//    order1->execute();
//    cout << order1->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Advance Class : ";
//    cout << order2->validate();
//    cout << endl;
//
//    cout << "Execute the Advance Class : " ;
//    order2->execute();
//    cout << order2->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Bomb Class : ";
//    cout << order3->validate();
//    cout << endl;
//
//    cout << "Execute the Bomb Class : " ;
//    order3->execute();
//    cout << order3->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Blockade Class : ";
//    cout << order4->validate();
//    cout << endl;
//
//    cout << "Execute the Blockade Class : " ;
//    order4->execute();
//    cout << order4->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Airlift Class : ";
//    cout << order5->validate();
//    cout << endl;
//
//    cout << "Execute the Airlift Class : " ;
//    order5->execute();
//    cout << order5->getExecuted();
//    cout << endl;
//
//    cout << "Validate the Negotiate Class : ";
//    cout << order6->validate();
//    cout << endl;
//
//    cout << "Execute the Negotiate Class : " ;
//    order6->execute();
//    cout << order6->getExecuted();
//    cout << endl;
//
//    cout << "Inserting 6 orders into the OrdersList" << endl;
//    ordersList->insertOrder(order1);
//    ordersList->insertOrder(order2);
//    ordersList->insertOrder(order3);
//    ordersList->insertOrder(order4);
//    ordersList->insertOrder(order5);
//    ordersList->insertOrder(order6);
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Removing the second order from the OrdersList..." ;
//    ordersList->removeOrder(1);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Moving the first order to the third position in the OrdersList...";
//    ordersList->moveOrder(1, 2);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Delete second order to the OrdersList...";
//    ordersList->removeOrder(1);
//    cout << endl;
//    cout << endl;
//
//    cout << "Printing the OrdersList: ";
//    ordersList->printOrders();
//    cout << endl;
//    cout << endl;
//
//    cout << "Delete the whole OrdersList..." << endl;
//    delete ordersList;
//    cout << endl;
//    cout << endl;
//}





