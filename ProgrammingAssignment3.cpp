


#include <iostream>
#include <string>

#include "Deck.h"
#include "Card.h"

using namespace consoleCards;

// IMPORTANT: Only add code in the section
// indicated below. The code I've provided
// makes your solution work with the 
// automated grader on Coursera

/**
 * Programming Assignment 3
 * @return exit status
*/
int main()
{
    // loop while there's more input
    std::string Input;
    std::getline(std::cin, Input);
    while (Input[0] != 'q')
    {
        // Add your code between this comment
        // and the comment below. You can of
        // course add more space between the
        // comments as needed

        // declare a deck variable
        Deck deck;
        // DON'T SHUFFLE THE DECK

         std::vector<Card> player1, player2, player3, player4;
        // deal 2 cards each to 4 players (deal properly, dealing
        // the first card to each player before dealing the
        // second card to each player)
        player1.push_back(deck.TakeTopCard());
        player2.push_back(deck.TakeTopCard());
        player3.push_back(deck.TakeTopCard());
        player4.push_back(deck.TakeTopCard());

        player1.push_back(deck.TakeTopCard());
        player2.push_back(deck.TakeTopCard());
        player3.push_back(deck.TakeTopCard());
        player4.push_back(deck.TakeTopCard());

        // deal 1 more card to players 2 and 3
        player2.push_back(deck.TakeTopCard());
        player3.push_back(deck.TakeTopCard());

        // flip all the cards over
        for (auto &card : player1)
        {
            card.FlipOver();
        }
        for (auto &card : player2)
        {
            card.FlipOver();
        }
        for (auto &card : player3)
        {
            card.FlipOver();
        }
        for (auto &card : player4)
        {
            card.FlipOver();
        }

         auto printPlayerCards = [](std::vector<Card>& playerCards) {
            for (auto& card : playerCards) {
                std::cout << card.GetRank() << " of " << card.GetSuit() << std::endl;
            }
        };

        printPlayerCards(player1); // Print cards for player 1
        printPlayerCards(player2); // Print cards for player 2
        printPlayerCards(player3); // Print cards for player 3
        printPlayerCards(player4); // Print cards for player 4

        // Don't add or modify any code below
        // this comment
        std::getline(std::cin, Input);
    }
}