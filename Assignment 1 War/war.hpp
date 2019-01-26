#ifndef WAR_HPP_INCLUDED
#define WAR_HPP_INCLUDED


#include <vector>

enum Suit{
    Hearts,
    Diamonds,
    Clubs,
    Spades,
};


enum Rank{
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};


struct Card{

    Suit suit;

    Rank rank;
};


struct Deck{

    std::vector <Card> cs;

    void make();
};

struct Player{

    Deck usable;
    Deck wins;
};

#endif // WAR_HPP_INCLUDED
