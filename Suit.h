// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#ifdef CONSOLECARDS_EXPORTS
#define CONSOLECARDS_API __declspec(dllexport)
#else
#define CONSOLECARDS_API __declspec(dllimport)
#endif

#include <iostream>

/**
 * @file Suit.h
*/

namespace consoleCards
{
	/**
	 * @brief An enumeration for card suits
	*/
	enum class Suit
	{
		Clubs,		
		Diamonds,	
		Hearts,		
		Spades		
	};
}
