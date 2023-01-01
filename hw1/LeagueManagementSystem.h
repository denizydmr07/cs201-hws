//Deniz Aydemir Section 1 22001859 

#ifndef __LEAGUEMANAGEMENTSYSTEM_H
#define __LEAGUEMANAGEMENTSYSTEM_H

#include "Team.h"
using namespace std;

class LeagueManagementSystem {
    public:
        LeagueManagementSystem();
        ~LeagueManagementSystem();

        void addTeam( const string name, const int year );
        void removeTeam( const string name );
        void addPlayer( const string teamName, const string playerName,
            const int jersey, const int salary );
        void removePlayer( const string teamName, const string playerName );
        void transferPlayer( const string playerName,
            const string departTeamName, const string arriveTeamName );
        void showAllTeams() const;
        void showTeam( const string name ) const;
        void showPlayer( const string name ) const;

        void updateTeamsBy(const int n); // n can be either 1 or -1
        bool isTeamExists(const string name, int& index) const;
    private:
        Team **teams; 
        int size;
};
#endif