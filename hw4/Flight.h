/*
Deniz Aydemir 22001859 Section 1
*/

#ifndef __FLIGHT_H__
#define __FLIGHT_H__
#include <string>
using namespace std;

class Flight {
    public:
    string depart;
    string destination;
    int id;
    int cost;

    Flight();
    //implement a copy constructor
    Flight(const Flight& other);
    Flight(string,string, int, int);
    //override <, >, and = according to destination
    bool operator<(const Flight& other) const;
    bool operator>(const Flight& other) const;
    bool operator==(const Flight& other) const;

};
#endif