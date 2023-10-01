#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include <sstream>
#include "Map.h"

using namespace std;

Map::Map()
{

}

Map::Map(const Map& mObj)
{
    this->continent = mObj.continent;
    this->territory = mObj.territory;
}

Map::Map(vector <Continent*> inContinent, vector <Territory*> inTerritory)
{
    this->continent = inContinent;
    this->territory = inTerritory;
}

vector <Continent*> Map::getContinent()
{
    return this->continent;
}

vector <Territory*> Map::getTerritory()   
{
    return this->territory;
}

void Map::setContinent(vector <Continent*> inContinent)
{
    this->continent = inContinent;
}  

void Map::setTerritory(vector <Territory*> inTerritory)
{
    this->territory = inTerritory;
}
   
Territory::Territory()
{
    this->territoryName = "";
    this->x = 0;
    this->y = 0;
    this->continentName = "";
    this->numberOfArmies = 0;
    this->owner = nullptr;
}

Territory::Territory(const Territory& tObj)
{
    this->territoryName = tObj.territoryName;
    this->x = tObj.x;
    this->y = tObj.y;
    this->continentName = tObj.continentName;
    this->numberOfArmies = tObj.numberOfArmies;
    this->owner = tObj.owner;
}

Territory::Territory(string inTerritoryName, int inX, int inY, string inContinentName, vector <Territory*> inAdjacentTerritories, int inArmyQuantity, Player* inTerritoryHolder)
{
    this->territoryName = inTerritoryName;
    this->x = inX;
    this->y = inY;
    this->continentName = inContinentName;
    this->adjacentTerritories = inAdjacentTerritories;
    this->numberOfArmies = inArmyQuantity;
    this->owner = inTerritoryHolder;
}

string Territory::getTerritoryName()
{
    return this->territoryName;
}

int Territory::getX()
{
    return this->x;
}

int Territory::getY()
{
    return this->y;
}

string Territory::getContinentName()
{
    return this->continentName;
}

vector <Territory*> Territory::getAdjacentTerritories()
{
    return this->adjacentTerritories;
}

void Territory::setTerritoryName(string inTerritoryName)
{
    this->territoryName = inTerritoryName;
}

void Territory::setX(int inX)
{
    this->x = inX;
}

void Territory::setY(int inY)
{
    this->y = inY;
}

void Territory::setContinentIndex(string inContinentName)
{
    this->continentName = inContinentName;
}
void Territory::setAdjaccentTerritories(vector <Territory*> inAdjacentTerritories)
{
    this->adjacentTerritories = inAdjacentTerritories;
}

Continent::Continent()
{
    this->continentIdentity = "";
    this->numberOfTerritories = 0; 
}

Continent::Continent(const Continent& cObj)
{
    this->continentIdentity = cObj.continentIdentity;
    this->numberOfTerritories = cObj.numberOfTerritories; 
    this->Territories = cObj.Territories;
}

Continent::Continent(string inContinentIdentity, int inNumberOfTerritories)
{
    this ->continentIdentity = inContinentIdentity;
    this ->numberOfTerritories = inNumberOfTerritories;
}

Continent::Continent(string inContinentIdentity, int inNumberOfTerritories, vector <Territory*> inTerritories)
{
    this ->continentIdentity = inContinentIdentity;
    this ->numberOfTerritories = inNumberOfTerritories;
    this ->Territories = inTerritories;
}
    
string Continent::getContinentIdentity()
{
    return this->continentIdentity;
}

int Continent::getNumberOfTerritories()
{
    return this->numberOfTerritories;
}

vector <Territory*> Continent::getTerritories()
{
    return this->Territories;
}

void Continent::setContinentIdentity(string inContinentIdentity)
{
    this->continentIdentity = inContinentIdentity;
}

void Continent::setNumberOfTerritories(int inContinentID)
{
    this->numberOfTerritories = inContinentID;
}

void Continent::setTerritories(vector <Territory*> inTerritories)
{
    this->Territories = inTerritories;
}

string mapLoader::getContinentNameFromLine(string inStr)
{
        return inStr.substr(0, inStr.find("="));
}

int mapLoader::getNumberOfTerritoriesFromLine(string inStr)
{
     return stoi(inStr.substr(inStr.find("=") + 1,inStr.length()-1));     
}


string mapLoader::getContinentIDFromTerritory(string inStr)
{
    
    vector<string> tokens;
    //stringstream lineStringStream(inStr);
    string token;
    string tmpStr;
    tmpStr = inStr;
    int offset = 0;
    //cout << inStr << endl;
    int i = 0;
    //for (int i = 0; i < 6; i++)
    while (tmpStr.length() > 1)
    {
        token = tmpStr.substr(offset, tmpStr.find(','));
        //cout << token << endl;
        tokens.push_back(token);
        i++;
        tmpStr =  tmpStr.substr(tmpStr.find(',') +1, tmpStr.length() - 1 );
        //cout << tmpStr.length() << endl;
    }

    return tokens[3];
    
    //token = inStr.substr(0, inStr.find(','));
    //cout << inStr.substr(0, inStr.find(',')) << endl;
    //cout << token << endl;
    //tmpStr =  inStr.substr(inStr.find(',') +1, inStr.length() - 1 );
    //token = tmpStr.substr(0, tmpStr.find(','));
    //cout << token << endl;
    // cout << tmpStr << endl;
    //cout << "AAA";
/*
    while (getline(lineStringStream, token, ','))
    {
        cout << token << endl;
        tokens.push_back(token);
    }
*/
}



Map* mapLoader::createMapFromConquestFile(string inFileName)
{
    vector <Continent*> mapContinents;
    vector <Territory*> mapTerritories;

    bool continentSectionFound = false;
    bool territorySectionFound = false;
    string read;
    ifstream inputfilestream;
    inputfilestream.open(inFileName);
   
    while (!inputfilestream.eof())
    {
        getline(inputfilestream, read);
        if(read == "[Continents]")
        {
            continentSectionFound = true;
        }
        else if (continentSectionFound)
        {
            if (read =="")
            {
                continentSectionFound = false;;
            }
            else
            {
                //cout << mapLoader::getContinentNameFromLine(read) << endl;
                //cout << mapLoader::getNumberOfTerritoriesFromLine(read) << endl;
                Continent* c = new Continent(mapLoader::getContinentNameFromLine(read), mapLoader::getNumberOfTerritoriesFromLine(read));
                mapContinents.push_back(c);
            }
            
        }
        else if(read == "[Territories]")
        {
            territorySectionFound = true;
        }
        else if(territorySectionFound)
        {
            if (read =="")
            {
                //territorySectionFound = false;
                continue;
            }
            else
            {
                cout << mapLoader::getContinentIDFromTerritory(read) << endl;
            }
        }
    }
    
    
    inputfilestream.close();
    /*
    for (int i = 0; i < mapContinents.size(); i++) 
    {
         cout << mapContinents[i]->getContinentIdentity() << endl;
    }
    */

   

}

