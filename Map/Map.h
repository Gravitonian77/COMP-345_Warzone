#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Player;

class Continent
{
    private:
        string continentIdentity;
        int continentID;

    public:
        //Default Constructor
        Continent();
        //Parameterized Constructor
        Continent(string inContinentIdentity, int inContinentID);

        //Accessors
        string getContinentIdentity();
        int getContinentID();

        //Setters
        void setContinentIdentity(string inContinentIdentity);
        void setContinentID(int inContinentID);
        
};

class Territory
{
   private:
        // "Conquest" game format
        string territoryIdentity;
        int x; //Cartesion coordinate x
        int y; //Cartesion coordinate y
        Continent *continentOfTerritory;
        vector<Territory*> adjacentTerritories;

        int armiesQuantity;
        //NEED TO INCLUDE THE PLAYER HEADFILE AT THE END
        Player *territoryHolder;

    public:

        //Constructors
        Territory();
        Territory(string inTerritoryIdentity, int inX, int inY, Continent inContinentOfTerritory, vector <Territory> inAdjacentTerritories);

        //Accessors
        string getTerritoryIdentity();
        int getX();
        int getY();
        Continent getContinentOfTerritory;
        vector <Territory> getAdjacentTerritories;

        //Setters
        void setTerritoryIdentity(string inTerritoryIdentity);
        void setX(int inX);
        void setY(int inY);
        void setContinentOfTerritory(Continent inContinentOfTerritory);
        void setAdjaccentTerritories(vector <Territory> inAdjacentTerritories);


};