// Defines functions to parse location and route data from files and create Location and Route objects accordingly. These functions are essential for setting up the data structures required for graph-based pathfinding algorithms.

#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Location.h"

using namespace std;

// Parses location data from a file, creates Location objects, and associates them with Route objects. Returns a vector of Location pointers.
vector<Location*> locationParser(string filename, vector<Route*> routes){ 
	fstream locations(filename.c_str()); // used to create an fstream object named locations that opens a file specified by the filename variable

	string country;
	string city;
	string latitude;
	string longitude;

	vector<Location*> cities;
	Location* node;

	while(locations.good()){
		getline(locations, country, ',');
		getline(locations, city, ',');
		getline(locations, latitude, ',');
		getline(locations, longitude);
		
		node = new Location(country, city, atof(latitude.c_str()), atof(longitude.c_str()) // used to convert a std::string to a double in C++. 
		);

		vector<Route*>::iterator it = routes.begin();

		while(it != routes.end()){
			if((*it) -> originS.compare(node -> capital) == 0){
				(*it) -> origin = node;
				node -> routes.push_back((*it));
			}
			else if((*it) -> destinationS.compare(node -> capital) == 0){
				(*it) -> destination = node;
			}
			++it;
		}

		cities.push_back(node);
	}
	cout << "Cities Parsed from: " << filename << endl;
	return cities;
}

// Parses route data from a file, creates Route objects, and stores them in a vector. Returns a vector of Route pointers.
vector<Route*> routeParser(string filename){

	fstream routes(filename.c_str());

	string originS;
	string destinationS;

	Location* origin = new Location();
	Location* destination = new Location();

	string type;
	string time;
	string cost;
	string note;

	vector<Route*> allRoutes;
	Route* edge;

	while(routes.good()){
		getline(routes, originS, ',');
		getline(routes, destinationS, ',');
		getline(routes, type, ',');
		getline(routes, time, ',');
		getline(routes, cost, ',');
		getline(routes, note);

		edge = new Route(origin, destination, type, atof(time.c_str()), atof(cost.c_str()), note);
		edge -> destinationS = destinationS;
		edge -> originS = originS;

		allRoutes.push_back(edge);
	}
	cout << "Routes Parsed from: " << filename << endl;
	return allRoutes;
}

#endif
