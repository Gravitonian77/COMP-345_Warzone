#include "Cards.h"

Card::Card(CardType type) : type(new CardType(type)) {}

Card::Card(const Card& other) : type(new CardType(*(other.type))) {}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        delete type;  // Release the previous type
        type = new CardType(*(other.type));
    }
    return *this;
}

Card::~Card() {
    delete type;
}

Card::CardType Card::getType() const {
    return *type;
}

void Card::play() {
    std::string typeName;

    switch (*type) {
        case CardType::BOMB:
            typeName = "BOMB";
            break;
        case CardType::REINFORCEMENT:
            typeName = "REINFORCEMENT";
            break;
        case CardType::BLOCKADE:
            typeName = "BLOCKADE";
            break;
        case CardType::AIRLIFT:
            typeName = "AIRLIFT";
            break;
        case CardType::DIPLOMACY:
            typeName = "DIPLOMACY";
            break;
        default:
            typeName = "UNKNOWN";
            break;
    }

    std::cout << "Card of type " << typeName << " has been played." << std::endl;
}


Deck::Deck() {
    // Initialize the deck with all card types
    for (int i = 0; i < 5; ++i) {
        cards.push_back(new Card(static_cast<Card::CardType>(i)));
    }
}

Deck::Deck(const Deck& other) {
    for (const Card* card : other.cards) {
        cards.push_back(new Card(*card));
    }
}

Deck& Deck::operator=(const Deck& other) {
    if (this != &other) {
        // Release memory for the current cards
        for (Card* card : cards) {
            delete card;
        }
        cards.clear();

        // Copy cards from the other deck
        for (const Card* card : other.cards) {
            cards.push_back(new Card(*card));
        }
    }
    return *this;
}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card* Deck::draw() {
    if (!cards.empty()) {
        Card* drawnCard = cards.back();
        cards.pop_back();
        return drawnCard;
    } else {
        // Handle the case when the deck is empty
        // You can throw an exception or return a special card
        return new Card(Card::CardType::BOMB); // Example, returning a bomb card
    }
}

void testCards() {
    Deck deck;
    deck.shuffle();

    // Create a hand object
    std::vector<Card*> hand;

    // Draw cards from the deck and add them to the hand
    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck.draw());
    }

    // Play the cards in the hand
    for (Card* card : hand) {
        card->play();
        delete card;  // Release the card after playing
    }
}
