#include "WoodenPuzzle.hpp"
#include <assert.h>


WoodenPuzzle::WoodenPuzzle() : board()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		board[i] = true;
	}
	
	// Set the middle pin to be empty
	board[indexOf(3, 3)] = false;
}


WoodenPuzzle::~WoodenPuzzle()
{
	
}


bool WoodenPuzzle::operator==(const WoodenPuzzle& otherPuzzle) const
{
	return board == otherPuzzle.board;
}


bool WoodenPuzzle::operator<(const WoodenPuzzle& other) const
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		// This board starts with 0, other board starts with 1
		if (!board[i] && other.board[i])
		{
			return true;
		}
		// This board starts with 1, other board starts with 0
		else if (board[i] && !other.board[i])
		{
			return false;
		}
		
		// If pieces are equal move on to comparing the next place
	}
	
	// If all places are equal return false
	return false;
}


vector<pair<shared_ptr<Action>, shared_ptr<WoodenPuzzle>>> WoodenPuzzle::getActions() const
{
	vector<pair<shared_ptr<Action>, shared_ptr<WoodenPuzzle>>> actions;
	
	pair<unsigned char, unsigned char> coords;
	JumpPin jumpAction = {0, 0, 0, 0};
	WoodenPuzzle newState;
	
	for (unsigned char i = 0; i < BOARD_SIZE; ++i)
	{
		if (board[i])
		{
			// Check each of the directions
			coords = coordOf(i);
			
			// Move pin up
			if (checkMove(coords.first, coords.second, coords.first, coords.second - 2, jumpAction, newState))
			{
				shared_ptr<WoodenPuzzle> neighbour = make_shared<WoodenPuzzle>(newState);
				shared_ptr<Action> action = make_shared<JumpPin>(jumpAction);
				actions.push_back({
					action,
					neighbour
				});
			}
			
			// Move pin down
			if (checkMove(coords.first, coords.second, coords.first, coords.second + 2, jumpAction, newState))
			{
				shared_ptr<WoodenPuzzle> neighbour = make_shared<WoodenPuzzle>(newState);
				shared_ptr<Action> action = make_shared<JumpPin>(jumpAction);
				actions.push_back({
					action,
					neighbour
				});
			}
			
			// Move pin left
			if (checkMove(coords.first, coords.second, coords.first - 2, coords.second, jumpAction, newState))
			{
				shared_ptr<WoodenPuzzle> neighbour = make_shared<WoodenPuzzle>(newState);
				shared_ptr<Action> action = make_shared<JumpPin>(jumpAction);
				actions.push_back({
					action,
					neighbour
				});
			}
			
			// Move pin right
			if (checkMove(coords.first, coords.second, coords.first + 2, coords.second, jumpAction, newState))
			{
				shared_ptr<WoodenPuzzle> neighbour = make_shared<WoodenPuzzle>(newState);
				shared_ptr<Action> action = make_shared<JumpPin>(jumpAction);
				actions.push_back({
					action,
					neighbour
				});
			}
		}
	}
	
	return actions;
}


ostream& operator<<(ostream& output, const WoodenPuzzle& puzzle)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if (i == 0 || i == 3 || i == 27 || i == 30)
		{
			cout << "    ";
		}
		
		cout << (puzzle.at(i) ? "* " : "  ");
		
		if (i == 2 || i == 5 || i == 12 || i == 19 || i == 26 || i == 29 || i == 32)
		{
			cout << endl;
		}
	}
	
	return output;
}


unsigned char WoodenPuzzle::indexOf(const unsigned char x, const unsigned char y)
{
	unsigned char index = 0,
		i = 0,
		rowStart = 2,
		rowEnd = 4;
	
	// Sum the fully completed rows (all the ones from 0 to y)
	while (i < y)
	{
		index += rowEnd - rowStart + 1;
		
		++i;
		
		if (i >= 2 && i <= 4)
		{
			rowStart = 0;
			rowEnd = 6;
		}
		else
		{
			rowStart = 2;
			rowEnd = 4;
		}
	}
	
	// Add the x coord
	index += x - rowStart;
	return index;
}


pair<unsigned char, unsigned char> WoodenPuzzle::coordOf(unsigned char index)
{
	unsigned char x = 0,
		y = 0,
		rowStart = 2,
		rowEnd = 4;
	
	while (index > rowEnd - rowStart)
	{
		++y;
		index -= rowEnd - rowStart + 1;
		
		if (y >= 2 && y <= 4)
		{
			rowStart = 0;
			rowEnd = 6;
		}
		else
		{
			rowStart = 2;
			rowEnd = 4;
		}
	}
	
	x = rowStart + index;
	return {x, y};
}


bool WoodenPuzzle::at(unsigned char x, unsigned char y) const
{
	return board[indexOf(x, y)];
}


bool WoodenPuzzle::at(unsigned char index) const
{
	return board[index];
}


bool WoodenPuzzle::checkMove(unsigned char pinX, unsigned char pinY, unsigned char newX, unsigned char newY, JumpPin &action, WoodenPuzzle& newState) const
{
	// First check that the new location is the bounds
	if (newY < 0 || newY > 6 || newX < 0 || newX > 6)
	{
		return false;
	}
	
	// Then check that the new location is within the plus shape
	if (!((newX >= 2 && newX <= 4) || (newY >= 2 && newY <= 4 && newX >= 0 && newX <= 6)))
	{
		return false;
	}
	
	// Then check the new spot is empty
	if (at(newX, newY))
	{
		return false;
	}
	
	unsigned char midX = (pinX + newX) / 2,
		midY = (pinY + newY) / 2;
	
	// Then check the spot in between the points is full
	if (!at(midX, midY))
	{
		return false;
	}
	
	// The move is valid, create the action and the new puzzle state
	action = {pinX, pinY, newX, newY};
	newState = WoodenPuzzle(*this);
	
	// The new location is now full
	newState.board[indexOf(newX, newY)] = true;
	// The mid point is now empty
	newState.board[indexOf(midX, midY)] = false;
	// The original point is now empty
	newState.board[indexOf(pinX, pinY)] = false;
	
	return true;
}








