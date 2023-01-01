/*
Deniz Aydemir 22001859 Section 1
*/

#include "Flight.h"
#include <string>
using namespace std;
  
Flight::Flight() {
    destination = "";
    id = 0;
    cost = 0;
}
Flight::Flight(const Flight& other) {
    this -> depart = other.depart;
    this->destination = other.destination;
    this->id = other.id;
    this->cost = other.cost;
}
Flight::Flight(string depart, string destination, int id, int cost) {
    this->depart  = depart;
    this->destination = destination;
    this->id = id;
    this->cost = cost;
} 

bool Flight::operator<(const Flight& other) const {
    return this->destination < other.destination;
}
bool Flight::operator>(const Flight& other) const {
    return this->destination > other.destination;
}
bool Flight::operator==(const Flight& other) const {
    return this->depart == other.depart && this->destination == other.destination;
}




