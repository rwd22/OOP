#include <iostream>

#include "cards.hpp"

std::ostream& operator<<(std::ostream& os, StandardC const& c)  //ostream for standard cards
{
  return os << c.rank << c.suit;
}

std::ostream& operator<<(std::ostream& os, JokerC const& c) //ostream for jokers
{
  return os << c.color << "J";
}

std::ostream& operator<<(std::ostream& os, Card const& c)   //ostream for cards
{
    if(c.type == Card::Standard)
    {
        return os << static_cast<StandardC const&>(c);  //ostreams standard cards
    }
    else
    {
        return os << static_cast<JokerC const&>(c); //ostreams jokers
    }
}

void cardType(Card const& c)    //prints card type
{
    if(c.type == Card::Joker)
    {
        std::cout << "This card is a joker" << std::endl;
    }
    else
    {
        std::cout << "This card is a standard card" << std::endl;
    }
}

void getColor(Card const& c)    //prints card color
{
    if(c.type == Card::Joker)
    {
        std::cout << c << std::endl;

    }
    else
    {
        //Useful if standard cards were given a color
        std::cout << "This card is not a joker" << std::endl;

    }
}
