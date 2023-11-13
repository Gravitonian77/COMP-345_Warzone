/*
Name: Dan Tran and Student ID: 27525834 COMP345
Assignment #1 
Due Date : 2023-10-06
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <stack>
#include "Map.h"

using namespace std;

//====================================================================================
//Map Functions
//====================================================================================

//Default Constructor
Map::Map()
{

}

//Copy Constructor
Map::Map(const Map& mObj)
{
    this->continent = mObj.continent;
    this->territory = mObj.territory;
}

//Parameterized Constructors
Map::Map(vector <Continent*> inContinent, vector <Territory*> inTerritory)
{
    this->continent = inContinent;
    this->territory = inTerritory;
}

//Destructor
Map::~Map()
{
    for (int i = 0; i < this->getContinent().size(); i++)
    {
        delete this->getContinent().at(i);

        this->getContinent().at(i) = NULL;
    }
    
    this->getContinent().clear();

    for (int i = 0; i < this->getTerritory().size(); i++)
    {
        delete this->getTerritory().at(i);

        this->getTerritory().at(i) = NULL;
    }
    
    this->getTerritory().clear();
}

//Getters
vector <Continent*> Map::getContinent()
{
    return this->continent;
}

vector <Territory*> Map::getTerritory()   
{
    return this->territory;
}
Territory*Map::getTerritoryByName(string terrName) { //Saqib
    for(auto it: getTerritory()){
    if(it->getTerritoryName() == terrName){
            return it;
    }
    }
    return nullptr;
}
//Setters
void Map::setContinent(vector <Continent*> inContinent)
{
    this->continent = inContinent;
}  

void Map::setTerritory(vector <Territory*> inTerritory)
{
    this->territory = inTerritory;
}

//Streams insertions
ostream& operator<<(ostream& out, const Map& m) {
	out << "Map has " << m.continent.size() << " of continents" << endl;
	return out;
}

//Assignment Operator
Map& Map::operator=(const Map& other)
{
    if (this == &other)
    {
        return *this;
    }

    for (int i = 0; i < this->getContinent().size(); i++)
    {
        delete this->getContinent().at(i);

        this->getContinent().at(i) = NULL;
    }

    this->getContinent().clear();

    for (int i = 0; i < other.continent.size(); i++)
    {
        this->getContinent().push_back(new Continent(*other.continent[i]));
    }

    for (int i = 0; i < this->getTerritory().size(); i++)
    {
        delete this->getTerritory().at(i);

        this->getTerritory().at(i) = NULL;
    }

    for (int i = 0; i < other.territory.size(); i++)
    {
        this->getTerritory().push_back(new Territory(*other.territory[i]));
    }

    return *this;   
}

//Get the size of total territores
int Map::getSizeOfTerritory()
{
    int counter = 0;

    for (int i = 0; i < this->getContinent().size(); i++)
    {
        counter = counter + this->getContinent()[i]->getTerritories().size();
    }

    return counter;
}

//Verify that currentTerritory has been visited during DFS process
bool Map::isVisited(Territory* currentTerritory, vector<Territory*>* visitedTerritory)
{
    for (int i = 0; i < visitedTerritory->size(); i++)
    {
        if (currentTerritory->getTerritoryName() == (*visitedTerritory)[i]->getTerritoryName()) //**********************************************************************
        {
            return true;
        }
    }
    
    return false;
}

//Traversal using DFS 
int Map::DFS(Territory* currentTerritory, vector<Territory*>* visitedTerritory)
{   
    stack <Territory*> stk;
    Territory* nodePop;

    stk.push(currentTerritory);

    while(!stk.empty())
    {
        nodePop = stk.top(); 
        stk.pop();

        if (!isVisited(nodePop, visitedTerritory))
        {
            visitedTerritory->push_back(nodePop);

            for (int i = 0; i < nodePop->getAdjacentTerritories().size(); i++)
            {
                stk.push(nodePop->getAdjacentTerritories()[i]);
            }
            
        }
    }
    return 0;
}

//Verifying validationg of subgraph continent
int Map::checkSubGraph(int index, vector <Territory*>* visitedContinent)
{
    for (int i = 0; i < continent.size(); i++)
    {  
        if (i != index)
        {
            for (int j = 0; j < continent[i]->getTerritories().size(); j++)
            {
                visitedContinent->push_back(continent[i]->getTerritories()[j]);
            }  
        }
    }

    DFS(continent[index]->getTerritories()[0], visitedContinent);

    if (visitedContinent->size() == getSizeOfTerritory())
    {
        cout << "The subgraph is connected for " <<   continent[index]->getContinentIdentity()  << endl;
    }

    return 0;
}


/**
 *  This is validate() method that makes the following checks:
 *  1) the map is a connected graph, 
 *  2) continents are connected subgraphs 
 *  3) each country belongs to one and only one continent
 * 
 * We do not need to verify if each country belongs to a specific continent since the Conquest Template files mandate that every territory must be linked to only one continent
*/
int Map::validate()
{
    vector <Territory*> visited;
    int sizeOfTerritory = getSizeOfTerritory();

    DFS(continent[0]->getTerritories()[0], &visited);
    
    //Checking if the map is a connected graph
    if (visited.size() == sizeOfTerritory)
    {
        cout << "The map  graph is connected." << endl;
    }
    else
    {
        cout << "The map graph is not connected.\n The program will terminate. " << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < continent.size(); i++)
    {
        vector <Territory*> visited2;
        checkSubGraph(i, &visited2);
    }
    return 0;
}

