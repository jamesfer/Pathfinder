#include "City.hpp"
#include "TravelTo.hpp"



City::City()
{
	
}


City::City(string name, float x, float y) : name(name), x(x), y(y)
{
	
}


void City::addRoute(shared_ptr<TravelTo> route)
{
	shared_ptr<Action> action = route;
	routes.push_back({
		action,
		route->getDestination().lock()
	});
}


vector<pair<shared_ptr<Action>, shared_ptr<City>>> City::getActions() const
{
	return routes;
}


bool City::operator<(const City& other) const
{
	return name < other.name;
}


bool City::operator==(const City& other) const
{
	return name == other.name;
}


string City::getName() const
{
	return name;
}


istream& operator>>(istream& input, City& obj)
{
	// Expect input to be: name x y
	input >> obj.name;
	input >> obj.x;
	input >> obj.y;
	return input;
}