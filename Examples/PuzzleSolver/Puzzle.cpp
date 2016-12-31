#include "Puzzle.hpp"
#include <algorithm>
#include <iomanip>


Puzzle::Puzzle(const unsigned short width, const unsigned short height) : width(width), height(height)
{
	// Allocate space for the board
	board.resize(width * height);
	
	// Assign default values
	for (int i = 0; i < width * height; i++)
	{
		board[i] = i;
	}
	
	zeroIndex = 0;
}


bool Puzzle::operator<(const Puzzle &other) const
{
	// Check the size of each puzzle first
	if (other.board.size() != board.size())
	{
		return other.board.size() < board.size();
	}
	
	for (int i = 0; i < board.size(); i++)
	{
		if (other.board[i] < board[i])
		{
			// Other is less than this
			return false;
		}
		else if (other.board[i] > board[i])
		{
			// Other is greater than this
			return true;
		}
	}
	
	// All indicies are equal
	return false;
}


bool Puzzle::operator==(const Puzzle& other) const
{
	// Check the size of each puzzle first
	if (other.width != width || other.height != height)
	{
		return false;
	}
	
	for (int i = 0; i < width * height; i++)
	{
		if (other.board[i] != board[i])
		{
			return false;
		}
	}
	
	return true;
}


vector<pair<shared_ptr<Action>, shared_ptr<Puzzle>>> Puzzle::getActions() const
{
	vector<pair<shared_ptr<Action>, shared_ptr<Puzzle>>> actions;
	pair<shared_ptr<Action>, shared_ptr<Puzzle>> action;
	
	unsigned short zeroX;
	unsigned short zeroY;
	coordsAt(zeroIndex, zeroX, zeroY);
	
	// Add up action
	if (makeMove(zeroX, zeroY - 1, Direction::up, action))
	{
		actions.push_back(action);
	}
	// Add left action
	if (makeMove(zeroX - 1, zeroY, Direction::left, action))
	{
		actions.push_back(action);
	}
	// Add down action
	if (makeMove(zeroX, zeroY + 1, Direction::down, action))
	{
		actions.push_back(action);
	}
	// Add right action
	if (makeMove(zeroX + 1, zeroY, Direction::right, action))
	{
		actions.push_back(action);
	}
	
	return actions;
}


istream& operator>>(istream& input, Puzzle& obj)
{
	for (int i = 0; i < obj.width * obj.height; i++)
	{
		input >> obj.board[i];
		
		// Update the zero index
		if (obj.board[i] == 0)
		{
			obj.zeroIndex = i;
		}
	}
	
	return input;
}


ostream& operator<<(ostream& output, const Puzzle& obj)
{
	for (int y = 0; y < obj.height; y++)
	{
		// Print top border
		cout << "+";
		for (int x = 0; x < obj.width; x++)
		{
			cout << setw(5) << setfill('-') << '+';
		}
		cout << endl;
		
		// Print number
		cout << "|";
		for (int x = 0; x < obj.width; x++)
		{
			cout << setw(3) << setfill(' ') << obj.board[obj.indexOf(x, y)];
			cout << " |";
		}
		cout << endl;
	}
	
	// Print bottom border
	cout << "+";
	for (int x = 0; x < obj.width; x++)
	{
		cout << setw(5) << setfill('-') << '+';
	}
	cout << endl;
	
	return output;
}


unsigned short Puzzle::at(const unsigned short index) const
{
	return board[index];
}


void Puzzle::extractDimensions(istream& input, unsigned short& width, unsigned short& height)
{
	input >> width;
	input.get();
	input >> height;
}


unsigned short Puzzle::indexOf(const unsigned short x, const unsigned short y) const
{
	return y * width + x;
}


void Puzzle::coordsAt(const unsigned short index, unsigned short &x, unsigned short &y) const
{
	x = index % width;
	y = index / width;
}


bool Puzzle::makeMove(unsigned short newZeroX, unsigned short newZeroY, Direction dir, pair<shared_ptr<Action>, shared_ptr<Puzzle> > &details) const
{
	// Return false if the moves are out of bounds
	if (newZeroX < 0 || newZeroX >= width
		|| newZeroY < 0 || newZeroY >= height)
	{
		return false;
	}
	
	// Copy this puzzle
	shared_ptr<Puzzle> newPuzzle = make_shared<Puzzle>(*this);
	
	// Swap the zero tile
	unsigned short newZeroIndex = indexOf(newZeroX, newZeroY);
	newPuzzle->board[zeroIndex] = newPuzzle->board[newZeroIndex];
	newPuzzle->board[newZeroIndex] = 0;
	newPuzzle->zeroIndex = newZeroIndex;
	
	// Update the pair
	details.first = make_shared<MoveTile>(dir);
	details.second = newPuzzle;
	
	return true;
}