int Map::continentControlBonus(Player* player) 
{
	int continentControlBonus = 0;
	for (Continent* c : getContinent()) {
		bool pHasAllTerritories = true;
		for (Territory* territory : c->getTerritories()) {
			if (territory->getOwner() != player) {
				pHasAllTerritories = false;;
                break;
			}
		}
		if (pHasAllTerritories) {
			continentControlBonus = continentControlBonus + c->getArmybonus();
		}
	}
	return continentControlBonus;
}
//====================================================================================
//Territory Functions
//====================================================================================

//Constructor
Territory::Territory()
{
    this->territoryName = "";
    this->x = 0;
    this->y = 0;
    this->continentName = "";
    this->numberOfArmies = 0;
    this->owner = nullptr;
}

//Parameterized Constructor
Territory::Territory(string inTerritoryName, int inX, int inY, string inContinentName, vector<string> inTerritoryIndex)
{
    this->territoryName = inTerritoryName;
    this->x = inX;
    this->y = inY;
    this->continentName = inContinentName;
    this->territoryIndex = inTerritoryIndex;
    this->numberOfArmies = 0;
}

//Copy Constructor
Territory::Territory(const Territory& tObj)
{
    this->territoryName = tObj.territoryName;
    this->x = tObj.x;
    this->y = tObj.y;
    this->continentName = tObj.continentName;
    this->territoryIndex = tObj.territoryIndex;
    this->adjacentTerritories = tObj.adjacentTerritories;
    this->numberOfArmies = tObj.numberOfArmies;
    this->owner = tObj.owner;
}



Territory::Territory(string inTerritoryName, int inX, int inY, string inContinentName,vector <string> inTerritoryIndex, vector <Territory*> inAdjacentTerritories, int inArmyQuantity, Player* inTerritoryHolder)
{
    this->territoryName = inTerritoryName;
    this->x = inX;
    this->y = inY;
    this->continentName = inContinentName;
    this->territoryIndex = inTerritoryIndex;
    this->adjacentTerritories = inAdjacentTerritories;
    this->numberOfArmies = inArmyQuantity;
    this->owner = inTerritoryHolder;
}

//Destructor
Territory::~Territory()
{
   this->adjacentTerritories.clear();
}

//Getters
string Territory::getTerritoryName() const // for Player class
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

vector<string> Territory::getTerritoryIndex()
{
    return this->territoryIndex;
}

vector <Territory*> Territory::getAdjacentTerritories()
{
    return this->adjacentTerritories;
}

int Territory::getNumberOfArmies () 
{
    return this->numberOfArmies;
}

Player* Territory::getOwner() // For Player class
{
    return owner;
}

bool Territory::operator!=(const Territory * other) //For Player class
{
    return this->owner != other->owner;
}

//Setters
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

void Territory::setTerritoryIndex(vector<string> inTerritoryIndex)
{
    this->territoryIndex = inTerritoryIndex;
}

void Territory::setAdjaccentTerritories(vector <Territory*> inAdjacentTerritories)
{
    this->adjacentTerritories = inAdjacentTerritories;
}
void Territory::setNumberOfArmies(int armies){
    this->numberOfArmies = armies;
}

void Territory::addAdjTerritory(Territory* t)
{
    this->adjacentTerritories.push_back(t);
}

void Territory::setPlayer(Player* inPlayer) // for Player class
{
    this->owner = inPlayer;
}

