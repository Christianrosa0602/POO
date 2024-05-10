//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(char name[30], int health, int attack, int defense, int speed, int level) : Character(name, health, attack, defense, speed, true, level) {
    experience = 0;
    this->level = 1;
}

void Player::doAttack(Character *target, vector<Enemy*> enemies) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
    if (target->getHealth() <= 0) {
        gainExperience(60, enemies);
    }
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "\tYou have taken " << damage << " damage" << endl;
    cout << "\n";
    if (health <= 0) {
        cout << "You have died" << endl;
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }

    this->fleed = fleed;
}

void Player::emote() {
    cout << "Jokes on you" << endl;
}

void Player::levelUp(vector<Enemy*> enemies) {
    int i;
    int hppls = getHealth() * .50;
    int atkpls = getAttack() * .50;
    int defpls = getDefense() * .50;
    int spdpls = getSpeed() * .50;
    setLevel(getLevel() + 1);
    setHealth(getHealth() + hppls);
    setAttack(getAttack() + atkpls);
    setDefense(getDefense() + defpls);
    setSpeed(getSpeed() + spdpls);

    for (i = 0; i < enemies.size(); i++) {
        enemies[i]->levelup();
    }


    cout << "\t>>>>>>>>> Level up ;v!!!! Your level current: " << getLevel() << " <<<<<<<<<<<<" << endl;
    cout << "\n\n";


}

void Player::gainExperience(int exp, vector<Enemy*> enemies) {
    experience += exp;
    if (experience >= 100) {
        int trash = experience - 100;
        levelUp(enemies);
        experience = trash;
    }
}

Character* Player::getTarget(vector<Enemy*> enemies) {
    int targetIndex = 0;
    while (true) {
        cout << "Choose your Problem <<<<" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            cout << i << ". " << enemies[i]->getName() << endl;
        }
        cout << "> ";
        cin >> targetIndex;
        cout << "\n";
        if (targetIndex >= enemies.size() || targetIndex < 0) {
            cout << "\t Invalid Option!!!!!!!!!" << endl;
            cout << "\n";
        }
        else break;
    }
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    bool oks = false;
    Character* target = nullptr;
    bool fleed = false;
    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    while (oks == false) {
        cout << "Choose your action" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Flee" << endl;
        cout << ">";
        cin >> option;
        cout << "\n";
        switch (option){
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target, enemies]() {
                doAttack(target, enemies);
                gainExperience(20, enemies);
                };
            oks = true;
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
                };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }
    return myAction;
}