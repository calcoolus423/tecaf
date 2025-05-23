/*****************************************************************************\
*  _____  _____   ____   ___   _____                                          *
* |_   _||  ___| / ___) / _ \ |  ___|                                         *
*   | |  | |__  | /    / /_\ \| |__                                           *
*   | |  |  __| | |    |  _  ||  __|                                          *
*   | |  | |___ | \___ | | | || |                                             *
*   |_|  |_____| \____)|_| |_||_|                                             *
*                                                                             *
*   A collection of algorithms and functions that make for a more diverse C++ *
*   coding experience. Primarily centered around mathematical functions,      *
*   expressions, and evaluations, this library allows for user-creation and   *
*   analysis of numerical/analystical functions.                              *
*   This file mostly acts as a wrapper for other hpp files.                   *
*	Written in C++20.
\*****************************************************************************/

#pragma once


#include "expression.hpp"
#include "realfx.hpp"


// calculate euler's constant
const long double E = std::exp(1);


	/* prototypes */

// purpose: prints the data to the console and breaks the line
// requires: anything that can be printed
// returns: nothing
template <class adt>
void print(adt data) { std::cout << data << '\n'; }

// purpose: print a line to the console
// requires: nothing
// returns: nothing
void print() { std::cout << '\n'; }

