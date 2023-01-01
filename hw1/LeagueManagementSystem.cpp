//Deniz Aydemir Section 1 22001859 

#include "LeagueManagementSystem.h"
#include <iostream>
using namespace std;


LeagueManagementSystem::LeagueManagementSystem()  { 
    this -> teams = new Team*[0];
    this -> size = 0;
}
LeagueManagementSystem::~LeagueManagementSystem() {
    for (int i = 0; i < size; i++) {
        delete teams[i];
    }
    
    delete[] teams;
    this -> size = 0;
}
void LeagueManagementSystem::addTeam(const string name, const int year) {
    int index = -1; //index to store team's index in the array if it exists
    if ((this -> isTeamExists(name, index))) { //if team is already exists, function will return
        cout << "Cannot add team. "
             << "Team " << name << " already exists."
             << endl;
        return;
    }
    

    this -> updateTeamsBy(+1); //incrementing array size by 1

    teams[size-1] = new Team(name,year);
    
    cout << "Added team " << name << "." << endl;
}

void LeagueManagementSystem::removeTeam(const string name) {
    int index = -1; //index to store team's index in array if it exists
    if (!(this -> isTeamExists(name, index))) { //if there is no existing team with name "name"
        cout << "Cannot remove team. "
             << "Team " << name << " does not exist."
             << endl;
        return;
    }

    delete teams[index];
    teams[index] = nullptr; //the method updateTeamsBy updates array with removing nullptr element

    this -> updateTeamsBy(-1);
    cout << "Removed team " << name << "." << endl;

}
void LeagueManagementSystem::addPlayer( const string teamName, const string playerName,
                const int jersey, const int salary ) {
    
    int indexOfTeam = -1;
    if(!(this -> isTeamExists(teamName, indexOfTeam))) {
        cout << "Cannot add player. "
             << "Team " << teamName << " does not exists."
             << endl;
        return; 
    }

    int indexOfPlayer = -1;
    if(this -> teams[indexOfTeam]-> isPlayerExists(jersey, indexOfPlayer)) { //it is a method of the Team class, searchs for player
        cout << "Cannot add player. "
             << "Jersey number " << jersey << " already exists "
             << "in team " << teamName << "."
             << endl;
        return;
    }

    //if neither the team nor player does not exist, function returns before the lines below
    teams[indexOfTeam] -> addPlayer(playerName, jersey, salary); //method of the Team class
    cout << "Added player " << playerName << " to team " << teamName << "." << endl;
}

void LeagueManagementSystem::removePlayer( const string teamName, const string playerName ) {
    
    int indexOfTeam = -1; //index to store team's index in array if it exists
    if(!(this -> isTeamExists(teamName, indexOfTeam))) {
        cout << "Cannot remove player. ";
        cout << "Team " << teamName << " does not exists.";
        cout << endl;
        return; 
    }

    teams[indexOfTeam]->removePlayer(playerName); //Team::removePlayer() gives error message if player does not exist 
}

void LeagueManagementSystem::transferPlayer( const string playerName,
        const string departTeamName, const string arriveTeamName ) {
    
    int indexOfDepartTeam = -1; //index to store depart team's index in array if it exists
    if (!(this -> isTeamExists(departTeamName, indexOfDepartTeam))) {
        cout << "Cannot transfer player. ";
        cout << "Team " << departTeamName << " does not exists.";
        cout << endl;
        return;
    }

    int indexOfArriveTeam = -1; //index to store arrive team's index in array if it exists
    if (!(this -> isTeamExists(arriveTeamName, indexOfArriveTeam))) {
        cout << "Cannot transfer player. ";
        cout << "Team " << arriveTeamName << " does not exists.";
        cout << endl;
        return;
    }

    int indexOfPlayer = -1; //index to store player's index in array if it exists
    int jersey = -1; //jersey number to store player's jersey if it exists
    
    if (!(this->teams[indexOfDepartTeam]->isPlayerExists(playerName,indexOfPlayer))) { // method of the Team class
        cout << "Cannot transfer player. ";
        cout << "Player " << playerName << " does not exist.";
        cout << endl;
        return;
    }
    
    // Team::transferPlayer() methods is called on arriveTeam
    if (this->teams[indexOfArriveTeam]->transferPlayer(this->teams[indexOfDepartTeam], indexOfPlayer)) { //Team::transferPlayer() gives an error if jersey is invalid
        cout << "Transferred player " << playerName;
        cout << " from team " << departTeamName;
        cout << " to team " << arriveTeamName;
        cout << "." << endl;
    }

}

void LeagueManagementSystem::showAllTeams() const {
    cout << "Teams in the league management system:" << endl;
    if (this->size == 0) {
        cout << "None" << endl;
        return;
    }

    for (int i = 0; i < this->size; i++) {
        cout << teams[i]->getName() << ", " 
            << teams[i]->getYear() << ", "
            << teams[i]->getSize() << " players, "
            << teams[i]->getTotalSalary() << " TL total salary"
            << endl;
    }
}

void LeagueManagementSystem::showTeam( const string name ) const {
    int indexofTeam = -1; //index to store team's index in array if it exists
    
    if (!(this->isTeamExists(name, indexofTeam))) {
        cout << "Team " << name << " does not exist."
            << endl;
        return;
    }
    cout << "Team:" << endl;
    cout << teams[indexofTeam]->getName() << ", " 
        << teams[indexofTeam]->getYear() << ", "
        << teams[indexofTeam]->getSize() << " players, "
        << teams[indexofTeam]->getTotalSalary() << " TL total salary"
        << endl;
    cout << "Players:" << endl;
    for (int i = 0; i < teams[indexofTeam]->getSize(); i++) {
        teams[indexofTeam]->printPlayerInfo(i); //Player::printPlayerInfo()
    }

}

void LeagueManagementSystem::showPlayer(const string name) const {
    int indexOfPlayer = -1;
    for (int i = 0; i < this->size; i++) {
        if (teams[i]->isPlayerExists(name, indexOfPlayer)) {
            teams[i]->printPlayerInfo(indexOfPlayer);
            cout << "Plays in team " << teams[i]->getName() << "." << endl;
            return;
        }
    }
    cout << "Player " << name << " does not exist." << endl;
}

bool LeagueManagementSystem::isTeamExists(const string name, int& index) const{
    for (int i = 0; i < size; i++) {
        if( (*teams[i]).getName() == name) {
            index = i; //storing index of the team
            return true;
        }
    }
    return false;
}

void LeagueManagementSystem::updateTeamsBy(const int change) {
    int tempSizeCount = 0; //to keep track of indexes of tempTeams array (for removeTeam cases)
    size += change; //updating size
    Team** tempTeams = new Team*[size]; //change can be either -1 or 1
    
    for (int i = 0; i < size - change; i++) { //size - change means initial value of size
        if (teams[i] == nullptr) {
            continue; //if teams[i] had been removed, it is assigned as nullptr
        }
        tempTeams[tempSizeCount] = teams[i];
        tempSizeCount++;
    }    
    delete[] teams;

    teams = new Team*[size]; 

    for (int i = 0; i < size; i++) {
        teams[i] = tempTeams[i];
    }
    delete[] tempTeams;
}
