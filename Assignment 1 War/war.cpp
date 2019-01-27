#include "war.hpp"

#include <vector>
#include <algorithm>
#include <random>




void Deck::make(){

    Card c;
    for (int i = 0; i < 13; ++i){
        for (int j = 0; j < 4; ++j){

            c.suit = (Suit)j;
            c.rank = (Rank)i;
            cs.push_back(c);
        }
    }
}

void Deck::cut(Deck & P1, Deck & P2){
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(cs), std::end(cs), rng);

    for(int i = 0; i < 52/2; ++i)
    {
        P1.cs.push_back(cs[i]);
    }
    for(int i = 52/2; i < 52; ++i)
    {
        P2.cs.push_back(cs[i]);
    }
}
