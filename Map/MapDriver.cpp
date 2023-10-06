/*
Name: Dan Tran and Student ID: 27525834 COMP345
Assignment #1 
Due Date : 2023-11-06
*/

#include <iostream>
#include "Map.h"
#include "Map.cpp"

using namespace std;

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

int main()
{
    testLoadMaps();
}