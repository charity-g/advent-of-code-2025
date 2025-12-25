#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <queue>

using namespace std;


// 234234234234278
// 23
// 2 4          
//              78

// 818181911112111
// 81
// 8 8
// 8   

// Source - https://stackoverflow.com/a/600306
// Posted by Greg Hewgill, modified by community. See post 'Timeline' for change history
// Retrieved 2025-12-24, License - CC BY-SA 4.0
// SIGNATURE: returns true if x is a power of two, or x == 0
bool IsPowerOfTwo(unsigned long x)
{
    return (x & (x - 1)) == 0;
}



class MinIntHeap {
    private:
        int size;
        vector<int> heap;     

        void heapifyUp(int index) {
            // check index exists
            if (index == 0 || index >=  size) {
                return;
            } 

            // continue with function
            int parent_index = (index - 1) / 2;
            // cout << "Heapify up called for index " << index << " with value " << heap[index] << " and parent index " << parent_index << " with value " << heap[parent_index] << endl;
            printHeap();
            if (heap[parent_index] > heap[index]) {
                int temp = heap[parent_index];
                heap[parent_index] = heap[index];
                heap[index] = temp;
                heapifyUp(parent_index);
            }
        }

        void heapifyDown(int index) {
            int lc_index = (2 * index) + 1;
            // check if left child exists
            if (lc_index >= size) {
                return;
            }
            int lc = heap[lc_index];
            

            int rc_index = (2 * index) + 2;
            // check if right child exists
            if (rc_index >= size) {
                // only left child exists
                if (heap[index] > lc) {
                    int temp = heap[index];
                    heap[index] = heap[lc_index];
                    heap[lc_index] = temp;
                    heapifyDown(lc_index);
                }
                return;
            }

            int rc = heap[rc_index];
            if (heap[index] > lc || heap[index] > rc) {
               if (lc < rc) {
                   int temp = heap[lc_index];
                   heap[lc_index] = heap[index];
                   heap[index] = temp;
                   heapifyDown(lc_index);
               } else {
                   int temp = heap[index];
                   heap[index] = heap[rc_index];
                   heap[rc_index] = temp;
                   heapifyDown(rc_index);
               }
             }

        }
    
    public:          
        MinIntHeap() {  
            size = 0;
        }
        void printHeap() {
            for (int i = 0; i < size; i++) {
                // cout << heap[i] << " ";
            }
            // cout << endl;
        }

        void insert(int val) {
            if (size == heap.size()) {
                heap.push_back(val);
            } else {
                heap[size] = val;
            }
            size++;
            heapifyUp(size - 1);
        }

        int remove() {
            int res = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapifyDown(0);
            return res;
        }

        int top() {
            return heap[0];
        }
};

int ctoi(char c) {
    return c - '0';
}

string removeFirstMatchingChar(string s, char c) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (s[i] == c) {
            s.erase(i, 1);
            return s;
        }
    }
    // cout << "Character " << c << " not found in string " << s << endl;
    return s;
}

string removeLastMatchingChar(string s, char c) {
    int n = s.length();
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == c) {
            s.erase(i, 1);
            return s;
        }
    }
    // cout << "Character " << c << " not found in string " << s << endl;
    return s;
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

    // cout << "First: " << first << " Second: " << second << endl;
    return (first * 10) + second;
}

// top twelve digits
long getLargestVoltageB(string bank) {
    int n = bank.length();
    std::priority_queue<int> pq;

    // starting from last twelve characters, add to pq, calculate res
    string res = bank.substr(n-12);
    for (int i = n - 12; i < n; i++) {
        pq.push(ctoi(bank[i]));
    }
    // cout << "Initial res: " << res << endl;
    
    // start for loop
    for (int i = n - 13; i >= 0; i--) {
        if (ctoi(bank[i]) >= ctoi(res[0])) {
            int removed_digit = pq.top();
            pq.pop();
            pq.push(ctoi(bank[i]));

            // cout << "Replacing " << removed_digit << " and adding this char in front: " << bank[i] << endl;

            res = removeFirstMatchingChar(res, to_string(removed_digit)[0]);
            res = bank[i] + res;
            // cout << "Updated res: " << res << endl;
        }
    }
    return stol(res);
}

int partA(vector<string> banks) {
    int total_output_voltage = 0;
    for (auto bank : banks) {
        int a = getLargestVoltage(bank);
        // cout << "Largest voltage for bank " << bank << " is " << a << endl;
        total_output_voltage += a;
    }
    // cout << "Part A: Total output voltage: " << total_output_voltage << endl;
    return total_output_voltage;

}


long partB(vector<string> banks) {
    long total_output_voltage = 0;
    for (auto bank : banks) {
        long a = getLargestVoltageB(bank);
        // cout << "Largest voltage for bank " << bank << " is " << a << endl;
        total_output_voltage += a;
    }
    cout << "Part B: Total output voltage: " << total_output_voltage << endl;
    return total_output_voltage;

}


int main(int argc, char** argv) {
    ifstream infile("inputs/day3.txt");
    vector<string> banks;
    string bank;
    while (getline(infile, bank)) {
        banks.push_back(bank);
    }
    

    partB(banks);
    return 0;
}
