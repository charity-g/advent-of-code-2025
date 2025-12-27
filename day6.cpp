#include <iostream>
#include <fstream>
#include <vector>
#include <execution>
#include <numeric>
#include <string>
#include <algorithm>
using namespace std;
const int PARTB_COLUMNS = 3;

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
    string line;
    int line_len;
    vector<char> column_types;
    vector<string> unrotated_columns;
    vector<vector<long>> columns;
    int i = 0, start_i = 0;

    while (getline(infile, line)) {
        if (!line.empty() && (line[0] == '*' || line[0] == '+')) {
            break;
        }
        unrotated_columns.push_back(line);
    }
    i = 0;
    while (i < line.size()) {
        if (line[i] != ' ') {
            column_types.push_back(line[i]);
        }
        i++;
    }

    
    line_len = unrotated_columns[0].size();
    vector<long> column;
    string col_str;
    for (int i = 0; i < line_len; i++) {
        col_str = "";
        for (auto col : unrotated_columns) {
            if (col[i] != ' ') {
                col_str += col[i];
            }
        }
        if (col_str.size() > 0) {
            column.push_back(stol(col_str));
        } else {
            columns.push_back(column);
            column.clear();
        }
    }
    columns.push_back(column);
    

    print(column_types, columns);
    return make_pair(column_types, columns);
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
