#ifndef CARDS_H
#define CARDS_H

#pragma once

#include <vector>
#include <string>

enum class CardType {
    BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
};

class Card {
private:
    CardType* type;
public:
    explicit Card(CardType type);
    Card(const Card& other);
    Card& operator=(const Card& other);
    ~Card();
    void play();
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
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
};

void testCards();  // Function declaration added here

#endif
