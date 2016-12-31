#ifndef JumpPin_hpp
#define JumpPin_hpp

#include "Action.hpp"


/**
 * The action of jumping a pin.
 */
class JumpPin : public Action
{
	unsigned char pinX;
	unsigned char pinY;
	unsigned char newX;
	unsigned char newY;
	
public:
	JumpPin(unsigned char pinX, unsigned char pinY, unsigned char newX, unsigned char newY);
	
	/**
	 * Prints the move in the form "(pinX, pinY) to (newX, newY)"
	 */
	virtual string toString() const;
};

#endif /* JumpPin_hpp */