//Streams insertions
ostream& operator<<(ostream& out, const Territory& t) 
{
	out << "Territory Name: " << t.territoryName << ", ";
    out << "Coordinate x: " << t.x << ", ";
    out << "Coordinate y: " << t.y << ", ";
    out << "Continent: " << t.continentName << ", ";
    out << "Adjacent Territories: " ;

    for (int i = 0; i < t.adjacentTerritories.size(); i++)
    {
        if (i == t.adjacentTerritories.size()-1)
        {
            cout << t.adjacentTerritories[i]->getTerritoryName() << endl;
            break;
        }

        cout << t.adjacentTerritories[i]->getTerritoryName() << ", ";
    }

	return out;
}

//Insertion Operator
Territory& Territory::operator=(const Territory& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->territoryName = other.territoryName;
    this->x = other.x;
    this->y = other.y;
    this->continentName = other.continentName;
    this->territoryIndex = other.territoryIndex;
    this->adjacentTerritories = other.adjacentTerritories;
    this->numberOfArmies = other.numberOfArmies;
    this->owner = other.owner;

    for (int i = 0; i < other.adjacentTerritories.size(); i++)
    {
        this->getAdjacentTerritories().push_back(new Territory(*other.adjacentTerritories[i]));
    }
    
    this->numberOfArmies = other.numberOfArmies;
    this->owner = other.owner;

    return *this;
        
}


//====================================================================================
//Continent Functions
//====================================================================================

//Constructors
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

Continent::Continent(string inContinentIdentity, int inNumberOfTerritories, vector <Territory*> inTerritories, int inArmybonus) //Saqib
{
    this ->continentIdentity = inContinentIdentity;
    this ->numberOfTerritories = inNumberOfTerritories;
    this ->Territories = inTerritories;
    this ->armyBonus = inArmybonus; //Saqib
}

//Destructor
Continent::~Continent()
{
    for (int i = 0; i < this->getTerritories().size(); i++)
    {
        delete this->getTerritories().at(i);

        this->getTerritories().at(i) = NULL;
    }

    this->getTerritories().clear();
    
}
    
//Getters
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

int Continent::getArmybonus(){ //Saqib
    return armyBonus;
}

