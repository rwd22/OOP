#ifndef WAR_HPP_INCLUDED
#define WAR_HPP_INCLUDED

#include <vector>
#include <ostream>

enum Suit{  //enumeration for suits
    Hearts,
    Diamonds,
    Clubs,
    Spades,
};

inline std::ostream & operator<<(std::ostream & os, Suit s){    //overloaded Ostream for suits
    switch(s){
    case Hearts: return os << "H";
    case Diamonds: return os << "D";
    case Clubs: return os << "C";
    case Spades: return os << "S";
    }
}

enum Rank{  //enumeration for rank
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

inline std::ostream & operator<<(std::ostream & os, Rank r){    //overloaded Ostream for rank
    switch(r){
    case One: return os << "1";
    case Two: return os << "2";
    case Three: return os << "3";
    case Four: return os << "4";
    case Five: return os << "5";
    case Six: return os << "6";
    case Seven: return os << "7";
    case Eight: return os << "8";
    case Nine: return os << "9";
    case Ten: return os << "T";
    case Jack: return os << "J";
    case Queen: return os << "Q";
    case King: return os << "K";
    case Ace: return os << "A";
    }
}

struct Card{    //Card structure, holds a suit and a rank for a card

    Suit suit;

    Rank rank;
};

struct Deck{    //deck struct, holds cards and can make a full deck and split that among two players

    std::vector <Card> cs;

    void make();
    void cut(Deck &, Deck &);
};

struct Player{  //player struct, holds two decks, one to use and one holding their winnings to be place into their usable hand when low on cards

    Deck usable;
    Deck wins;
};

#endif // WAR_HPP_INCLUDED
