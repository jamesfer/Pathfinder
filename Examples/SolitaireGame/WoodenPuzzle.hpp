#ifndef WoodenPuzzle_hpp
#define WoodenPuzzle_hpp

#define BOARD_SIZE 4 * 6 + 9

#include "State.hpp"
#include <map>
#include <iostream>
#include <array>
#include "JumpPin.hpp"

using namespace std;


/**
 * Represent a wooden pin puzzle in this shape:
 *   0 1 2 3 4 5 6
 * 0     * * *
 * 1     * * *
 * 2 * * * * * * *
 * 3 * * *   * * *
 * 4 * * * * * * *
 * 5     * * *
 * 6     * * *
 */
class WoodenPuzzle
{
	/**
	 * Indexes that are true have a pin in them
	 */
	array<bool, BOARD_SIZE> board;
	
public:
	WoodenPuzzle();
	
	
	virtual ~WoodenPuzzle();
	
	
	/**
	 * Checks that the pins match on each board
	 */
	bool operator==(const WoodenPuzzle& other) const;
	
	
	/**
	 * Sort the puzzles by board state. Indexes that have a 1 come after 0s.
	 */
	bool operator<(const WoodenPuzzle& other) const;
	
	
	/**
	 * Returns neighbouring board states
	 */
	vector<pair<shared_ptr<Action>, shared_ptr<WoodenPuzzle>>> getActions() const;
	
	
	/**
	 * Prints the board in the correct shape.
	 */
	friend ostream& operator<<(ostream& output, const WoodenPuzzle& puzzle);
	
	
	/**
	 * Turns x y coordinates into a linear index.
	 */
	static unsigned char indexOf(const unsigned char x, const unsigned char y);
	
	
	/**
	 * Converts a linear index into x y coords
	 */
	static pair<unsigned char, unsigned char> coordOf(unsigned char index);
	
	
	/**
	 * Returns whether there is a pin at the coordinates x and y
	 */
	bool at(unsigned char x, unsigned char y) const;
	
	
	/** 
	 * Returns whether there is a pin at the linear index.
	 */
	bool at(unsigned char index) const;
	
protected:
	/**
	 * Returns true if a move is valid.
	 * A valid move means that there is no pin at (newX, newY) and there is a 
	 * pin in the gap between (pinX, pinY) and (newX, newY).
	 */
	bool checkMove(unsigned char pinX, unsigned char pinY, unsigned char newX, unsigned char newY, JumpPin& action, WoodenPuzzle& newState) const;
	
public:
	/**
	 * Heuristic functor that returns the number of pins remaining.
	 */
	struct PiecesRemainingHeuristic
	{
		int operator()(shared_ptr<WoodenPuzzle> puzzle) const
		{
			// Start at -1 because we want to count the moves until 1 pin is left
			// Therefore if a board has 1 pin remaining it should have a cost of 0
			int remainingPins = -1;
			
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				if (puzzle->board[i])
				{
					++remainingPins;
				}
			}
			
			return remainingPins;
		}
	};
	
	
	/**
	 * Returns true when there is only one pin remaining.
	 */
	struct SuccessCheck
	{
		bool operator()(const WoodenPuzzle& puzzle) const
		{
			unsigned char remainingPins = 0;
			
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				if (puzzle.board[i])
				{
					++remainingPins;
				}
			}
			
			return remainingPins == 1;
		}
	};
};


#endif /* WoodenPuzzle_hpp */
