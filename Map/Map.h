/*
Name: Dan Tran and Student ID: 27525834 COMP345
Assignment #1 
Due Date : 2023-10-06
*/

#pragma once

#include <iostream>
#include <vector>
using namespace std;


class Player;
/**
* Implementation of a "Territory" class.
*/
class Territory
{
   private:
        //Attributes
        string territoryName;
        int x; 
        int y; 
        string continentName;
        vector <string> territoryIndex;

        vector<Territory*> adjacentTerritories;

        int numberOfArmies;
        Player *owner;
    public:

        //Constructors
        Territory();
        Territory(string inTerritoryName, int inX, int inY, string inContinentName, vector<string> inTerritoryIndex);
        Territory(const Territory& tObj);
        Territory(string inTerritoryName, int inX, int inY, string inContinentName,vector <string> inTerritoryIndex, vector <Territory*> inAdjacentTerritories, int inArmyQuantity, Player* inTerritoryHolder);
        //Destructors
        ~Territory();

        //Accessors
        string getTerritoryName()const; // for Player Class
        int getX();
        int getY();
        string getContinentName();
        vector<string> getTerritoryIndex();
        vector <Territory*> getAdjacentTerritories();
        Player* getOwner(); //for Player Class
        int getNumberOfArmies(); //for Order Class

        //For Player class
        bool operator !=(const Territory* other);

        //Setters
        void setPlayer(Player* inPlayer); // For Player class
        void setTerritoryName(string inTerritoryName);
        void setX(int inX);
        void setY(int inY);
        void setTerritoryIndex(vector<string> inTerritoryIndex);
        void setContinentIndex(string inContinentIndex);
        void setAdjaccentTerritories(vector <Territory*> inAdjacentTerritories);
        void setNumberOfArmies(int NumberOfArmies);

        //Adders
        void addAdjTerritory(Territory* t);

        //Streams Assignment
        friend ostream& operator<<(ostream& out, const Territory& t);

        // OPERATOR OVERLOADS
	    Territory& operator=(const Territory& other);

    int getNumberOfArmies();
};

/**
* Implementation of a "Continent" class.
*/
class Continent
{
    private:
        //Attributes
        string continentIdentity;
        int numberOfTerritories;
        vector <Territory*> Territories;

    public:
        //Constructors
        Continent();
        Continent(const Continent& cObj);
        Continent(string inContinentIdentity, int inNumberOfTerritories);
        Continent(string inContinentIdentity, int inNumberOfTerritories, vector <Territory*> inTerritories);

        //Destructor
        ~Continent();

        //Accessors
        string getContinentIdentity();
        int getNumberOfTerritories();
        vector <Territory*> getTerritories();

        //Setters
        void setContinentIdentity(string inContinentIdentity);
        void setNumberOfTerritories(int inContinentID);
        void setTerritories(vector <Territory*> inTerritories);

        //Adders
        void addTerritoryToContinent(Territory* t);

        //Stream Insertions
        friend ostream& operator<<(ostream& out, const Continent& c);

        // OPERATOR OVERLOADS
	    Continent& operator=(const Continent& other);
        
};


/**
* Implementation of a "Map" class.
*/
class Map
{
    private:
        //Attributes
        vector <Continent*> continent;
        vector <Territory*> territory;

    public:
        //Constructors
        Map();
        Map(const Map& mObj);
        Map(vector <Continent*> inContinent, vector <Territory*> inTerritory);

        //Destructor
        ~Map();

        //Accessors
        vector <Continent*> getContinent();
        vector <Territory*> getTerritory();

        //Setters
        void setContinent(vector <Continent*> inContinent);
        void setTerritory(vector <Territory*> inTerritory);

        //Validate Method
        int getSizeOfTerritory();
        bool isVisited(Territory* currentTerritory, vector<Territory*>* visitedTerritory);
        int checkSubGraph (int indexOfContinent, vector<Territory*>* visited2);
        int DFS(Territory* currentTerritory, vector<Territory*>* visitedContinent);
        int validate();

        //Stream insertions
        friend ostream& operator<<(ostream& out, const Map& m);

    // OPERATOR OVERLOADS
        Map& operator=(const Map& other);

};


/**
* Implementation of a "Map" class.
*/
class mapLoader
{
    private:
    public:

    static Map* createMapFromConquestFile(string fileName);

    static string getContinentNameFromLine(string inStr);
    static int getNumberOfTerritoriesFromLine(string inStr);

    static Territory* getTerritoryFields(string inStr);

};