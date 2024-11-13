

#pragma once

#ifdef CONSOLECARDS_EXPORTS
#define CONSOLECARDS_API __declspec(dllexport)
#else
#define CONSOLECARDS_API __declspec(dllimport)
#endif

#include "Rank.h"
#include "Suit.h"

namespace consoleCards
{
	/**
	 * A playing card
	*/
	class CONSOLECARDS_API Card
	{
	private:
		Rank Rank;
		Suit Suit;
		bool bFaceUp;
	public:
		/**
		 * Constructs a card with the given rank and suit
		 * @param Rank rank
		 * @param Suit suit
		*/
		Card(consoleCards::Rank Rank, consoleCards::Suit Suit);

		/**
		 * Gets the string representation of the card rank. If
		 *		the card isn't face up, returns a string to that effect
		 * @return rank
		*/
		std::string GetRank();

		/**
		 * Gets the string representation of the card suit. If
		 *		the card isn't face up, returns a string to that effect
		 * @return suit
		*/
		std::string GetSuit();

		/**
		 * Gets whether or not the card is face up
		 * @return true if face up, false if face down
		*/
		bool IsFaceUp();

		/**
		 * Flips the card over
		*/
		void FlipOver();

		/**
		 * Prints the card
		*/
		void Print();
	};
}