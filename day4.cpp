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

int rollsLeft(const vector<vector<bool>>& map) {
    int rolls = 0;
    int rows = map.size();
    int cols = map[0].size();
    
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (map[r][c]) {
                rolls++;
            }
        }
    }
    return rolls;
}

int removeRollsOnMap(vector<vector<bool>>& map) {
    int rolls = 0;
    int rows = map.size();
    int cols = map[0].size();

    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (map[r][c] && hasLessThanFourNeighbors(map, r, c)) {
                rolls++;
                map[r][c] = false;
            }
        }
    }
    return rolls;
}

void printMap(const vector<vector<bool>>& map) {
    int rows = map.size();
    int cols = map[0].size();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (map[r][c]) {
                cout << "@";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void partA(vector<vector<bool>>& map) {
    int rolls = removeRollsOnMap(map);
    cout << "Part A found " << rolls << " rolls" << endl;
}

void partB(vector<vector<bool>>& map) {
    int rolls_removed = 0;
    int rows = map.size();
    int cols = map[0].size();

    int rolls_prev_left = 0;
    int rolls_left = rollsLeft(map);
    while (rolls_prev_left != rolls_left) {
        int a = removeRollsOnMap(map);
        rolls_removed += a;
        // cout << "After removing " << a << " rolls, " << rolls_left - a << " remain:" << endl;
        // printMap(map);
        rolls_prev_left = rolls_left;
        rolls_left = rollsLeft(map);
    }


    cout << "Part B found " << rolls_removed << " rolls that were removed." << endl;
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
    partB(map);
    return 0;
}
