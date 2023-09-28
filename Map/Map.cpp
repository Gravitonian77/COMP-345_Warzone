#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include "Map.h"

using namespace std;

 Territory::Territory()
{
    this->territoryIdentity = "";
    this->x = 0;
    this->y = 0;
    this->continentOfTerritory = nullptr;
    this->armiesQuantity = 0;
    this->territoryHolder = nullptr;
}

Territory::Territory(string inTerritoryIdentity, int inX, int inY, Continent* inContinentOfTerritory, vector <Territory*> inAdjacentTerritories, int inArmyQuantity, Player* inTerritoryHolder)
{
    this->territoryIdentity = inTerritoryIdentity;
    this->x = inX;
    this->y = inY;
    this->continentOfTerritory = inContinentOfTerritory;
    this->adjacentTerritories = inAdjacentTerritories;
    this->armiesQuantity = inArmyQuantity;
    this->territoryHolder = inTerritoryHolder;
}

string Territory::getTerritoryIdentity()
{
    return this->territoryIdentity;
}

int Territory::getX()
{
    return this->x;
}

int Territory::getY()
{
    return this->y;
}

Continent* Territory::getContinentOfTerritory()
{
    return this->continentOfTerritory;
}

vector <Territory*> Territory::getAdjacentTerritories()
{
    return this->adjacentTerritories;
}

void Territory::setTerritoryIdentity(string inTerritoryIdentity)
{
    this->territoryIdentity = inTerritoryIdentity;
}

void Territory::setX(int inX)
{
    this->x = inX;
}

void Territory::setY(int inY)
{
    this->y = inY;
}

void Territory::setContinentOfTerritory(Continent* inContinentOfTerritory)
{
    this->continentOfTerritory = inContinentOfTerritory;
}
void Territory::setAdjaccentTerritories(vector <Territory*> inAdjacentTerritories)
{
    this->adjacentTerritories = inAdjacentTerritories;
}

Continent::Continent()
{
    this->continentIdentity = "";
    this->continentID = 0; 
}

Continent::Continent(string inContinentIdentity, int inContinentID, vector <Territory*> inTerritories)
{
    this ->continentIdentity = inContinentIdentity;
    this ->continentID = inContinentID;
    this ->Territories = inTerritories;
}
    
string Continent::getContinentIdentity()
{
    return this->continentIdentity;
}

int Continent::getContinentID()
{
    return this->continentID;
}

vector <Territory*> Continent::getTerritories()
{
    return this->Territories;
}

void Continent::setContinentIdentity(string inContinentIdentity)
{
    this->continentIdentity = inContinentIdentity;
}

void Continent::setContinentID(int inContinentID)
{
    this->continentID = inContinentID;
}

void Continent::setTerritories(vector <Territory*> inTerritories)
{
    this->Territories = inTerritories;
}

