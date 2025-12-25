#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


// 234234234234278
// 23
// 2 4          
//              78

// 818181911112111
// 81
// 8 8
// 8   

int ctoi(char c) {
    return c - '0';
}

int getLargestVoltage(string bank) {
    int n = bank.length();
    int first, second, curr_digit = 0;

    for (int i = 0; i < n-1; i++) {
        curr_digit = ctoi(bank[i]);
        if (curr_digit > first) {
            first = curr_digit;
            second = 0; // reset second
        } else if (curr_digit > second) {
            second = curr_digit;
        }
    }
    // check last n-1th digit 
    curr_digit = ctoi(bank[n-1]);
    if (curr_digit > second) {
        second = curr_digit;
    }

    cout << "First: " << first << " Second: " << second << endl;
    return (first * 10) + second;
}

int partA(vector<string> banks) {
    int total_output_voltage = 0;
    for (auto bank : banks) {
        int a = getLargestVoltage(bank);
        cout << "Largest voltage for bank " << bank << " is " << a << endl;
        total_output_voltage += a;
    }
    cout << "Part A: Total output voltage: " << total_output_voltage << endl;
    return total_output_voltage;

}


int main(int argc, char** argv) {
    ifstream infile("inputs/day3.txt");
    vector<string> banks;
    string bank;
    while (getline(infile, bank)) {
        banks.push_back(bank);
    }
    

    partA(banks);
    return 0;
}