//Setters
void Continent::setArmyBonus(int inArmyBonus){
    this->armyBonus = inArmyBonus;
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

void Continent::addTerritoryToContinent(Territory* t)
{
    this->Territories.push_back(t);
}

//Streams insertion
ostream& operator<<(ostream& out, const Continent& c) {
	out << "Continent Name: " << c.continentIdentity << ", ";
    out << "Numbers of territories: " << c.numberOfTerritories << endl;

	return out;
}

//Assignment Operator
Continent& Continent::operator=(const Continent& other)
{
    if (this == &other)
    {
        return *this; 
    }

    this->continentIdentity = other.continentIdentity;
    this->numberOfTerritories = other.numberOfTerritories;

    for (int i = 0; i < this->getTerritories().size(); i++)
    {
        delete this->getTerritories().at(i);

        this->getTerritories().at(i) = NULL;
    }

    this->getTerritories().clear();

    for (int i = 0; i < other.Territories.size(); i++)
    {
        this->getTerritories().push_back(new Territory(*other.Territories[i]));
    }
    
}



//====================================================================================
//MapLoader Functions
//====================================================================================

//Check continent name from string line input from map file
string mapLoader::getContinentNameFromLine(string inStr)
{
    bool isErrorThrown = false;

    try {
        return inStr.substr(0, inStr.find("="));
    }catch (const std::exception &e)
    {
        isErrorThrown = true;
        cout << "Map file is currently invalid. " << endl;
        //std::cerr << e.what() << endl;
    }

    if (isErrorThrown)
        exit(EXIT_FAILURE);

}

//Check numbers of terrotires from sting line input from map file
int mapLoader::getNumberOfTerritoriesFromLine(string inStr)
{
    bool isErrorThrown = false;
    try{
         return stoi(inStr.substr(inStr.find("=") + 1,inStr.length()-1));     
    } catch (const std::exception &e)
    {
        isErrorThrown = true;
        cout << "Map file is invalid. " << endl;
        //std::cerr << e.what() << endl;
    }

    if (isErrorThrown)
        exit(EXIT_FAILURE);

}

//Splitting the input map file line and settings the territory fields
Territory* mapLoader::getTerritoryFields(string inStr)
{
    
    bool isErrorThrown = false;
    vector<string> tokens;
    string token;
    string tmpStr;
    tmpStr = inStr;
    int offset = 0;
    
    int i = 0;
    size_t found;
    

    found = tmpStr.find(',');

    if (found == string::npos) 
    {
        cout << "Map file is invalid. " << endl;
        exit(EXIT_FAILURE);
    }

    while (tmpStr.length())
    {
        
        
        found = tmpStr.find(',');
        if (found != string::npos) 
        {
            token = tmpStr.substr(offset, tmpStr.find(','));
        }
        else
        {
            token = tmpStr;
            tokens.push_back(token);
            break;
        }
        
        tokens.push_back(token);
        i++;
        
        tmpStr =  tmpStr.substr(tmpStr.find(',') +1, tmpStr.length() - 1 );
        
    }

    //Creating Territory Objects to return
    string inTerritoryName = tokens[0];
    int inX = stoi(tokens[1]);
    int inY = stoi(tokens[2]);
    string inContinentName = tokens[3] ;

    vector<string> inTerritoryIndex;
    for (int i = 4; i < tokens.size(); i++) 
    {
        inTerritoryIndex.push_back(tokens[i]);
        
    }
    

    Territory* t = new Territory(inTerritoryName, inX, inY, inContinentName, inTerritoryIndex );

    return t;
    
}

//Loading map by inputing the Conquest Map file
Map* mapLoader::createMapFromConquestFile(string inFileName)
{
    vector <Continent*> mapContinents;
    vector <Territory*> mapTerritories;

    bool continentSectionFound = false;
    bool territorySectionFound = false;
    bool invalidFile = true;
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
                continue;
            }
            else
            {
                mapTerritories.push_back(mapLoader::getTerritoryFields(read));
                
            }
        }
    }

    
    //Mapping Adjacent territories 
    string territoryIndex;

    for(int i=0; i < mapTerritories.size(); i++)
    {
        for (int j=0; j < mapTerritories[i]->getTerritoryIndex().size(); j++)
        {
            territoryIndex = mapTerritories[i]->getTerritoryIndex()[j];
            for (int k=0; k < mapTerritories.size(); k++)
            {
                if (territoryIndex == mapTerritories[k]->getTerritoryName())
                {
                    mapTerritories[i]->addAdjTerritory(mapTerritories[k]);   
                }
            }  
        }
    }

    //Mapping of Territory to Continent
    string continentIndex;
    int numberOfTerritories;

    for (int i = 0; i < mapContinents.size(); i++)
    {
        continentIndex = mapContinents[i]->getContinentIdentity();
        numberOfTerritories = mapContinents[i]->getNumberOfTerritories();
        for (int j = 0; j < mapTerritories.size(); j++)
        {
            if(continentIndex == mapTerritories[j]->getContinentName())
            {
                mapContinents[i]->addTerritoryToContinent(mapTerritories[j]);
            }
        }
        
    }

    
    inputfilestream.close();

    Map* m = new Map(mapContinents, mapTerritories);
    return m;
}
/*
void testLoadMaps()
{
    //==================================================================================================================
    //Loading first valid map
    //==================================================================================================================
        cout << "Let's load a map!\n" << endl;

        Map* m1 = mapLoader::createMapFromConquestFile("Canada.map");

        cout << "The program will now display all continents object...\n" << endl;
        for (int i = 0; i < m1->getContinent().size(); i++)
        {
            cout << *m1->getContinent()[i];
        }

        cout << "\nThe program will now display all territories object...\n" << endl;
        for (int i = 0; i < m1->getSizeOfTerritory(); i++)
        {
            cout << *m1->getTerritory()[i];
        }

    //The program will validate the map
        cout << "\nThe program will now validate the map..." << endl;
        m1->validate();




    //==================================================================================================================
    //Loading second valid map
    //==================================================================================================================
    cout << "\n\nLet's load another map!\n" << endl;

        Map* m2 = mapLoader::createMapFromConquestFile("Alabama.map");

        cout << "The program will now display all continents object...\n" << endl;
        for (int i = 0; i < m2->getContinent().size(); i++)
        {
            cout << *m2->getContinent()[i];
        }

        cout << "\nThe program will now display all territories object...\n" << endl;
        for (int i = 0; i < m2->getSizeOfTerritory(); i++)
        {
            cout << *m2->getTerritory()[i];
        }

    //The program will validate the map
        cout << "\nThe program will now validate the map..." << endl;
        m2->validate();

    //==================================================================================================================
    //Validating an non connected graph map
    //==================================================================================================================
    cout << "\n\nThe program will now validate a non connected graph Map (Invalid)\n" << endl;
     Map* m3 = mapLoader::createMapFromConquestFile("CanadaError.txt");
     m3->validate();

     //==================================================================================================================
    //Loading an invalid map file
    //==================================================================================================================
    cout << "\n\nThe program will now load an invalid map file\n" << endl;
     Map* m4 = mapLoader::createMapFromConquestFile("InvalidMap.txt");
  


}
*/