#include <iostream>
#include <fstream>
#include <chrono>
#include <regex>
#include <vector>
#include <list>
#include <string>
#include <cstring>
using namespace std;

void printMachineButtons(const vector<vector<list<int>>>& machine_buttons) {
    for (const auto& buttons : machine_buttons) {
        cout << "Machine Buttons:" << endl;
        for (const auto& button : buttons) {
            cout << "  Button presses: ";
            for (const auto& press : button) {
                cout << press << " ";
            }
            cout << endl;
        }
    }
}

// returns new state after pressing button, which toggles the indexes in the list
string pressButton(const string& state, const list<int>& indexes) {
    string new_state = state;
    for (const int i: indexes) {
        new_state[i] = (state[i] == '.') ? '#' : '.';
    }
    return new_state;
}

list<pair<string, int>> generateNextStates(const string indicator, const list<int>& indexes, list<pair<string, int>>& states, int* min_presses) {
    list<pair<string, int>> new_states;
    while (!states.empty()) {
        string state = states.back().first;
        int presses = states.back().second;
        states.pop_back();
        // check if state is same as indicator
        // cout << "[" << indicator <<"] "<<  "Current state: " << state << " after " << presses << " presses and deciding to press button ";
        // for (const int idx : indexes) {
        //     cout << idx << ", ";
        // }
        // cout << endl;
        if (state == indicator) *min_presses = min(*min_presses, presses);
        // else, add two options for new state to take or not take curr button press 
        new_states.push_back({state, presses}); // not take
        new_states.push_back({pressButton(state, indexes), presses + 1}); // take
    }
    return new_states;
}

int fewestButtonPressesToStart(const string& indicator, const vector<list<int>>& buttons) {
    list<pair<string, int>> states = {{string(indicator.size(), '.'), 0}};
    int min_presses = buttons.size() + 1;
    for (int i = 0; i < buttons.size(); i++) {
        list<pair<string, int>> new_states = generateNextStates(indicator, buttons[i], states, &min_presses);
        states = new_states;
    }
    generateNextStates(indicator, {}, states, &min_presses); // final check without pressing any button
    
    if (min_presses == buttons.size() + 1) {
        cout << "Could not reach indicator state: " << indicator << endl;
    } else {
        cout << "Reached indicator state: " << indicator << " in " << min_presses << " presses" << endl;
    }
    return min_presses;
}

void partA(const vector<string>& machine_indicators, const vector<vector<list<int>>>& machine_buttons) {
    int presses = 0;
    for (int i = 0; i < machine_indicators.size(); ++i) {
        const string& indicator = machine_indicators[i];
        const vector<list<int>>& buttons = machine_buttons[i];
        int presses_for_machine = fewestButtonPressesToStart(indicator, buttons);
        cout << "Machine " << i << " started with " << presses_for_machine << " presses" << endl;
        presses += presses_for_machine;
    }
    
    cout << "Part A started all machines with "  << presses << " button presses" << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day10.txt");
    string line;
    
    vector<string> machine_indicators;
    vector<vector<list<int>>> machine_buttons;

    while (getline(infile, line)) {
        smatch indicator;
        regex_search(line, indicator, regex("\\[([\\.#]+)\\]"));
        machine_indicators.push_back(indicator.str(1));

        vector<list<int>> buttons;
        regex buttonPattern("\\(([\\d,]*\\d+)\\)");
        const vector<smatch> matches{
            sregex_iterator{cbegin(line), cend(line), buttonPattern},
            sregex_iterator{}
        };
        for (const auto& match : matches) {
            list<int> button_presses;
            std::istringstream iss(match.str(1));
            std::string token;
            while (std::getline(iss, token, ',')) {
                button_presses.push_back(stoi(token));
            }
            buttons.push_back(button_presses);
        }
        machine_buttons.push_back(buttons);
    }

    auto beg = chrono::high_resolution_clock::now();
    partA(machine_indicators, machine_buttons);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
    cout << "Time taken to run function: " << duration.count() << " microseconds" << endl;

    return 0;
}