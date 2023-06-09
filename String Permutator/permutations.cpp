#include <iostream>

using namespace std;

// reorders functions. Parameters = input, left index
void reorder(string in, int index) {

    // base case when the length of input is the current index
    if (in.length() == index) {
        cout << in << endl;
    } else {
        int counter = index;

        while (counter < in.length()) {
            swap(in[index], in[counter]);
            reorder(in, index + 1);
            counter++;
        }
    }
}

// calls reorder function
void permutations(std::string in) { reorder(in, 0); }