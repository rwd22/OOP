#ifndef CARDS_HPP_INCLUDED
#define CARDS_HPP_INCLUDED
#include <vector>

enum Suit { //suit enumerator
    Hearts,
    Diamonds,
    Clubs,
    Spades,
};

inline std::ostream & operator<<(std::ostream & os, Suit s){ //ostream for suit
    switch(s){
    case Hearts: return os << "H";
    case Diamonds: return os << "D";
    case Clubs: return os << "C";
    case Spades: return os << "S";
    }
}

enum Rank { //rank enumerator
  Ace,
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
};

inline std::ostream & operator<<(std::ostream & os, Rank const& r){   //ostream for rank
    switch(r){
    case Ace: return os << "A";
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
    }
}

enum Color {    //color enumerator
  Black,
  Red,
};

inline std::ostream & operator<<(std::ostream & os, Color c){    //ostream for color
    switch(c){
    case Black: return os << "B";
    case Red: return os << "R";
    }
}

struct Card{    //Card structure

    enum Type{

        Standard,
        Joker,

    };

    Card(Type t) : type(t) {}

    Type type;
};

	void cardType(Card const& c);    //query type of card
    void getColor(Card const& c);   //print a card's color

std::ostream& operator<<(std::ostream& os, Card const& c);  //ostream for cards

struct StandardC : Card {   //standard card structure

    StandardC(Rank r, Suit s)
        : Card(Standard), rank(r), suit(s){}

      Rank rank;
      Suit suit;
};

std::ostream& operator<<(std::ostream& os, StandardC const& c); //ostream for standard cards

struct JokerC : Card{   //joker structure

    JokerC(Color c)
        : Card(Joker), color(c){}

        Color color;
};

std::ostream& operator<<(std::ostream& os, JokerC const& c);    //ostream for jokers
#endif // CARDS_HPP_INCLUDED
