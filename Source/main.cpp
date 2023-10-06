// MainDriver.cpp
#include "Cards.h"

// Function to test the Card classes
void testCards() {
    Deck deck;
    Hand hand;

    // Fill the hand by drawing cards from the deck
    for (int i = 0; i < 5; ++i) {
        Card card = deck.draw();
        hand.addCard(card);
    }

    // Play all cards in the hand and return them to the deck
    hand.playAll(deck);

    std::cout << "Cards remaining in the deck: " << deck.size() << std::endl;
}

int main() {
    testCards();
    return 0;
}
