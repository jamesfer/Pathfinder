#ifndef City_hpp
#define City_hpp

#include "State.hpp"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

using namespace std;

class Action;
class TravelTo;


/**
 * Each state in this scenario is represented by a city.
 */
class City
{
	/**
	 * Name of the city.
	 */
	string name;
	
	/**
	 * Cartesian coordinates of the city.
	 */
	float x;
	float y;
	
	/**
	 * List of paths to neighbouring cities.
	 */
	vector<pair<shared_ptr<Action>, shared_ptr<City>>> routes;
	
public:
	/**
	 * Creates an empty city.
	 * Default constructor required to be used with a map.
	 */
	City();
	
	
	City(string name, float x, float y);
	
	
	/**
	 * Adds a new route to this city.
	 */
	void addRoute(shared_ptr<TravelTo> route);
	
	
	/**
	 * Returns neighbouring cities
	 */
	vector<pair<shared_ptr<Action>, shared_ptr<City>>> getActions() const;
	
	
	/**
	 * Sorts cities lexographically by their name.
	 */
	bool operator<(const City& other) const;
	
	
	/**
	 * Returns true if the name of other matches the name of this.
	 */
	bool operator==(const City& other) const;
	
	
	/**
	 * Getter for name
	 */
	string getName() const;
	
	
	/**
	 * Reads the city from a stream in the form: name x y
	 */
	friend istream& operator>>(istream& input, City& obj);
	
	
	/**
	 * Heuristic functor that checks the straight line distance between the 
	 * current city and the goal.
	 */
	struct StraightLineDistanceHeuristic
	{
	private:
		const City& goal;
		
	public:
		StraightLineDistanceHeuristic(const City& goal) : goal(goal)
		{
			
		}
		
		int operator()(shared_ptr<City> city) const
		{
			return sqrt(pow(goal.x - city->x, 2) + pow(goal.y - city->y, 2));
		}
	};
};

#endif /* City_hpp */
