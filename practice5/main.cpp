#include <iostream>

#include "cards.hpp"

int main()
{
    std::cout << JokerC(Red) << std::endl;

    cardType(JokerC(Red));

    getColor(JokerC(Red));

    std::cout << StandardC(Four, Hearts) << std::endl;

    cardType(StandardC(Ace, Spades));

    getColor(StandardC(Ace, Spades));


    return 0;
}