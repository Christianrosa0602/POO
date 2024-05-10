//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"

struct Action;
class Player;

class Enemy : public Character {
private:
    int level = 0;
public:
    Enemy(char[30], int, int, int, int, int);
    int getMaxHealth();
    void doAttack(Character* target);
    void takeDamage(int damage) override;
    void levelup();
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> teamMembers);
};



#endif //RPG_ENEMY_H
