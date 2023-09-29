// CardsDriver.cpp
#include "Cards.h"

void testCards() {
    Deck deck;
    Hand hand;

    // Draw cards from the deck and add them to the hand.
    for (int i = 0; i < 5; ++i) {
        Card drawnCard = deck.draw();
        hand.addCard(drawnCard);
    }

    // Play all cards in the hand.
    hand.playAll();
}

int main() {
    testCards();
    return 0;
}