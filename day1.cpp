#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define TOTAL_DIALS 100
#define STARTING_DIAL 50

int turnDial(int currentDial, std::string instruction) {
    // int nextDial = currentDial + instruction with 100 logic
    // return nextDial;
    return 0; 
}

int main(int argc, char** argv) {
    std::cout << "Day 1 Part 1" << std::endl;
    int currentDial = STARTING_DIAL;
    int numberOfZeros = 0;
    std::ifstream infile("input1.txt");
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