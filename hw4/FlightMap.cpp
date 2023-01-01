/*
Deniz Aydemir 22001859 Section 1
*/

#include "FlightMap.h"
using namespace std;
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

//Constructor
FlightMap::FlightMap(const string cityFile, const string flightFile) {
    fstream MyCityFile(cityFile, ios_base::in);
    fstream MyFlightFile(flightFile, ios_base::in);

    // In order to find city and flight counts
    fstream MyMockCityFile(cityFile, ios_base::in);
    fstream MyMockFlightFile(flightFile, ios_base::in);

    int cityCount = 0;
    int flightCount = 0;

    string mockCity;
    string mockFlight;

    while (MyMockCityFile >> mockCity) {
        cityCount++;
    }

    //resizing graph
    graph.resize(cityCount);

    while (MyMockFlightFile >> mockFlight) {
        flightCount++;
    }
    MyMockCityFile.close();
    MyMockFlightFile.close();


    string city;
    for (int i = 0; i < cityCount; i++) {
        MyCityFile >> city;
        cities.push_back(city);
    }
    MyCityFile.close();

    
    //sorting cities vector
    for (long unsigned int i = 0; i < cities.size(); i++) {
        int minIndex = i;
        for (long unsigned int j = i + 1; j < cities.size(); j++) {
            if (cities[j] < cities[minIndex]) {
                minIndex = j;
            }
        }
        string temp = cities[i];
        cities[i] = cities[minIndex];
        cities[minIndex] = temp;
    }

    string origin, destination;
    string strId, strCost;
    int id, cost;
    
    //creating the graph
    for (int i = 0;i < flightCount; i++) {

        getline(MyFlightFile,origin, ';');
        getline(MyFlightFile,destination, ';');
        getline(MyFlightFile,strId, ';');
        getline(MyFlightFile,strCost, '\n');

        //finding index of origin city in cities vector
        int originCityIndex;
        for (long unsigned int i = 0; i < cities.size(); i++) {
            if (cities[i] == origin) {
                originCityIndex = i;
                break;
            }
        }
        //string to int
        stringstream ss1;
        stringstream ss2;

        ss1 << strId;
        ss1 >> id;

        ss2 << strCost;
        ss2 >> cost;

        //adding flight to corresponding place
        Flight fl(origin, destination,id,cost);
        graph[originCityIndex].push_back(fl);
    }
    MyFlightFile.close();

    //sorting flights
    for (long unsigned int i = 0; i < graph.size(); i++) { //WARNING
        graph[i].sort();
    }

    cout << cityCount << " cities and " << flightCount << " flights have been loaded" << endl;
}
//Destructor
FlightMap::~FlightMap() {
    cities.clear();
    graph.clear();
}

//display all cities
void FlightMap::displayAllCities() const{
    cout << "The list of the cities that HPAir serves is given below:" << endl;
    for (long unsigned int i = 0; i < cities.size(); i++) {
        cout << cities[i] << ", ";
    }
    cout << endl;
}

void FlightMap::displayAdjacentCities(const string cityName) const {
    //first find the index of the city
    // The pdf does not say anything about invalid input
    
    int cityIndex = -1;
    for (long unsigned int i = 0; i < cities.size(); i++) {
        if (cities[i] == cityName) {
            cityIndex = i;
            break;
        }
    }
    cout << "The cities adjacent to " << cityName << " are:" << endl;
    cout << cityName << " -> ";
    list<Flight>::const_iterator iter;
    for (iter = graph[cityIndex].begin(); iter != graph[cityIndex].end(); ++iter) {
        cout << (*iter).destination << ", ";
    }
    cout << endl;
}

void FlightMap::displayFlightMap() const {
    cout << "The whole flight map is given below:" << endl;

    for (long unsigned int i = 0; i < cities.size(); i++) {
        cout << cities[i] << " -> ";
        list<Flight>::const_iterator iter;
        for (iter = graph[i].begin(); iter != graph[i].end(); iter++) {
            cout << (*iter).destination << ", ";
        }
        cout << endl;
    }
}

