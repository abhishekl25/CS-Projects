// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#ifdef CONSOLECARDS_EXPORTS
#define CONSOLECARDS_API __declspec(dllexport)
#else
#define CONSOLECARDS_API __declspec(dllimport)
#endif

#include "Card.h"

#include <vector>

namespace consoleCards
{
	/**
	 * A deck of cards
	*/
	class CONSOLECARDS_API Deck
	{
	private:
		std::vector<Card> Cards;
	public:
		/**
		 * Constructor
		*/
		Deck();

		/**
		 * Gets whether or not the deck is empty
		 * @return true if the deck is empty, false otherwise
		*/
		bool IsEmpty();

		/**
		 * Cuts the deck of cards at the given location
		 * @param Location location at which to cut the deck
		*/
		void Cut(unsigned int Location);

		/**
		 * Shuffles the deck
		 * @see http://download.oracle.com/javase/1.5.0/docs/api/java/util/Collections.html#shuffle%28java.util.List%29
		*/
		void Shuffle();

		/**
		 * Takes the top card from the deck. If the deck is empty, throws
		 *		an exception
		 * @return top card
		*/
		Card TakeTopCard();

		/**
		 * Prints the cards in the deck, top to bottom
		*/
		void Print();
	};
}
