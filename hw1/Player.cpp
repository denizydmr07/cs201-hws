//Deniz Aydemir Section 1 22001859 

#include "Player.h"
using namespace std;
Player::Player() {
    setName("");
    setJersey(-1);
    setSalary(-1);
}

Player::Player(string name, int jersey, int salary) {
    setName(name);
    setJersey(jersey);
    setSalary(salary);
}

string Player::getName() {
    return Player::name;
}

void Player::setName(string name) {
    Player::name = name;
}

int Player::getJersey() {
    return Player::jersey;
}

void Player::setJersey(int jersey) {
    Player::jersey = jersey;
}

int Player::getSalary() {
    return Player::salary;
}

void Player::setSalary(int salary) {
    Player::salary = salary;
}
