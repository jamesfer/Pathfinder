//
//  MoveTile.hpp
//  Puzzle Solver
//
//  Created by James Ferguson on 19/04/2016.
//  Copyright © 2016 James Ferguson. All rights reserved.
//

#ifndef MoveTile_hpp
#define MoveTile_hpp

#include "Action.hpp"


enum class Direction {
	up,
	down,
	left,
	right
};


class MoveTile : public Action
{
	Direction dir;
	
public:
	MoveTile(Direction dir);
	
	virtual string toString() const override;
};

#endif /* MoveTile_hpp */
