#include "TravelTo.hpp"
#include <sstream>
#include "City.hpp"



TravelTo::TravelTo(weak_ptr<City> from, weak_ptr<City> to, float distance) : from(from), to(to)
{
	cost = distance;
}


string TravelTo::toString() const
{
	stringstream output;
	output << from.lock()->getName();
	output << "--" << cost << "-->";
	output << to.lock()->getName();
	return output.str();
}


weak_ptr<City> TravelTo::getInitial() const
{
	return from;
}


weak_ptr<City> TravelTo::getDestination() const
{
	return to;
}


istream& operator>>(istream& input, TravelTo& obj)
{
	// Expect input to be: to
	return input;
}


void TravelTo::createRoadBetween(shared_ptr<City> a, shared_ptr<City> b, float distance)
{
	shared_ptr<TravelTo> aToB = make_shared<TravelTo>(a, b, distance);
	shared_ptr<TravelTo> bToA = make_shared<TravelTo>(b, a, distance);
	
	a->addRoute(aToB);
	b->addRoute(bToA);
}














