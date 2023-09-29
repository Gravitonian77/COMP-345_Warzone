#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

Card::Card(CardType type) : type_(type) {}

void Card::play() {
    std::cout << "Playing a " << getTypeAsString() << " card." << std::endl;
}

Card::CardType Card::getType() const {
    return type_;
}

std::string Card::getTypeAsString() const {
    // Convert the card type to a string for display purposes.
    switch (type_) {
        case BOMB:
            return "bomb";
        case REINFORCEMENT:
            return "reinforcement";
        case BLOCKADE:
            return "blockade";
        case AIRLIFT:
            return "airlift";
        case DIPLOMACY:
            return "diplomacy";
        default:
            return "unknown";
    }
}

Deck::Deck() {
    initializeDeck();
}

void Deck::initializeDeck() {
    cards_.clear();
    // Initialize the deck with five cards of each type and shuffle them.
    for (int i = 0; i < 5; ++i) {
        cards_.emplace_back(Card::BOMB);
        cards_.emplace_back(Card::REINFORCEMENT);
        cards_.emplace_back(Card::BLOCKADE);
        cards_.emplace_back(Card::AIRLIFT);
        cards_.emplace_back(Card::DIPLOMACY);
    }
    shuffleDeck();
}

Card Deck::draw() {
    if (cards_.empty()) {
        initializeDeck();
    }
    // Draw and return the top card from the deck.
    Card drawnCard = cards_.back();
    cards_.pop_back();
    return drawnCard;
}

void Deck::shuffleDeck() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Shuffle the cards in the deck using random shuffling.
    std::random_shuffle(cards_.begin(), cards_.end());
}

void Hand::addCard(const Card& card) {
    // Add a card to the hand.
    cards_.push_back(card);
}

void Hand::playAll() {
    // Simulate playing all cards in the hand.
    for (Card& card : cards_) {
        card.play();
    }
    // Clear the hand after playing all cards.
    cards_.clear();
}