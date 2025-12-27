#include <iostream>
#include <fstream>
#include <vector>
#include <execution>
#include <numeric>
#include <string>
#include <algorithm>
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


pair<vector<char>, vector<vector<long>>> partAParsing(ifstream& infile) {
    vector<char> column_types;
    vector<vector<long>> columns;
    string line;
    
    getline(infile, line);
    int i = 0;
    while (i < line.size()) {
            int start_i = i;
            while (i < line.size() && line[i] != ' ') {
                i++;
            }
            // cout << "column=" << line.substr(start_i, i - start_i) << endl;
            vector<long> column;
            column.push_back(stol(line.substr(start_i, i - start_i)));
            columns.push_back(column);
            i++;
            while (i < line.size() && line[i] == ' ') {
                i++;
            }
    }

    while (getline(infile, line)) {
        int col_i = 0;
        i = 0;
        while (i < line.size()) {
            int start_i = i;
            while (i < line.size() && line[i] != ' ') {
                i++;
            }
            // cout << "column=" << line.substr(start_i, i - start_i) << endl;
            try {
                columns[col_i].push_back(stol(line.substr(start_i, i - start_i)));   
            } catch (const std::exception& e) {
                column_types.push_back(line[start_i]);
            }
            i++;
            while (i < line.size() && line[i] == ' ') {
                i++;
            }
            col_i++;
        }
    }
    return make_pair(column_types, columns);
}


string to_string_func(long v) {
    return to_string(v);
}

pair<vector<char>, vector<vector<long>>> partBParsing(ifstream& infile) {
    auto [column_types, columns] = partAParsing(infile);
    vector<vector<long>> partb_columns;
    print(column_types, columns);

    for (const auto& col : columns) {
        vector<string> partb_col_string(col.size(), ""); 

        for (auto number : col) {
            string digits = to_string(number);
            for (int i = 0; i < digits.size(); i++) {
                
                partb_col_string[digits.size() - 1 - i] += digits[i];
            }
        }

        vector<long> partb_col;
        transform(partb_col_string.begin(), partb_col_string.end(), back_inserter(partb_col), [](const string& s) { return stol(s); });
        partb_columns.push_back(partb_col);
    }

    print(column_types, partb_columns);
    return make_pair(column_types, partb_columns);
}

long calculation(const vector<char>& column_types, const vector<vector<long>>& columns) {
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
    return checksum;
}


void partA(ifstream& infile) {
    auto [column_types, columns] = partAParsing(infile);
    long result = calculation(column_types, columns);
    cout << "Part A has a checksum of " << result << endl;
}

void partB(ifstream& infile) {
    auto [column_types, columns] = partBParsing(infile);
    long result = calculation(column_types, columns);
    cout << "Part B has a checksum of " << result << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day6.txt");
    partB(infile);
    
    return 0;
}
