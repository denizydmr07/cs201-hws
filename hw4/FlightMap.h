/*
Deniz Aydemir 22001859 Section 1
*/

#ifndef __FLIGHTMAP_H__
#define __FLIGHTMAP_H__
#include <string>
#include "Flight.h"
#include <list>
#include <vector>
#include <stack>
using namespace std;

class FlightMap {
    public:
        FlightMap( const string cityFile, const string flightFile );
        ~FlightMap();
        void displayAllCities() const;
        void displayAdjacentCities( const string cityName ) const;
        void displayFlightMap() const;
        void findFlights( const string deptCity, const string destCity ) const;

        vector<string> cities;
        vector<list<Flight> > graph;  
        int getIndexOfCity(const string cityName) const;
};
#endif