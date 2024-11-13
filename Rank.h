// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#ifdef CONSOLECARDS_EXPORTS
#define CONSOLECARDS_API __declspec(dllexport)
#else
#define CONSOLECARDS_API __declspec(dllimport)
#endif

#include <iostream>

/**
 * @file Rank.h
*/

namespace consoleCards
{
	/**
	 * @brief An enumeration for card ranks
	*/
	enum class Rank
	{
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
	};
}
