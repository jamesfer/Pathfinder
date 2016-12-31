//
//  MoveTile.cpp
//  Puzzle Solver
//
//  Created by James Ferguson on 19/04/2016.
//  Copyright © 2016 James Ferguson. All rights reserved.
//

#include "MoveTile.hpp"


MoveTile::MoveTile(Direction dir) : dir(dir)
{
	
}


string MoveTile::toString() const
{
	switch (dir) {
		case Direction::up:
			return "up";
		case Direction::down:
			return "down";
		case Direction::left:
			return "left";
		case Direction::right:
			return "right";
	}
}