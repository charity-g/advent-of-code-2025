#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define TOTAL_DIALS 100
#define STARTING_DIAL 50

int turnDial(int currentDial, std::string instruction) {
    int dialToMove = std::stoi(instruction.substr(1));
    // std::cout << "Current Dial: " << currentDial << ", Instruction: " << instruction << ", Dial to Move: " << dialToMove << std::endl;
    if (instruction[0] == 'L') {
         dialToMove *= -1;
    }
    int nextDial = currentDial + dialToMove;
    while (nextDial < 0) {
        nextDial += TOTAL_DIALS;
    }
    while (nextDial >= TOTAL_DIALS) {
        nextDial -= TOTAL_DIALS;
    }
    return nextDial;
}

int main(int argc, char** argv) {
    int currentDial = STARTING_DIAL;
    int numberOfZeros = 0;
    std::ifstream infile("inputs/day1.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        // std::cout << "Processing instruction: " << line << std::endl;
        currentDial = turnDial(currentDial, line);
        if (currentDial == 0) {
            numberOfZeros++;
        }
    }
    std::cout << "Number of times dial reached zero: " << numberOfZeros << std::endl;
    return numberOfZeros;
}