void FlightMap::findFlights(const string depCity, const string destCity)  const{
    cout << "Request is to fly from " << depCity << " to " << destCity << ":" << endl;
    
    stack<string> path;
    list<stack<string>> paths;

    stack<Flight> flights;
    bool first = true;
    string s;

    path.push(depCity);

    string top = path.top();

    while (!path.empty()) {
        int cityIndex = this->getIndexOfCity(top);
        string next;

        bool hasNext = false;
        bool alreadyExists = false;
        list<Flight>::const_iterator iter;
        for (iter = graph[cityIndex].begin(); iter != graph[cityIndex].end(); iter++) {
            string dest = (*iter).destination;
            Flight copyFlight((*iter).depart, (*iter).destination, (*iter).id, (*iter).cost);
            //Flight copyFlight2((*iter).destination, (*iter).depart, (*iter).id, (*iter).cost);
            stack<Flight> copyFlights = flights;
            stack<string> copyPath = path;

            while (!copyFlights.empty()) {
                //cout << "---" << endl <<path.size() << endl << flights.size() << endl << "---" << endl;
                if(copyFlights.top() == copyFlight) {
                    //cout << (*iter).depart << " " << (*iter).destination << endl;
                    alreadyExists = true;
                    break;
                }
                copyFlights.pop();
            }

            if (first) {
                first = false;
                alreadyExists = false;
            }

            while (!copyPath.empty()) {
                //cout << "x" << endl;
                if (copyPath.top() == dest) {
                    alreadyExists = true;
                    //cout << copyPath.top() << dest << endl;;
                    break;
                }
                copyPath.pop();
            }

            if (copyFlights.empty() && copyPath.empty()) {
                alreadyExists = false;
            }

            if (!alreadyExists) {
                Flight copyFlight2 = copyFlight;
                flights.push(copyFlight2);
                //cout << "pushed" << copyFlight2.depart << copyFlight2.destination << endl;
                next = dest;
                hasNext = true;
                break;
            }

            
        }
        if (!hasNext) {
            path.pop();
            
        }
        else {
            path.push(next);
        }
        if (!path.empty()) {
            top = path.top();
            //cout << top << endl;
        }
        if (top == destCity) {
            if (!path.empty())
            {
                stack<string> copyPath(path);
                paths.push_back(copyPath);
                path.pop();
                //if flight is not a direct from depart city to dest city
                if (!(flights.top().depart == depCity && flights.top().destination == destCity)) {
                    flights.pop();
                }
            }
        }

    }

    //cout << paths.size() << endl;

    if (paths.empty()) {
        cout << "Sorry. HPAir does not fly from " << depCity << " to " << destCity << "." << endl;
        return;
    }


    //traversing paths list, and sort paths by their total cost in a new list
    list<stack<string>> sortedPaths;    
    list<stack<string>>::const_iterator iter;
    //cout << paths.size() << endl;
    for (iter = paths.begin(); iter != paths.end(); iter++) {
        stack<string> copyPath = (*iter);
        stack<string> reverseCopyPath;

        while (!copyPath.empty()) {
            reverseCopyPath.push(copyPath.top());
            copyPath.pop();
        }

        int totalCost = 0;

        string firstCity = reverseCopyPath.top();
        reverseCopyPath.pop();
        while (!reverseCopyPath.empty()) {
            string next = reverseCopyPath.top();
            reverseCopyPath.pop();

            list<Flight>::const_iterator iter2;
            for (iter2 = graph[this->getIndexOfCity(firstCity)].begin(); iter2 != graph[this->getIndexOfCity(firstCity)].end(); iter2++) {
                if ((*iter2).destination == next) {
                    totalCost += (*iter2).cost;
                }
            }

            firstCity = next;
        }

        if (sortedPaths.empty()) {
            //cout << "SP size: " << sortedPaths.size() << endl;
            sortedPaths.push_back((*iter));
        }
        else {
            //cout << "SP size: " << sortedPaths.size() << endl;
            list<stack<string>>::iterator iter2;
            for (iter2 = sortedPaths.begin(); iter2 != sortedPaths.end(); iter2++) {
                stack<string> copyPath2 = (*iter2);
                stack<string> reverseCopyPath2;

                while (!copyPath2.empty()) {
                    reverseCopyPath2.push(copyPath2.top());
                    copyPath2.pop();
                }

                int totalCost2 = 0;

                string firstCity2 = reverseCopyPath2.top();
                reverseCopyPath2.pop();
                while (!reverseCopyPath2.empty()) {
                    string next2 = reverseCopyPath2.top();
                    reverseCopyPath2.pop();

                    list<Flight>::const_iterator iter3;
                    for (iter3 = graph[this->getIndexOfCity(firstCity2)].begin(); iter3 != graph[this->getIndexOfCity(firstCity2)].end(); iter3++) {
                        if ((*iter3).destination == next2) {
                            totalCost2 += (*iter3).cost;
                        }
                    }

                    firstCity2 = next2;
                }
                if (totalCost < totalCost2) {
                    sortedPaths.insert(iter2, (*iter));
                    break;
                }

            }
            if (iter2 == sortedPaths.end()) {
                sortedPaths.push_back((*iter));
            }
        }
    }


    list<stack<string>>::const_iterator iter3;
    //cout << sortedPaths.size() << endl;
    for (iter3 = sortedPaths.begin(); iter3 != sortedPaths.end(); iter3++) {
        stack<string> copyPath = (*iter3);
        stack<string> reverseCopyPath;

        while (!copyPath.empty()) {
            reverseCopyPath.push(copyPath.top());
            copyPath.pop();
        }

        int totalCost = 0;

        string firstCity = reverseCopyPath.top();
        reverseCopyPath.pop();
        while (!reverseCopyPath.empty()) {
            string next = reverseCopyPath.top();
            reverseCopyPath.pop();

            list<Flight>::const_iterator iter2;
            for (iter2 = graph[this->getIndexOfCity(firstCity)].begin(); iter2 != graph[this->getIndexOfCity(firstCity)].end(); iter2++) {
                if ((*iter2).destination == next) {
                    totalCost += (*iter2).cost;
                
                    cout << "Flight #" << (*iter2).id << " from " << firstCity << " to " << next << ", Cost: " << (*iter2).cost << " TL" << endl;
                }
            }

            firstCity = next;
        }
        cout << "Total Cost: " << totalCost << " TL" << endl;
    }
}
int FlightMap::getIndexOfCity(const string cityName) const {
    int index = -1;
    for (long unsigned int i = 0; i < cities.size(); i++) {
        if (cities[i] == cityName) {
            index = i;
            break;
        }
    }
    return index;
}