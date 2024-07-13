// This code defines the Location class with attributes for geographical details and pathfinding purposes, along with necessary methods and operators

#ifndef LOCATION_H                   // if not defined
#define LOCATION_H                   // then define           -> to avoid multiple inclusions to same header file

#include <string>
#include <vector>

#include "Route.h"
class Route;                         // Forward declaration is a way to inform the compiler about the existence of a class before fully defining it to avoid circular dependencies. -> Circular dependencies can arise when two classes reference each other, either directly or indirectly.

using namespace std;

class Location{
public:
		string country;
		string capital;
		float lat;
		float lon;

		vector<Route*> routes;

		bool exists;
		Location* previous;
		float lengthFromStart;

		Location();
		~Location();
		Location(string count, string cap);
		Location(string count, string cap, float lt, float lg);

		float getWeight(Location* start, Location* end);

		int operator== (const Location &rhs) const;
		int operator< (const Location &rhs) const;
		int operator> (const Location &rhs) const;

		bool operator()(Location& l1, Location& l2);
};

Location::Location(){
	country = "";
	capital = "";
	lat = 0;
	lon = 0;

	// Used as a highest value possible for comparison purposes
	lengthFromStart = 999999;

	exists = true;

	previous = NULL;
}

Location::~Location(){};

Location::Location(string count, string cap){
	country = count;
	capital = cap;
	lat = 0;
	lon = 0;

	lengthFromStart = 999999;

	exists = true;

	previous = NULL;
}

Location::Location(string count, string cap, float lt, float lg){
	country = count;
	capital = cap;
	lat = lt;
	lon = lg;

	lengthFromStart = 999999;

	exists = true;

	previous = NULL;
}

int Location::operator== (const Location &rhs) const{
	
	if(this -> capital.compare(rhs.capital) == 0){
		return 0;
	}
	return 1;
}

int Location::operator< (const Location &rhs) const{
	if(this -> lengthFromStart < rhs.lengthFromStart){
		return 1;
	}
}

int Location::operator> (const Location &rhs) const{
	if(this -> lengthFromStart > rhs.lengthFromStart){
		return 1;
	}
}

class compareLocation
{ // The compareLocation functor is designed to facilitate comparisons between Location objects in data structures that require sorting or prioritization.

public:
	bool operator()(const Location* l1, const Location* l2) const{
		bool output = false;
		if(l1->lengthFromStart > l2->lengthFromStart){
			output = true;
		}
		return output;
	}
};

#endif // to mark the end of a conditional preprocessor directive that started with #if, #ifdef, or #ifndef
