#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Player;

class Territory
{
   private:
        // "Conquest" game format
        string territoryName;
        int x; //Cartesion coordinate x
        int y; //Cartesion coordinate y
        string continentName;
        vector <string> territoryIndex;
        vector<Territory*> adjacentTerritories;

        int numberOfArmies;
        Player *owner;
    public:

        //Constructors
        Territory();
        Territory(const Territory& tObj);
        Territory(string inTerritoryName, int inX, int inY, string inContinentName, vector <Territory*> inAdjacentTerritories, int inArmyQuantity, Player* inTerritoryHolder);

        //Accessors
        string getTerritoryName();
        int getX();
        int getY();
        string getContinentName();
        vector <Territory*> getAdjacentTerritories();

        //Setters
        void setTerritoryName(string inTerritoryName);
        void setX(int inX);
        void setY(int inY);
        void setContinentIndex(string inContinentIndex);
        void setAdjaccentTerritories(vector <Territory*> inAdjacentTerritories);


};

class Continent
{
    private:
        string continentIdentity;
        int numberOfTerritories;
        vector <Territory*> Territories;

    public:
        //Constructors
        Continent();
        Continent(const Continent& cObj);
        Continent(string inContinentIdentity, int inNumberOfTerritories);
        Continent(string inContinentIdentity, int inNumberOfTerritories, vector <Territory*> inTerritories);

        //Accessors
        string getContinentIdentity();
        int getNumberOfTerritories();
        vector <Territory*> getTerritories();

        //Setters
        void setContinentIdentity(string inContinentIdentity);
        void setNumberOfTerritories(int inContinentID);
        void setTerritories(vector <Territory*> inTerritories);
        
};



class Map
{
    private:
        vector <Continent*> continent;
        vector <Territory*> territory;

    public:
        //Constructors
        Map();
        Map(const Map& mObj);
        Map(vector <Continent*> inContinent, vector <Territory*> inTerritory);

        //Accessors
        vector <Continent*> getContinent();
        vector <Territory*> getTerritory();

        //Setters
        void setContinent(vector <Continent*> inContinent);
        void setTerritory(vector <Territory*> inTerritory);
};








class mapLoader
{
    private:
    public:

    static Map* createMapFromConquestFile(string fileName);

    static string getContinentNameFromLine(string inStr);
    static int getNumberOfTerritoriesFromLine(string inStr);

    static string getContinentIDFromTerritory(string inStr);

};
