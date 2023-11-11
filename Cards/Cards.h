#ifndef CARDS_H
#define CARDS_H

#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum class CardType {
    BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
};

class Card {
private:
    CardType* type;
    string cardTypeName;
public:
    explicit Card(CardType type);
    Card(const Card& other);
    Card& operator=(const Card& other);
    ~Card();
    void play();
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    CardType* getType() const; 
    string getCardTypeName() const;
};
};

class Deck {
private:
    std::vector<Card*> cards;
public:
    Deck();
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);
    ~Deck();
    Card* draw();
    void returnCard(Card* card);
};

class Hand {
private:
    std::vector<Card*> cards;
public:
    Hand();
    Hand(const Hand& other);
    Hand& operator=(const Hand& other);
    ~Hand();
    void addCard(Card* card);
    void playAll(Deck& deck);
    std::vector<Card*> getCards() const;
};

void testCards();  // Function declaration added here

#endif
