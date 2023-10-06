#include "Cards.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Card Method Implementations
Card::Card(CardType type) {
    this->type = new CardType(type);
}

Card::Card(const Card& other) {
    type = new CardType(*(other.type));
}

Card& Card::operator=(const Card& other) {
    if (this == &other) return *this;
    delete type;
    type = new CardType(*(other.type));
    return *this;
}

Card::~Card() {
    delete type;
}

void Card::play() {
    std::string cardName;
    switch (*type) {
        case CardType::BOMB:
            cardName = "Bomb";
            break;
        case CardType::REINFORCEMENT:
            cardName = "Reinforcement";
            break;
        case CardType::BLOCKADE:
            cardName = "Blockade";
            break;
        case CardType::AIRLIFT:
            cardName = "Airlift";
            break;
        case CardType::DIPLOMACY:
            cardName = "Diplomacy";
            break;
    }
    std::cout << "Playing a card of type: " << cardName << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    std::string cardName;
    switch (*(card.type)) {
        case CardType::BOMB:
            cardName = "Bomb";
            break;
        case CardType::REINFORCEMENT:
            cardName = "Reinforcement";
            break;
        case CardType::BLOCKADE:
            cardName = "Blockade";
            break;
        case CardType::AIRLIFT:
            cardName = "Airlift";
            break;
        case CardType::DIPLOMACY:
            cardName = "Diplomacy";
            break;
    }
    os << "Card Type: " << cardName;
    return os;
}

// Deck Method Implementations
Deck::Deck() {
    for(int i = 0; i < 5; ++i) {  // Assuming we create a deck with one card of each type
        cards.push_back(new Card(static_cast<CardType>(i)));
    }
    std::srand(std::time(nullptr));  // Seed for random shuffling
}

Deck::Deck(const Deck& other) {
    for(auto& card : other.cards) {
        cards.push_back(new Card(*card));
    }
}

Deck& Deck::operator=(const Deck& other) {
    if (this == &other) return *this;

    for(auto& card : cards) {
        delete card;
    }
    cards.clear();

    for(auto& card : other.cards) {
        cards.push_back(new Card(*card));
    }
    return *this;
}

Deck::~Deck() {
    for(auto& card : cards) {
        delete card;
    }
}

Card* Deck::draw() {
    int random_index = std::rand() % cards.size();
    Card* drawnCard = cards[random_index];
    cards.erase(cards.begin() + random_index);
    return drawnCard;
}

void Deck::returnCard(Card* card) {
    cards.push_back(new Card(*card));  // Return a new copy of the card to the deck
}

// Hand Method Implementations
Hand::Hand() = default;

Hand::Hand(const Hand& other) {
    for(auto& card : other.cards) {
        cards.push_back(new Card(*card));
    }
}

Hand& Hand::operator=(const Hand& other) {
    if (this == &other) return *this;

    for(auto& card : cards) {
        delete card;
    }
    cards.clear();

    for(auto& card : other.cards) {
        cards.push_back(new Card(*card));
    }
    return *this;
}

Hand::~Hand() {
    for(auto& card : cards) {
        delete card;
    }
}

void Hand::addCard(Card* card) {
    cards.push_back(card);
}

void Hand::playAll(Deck& deck) {
    for(auto& card : cards) {
        card->play();
        deck.returnCard(card);
    }
    cards.clear();
}

void testCards() {  // Function definition added here
    Deck deck;
    Hand hand;

    std::cout << "Drawing 5 cards..." << std::endl;
    for (int i = 0; i < 5; ++i) {
        hand.addCard(deck.draw());
    }

    std::cout << "Playing all cards in hand..." << std::endl;
    hand.playAll(deck);
}
