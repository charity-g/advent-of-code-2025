#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

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
            if (index >=  size) {
                return;
            } 

            // continue with function
            int parent_index = floor((index - 1) / 2);
            if (index && heap[parent_index] > heap[index]) {
                swap(heap[parent_index], heap[index]);
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
                    swap(heap[index], heap[lc_index]);
                    heapifyDown(lc_index);
                }
                return;
            }

            int rc = heap[rc_index];
            if (heap[index] > lc || heap[index] > rc) {
               if (lc < rc) {
                   swap(heap[index], heap[lc_index]);
                   heapifyDown(lc_index);
               } else {
                   swap(heap[index], heap[rc_index]);
                   heapifyDown(rc_index);
               }
             }

        }
    
    public:          
        MinIntHeap() {  
            size = 0;
        }

        void insert(int val) {
            if (size == heap.capacity()) {
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
int getLargestVoltageB(string bank) {
    int n = bank.length();
    MinIntHeap pq;

    // starting from last twelve characters, add to pq, calculate res
    int res = stoi(bank.substr(n-12, 12));
    for (int i = n - 12; i < n; i++) {
        pq.insert(ctoi(bank[i]));
    }

    // start for loop
    for (int i = n - 13; i >= 0; i--) {
        pq.insert(ctoi(bank[i]));
    }
    return res;
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


int partB(vector<string> banks) {
    int total_output_voltage = 0;
    for (auto bank : banks) {
        int a = getLargestVoltageB(bank);
        cout << "Largest voltage for bank " << bank << " is " << a << endl;
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
    

    partA(banks);
    return 0;
}
