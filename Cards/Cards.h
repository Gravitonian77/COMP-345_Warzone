#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

class Card {
public:
    enum class CardType { BOMB,
            REINFORCEMENT,
            BLOCKADE,
            AIRLIFT,
            DIPLOMACY };

    explicit Card(CardType type);
    Card(const Card& other);
    Card& operator=(const Card& other);
    ~Card();

    [[nodiscard]] CardType getType() const;
    void play();  // Play the card and add an order

private:
    CardType* type;  // Use a pointer for card type
};

class Deck {
public:
    Deck();
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);
    ~Deck();

    void shuffle();
    Card* draw();  // Use a pointer for the drawn card

private:
    std::vector<Card*> cards;  // Use pointers for cards in the deck
};

void testCards();

#endif
