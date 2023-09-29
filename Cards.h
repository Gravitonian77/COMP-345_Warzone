#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>

class Card {
public:
    enum CardType {
        BOMB,
        REINFORCEMENT,
        BLOCKADE,
        AIRLIFT,
        DIPLOMACY
    };

    // Constructor to initialize a Card object with a specific type.
    Card(CardType type);

    // Method to simulate playing a card.
    void play();

    // Getter method to retrieve the card's type.
    CardType getType() const;

    // Getter method to retrieve the card's type as a string.
    std::string getTypeAsString() const;

private:
    CardType type_;
};

class Deck {
public:
    // Constructor to initialize a Deck object.
    Deck();

    // Method to initialize and shuffle the deck.
    void initializeDeck();

    // Method to draw a card from the deck.
    Card draw();

private:
    std::vector<Card> cards_;

    // Helper method to shuffle the deck.
    void shuffleDeck();
};

class Hand {
public:
    // Method to add a card to the hand.
    void addCard(const Card& card);

    // Method to simulate playing all cards in the hand.
    void playAll();

private:
    std::vector<Card> cards_;
};

#endif // CARDS_H
