#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main(int argc, char** argv) {
    ifstream infile("inputs/day12.txt");

    
    auto beg = chrono::high_resolution_clock::now();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
    cout << "Time taken to run function: " << duration.count() << " microseconds" << endl;

    return 0;
}
// LOL i give up