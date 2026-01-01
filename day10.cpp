#include <iostream>
#include <fstream>
#include <chrono>
#include <regex>
#include <vector>
#include <list>
#include <string>
#include <cstring>
using namespace std;

list<int> splitByComma(const string& str) {
    list<int> result;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, ',')) {
        result.push_back(stoi(token));
    }
    return result;
}

void printState(const list<int>& state) {
    cout << "Joltage state: ";
    for (const int j : state) {
        cout << j << " ";
    }
    cout << endl;
}

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
string pressButtonForIndicator(const string& state, const list<int>& indexes) {
    string new_state = state;
    for (const int i: indexes) {
        new_state[i] = (state[i] == '.') ? '#' : '.';
    }
    return new_state;
}

list<int> pressButtonForJoltage(const list<int> state, const list<int>& indexes) {
    list<int> new_state = {};
    int i = 0;
    list<int>::const_iterator it_state = state.begin();
    for (const int j : indexes) {
        while (i < j && it_state != state.end()) {
            new_state.push_back(*it_state);
            ++it_state;
            ++i;
        }
        if (it_state != state.end()) {
            new_state.push_back(*it_state - 1);
            ++it_state;
            ++i;
        }
    }
    while (it_state != state.end()) {
        new_state.push_back(*it_state);
        ++it_state;
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
        new_states.push_back({pressButtonForIndicator(state, indexes), presses + 1}); // take
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
    }
    // else {
    //     cout << "Reached indicator state: " << indicator << " in " << min_presses << " presses" << endl;
    // }
    return min_presses;
}

void partA(const vector<string>& machine_indicators, const vector<vector<list<int>>>& machine_buttons) {
    int presses = 0;
    for (int i = 0; i < machine_indicators.size(); ++i) {
        const string& indicator = machine_indicators[i];
        const vector<list<int>>& buttons = machine_buttons[i];
        int presses_for_machine = fewestButtonPressesToStart(indicator, buttons);
        presses += presses_for_machine;
    }
    
    cout << "Part A started all machines with "  << presses << " button presses" << endl;
}

pair<vector<string>, vector<vector<list<int>>>> parseInputA(ifstream& infile) {
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
    return {machine_indicators, machine_buttons};
}

pair<vector<list<int>>, vector<vector<list<int>>>> parseInputB(ifstream& infile) {
    string line;    
    vector<list<int>> joltage_requirements;
    vector<vector<list<int>>> machine_buttons;

    while (getline(infile, line)) {
        smatch joltage;
        regex_search(line, joltage, regex("\\{([\\d\\,]+)\\}"));
        joltage_requirements.push_back(splitByComma(joltage.str(1)));

        vector<list<int>> buttons;
        regex buttonPattern("\\(([\\d,]*\\d+)\\)");
        const vector<smatch> matches{
            sregex_iterator{cbegin(line), cend(line), buttonPattern},
            sregex_iterator{}
        };
        for (const auto& match : matches) {
            list<int> button_presses = splitByComma(match.str(1));
            buttons.push_back(button_presses);
        }
        machine_buttons.push_back(buttons);
    }
    
    return {joltage_requirements, machine_buttons};    
}

// returns 1 if all elements in joltage are zero
// returns 0 if all elements in joltage are >= 0
// returns -1 if any element in joltage is < 0
int isAllZeroes(const list<int>& joltage) {
    bool isAllZeroes = false;
    for (const int j : joltage) {
        if (j < 0) return -1;
    }
    return isAllZeroes;
}

int fewestButtonPressesToConfigureJoltage(const list<int>& joltage, const vector<list<int>>& buttons) {
    // For now, just return number of buttons as placeholder
    list<pair<list<int>, int>> states = {{joltage, 0}};
    while(!states.empty()) {
        list<int> state = states.front().first;
        int presses = states.front().second;
        states.pop_front();
        cout << presses << ": ";
        printState(state);

        // Check if state is all zeros
        int isAllZeroesStatus = isAllZeroes(state);
        if (isAllZeroesStatus == 1) {
            return presses;
        } else if (isAllZeroesStatus == -1) {
            continue; // invalid state, skip
        } else {// else add children states
            int new_presses = presses + 1;
            for (const auto& button : buttons) {
                list<int> new_state = pressButtonForJoltage(state, button);
                states.push_back({new_state, presses + 1});
            }
        }
    }

    return buttons.size();
}

void partB(const vector<list<int>>& joltage_requirements, const vector<vector<list<int>>>& machine_buttons) {
    int presses = 0;
    for (int i = 0; i < joltage_requirements.size(); ++i) {
        const list<int>& joltage = joltage_requirements[i];
        const vector<list<int>>& buttons = machine_buttons[i];
        presses += fewestButtonPressesToConfigureJoltage(joltage, buttons);
    }
    cout << "Part B got to final joltage with "  << presses << " button presses" << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day10.txt");
    
    auto beg = chrono::high_resolution_clock::now();
    
    // auto [machine_indicators, machine_buttons] = parseInputA(infile);
    // partA(machine_indicators, machine_buttons);
    auto [joltage_requirements, machine_buttons] = parseInputB(infile);
    partB(joltage_requirements, machine_buttons);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
    cout << "Time taken to run function: " << duration.count() << " microseconds" << endl;

    return 0;
}