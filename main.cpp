#include "World.h"
#include <iostream>
#include <string>

// Get valid input for probabilities
double getValidProbability(double& probability, const std::string& message) {
    double input;
    do {
        std::cout << message << " (0.0 - " << probability << "): ";
        std::cin >> input;
        if (input < 0 || input > probability) {
            std::cout << "Invalid input. Please enter a probability (double) between 0.0 and " << probability << "." << std::endl;
        }
    } while (input < 0 || input > probability);
    probability -= input;
    return input;
}

// get valid input for levels and lives within the range 1-3
int getValidInput(const std::string& prompt) {
    int input;
    do {
        std::cout << prompt;
        std::cin >> input;
        if (input < 1 || input > 3) {
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
        }
    } while (input < 1 || input > 3);
    return input;
}

int main(int argc, char **argv){
    int lvls, lives;
    // get levels and lives
    lvls = getValidInput("Enter number of levels (1-3): ");
    lives = getValidInput("Enter number of lives (1-3): ");

    double probability = 1.0;
    double p_coins, p_nothing, p_goombas, p_koopas, p_mushroom;

    std::cout << "Please enter the probabilities (NEXT FIVE MUST ADD UP TO 1.0): " <<std::endl;
    // get probability values
    p_coins = getValidProbability(probability, "Probability of coins");
    p_nothing = getValidProbability(probability, "Probability of empty spaces");
    p_goombas = getValidProbability(probability, "Probability of Goombas");
    p_koopas = getValidProbability(probability, "Probability of Koopas");
    p_mushroom = getValidProbability(probability, "Probability of Mushrooms");

    // create world and simulate
    World w;
    w.createWorld(lvls, lives, p_coins, p_nothing, p_goombas, p_koopas, p_mushroom);

    return 0;
}

