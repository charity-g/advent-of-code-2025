
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
using namespace std;

// inclusive [start, end]
long calculateInvalidSumB(string start, string end) {
    int n_half = start.length() / 2;
    int half_start;

    if (start.length() % 2 == 1) {
        half_start = stoi("1" + string(n_half, '0')); // ceil even number of digits
    } else {
        half_start = stoi(start.substr (0, n_half));
        if (stoi(start.substr (n_half, n_half)) > half_start) {
            half_start = half_start + 1;
        }
    }

    n_half = end.length() / 2;
    int half_end;
    if (end.length() % 2 == 1) {
        half_end = stoi(string(n_half, '9')); // todo for floor even number of digits
    } else {
        half_end = stoi(end.substr (0, n_half));
        if (stoi(end.substr (n_half, n_half)) < half_end) {
            half_end = half_end - 1;
        }
    }
    long sum = 0;
    for (int i = half_start; i <= half_end; i++) {
        string first_half = to_string(i);
        string second_half = first_half;
        string full_number = first_half + second_half;
        long full_num_int = stol(full_number);
        if (full_num_int < stol(start) && full_num_int > stol(end)) {
            cout << "Error in bounds calculation! Number:" << full_num_int << endl;
        }
        sum += full_num_int;
        // cout << "Adding number: " << full_num_int << endl;
    }
    return sum;
}

// inclusive [start, end]
long calculateInvalidSumA(string start, string end) {
    int n_half = start.length() / 2;
    int half_start;

    if (start.length() % 2 == 1) {
        half_start = stoi("1" + string(n_half, '0')); // ceil even number of digits
    } else {
        half_start = stoi(start.substr (0, n_half));
        if (stoi(start.substr (n_half, n_half)) > half_start) {
            half_start = half_start + 1;
        }
    }

    n_half = end.length() / 2;
    int half_end;
    if (end.length() % 2 == 1) {
        half_end = stoi(string(n_half, '9')); // todo for floor even number of digits
    } else {
        half_end = stoi(end.substr (0, n_half));
        if (stoi(end.substr (n_half, n_half)) < half_end) {
            half_end = half_end - 1;
        }
    }
    long sum = 0;
    for (int i = half_start; i <= half_end; i++) {
        string first_half = to_string(i);
        string second_half = first_half;
        string full_number = first_half + second_half;
        long full_num_int = stol(full_number);
        if (full_num_int < stol(start) && full_num_int > stol(end)) {
            cout << "Error in bounds calculation! Number:" << full_num_int << endl;
        }
        sum += full_num_int;
        // cout << "Adding number: " << full_num_int << endl;
    }
    return sum;
}

int main(int argc, char** argv) {
    ifstream infile("inputs/day2.txt");
    string instring;
    string line;
    while (getline(infile, line)) {
        instring += line;
    }
    
    vector<array<string,2>> ranges = {};

    while (!instring.empty()) {
        int dash_pos = instring.find('-');
        int comma_pos = instring.find(',');

        string first_num = instring.substr(0, dash_pos);
        string second_num = (comma_pos == string::npos)
            ? instring.substr(dash_pos + 1)
            : instring.substr(dash_pos + 1, comma_pos - dash_pos - 1);

        ranges.push_back(std::array<string,2>{ { first_num, second_num } });

        if (comma_pos == string::npos) break;
        instring = instring.substr(comma_pos + 1);
    }


    long invalid_sum = 0;
    for (const auto& range : ranges) {
        // invalid_sum += calculateInvalidSumA(range[0], range[1]); //Part A
        invalid_sum += calculateInvalidSumB(range[0], range[1]); //Part B
    }
    
    cout << "Part B: " << invalid_sum << endl;
    return 1;
}