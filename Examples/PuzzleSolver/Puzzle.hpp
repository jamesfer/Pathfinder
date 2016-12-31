#ifndef Puzzle_hpp
#define Puzzle_hpp

#include <array>
#include <vector>
#include <utility>
#include <iostream>
#include <memory>
#include "Action.hpp"
#include "MoveTile.hpp"

using namespace std;


class Puzzle
{
	/**
	 * The numbers of the tiles on the board
	 */
	vector<unsigned short> board;
	
	
	/** 
	 * Dimensions of the puzzle
	 */
	unsigned short width;
	unsigned short height;
	
	
	/**
	 * Index of the zero tile
	 */
	unsigned short zeroIndex;
	
	
public:
	Puzzle(const unsigned short width, const unsigned short height);
	
	
	/**
	 * Compares puzzles first by their length, and then by the numbers in 
	 * their board array.
	 */
	bool operator<(const Puzzle& other) const;
	
	
	/**
	 * Checks that board states match exactly
	 */
	bool operator==(const Puzzle& other) const;
	
	
	/**
	 * Returns neighbouring puzzles.
	 */
	vector<pair<shared_ptr<Action>, shared_ptr<Puzzle>>> getActions() const;
	
	
	/**
	 * Stream read operator
	 */
	friend istream& operator>>(istream& input, Puzzle& obj);
	
	
	/**
	 * Prints the board in shape
	 */
	friend ostream& operator<<(ostream& output, const Puzzle& obj);
	
	
	/**
	 * Returns the number on the board at the given index
	 */
	unsigned short at(const unsigned short index) const;
	
	
	/**
	 * Helper function to extract the dimensions from a stream in the form: MxN
	 */
	static void extractDimensions(istream& input, unsigned short& width, unsigned short& height);
	
	
private:
	/**
	 * Converts a set of coordinates into a linear index.
	 */
	unsigned short indexOf(const unsigned short x, const unsigned short y) const;
	
	/**
	 * Converts a linear index into a set of coordinates
	 */
	void coordsAt(const unsigned short index, unsigned short& x, unsigned short& y) const;
	
	/**
	 * Performs a move if valid and stores the new state and action details in 
	 * the pair argument.
	 */
	bool makeMove(unsigned short newZeroX, unsigned short newZeroY, Direction dir, pair<shared_ptr<Action>, shared_ptr<Puzzle>>& details) const;
	
public:
	struct ManhattanDistanceHeuristic
	{
	private:
		Puzzle* goal;
		
	public:
		ManhattanDistanceHeuristic(Puzzle* goal) : goal(goal)
		{
			
		}
		
		
		int operator()(const shared_ptr<Puzzle>& puzzle) const
		{
			int estimate = 0;
			unsigned short curX, curY, goalX, goalY;
			
			// Loop through each piece in the current puzzle
			for (unsigned short i = 0; i < puzzle->board.size(); i++)
			{
				if (puzzle->board[i] == 0)
				{
					// Do not count the zero index
					continue;
				}
				
				// Loop through each piece in the goal puzzle
				for (unsigned short j = 0; j < goal->board.size(); j++)
				{
					if (puzzle->board[i] == goal->board[j])
					{
						puzzle->coordsAt(i, curX, curY);
						goal->coordsAt(j, goalX, goalY);
						
						// Calculate the manhattan distance
						estimate += abs(curX - goalX) + abs(curY - goalY);
					}
				}
			}
			
			return estimate;
		}
	};
};

#endif /* Puzzle_hpp */
