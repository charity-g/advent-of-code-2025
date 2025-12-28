#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <numeric>
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
    vector<string> matrix;
    string line;

    while (getline(infile, line)) {
        matrix.push_back(line);
    }
    
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < m; ++i) {
        dp[n - 1][i] = 1;
    }

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == '^') {
                int total = 0;
                if (j > 0) {
                    total += dp[i + 1][j - 1];
                } 
                if (j < m - 1) {
                    total += dp[i + 1][j + 1];
                }
                dp[i][j] = total;
            } else {
                dp[i][j] = dp[i + 1][j];
            }
        }
    }

    int timelines = dp[0][start];

    cout << "Part B shows that there are: " << timelines << " timelines." << endl;
}


void partB_nonDP(ifstream& infile, int start) {
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
