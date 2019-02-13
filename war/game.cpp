#include <iostream>
#include "war.hpp"
#include "game.hpp"

#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>


void Game::play() //fully plays a game of war, printing the results of each "Battle"
{
    Player one; //set up the two players
    Player two;

    Deck pile;//an extra deck for war cards

    Deck d;//construct and cut a main deck among two players
    d.make();
    d.cut(one.usable, two.usable);

    std::string key;    //setting up variables
    bool warloop;
    bool endgame = false;
    int winner = 0;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();    //seeds used for shuffling
    auto rng = std::default_random_engine (seed);


    while( endgame == false)
    {
        if(one.usable.cs[one.usable.cs.size()-1].get_rank() > two.usable.cs[two.usable.cs.size()-1].get_rank()) //if P1 wins give the cards to his win pile
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

            one.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            one.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();
        }
        else if(one.usable.cs[one.usable.cs.size()-1].get_rank() < two.usable.cs[two.usable.cs.size()-1].get_rank())    //if P2 wins the cards go to his pile
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

            two.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            two.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();
        }
        else    //the cards tie and there is a war
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") ties with other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;
            std::cout << "THIS MEANS WAR" << std::endl;

            warloop = true;

            if(one.usable.cs.size() <= 2)   //ensure there are enough cards for a war
                {
                    if((one.wins.cs.size() + one.usable.cs.size()) <= 3)    //if the win pile has insufficient cards to continue end the game
                    {
                        std::cout << "Player 1 does not have enough cards for war!" << std::endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else    //otherwise add the win pile to the players hand
                    {
                        std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)   //do the same check for player 2
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 2 does not have enough cards for war!" << std::endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                        two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                        two.wins.cs.clear();
                    }
                }

            pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 war card to pile
            pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 war card to pile

            one.usable.cs.pop_back();   //remove previous cards
            two.usable.cs.pop_back();

            while(warloop == true)
            {
                if(one.usable.cs.size() <= 2)
                {
                    if((one.wins.cs.size() + one.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 1 does not have enough cards for war!" << std::endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 2 does not have enough cards for war!" << std::endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                        two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                        two.wins.cs.clear();
                    }
                }

                pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 first card
                pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 first card

                one.usable.cs.pop_back();   //remove previous cards from players
                two.usable.cs.pop_back();

                if(one.usable.cs[one.usable.cs.size()-1].get_rank() > two.usable.cs[two.usable.cs.size()-1].get_rank())
                {
                    std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

                    pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                    pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                    one.usable.cs.pop_back();   //remove previous cards from players
                    two.usable.cs.pop_back();

                    one.wins.cs.insert(one.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                    pile.cs.clear();

                    warloop = false;

                }
                else if(one.usable.cs[one.usable.cs.size()-1].get_rank() < two.usable.cs[two.usable.cs.size()-1].get_rank())
                {
                    std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

                    pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                    pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                    one.usable.cs.pop_back();   //remove previous cards from players
                    two.usable.cs.pop_back();

                    two.wins.cs.insert(two.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                    pile.cs.clear();

                    warloop = false;
                }
            }
        }

        if(one.usable.cs.empty() == true )  //check for empty hands, if they are empty check the wins pile for that player and see if continuing is possible, otherwise the game is over
        {
            if(one.wins.cs.empty() == true)
            {
                winner = 2;
                endgame = true;
            }
            else
            {
                std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                one.wins.cs.clear();
            }
        }
        if(two.usable.cs.empty() == true )
        {
            if(two.wins.cs.empty() == true)
            {
                winner = 1;
                endgame = true;
            }
            else
            {
                std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                two.wins.cs.clear();
            }
        }
    }

    std::cout << "Winner is:" << winner << std::endl;
}

void Game::single()
{
    Player one; //set up the two players
    Player two;

    Deck pile;//an extra deck for war cards

    Deck d;//construct and cut a main deck among two players
    d.make();
    d.cut(one.usable, two.usable);

    std::string key;    //setting up variables
    bool warloop;
    bool endgame = false;
    int winner = 0;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();    //seeds used for shuffling
    auto rng = std::default_random_engine (seed);



        if(one.usable.cs[one.usable.cs.size()-1].get_rank() > two.usable.cs[two.usable.cs.size()-1].get_rank()) //if P1 wins give the cards to his win pile
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

            one.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            one.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();
        }
        else if(one.usable.cs[one.usable.cs.size()-1].get_rank() < two.usable.cs[two.usable.cs.size()-1].get_rank())    //if P2 wins the cards go to his pile
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

            two.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            two.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();
        }
        else    //the cards tie and there is a war
        {
            std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") ties with other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;
            std::cout << "THIS MEANS WAR" << std::endl;

            warloop = true;

            if(one.usable.cs.size() <= 2)   //ensure there are enough cards for a war
                {
                    if((one.wins.cs.size() + one.usable.cs.size()) <= 3)    //if the win pile has insufficient cards to continue end the game
                    {
                        std::cout << "Player 1 does not have enough cards for war!" << std::endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else    //otherwise add the win pile to the players hand
                    {
                        std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)   //do the same check for player 2
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 2 does not have enough cards for war!" << std::endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                        two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                        two.wins.cs.clear();
                    }
                }

            pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 war card to pile
            pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 war card to pile

            one.usable.cs.pop_back();   //remove previous cards
            two.usable.cs.pop_back();

            while(warloop == true)
            {
                if(one.usable.cs.size() <= 2)
                {
                    if((one.wins.cs.size() + one.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 1 does not have enough cards for war!" << std::endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        std::cout << "Player 2 does not have enough cards for war!" << std::endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                        two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                        two.wins.cs.clear();
                    }
                }

                pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 first card
                pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 first card

                one.usable.cs.pop_back();   //remove previous cards from players
                two.usable.cs.pop_back();

                if(one.usable.cs[one.usable.cs.size()-1].get_rank() > two.usable.cs[two.usable.cs.size()-1].get_rank())
                {
                    std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

                    pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                    pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                    one.usable.cs.pop_back();   //remove previous cards from players
                    two.usable.cs.pop_back();

                    one.wins.cs.insert(one.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                    pile.cs.clear();

                    warloop = false;

                }
                else if(one.usable.cs[one.usable.cs.size()-1].get_rank() < two.usable.cs[two.usable.cs.size()-1].get_rank())
                {
                    std::cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].get_suit() << one.usable.cs[one.usable.cs.size()-1].get_rank() << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].get_suit() << two.usable.cs[two.usable.cs.size()-1].get_rank() << ")" << std::endl;

                    pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                    pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                    one.usable.cs.pop_back();   //remove previous cards from players
                    two.usable.cs.pop_back();

                    two.wins.cs.insert(two.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                    pile.cs.clear();

                    warloop = false;
                }
            }
        }

        if(one.usable.cs.empty() == true )  //check for empty hands, if they are empty check the wins pile for that player and see if continuing is possible, otherwise the game is over
        {
            if(one.wins.cs.empty() == true)
            {
                winner = 2;
                endgame = true;
            }
            else
            {
                std::shuffle(std::begin(one.wins.cs), std::end(one.wins.cs), rng);

                one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                one.wins.cs.clear();
            }
        }
        if(two.usable.cs.empty() == true )
        {
            if(two.wins.cs.empty() == true)
            {
                winner = 1;
                endgame = true;
            }
            else
            {
                std::shuffle(std::begin(two.wins.cs), std::end(two.wins.cs), rng);

                two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                two.wins.cs.clear();
            }
        }

}
