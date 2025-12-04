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

int turnDialB(int* zeroCount, int currentDial, std::string instruction) {
    int dialToMove = std::stoi(instruction.substr(1));
    // std::cout << "Current Dial: " << currentDial << ", Instruction: " << instruction << ", Dial to Move: " << dialToMove << std::endl;
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
    if (nextDial == 0) {
        (*zeroCount)++;
    }
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
        currentDial = turnDialB(&zeroCount, currentDial, line);
    }
    std::cout << "Number of times dial reached zero: " << zeroCount << std::endl;
    return zeroCount;
}

int partB() {
    int currentDial = STARTING_DIAL;
    std::ifstream infile("inputs/day1.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::cout << "Processing instruction: " << line << std::endl;
        currentDial = turnDial(currentDial, line);
    }
    std::cout << "Final Dial Position: " << currentDial << std::endl;
    return currentDial;
}

int main(int argc, char** argv) {
    // partA();
    partB();
}