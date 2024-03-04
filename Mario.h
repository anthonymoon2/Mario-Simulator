#include <iostream>
using namespace std;
#include <cstdlib>

class Mario{
    public:
        void setLives(int V); 
        int getLives(void); 
        void addLife(int life);

        void setCoins(int C);
        int getCoins(void);
        int addCoin(int add);

        void setPowerLevel(int power);
        int getPowerLevel(void);
        int increasePowerLevel(int mushroom);

        void setDefeatedCount(int defeated);
        int getDefeatedCount(void);

        bool fightGoomba(void);
        bool fightKoomba(void);
        bool fightBoss(void);

        Mario(); // class constructor
        ~Mario(); // class destructor
    private: 
        int lives;
        int coins;
        int powerLevel;
        int defeatedCount;

};