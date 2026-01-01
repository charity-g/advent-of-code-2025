#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <unordered_map>
#include <regex>
using namespace std;

const string START_DEVICE_A = "you"; // for PART A
const string START_DEVICE_B = "svr"; // for PART B
const string END_DEVICE = "out";

vector<string> splitBySpaces(const string& str) {
    vector<string> result;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        result.push_back(token);
    }
    return result;
}

void printGraph(unordered_map<string, vector<string>>& graph) {
    for (const auto& [device, outputs] : graph) {
        cout << device << " -> ";
        for (const auto& out : outputs) {
            cout << out << " ";
        }
        cout << endl;
    }
}

void printPath(const set<string>& path) {
    cout << "Path: ";
    for (const auto& device : path) {
        cout << device << " ";
    }
    cout << endl;
}

void printValidPathExistsDp(const unordered_map<string, int>& validPathExists) {
    cout << "Valid Path Exists DP Table:" << endl;
    for (const auto& [device, count] : validPathExists) {
        cout << "  " << device << ": " << count << endl;
    }
}

void partA(unordered_map<string, vector<string>>& graph) {
    int paths = 0;
    list<pair<string, set<string>>> states = {{START_DEVICE_A, {}}};

    while (!states.empty()) {
        string device = states.back().first;
        set<string> path = states.back().second;
        states.pop_back();

        if (device == END_DEVICE) {
            paths++;
            continue;
        }

        path.insert(device);
        for (const auto& output_device : graph[device]) {
            if (path.find(output_device) == path.end()) {
                states.push_back({output_device, path});
            }
        }
    }

    cout << "Part A found " << paths << " paths from " << START_DEVICE_A << " to " << END_DEVICE << endl;
}

int pathsToEndDeviceThroughDacFft(unordered_map<string, vector<string>>& graph, unordered_map<string, int>& validPathExists, const string& device, const set<string>& path) {
    if (device == END_DEVICE) {
        // printPath(path);
        // printValidPathExistsDp(validPathExists);
        if (path.find("dac") != path.end() &&
            path.find("fft") != path.end()) {
            return 1;
        } else {
            return 0;
        };
    }

    // if (validPathExists.find(device) != validPathExists.end()) {
    //     return validPathExists[device];
    // }

    int total_paths = 0;
    set<string> new_path = path;
    new_path.insert(device);
    for (const auto& output_device : graph[device]) {
        if (new_path.find(output_device) == new_path.end()) {
            total_paths += pathsToEndDeviceThroughDacFft(graph, validPathExists, output_device, new_path);
        }
    }
    // if (total_paths > 0) {
    //     validPathExists[device] = total_paths;
    // }
    cout << "Device " << device << " has " << total_paths << " valid paths to " << END_DEVICE << endl;
    return total_paths;
}


void partB(unordered_map<string, vector<string>>& graph) {
    int paths = 0;
    list<pair<string, set<string>>> states = {{START_DEVICE_B, {}}};
    unordered_map<string, int> validPathExists;

    paths = pathsToEndDeviceThroughDacFft(graph, validPathExists, START_DEVICE_B, {});

    cout << "Part B found " << paths << " paths from " << START_DEVICE_B << " to " << END_DEVICE << endl;
}


int main(int argc, char** argv) {
    ifstream infile("inputs/day11.txt");
    string line;

    unordered_map<string, vector<string>> device_outputs;

    while (getline(infile, line)) {
        smatch device_IO;
        regex_search(line, device_IO, regex("(.*): (.*)"));
        string device = device_IO.str(1);
        string outputs_str = device_IO.str(2);
        vector<string> outputs = splitBySpaces(outputs_str);
        device_outputs[device] = outputs;
    }
    
    auto beg = chrono::high_resolution_clock::now();
    // printGraph(device_outputs);
    // partA(device_outputs); 
    partB(device_outputs);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
    cout << "Time taken to run function: " << duration.count() << " microseconds" << endl;

    return 0;
}