#include "Mario.h"

Mario::Mario(){} // default constructor
Mario::~Mario(){} // default destructor


// setter and getters for lives
void Mario::setLives(int V){
    lives = V;
}
int Mario::getLives(void){
    return lives;
}
// add a life
void Mario::addLife(int life){
    lives += 1;
}

// setter and getters for coins
void Mario::setCoins(int C){
    coins = C;
}
int Mario::getCoins(void){
    return coins;
}
int Mario::addCoin(int add){
    coins += 1;
    if (coins == 20){
        lives += 1;
        coins = 0;
    }
    return coins;
}
// setter and getter for powerlevels
void Mario::setPowerLevel(int power){
    powerLevel = power;
}
int Mario::getPowerLevel(void){
    return powerLevel;
}
int Mario::increasePowerLevel(int mushroom){
    if (powerLevel != 2){
        powerLevel += mushroom;
    }
    return powerLevel;
}
// setter and getter for how many enemies defeated
void Mario::setDefeatedCount(int defeated){
    defeatedCount = defeated;
}
int Mario::getDefeatedCount(void){
    return defeatedCount;
}

// bool which uses rand() function to determine if mario won/lost
bool Mario::fightGoomba(void){
    int chance = rand() % 5; 
    if (chance <= 3){ // this is because mario has 80% chance of winning
        defeatedCount += 1;
        return true;
    }
    else{ // lose to goomba
        if (powerLevel == 0){
            lives -= 1;
        }
        else {
            powerLevel -=1;
        }
        return false;
    }
}
// bool which uses rand() function to determine if mario won/lost
bool Mario::fightKoomba(void){
    int chance = rand() % 100; 
    if (chance <= 64){ // 65% chance of winning
        defeatedCount += 1;
        return true;
    }
    else{ // lose to koomba
        if (powerLevel == 0){
            lives -= 1;
        }
        else {
            powerLevel -=1;
        }
        return false;
    }
}
// bool which uses rand() function to determine if mario won/lost
bool Mario::fightBoss(void){
    int chance = rand() % 4; // 50% chance of winning
    if (chance == 0){
        defeatedCount += 1;
        return true;
    }
    else{ // lose to boss
        if (powerLevel < 2){
            lives -= 1;
        }
        else {
            powerLevel -=2;
        }
        return false;
    }
}






