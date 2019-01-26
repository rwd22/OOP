#include "war.hpp"

#include <vector>


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
