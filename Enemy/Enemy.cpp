//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>


using namespace std;

int maxHealth = 0;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(char name[], int health, int attack, int defense, int speed, int level) : Character(name, health, attack, defense, speed, false, level) {
    maxHealth = health;
    level = 1;
};

int Enemy::getMaxHealth() {
    return maxHealth;
}



void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<getName()<<" \t*****has died*****\n"<<endl;
    }
    else {
        cout<<"\t"<< getName() << " has taken " << damage << " damage" <<"\n" << endl;
        cout << "\n";
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player*> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    if ((this->getMaxHealth() * 0.50 >= this->getHealth()) && rand() % 100 < 30) {
        myAction.action = [this, target]() {
            this->fleed = true;
            };
    }
    else {
        myAction.action = [this, target]() {
            doAttack(target);
            };

    }

        return myAction;

    }

void Enemy::levelup() {
    int hppls = this->getHealth() * .50;
    int atkpls = this->getAttack() * .50;
    int defpls = this->getDefense() * .50;
    int spdpls = this->getSpeed() * .50;
    this->setLevel(getLevel() + 1);
    this->setHealth(getHealth() + hppls);
    this->setAttack(getAttack() + atkpls);
    this->setDefense(getDefense() + defpls);
    this->setSpeed(getSpeed() + spdpls);


    cout << "\t>>>>>>>>> The enemy [" << getName() << "] has leveled up, he kills you!! level current to destroy you : " << getLevel() << " <<<<<<<<<<<<" << endl;
    cout << "\n\n";
}