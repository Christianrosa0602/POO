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

Player::Player(char name[], int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    experience = 0;
    level = 1;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
    if (target->getHealth() <= 0) {
        gainExperience(60);
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

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);


    cout << "\t>>>>>>>>>>> Level 1/(down) <<<<<<<<<<<<<<<<<<";
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        int trash = experience - 100;
        levelUp();
        experience = trash;
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "\t****Choose a enemy****\n" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
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
            myAction.action = [this, target]() {
                doAttack(target);
                gainExperience(5);
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