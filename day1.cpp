#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
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

int turnDialB(int* zeroCount, int currentDial, std::string instruction) {
    int dialToMove = std::stoi(instruction.substr(1));
    if (instruction[0] == 'L') {
         dialToMove *= -1;
    }
    int nextDial = currentDial + dialToMove;
    while (nextDial < 0) {
        (*zeroCount)++;
        nextDial += TOTAL_DIALS;
    }
    while (nextDial >= TOTAL_DIALS) {
        (*zeroCount)++;
        nextDial -= TOTAL_DIALS;
    }
    if (currentDial == 0) {
        (*zeroCount)++;
    }
 
    std::cout << "Processing instruction: " << 
        currentDial << " " <<
        instruction << " " << dialToMove << " " << nextDial << " " << *zeroCount << std::endl;
    return nextDial;
}


int partA() {
    int currentDial = STARTING_DIAL;
    int zeroCount = 0;
    std::ifstream infile("inputs/day1.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        // std::cout << "Processing instruction: " << line << std::endl;
        currentDial = turnDial(currentDial, line);
        if (currentDial == 0) {
            zeroCount++;
        }
    }
    std::cout << "Number of times dial reached zero: " << zeroCount << std::endl;
    return zeroCount;
}

int partB() {
    int currentDial = STARTING_DIAL;
    int zeroCount = 0;
    std::ifstream infile("inputs/day1.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        currentDial = turnDialB(&zeroCount, currentDial, line);
    }
    std::cout << "Final Zero Count: " << zeroCount << std::endl;
    return zeroCount;
}

int main(int argc, char** argv) {
    // partA();
    partB();
}