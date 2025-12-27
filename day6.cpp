#include <iostream>
#include <fstream>
#include <vector>
#include <execution>
#include <numeric>
using namespace std;

void print(const vector<char>& column_types, const vector<vector<long>>& columns) {
    for (const auto& col : column_types) {
        cout << col << " ";
    }
    cout << endl;

    for (const auto& col : columns) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void partA(const vector<char>& column_types, const vector<vector<long>>& columns) {
    long checksum = 0;


    for (int i = 0; i < columns.size(); i++) {
        long curr_checksum = 0;
        if (column_types[i] == '*') {
            curr_checksum = reduce(columns[i].begin(), columns[i].end(), long(1), std::multiplies<long>());
        } else if (column_types[i] == '+') {
            curr_checksum = reduce(columns[i].begin(), columns[i].end());
        } else {
            cout << "[partA] Unknown column type " << column_types[i] << " at index " << i << endl;
        }
        checksum += curr_checksum;
    }
    cout << "Part A has a checksum of " << checksum << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day6.txt");

    vector<char> column_types;
    vector<vector<long>> columns;
    string line;
    
    getline(infile, line);
    for (int i = DEFAULT_COL_LEN - 1; i < line.size(); i += DEFAULT_COL_LEN + 1) {
            // cout << "column=" << line.substr(i - DEFAULT_COL_LEN + 1, DEFAULT_COL_LEN) << endl;
            vector<long> column;
            column.push_back(stol(line.substr(i - DEFAULT_COL_LEN + 1, DEFAULT_COL_LEN)));
            columns.push_back(column);
    }

    while (getline(infile, line)) {
        int col_i = 0;
        for (int i = DEFAULT_COL_LEN - 1; i < line.size(); i += DEFAULT_COL_LEN + 1) {
            // cout << "column=" << line.substr(i - DEFAULT_COL_LEN + 1, DEFAULT_COL_LEN) << endl;
            try {
                columns[col_i].push_back(stol(line.substr(i - DEFAULT_COL_LEN + 1, DEFAULT_COL_LEN)));    
            } catch (const std::exception& e) {
                column_types.push_back(line[i - DEFAULT_COL_LEN + 1]);
            }
            col_i++;
        }

    }
    
    // print(column_types, columns);
    partA(column_types, columns);

    return 0;
}
