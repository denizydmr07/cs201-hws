#include "FlightMap.h"
#include <iostream>
using namespace std;

int main() {
    FlightMap fm( "cityFile.txt", "flightFile.txt" );
    cout << endl;

    /*
    fm.displayAllCities();
    cout << endl;

    fm.displayAdjacentCities( "W" );
    cout << endl;

    fm.displayAdjacentCities( "X" );
    cout << endl;

    fm.displayFlightMap();
    cout << endl;

    fm.findFlights("W", "Z");
    cout << endl;

    fm.findFlights("S", "P");
    cout << endl;

    fm.findFlights("Y", "Z");
    cout << endl;
    
    fm.findFlights("P", "Z");
    cout << endl;
    */

    //3
    /*
    fm.findFlights( "S", "T" ); 
    cout << endl;

    fm.findFlights( "W", "X" );
    cout << endl;

    fm.findFlights( "S", "X" );
    cout << endl;
    return 0;
    */
    //1_2
    /*
    fm.displayAllCities();
    cout << endl;

    fm.displayAdjacentCities( "X" );
    cout << endl;

    fm.displayAdjacentCities( "W" );
    cout << endl;

    fm.displayFlightMap();
    cout << endl;
    */

   fm.displayAllCities();
   cout << endl;
   fm.displayFlightMap();
   cout << endl;
   fm.findFlights( "A", "N" );
   cout << endl;

   fm.findFlights( "E", "A" );
   cout << endl;

   fm.findFlights( "A", "D" );
   cout << endl;
   
}