#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
using namespace std;

int findStartX(const string& line) {
    int res = line.find('S');   
    return res;
}

void partA(ifstream& infile, int start) {
    int splits = 0;
    string line;
    set<int> q = {start};

    while(getline(infile, line)) {
        set<int> new_q;
        for (int pos : q) {
            if (pos < 0 || pos >= line.size()) {
                continue;
            }
            if (line[pos] == '^') {
                splits++;
                new_q.insert(pos - 1);
                new_q.insert(pos + 1);
            } else {
                new_q.insert(pos);
            }
        }    
        q = new_q;
    }

    cout << "Part A shows that laser splits: " << splits << " times." << endl;
}

void partB(ifstream& infile, int start) {
    int splits = 0;
    string line;
    list<int> q = {start};

    while(getline(infile, line)) {
        list<int> new_q;
        for (int pos : q) {
            if (pos < 0 || pos >= line.size()) {
                continue;
            }
            if (line[pos] == '^') {
                splits++;
                new_q.push_back(pos - 1);
                new_q.push_back(pos + 1);
            } else {
                new_q.push_back(pos);
            }
        }    
        q = new_q;
    }

    cout << "Part B shows that laser splits: " << splits << " times." << endl;
}

int main(int argc, char** argv) {
    ifstream infile("inputs/day7.txt");
    string line;
    getline(infile, line);
    int start = findStartX(line);

    // partA(infile, start);
    partB(infile, start);

    return 0;
}
