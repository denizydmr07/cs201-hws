//Deniz Aydemir Section 1 22001859 

#include "Team.h"
#include <iostream>
using namespace std;

Team::Team() {
    this->setName("");
    this->setYear(-1);
    this->players = new Player*[0];
    this->size = 0;
}

Team::Team(string name, int year) {
    this->setName(name);
    this->setYear(year);
    this->players = new Player*[0];
    this->size = 0;
}

Team::~Team() {
    for (int i = 0; i < size; i++) {
        delete players[i];
    }
    
    delete[] players;
}

string Team::getName() {
    return Team::name;
}

void Team::setName(string name) {
    Team::name = name;
}

int Team::getYear() {
    return Team::year;
}

void Team::setYear(int year) {
    Team::year = year;
}

int Team::getSize() {
    return Team::size;
}
void Team::incrementSize() {
    Team::size++;
}

void Team::decreaseSize() {
    Team::size--;
}

void Team::addPlayer(const string name, const int jersey, const double salary) {
    for (int i = 0; i < size; i++) {
        if ((*players[i]).getJersey() == jersey) {
            cout << "Cannot add player. ";
            cout << "Player " << name << " already exists.";
            cout << endl;
            return;
        }
    }

    this -> updatePlayersBy(+1);

    players[size-1] = new Player(name,jersey,salary);
}

void Team::removePlayer(const string name) {
    int index = -1; //index to store player's index if s/he exists
    if (!(this -> isPlayerExists(name, index))) { //if there is no existing player with name "name"
        cout << "Cannot remove player. ";
        cout << "Player " << name << " does not exist.";
        cout << endl;
        return;
    }

    delete players[index];
    players[index] = nullptr; 
    

    this -> updatePlayersBy(-1); //as indicated player is now nullptr, it will be removed in this method
    cout << "Removed player " << name << " from team " << this->name << "." << endl;

}

bool Team::isPlayerExists(const string name, int& index) {
    for (int i = 0; i < size; i++) {
        if( (*players[i]).getName() == name) {
            index = i; //if player exists, its index will be stored
            return true;
        }
    }
    return false;
}

bool Team::isPlayerExists(const int jersey, int& index) {
    for (int i = 0; i < size; i++) {
        if( (*players[i]).getJersey() == jersey) {
            index = i; //if player exists, its index will be stored
            return true;
        }
    }
    return false;
}

bool Team::transferPlayer(Team* departTeam,const int playerIndex) {
    int indexOfPlayerInArriveTeam = -1; //index to store of any player who have same jersey with given player
    const int playerJersey = departTeam->players[playerIndex]->getJersey(); // getting jersey number of given player

    if (this->isPlayerExists(playerJersey, indexOfPlayerInArriveTeam)) { // checking if given player exists
        cout << "Cannot transfer player. ",
        cout << "Jersey number " << playerJersey << " already exists in team ";
        cout << this->name << "." << endl;
        return false;
    }
    this->updatePlayersBy(1); //increasing arriveTeam's length
    this->players[this->size - 1] = departTeam->players[playerIndex]; //adding player's pointer to arriveTeam

    //to remove player's pointer from depart team, not player itself
    //thus, i dont use removePlayer() method that deletes player from heap

    Player** tempPlayers = new Player*[departTeam->size-1];
    int tempPlayerIndex = 0;
    for (int i = 0; i < departTeam->size; i++) {
        if (i != playerIndex) {
            tempPlayers[tempPlayerIndex] = departTeam->players[i];
        }
    }
    delete[] departTeam->players;

    departTeam->players = new Player*[departTeam->size-1];
    departTeam->size--;

    for (int i = 0; i < departTeam->size; i++) {
        departTeam->players[i] = tempPlayers[i];
    }
    delete[] tempPlayers;

    return true;
}

void Team::updatePlayersBy(const int change) {
    int tempSizeCount = 0; //to keep track of indexes of tempTeams array (for removeTeam cases)
    size += change; //updating size
    Player** tempPlayers = new Player*[size]; //change can be either -1 or 1
    
    for (int i = 0; i < size - change; i++) { //size - change means initial value of size
        if (players[i] == nullptr) {
            continue; //if teams[i] had been removed, it is assigned as nullptr
        }
        tempPlayers[tempSizeCount] = players[i];
        tempSizeCount++;
    }    
    delete[] players;

    players = new Player*[size]; 

    for (int i = 0; i < size; i++) {
        players[i] = tempPlayers[i];
    }
    delete[] tempPlayers;
}

int Team::getTotalSalary() {
    int salary = 0;
    for (int i = 0; i < size; i++) {
        salary += this->players[i]->getSalary();
    }
    return salary;
}

void Team::printPlayerInfo(const int index) {
    if (index >= size) {
        cout << "Invalid index!" << endl; 
        return;
    }
    cout << players[index]->getName() << ", "
        << "jersey " << players[index]->getJersey() << ", "
        << players[index]->getSalary() << " TL salary"
        << endl;
}
