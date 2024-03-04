#include "World.h"

#include <cstdlib> // this is for the random generator 
#include <ctime>

World::World(){
    srand(static_cast<unsigned>(time(nullptr))); // for random num generator
}; 
World::~World(){}; 

// main function
void World::createWorld(int L, int V, double c, double l, double g, double k, double m){
    int lvl = 0;
    int N = 4; // grid size

    newWorld.resize(L, std::vector<std::vector<char> >(N, std::vector<char>(N, 'x'))); // Initialize with 'x'

    int totalElements = N*N; 
    // gives the number of each item to add to the 2D array 
    int numOfCoins = totalElements * c; 
    int numOfNothing = totalElements * l;
    int numOfGoombas = totalElements * g;
    int numOfKoopas = totalElements * k;
    int numOfMushrooms = totalElements * m; 

    // fill in the array with x
    for (int a = 0; a < L; a++){
        for (int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                newWorld[a][j][k] = 'x';
            }
        }
    }

    // Populate World
    populateEntity(L, N, numOfCoins, 'c'); // For coins
    populateEntity(L, N, numOfGoombas, 'g'); // For Goombas
    populateEntity(L, N, numOfKoopas, 'k'); // For Koopas
    populateEntity(L, N, numOfMushrooms, 'm'); // For Mushrooms

    addBoss(L, N);

    // run World
    printWorld(L, N, V);
}

// Unified function to populate entities
void World::populateEntity(int L, int N, int numOfEntities, char entityChar) {
    for (int a = 0; a < L; a++) {
        int entitiesPlaced = 0;
        while (entitiesPlaced < numOfEntities) {
            int x = rand() % N;
            int y = rand() % N;

            if (newWorld[a][x][y] == 'x') {
                newWorld[a][x][y] = entityChar;
                entitiesPlaced++;
            }
        }
    }
}

// add boss
void World::addBoss(int L, int N){
    // generating a random position for the boss
    int f = rand() % N;
    int z = rand() % N;
    for (int a = 0; a < L; a++){
        newWorld[a][f][z] = 'b'; // b stands for BOSS
    }
}

void World::printCurrentWorld(int L, int N, int V){
    string output;

    for (int i = 0; i < L; i++){ 
        output += "level:" + std::to_string(i + 1) + "\n";
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                std::string s(1, newWorld[i][j][k]);
                output += s + " ";
            }
            output += "\n";
        }
        output += "\n";
    }

    cout << output;
}

void World::simulateMario(Mario mario, int lvl, int pointOne, int pointTwo, char positionEntity, bool& gameOver, int L){
    string output;

    output += "[" + std::to_string(pointTwo + 1) + "][" + std::to_string(pointOne + 1) + "] " + "\n";
    output += "Action: ";
    
    // switch statement that takes in the char of current Mario position
    switch(positionEntity){ 
        case 'c':
        output += "Mario collected a coin.";
        mario.addCoin(1);
        changeEntity = true;
        break;
    case 'x':
        output += "The position is empty.";
        break;
    case 'g':
        if (mario.fightGoomba()){
            newWorld[lvl][pointOne][pointTwo] = 'x';
            changeEntity = true;
            output += "Mario fought a Goomba and won.";
        }
        else {
            output += "Mario fought a Goomba and lost.";
        }
        break;
    case 'k':
        if (mario.fightKoomba()){
            changeEntity = true;
            output += "Mario fought a Koomba and won.";
        }      
        else{
            output += "Mario fought a Koomba and lost.";
        }     
        break;
    case 'm':
        output += "Mario ate a mushroom.";
        mario.increasePowerLevel(1);
        break;
    case 'b':
        if (mario.fightBoss()){
            output += "Mario fought the level boss and won.";
            int endGame = L - 1;
            if (lvl == endGame){
                output += "\n";
                output += "Mario won the game.";
                gameOver = true;
            }
            else{
                lvl += 1;
            }
        }  
        else {
            gameOver = true;
            output += "Mario fought the level boss and lost.";
        }
        break;
    }

    // mario adds a life every 7 kills
    if (mario.getDefeatedCount() == 7){ 
        cout << "Mario defeated 7 enemies so he got one more life.";
        mario.addLife(1); 
    }

    output += "\nPower Level: " + std::to_string(mario.getPowerLevel());
    output += " Coins: " + std::to_string(mario.getCoins());
    output += " Lives: " + std::to_string(mario.getLives());
    output += " Enemies defeated: " + std::to_string(mario.getDefeatedCount()) + "\n";
    cout << output;
}


// simulate and print game
void World::printWorld(int L, int N, int V){

    // create variables
    string output;
    int lvl = 0;
    int numOfMoves;

    // make a random point where mario will begin the game
    int pointOne = rand() % N;
    int pointTwo = rand() % N; 
    char positionEntity = newWorld[0][pointOne][pointTwo];

    // Create Mario object and set all attributes
    Mario mario; 
    mario.setCoins(0); 
    mario.setLives(V);
    mario.setPowerLevel(0);
    mario.setDefeatedCount(0);

    // Get first original entity to replace after mario spawns
    char originalEntity = newWorld[lvl][pointOne][pointTwo];

    // Print Original World with Mario's starting position
    newWorld[lvl][pointOne][pointTwo] = 'H';
    cout << "\nAction: Mario Spawned \n";
    printCurrentWorld(L, N, V);
    
    // replace Mario spawn position with original entity
    newWorld[lvl][pointOne][pointTwo] = originalEntity;

    int prevPointOne = -1;
    int prevPointTwo = -1;

    while (!gameOver){
        prevPointOne = pointOne;
        prevPointTwo = pointTwo;

        // Get coordinates for next Mario movement
        int direction = rand() % 4; // gives a random number between 0-3

        if (direction == 0){ 
            pointOne +=1;
            cout << "Mario moved down to position: ";
        }
        else if (direction == 1){
            pointOne -= 1;
            cout << "Mario moved up to position: ";
        }
        else if (direction == 2){ 
            pointTwo += 1;
            cout << "Mario moved right to position: ";
        }
        else { 
            pointTwo -= 1;
            cout << "Mario moved left to position: ";
        }

        // Movement for Mario when he has to wrap around horizontally
        if (pointOne == N){ 
            pointOne -= N;
        }
        else if (pointOne == -1){ 
            pointOne = N-1;
        }
        // Movement for Mario when he has to wrap around vertically 
        if (pointTwo == N){ 
            pointTwo -= N;
        }
        else if (pointTwo == -1){ 
            pointTwo = N-1;
        }

        // update position entity with Mario's next position's entity
        positionEntity = newWorld[lvl][pointOne][pointTwo];
        // simulate Mario (print out what move he made)
        simulateMario(mario, lvl, pointOne, pointTwo, positionEntity, gameOver, L);
        // replace current position with H
        newWorld[lvl][pointOne][pointTwo] = 'H';
        // print out current World
        printCurrentWorld(L, N, V);


        // If mario got a coin or defeated an enemy
        if (changeEntity){
            newWorld[lvl][pointOne][pointTwo] = 'x';
        }
        else{
            newWorld[lvl][pointOne][pointTwo] = positionEntity;
        }

        // checks if mario has no lives
        if (mario.getLives() == 0 || gameOver){
            output += " Mario lost the game.";
            gameOver = true;
            break;
        }

        numOfMoves += 1;
        changeEntity = false;
    }
}

