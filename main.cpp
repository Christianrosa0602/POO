#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("Axheteris", 20, 10, 6, 10, 1);
    Enemy *enemy = new Enemy("Cakal", 20, 5, 2, 7, 1);
    Enemy *enemy2 = new Enemy("Alucin", 15, 4, 2, 2, 1);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
