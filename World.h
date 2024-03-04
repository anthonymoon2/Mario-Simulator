#include <iostream>
using namespace std;

#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"

class World{
    public: 
        World();
        ~World();

        // create world 
        void createWorld(int L, int V, double c, double l, double g, double k, double m);

    private: 
        bool gameOver;
        bool changeEntity;

        void populateEntity(int L, int N, int numOfEntities, char entityChar);
        void addBoss(int L, int N);
        void printCurrentWorld(int L, int N, int V);
        void simulateMario(Mario mario, int lvl, int pointOne, int pointTwo, char positionEntity, bool& gameOver, int L);

        void printWorld(int L, int N, int V);
        std::vector<std::vector<std::vector<char> > > newWorld;
};

#endif // WORLD_H