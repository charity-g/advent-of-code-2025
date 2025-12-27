#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

bool itemInRanges(long item, const vector<list<long>>& ranges) {
    //binary search for item in ranges
    int l = 0; int r = ranges.size() - 1;

    while (l <= r) {
        int m = (r + l) / 2;
        // cout << "indexes (m/r/l)" << m  << " " << r << " " << l << ": " << item << " vs range " << ranges[m].front() << "-" << ranges[m].back() << endl;
        if (item >= ranges[m].front() && item <= ranges[m].back()) {
            return true;
        } else if (item < ranges[m].front()) {
            r = m - 1;
        } else if (item > ranges[m].back()) {
            l = m + 1;
        } else {
            cout << "[itemInRanges] Should not reach here!" << endl;
        }
    }
    return false;
}

// Sorts and merges overlapping ranges
vector<list<long>> sortMergeOverlappingRanges(vector<list<long>>& ranges) {
    // sort in place ranges by start value
    sort(ranges.begin(), ranges.end(), [](const list<long>& a, const list<long>& b) {
        return a.front() < b.front();
    });

    // go through ranges and merge overlaps
    vector<list<long>> merged_ranges;
    for (const auto& range : ranges) {
        if (merged_ranges.empty() || merged_ranges.back().back() < range.front()) {
            merged_ranges.push_back(range);
        } else { // merge!
            merged_ranges.back().back() = max(merged_ranges.back().back(), range.back());
        }
    }

    // cout << "Merged ranges:" << endl;
    // for (const auto& range : merged_ranges) {
    //     cout << range.front() << "-" << range.back() << endl;
    // }

    return merged_ranges;
}

void partA(vector<list<long>>& ranges, ifstream& infile) {
    
    vector<list<long>> merged_ranges = sortMergeOverlappingRanges(ranges);

    // continue with infile 
    int fresh_count = 0;
    string line;
    while (getline(infile, line)) {
        long item = stol(line);
        if (itemInRanges(item, merged_ranges)) {
            fresh_count++;
            // cout << "Item " << item << " is fresh." << endl;
        } else {
            continue;
            // cout << "Item " << item << " is not fresh." << endl;
        }
    }
    
    cout << "Part A found " << fresh_count << " fresh items." << endl;
}

void partB(vector<list<long>>& ranges) {
    vector<list<long>> merged_ranges = sortMergeOverlappingRanges(ranges);

    long possible_count = 0;
    for (auto it = merged_ranges.begin(); it != merged_ranges.end(); ++it) {
        long gap = it->back() - it->front() + 1;
        cout << "Range " << it->front() << "-" << it->back() << " has size " << gap << endl;
        possible_count += gap;
    }

    cout << "Part B found " << possible_count << " possible fresh items." << endl;
}

int main(int argc, char** argv) {
    ifstream infile("inputs/day5.txt");

    vector<list<long>> ranges;
    string line;
    while (getline(infile, line)) {
        if (line.empty() || line == "\n") {
            cout << "Reached end of ranges input." << endl;
            break;
        }
        int range_index = line.find('-');
        list<long> row = {stol(line.substr(0, range_index)), stol(line.substr(range_index + 1))};
        ranges.push_back(row);
    }

    // partA(ranges, infile);
    partB(ranges);
    return 0;
}
