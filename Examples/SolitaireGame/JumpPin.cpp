#include "JumpPin.hpp"
#include <sstream>


JumpPin::JumpPin(unsigned char pinX, unsigned char pinY, unsigned char newX, unsigned char newY) : pinX(pinX), pinY(pinY), newX(newX), newY(newY)
{
	
}


string JumpPin::toString() const
{
	stringstream output;
	output << "(" << (int) pinX << ", " << (int) pinY << ")";
	output << " to ";
	output << "(" << (int) newX << ", " << (int) newY << ")";
	return output.str();
}