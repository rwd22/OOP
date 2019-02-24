#ifndef WAR_HPP_INCLUDED
#define WAR_HPP_INCLUDED

#include <vector>
#include <ostream>
#include <assert.h>

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

enum Color{
	Black,
	Red,
};

inline std::ostream & operator<<(std::ostream& os, Color c)
{
  return os << (c == Black ? "B" : "R");
}

class Card{    //Card structure, holds a suit and a rank for a card

    public:
        Card() {};

        void set_Suit(Suit suit)
        {
            data = data | suit;
            data = data << 4;
        }
        void set_Rank(Rank rank)
        {
            data = data | rank;
        }
		void set_Joker(Color c)
		{
			assert(get_type() == false);
			data = data | c;
			
			data = data << 1;
			
			data = data | 1;
			
			data = data << 6;
		}
		

        Rank get_rank() const {return(Rank) (data & 0xf); }
        Suit get_suit() const {return(Suit) (data >> 4 & 0xf); }
		Color get_color() const{return(Color) (data >> 6 & 0xf);}
		bool get_type() const {return(bool) (data >> 7 & 0xf);}

    private:

        unsigned int data = 0;

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

/*#ifndef WAR_HPP_INCLUDED
#define WAR_HPP_INCLUDED

#include <vector>
#include <ostream>
#include <cassert>



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

enum Color{
	Black,
	Red,
};

inline std::ostream & operator<<(std::ostream& os, Color c)
{
  return os << (c == Black ? "B" : "R");
}


class Joker{
	public:
		Joker(Color c)
			: color(c)
			{}
			
		Color get_color() const {return color;}
		
	private:
		Color color;
};

inline std::ostream & operator<<(std::ostream& os, Joker c)
{
  return os << c.get_color();
}



class Card{    //Card structure, holds a suit and a rank for a card

    public:
        Card() {};

        void set_Suit(Suit suit)
        {
            data = data | suit;
            data = data << 4;
        }
        void set_Rank(Rank rank)
        {
            data = data | rank;
        }

        Rank get_rank() const {return(Rank) (data & 0xf); }
        Suit get_suit() const {return(Suit) (data >> 4 & 0xf); }

    private:

        unsigned int data = 0;

};

inline std::ostream& operator<<(std::ostream& os, Card c)
{
  return os << c.get_suit() << c.get_rank();
}


union CardData
{
	CardData()
	: sc()
	{}
	
	CardData(Color c)
		: jc(c)
	{}
	
	Card sc;
	Joker jc;
};

enum CardType
{
	Standard,
	Joker,
};

class PlayingCard
{
	public:
		PlayingCard()
			: tag(Standard), data()
		{}
		
		PlayingCard(Color c)
			:tag(Joker), data(c)
		{}
		
		bool is_standard() const { 
			return tag == Standard;
		}

		bool is_joker() const { 
			return tag == Joker;
		}
		
		Rank get_rank() const {
			assert(is_standard());
			return data.sc.get_rank();
		}

		Suit get_suit() const { 
			assert(is_standard());
			return data.sc.get_suit();
		}

		Color get_color() const { 
			assert(is_joker());
			return data.jc.get_color();
		}

	private:
		CardType tag;
		CardData data;
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

#endif // WAR_HPP_INCLUDED*/
