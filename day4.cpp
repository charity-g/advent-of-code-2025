#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

bool hasLessThanFourNeighbors(const vector<vector<bool>>& map, int r, int c) {
    int rows = map.size();
    int cols = map[0].size();
    int roll_count = 0;
    list<int> i_vals = {r};
    list<int> j_vals = {c};

    // check up
    if (r > 0) {
        i_vals.push_back(r - 1);
    }
    // check down
    if (r < rows - 1) {
        i_vals.push_back(r + 1);
    }
    // check left
    if (c > 0) {
        j_vals.push_back(c - 1);
    }
    // check right
    if (c < cols - 1) {
        j_vals.push_back(c + 1);
    }

    for (int i : i_vals) {
        for (int j : j_vals) {
            if ((i != r || j != c) && map[i][j]) {
                roll_count++;
            }
        }
    }

    // cout << "Roll count for (" << r << "," << c << "): " << roll_count << endl;
    return roll_count < 4;
}

void partA(const vector<vector<bool>>& map) {
    int rolls = 0;

    int rows = map.size();
    int cols = map[0].size();

    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (map[r][c] && hasLessThanFourNeighbors(map, r, c)) {
                rolls++;
            }
        }
    }


    cout << "Part A found " << rolls << " rolls" << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day4.txt");

    vector<vector<bool>> map;
    string line;
    while (getline(infile, line)) {
        vector<bool> row;
        for (char c : line) {
            if (c == '@') {
                row.push_back(true);
            } else {
                row.push_back(false);
            }
        }
        map.push_back(row);
    }
    partA(map);
    return 0;
}
