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

    string key;
    bool loopFlag = true;
    bool warloop;
    bool endgame = false;
    int warcount = 0;
    int warwin = 0;


    vector<Card>::iterator itone;
     vector<Card>::iterator ittwo;


    //while( endgame == false)
   // {

        loopFlag = true;

        do  //validation for the file name
        {
            std::cout << "Press A to play a card." << endl;
            cin >> key;

            if(key != "A")    //checking to see if the file exists
            {
                cout << "Press Enter to play a card.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                loopFlag = false;
            }
        }while(loopFlag);

        if(one.usable.cs[one.usable.cs.size()-1].rank > two.usable.cs[two.usable.cs.size()-1].rank)
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") beats other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

            one.wins.cs.push_back(one.usable.cs[one.usable.cs.size()]);
            one.wins.cs.push_back(two.usable.cs[two.usable.cs.size()]);

            one.wins.cs.pop_back();
            two.wins.cs.pop_back();
        }
        else if(one.usable.cs[one.usable.cs.size()-1].rank < two.usable.cs[two.usable.cs.size()-1].rank)
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") loses to other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;

            two.wins.cs.push_back(one.usable.cs[one.usable.cs.size()]);
            two.wins.cs.push_back(two.usable.cs[two.usable.cs.size()]);

            one.wins.cs.pop_back();
            two.wins.cs.pop_back();
        }
        else
        {
            cout << "Your card (rank: " << one.usable.cs[one.usable.cs.size()-1].rank << ") ties with other card (rank: " << two.usable.cs[two.usable.cs.size()-1].rank << ")" << endl;
            cout << "THIS MEANS WAR" << endl;

            itone = one.usable.cs.end() -1; //iterator to last element i.e. card just played
            ittwo = two.usable.cs.end() -1;

            //now set to two cards forward, check value and give winner the six cards ( card just played, card after, and card compared for the war for each player

            warloop = true;

            while(warloop == true)
            {
                itone--;
                itone--;//player one card to compare
                ittwo--;
                ittwo--;//player two card to compare


                if((*itone).rank > (*ittwo).rank)
                {
                    cout << "Your card (rank: " << (*itone).rank << ") beats other card (rank: " << (*ittwo).rank << ")" << endl;

                    warcount++;

                    warwin = 1;



                    warloop = false;

                }

                else if((*itone).rank < (*ittwo).rank)
                {
                    cout << "Your card (rank: " << (*itone).rank << ") loses to other card (rank: " << (*ittwo).rank << ")" << endl;

                    warcount++;

                    warwin = 2;

                    warloop = false;

                }
                else
                {
                    cout << "Your card (rank: " << (*itone).rank<< ") ties with other card (rank: " << (*ittwo).rank << ")" << endl;
                    cout << "THIS MEANS WAR" << endl;

                    warcount++;
                }
            }

            if(warwin == 1)
            {
               while(warcount != 0)
                {
                    one.wins.cs.push_back(*itone);
                    one.wins.cs.push_back(*ittwo);

                    itone++;//card after
                    ittwo++;

                    one.wins.cs.push_back(*itone);
                    one.wins.cs.push_back(*ittwo);

                    itone++;//source of war
                    ittwo++;

                    one.wins.cs.push_back(*itone);
                    one.wins.cs.push_back(*ittwo);

                    one.wins.cs.pop_back();//war card
                    two.wins.cs.pop_back();

                    one.wins.cs.pop_back();//middle card
                    two.wins.cs.pop_back();

                    one.wins.cs.pop_back();//compared for war
                    two.wins.cs.pop_back();

                        warcount--;
                }
                warwin = 0;
            }
            else
            {
                while(warcount != 0)
                {
                    two.wins.cs.push_back(*itone);
                    two.wins.cs.push_back(*ittwo);

                    itone++;//card after
                    ittwo++;

                    two.wins.cs.push_back(*itone);
                    two.wins.cs.push_back(*ittwo);

                    itone++;//source of war
                    ittwo++;

                    two.wins.cs.push_back(*itone);
                    two.wins.cs.push_back(*ittwo);

                    one.wins.cs.pop_back();//war card
                    two.wins.cs.pop_back();

                    one.wins.cs.pop_back();//middle card
                    two.wins.cs.pop_back();

                    one.wins.cs.pop_back();//compared for war
                    two.wins.cs.pop_back();

                    warcount--;
                }
                warwin = 0;

            }






        }

    //}



    return 0;
}