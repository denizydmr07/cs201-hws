//Deniz Aydemir Section 1 22001859 

#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>
using namespace std;

class Player {
    public:
        Player();
        Player(string name, int jersey, int salary);
        string getName();
        void setName(string name);
        int getJersey();
        void setJersey(int jersey);
        int getSalary();
        void setSalary(int salary);
    private:
        string name;
        int jersey;
        int salary;
};
#endif