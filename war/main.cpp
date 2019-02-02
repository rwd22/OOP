#include <iostream>
#include "war.hpp"


#include <vector>
#include <limits>

using namespace std;

int main()
{
    Player one;
    Player two;
    Deck d;
    d.make();
    d.cut(one.usable, two.usable);
    Deck pile;

    string key;
    bool loopFlag = true;
    bool warloop;
    bool endgame = false;
    int warcount = 0;
    int warwin = 0;
    int winner = 0;


    vector<Card>::iterator itone;
     vector<Card>::iterator ittwo;

    while( endgame == false)
    {
       /* cout << "one" << endl;


                for(int i = 0; i < one.usable.cs.size(); ++i)
                {
                    cout << one.usable.cs[i].rank << endl;
                }
                        cout << "two" << endl;

                for(int i = 0; i < two.usable.cs.size(); ++i)
                {
                    cout << two.usable.cs[i].rank << endl;
                }*/

                   /*     cout << "one" << endl;


                for(int i = 0; i < one.wins.cs.size(); ++i)
                {
                    cout << one.wins.cs[i].rank << endl;
                }
                        cout << "two" << endl;

                for(int i = 0; i < two.wins.cs.size(); ++i)
                {
                    cout << two.wins.cs[i].rank << endl;
                }*/


        loopFlag = true;

       // cout << one.usable.cs.size() << " and " << two.usable.cs.size() << endl;

       /* do  //validation for the file name
        {
            std::cout << "Enter a to play a card." << endl;
            cin >> key;

            if(key != "a")    //checking to see if the file exists
            {
                cout << "Press Enter to play a card.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                loopFlag = false;
            }
        }while(loopFlag);*/

        if(one.usable.cs[one.usable.cs.size()-1].rank > two.usable.cs[two.usable.cs.size()-1].rank)
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

            one.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            one.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();

        }
        else if(one.usable.cs[one.usable.cs.size()-1].rank < two.usable.cs[two.usable.cs.size()-1].rank)
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

            two.wins.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);
            two.wins.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);

            one.usable.cs.pop_back();
            two.usable.cs.pop_back();
        }
        else
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") ties with other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;
            cout << "THIS MEANS WAR" << endl;

            //cout << one.usable.cs.size() << " and " << two.usable.cs.size() << endl;

            warloop = true;
            warcount = 0;

            if(one.usable.cs.size() <= 2)
                {
                    if((one.wins.cs.size() + one.usable.cs.size()) <= 3)
                    {
                        cout << "Player 1 does not have enough cards for war!" <<endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        cout << "Player 2 does not have enough cards for war!" <<endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
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
                        cout << "Player 1 does not have enough cards for war!" <<endl;
                        winner = 2;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        one.usable.cs.insert(one.usable.cs.begin(), one.wins.cs.begin(), one.wins.cs.end());

                        one.wins.cs.clear();
                    }
                }

                if(two.usable.cs.size() <= 2)
                {
                    if((two.wins.cs.size() + two.usable.cs.size()) <= 3)
                    {
                        cout << "Player 2 does not have enough cards for war!" <<endl;
                        winner = 1;
                        endgame = true;
                        warloop = false;
                    }
                    else
                    {
                        two.usable.cs.insert(two.usable.cs.begin(), two.wins.cs.begin(), two.wins.cs.end());

                        two.wins.cs.clear();
                    }
                }

                //itone = one.usable.cs.end() -1; //iterator to last element i.e. card just played
                //ittwo = two.usable.cs.end() -1;

                //start at back, put one in pile, put two in pile and compare. IF one wins give pile to that player, else do same again

            pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 first card
            pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 first card

            one.usable.cs.pop_back();   //remove previous cards from players
            two.usable.cs.pop_back();

            //compare next player cards

            if(one.usable.cs[one.usable.cs.size()-1].rank > two.usable.cs[two.usable.cs.size()-1].rank)
            {
                cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

                pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                one.usable.cs.pop_back();   //remove previous cards from players
                two.usable.cs.pop_back();

                one.wins.cs.insert(one.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                pile.cs.clear();

                warloop = false;

            }
            else if(one.usable.cs[one.usable.cs.size()-1].rank < two.usable.cs[two.usable.cs.size()-1].rank)
            {
                cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

                pile.cs.push_back(one.usable.cs[one.usable.cs.size()-1]);//add p1 next card
                pile.cs.push_back(two.usable.cs[two.usable.cs.size()-1]);//add p2 next card

                one.usable.cs.pop_back();   //remove previous cards from players
                two.usable.cs.pop_back();

                two.wins.cs.insert(two.wins.cs.begin(), pile.cs.begin(), pile.cs.end());

                pile.cs.clear();

                warloop = false;
            }

            //add to pile + remove from players

            //give to winner + set warloop false















            }












        }
        if(one.usable.cs.empty() == true )//&& one.wins.cs.empty() == true)
        {
            if(one.wins.cs.empty() == true)
            {
                winner = 2;
                endgame = true;
            }
            else
            {
                one.usable.cs.swap(one.wins.cs);

            }
        }
        if(two.usable.cs.empty() == true )//&& two.wins.cs.empty() == true)
        {
            if(two.wins.cs.empty() == true)
            {
                winner = 1;
                endgame = true;
            }
            else
            {
                two.usable.cs.swap(two.wins.cs);
            }

        }

    }

    cout << "Winner is:" << winner << endl;



    return 0;
}
