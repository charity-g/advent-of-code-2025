
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <set>
using namespace std;

std::string repeat_substring(const std::string& sub, int n) {
    std::string result = "";
    for (int i = 0; i < n; ++i) {
        result += sub;
    }
    return result;
}

// inclusive [start, end]
long calculateInvalidSumB(string start, string end) {
    int n = start.length();
    long starti = stol(start);
    long endi = stol(end);

    int max_digits = end.length() % 2 == 0 ? end.length() / 2 : (end.length() / 2) + 1;

    long sum = 0;
    set<string> seen;
    for (long i = 1; i <= max_digits; i++) {
        // continue if digits dont divide into
        if (n % i != 0) {
            continue;
        }
        int substr_start;
        if (//(curr i = curr digit loop) > half of start digits 
            i > (start.length() / 2)
            ) {
            substr_start = stoi("1" + string(i - 1, '0'));
        } else {
            substr_start = stoi(start.substr (0, i));
            if (stol(repeat_substring(to_string(substr_start), n / i)) < starti) {
                substr_start = substr_start + 1;
            }
        }

        int substr_end; 
        if (
            //end digits > i digits
            max_digits > i
            ) {
            substr_end = stoi(string(i, '9'));
        } else {
            substr_end = stoi(end.substr (0, i));
            if (stol(repeat_substring(to_string(substr_end), n / i)) > endi) {
                substr_end = substr_end - 1;
            }
        }

        cout << "Checking substrings of length " << i << " from " << substr_start << " to " << substr_end << endl;
        for (int j = substr_start; j <= substr_end; j++) {
            string sub_str = to_string(j);
            string full_number = repeat_substring(sub_str, n / i);
            if (seen.find(full_number) != seen.end()) {
                continue;
            }
            seen.insert(full_number);
            long full_num_int = stol(full_number);
            if (full_num_int >= starti && full_num_int <= endi) {
                sum += full_num_int;
                cout << "Adding number: " << full_num_int << endl;   
            }
        }
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
        cout << "Adding number: " << full_num_int << endl;
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
    return 0;
}