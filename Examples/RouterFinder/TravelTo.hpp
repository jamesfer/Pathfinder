#ifndef TravelTo_hpp
#define TravelTo_hpp

#include "Action.hpp"
#include <iostream>

using namespace std;

class City;


/**
 * Action of moving from one city to another.
 */
class TravelTo : public Action
{
	// Store the cities as weak pointers to prevent circular references.
	weak_ptr<City> from;
	weak_ptr<City> to;
	
public:
	TravelTo(weak_ptr<City> from, weak_ptr<City> to, float distance);
	
	
	/**
	 * Converts the action into a string in the form:
	 * from.name --cost--> to.name
	 */
	virtual string toString() const;
	
	
	/**
	 * Getter for the initial city.
	 */
	weak_ptr<City> getInitial() const;
	
	
	/**
	 * Getter for the destination city
	 */
	weak_ptr<City> getDestination() const;
	
	
	/**
	 * Reads a path from a stream in the form: from to distance
	 */
	friend istream& operator>>(istream& input, TravelTo& obj);
	
	
	/**
	 * Helper function that adds a route between a and b going both directions.
	 */
	static void createRoadBetween(shared_ptr<City> a, shared_ptr<City> b, float distance);
};


#endif /* TravelTo_hpp */
