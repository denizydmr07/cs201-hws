//Deniz Aydemir Section 1 22001859 

#ifndef __TEAM_H
#define __TEAM_H

#include "Player.h"


using namespace std;

class Team {
    public:
        Team();
        ~Team();
        Team(string name, int year);
        string getName();
        void setName(string name);
        int getYear();
        void setYear(int year);
        int getSize();
        void incrementSize();
        void decreaseSize();

        void addPlayer(const string name, const int jersey, const double salary);
        void updatePlayersBy(const int change);
        bool isPlayerExists(const string name, int& index);
        bool isPlayerExists(const int jersey, int& index);
        void removePlayer(const string name);
        bool transferPlayer(Team* departTeam, const int playerIndex);
        int getTotalSalary();
        void printPlayerInfo(const int index);
    private:
        string name;
        int year;
        Player** players;
        int size;
};
#endif