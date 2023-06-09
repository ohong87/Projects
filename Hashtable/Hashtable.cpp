#include "Hashtable.h"
#include <iostream>
#include <string>

using namespace std;

std::string generateRandomKey() {
    std::string key = "";
    for(int i = 0; i < 12; i++) {
        //Generate a random lowercase letter
        key += 'a' + rand() % 26;
    }
    return key;
}

int main(){
    srand(time(NULL));

    //Birthday paradox
    int bDayCount[1000];

    for(int i = 0; i < 1000; i++){ 
        Hashtable<int> test (true, 365);
        
        bool hasProbe = false;
        int counter = 0;
        
        while(!hasProbe){
            if(test.add(generateRandomKey(), i) > 0) hasProbe = true;
            counter++;
        }
        bDayCount[i] = counter;
    }

    int bDayUpperCounter = 0;
    for(int i = 0; i < 1000; i++){
        if(bDayCount[i] <= 23) bDayUpperCounter++;
    }
    cout << "Birthday Paradox (23 or less): " << (bDayUpperCounter/1000.0) * 100.0 << "%" << endl;

    //Probe Rate
    int probeCount = 0; 
    int n = 100;
    Hashtable<int> test (true, 11);

    for(int i = 0; i < n; i++){
        probeCount += test.add(generateRandomKey(), i);
    }
    cout << "Expected Probe: " << 2.0*n/3 << " Actual: " << 2.0*probeCount/3 << endl;

    return 0;
}