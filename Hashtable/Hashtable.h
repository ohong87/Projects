#include <vector>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <math.h>

using namespace std;

template <class T>
class Hashtable{
    public:
        Hashtable(bool debug = false, unsigned int size = 11);
        ~Hashtable();

        int add(string k, const T& val);
        const T& lookup(string k);
        void reportAll(ostream &) const;

    private:
        void resize();
        int hash(string k) const;
        pair<string, T> **table;
        int rVal[5];
        int size;
        bool debug;
        int items;
};

template <typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size){
    if(debug){
        rVal[0] = 983132572;
        rVal[1] = 1468777056;
        rVal[2] = 552714139;
        rVal[3] = 984953261;
        rVal[4] = 261934300;
    }
    else{
        for(int i = 0; i < 5; i++){
            rVal[i] = rand() % size;
        }
    }
    this -> size = size;
    this -> debug = debug;
    items = 0;

    table = new pair<string, T> *[size]();
}

template <typename T>
Hashtable<T>::~Hashtable(){
    for(int i = 0; i < size; i++){
        if(table[i] != nullptr) delete table[i];
    }
    delete[] table;
}

template <typename T>
int Hashtable<T>::add(string k, const T& val){
    int index = hash(k);
    int probe = 0;
    bool hasCollision = true;

    if(table[index] == nullptr){ //no collision
        if((items + 1.0)/size > 0.5){
            resize();
            index = hash(k);
        }

        pair<string, T>* temp = new pair<string, T>(k, val);
        
        table[index] = temp;
        items++;
    }
    else if(table[index] -> first == k) return probe; //inserting same thing
    else{ //collision
        if((items + 1.0)/size > 0.5){
            resize();
            index = hash(k);
        }
        while(hasCollision){
            if(table[(long long)((long long) index + pow(probe+1.0, 2)) % size] == nullptr){
                index = (long long)((long long) index + pow(probe+1.0, 2)) % size;

                pair<string, T>* temp = new pair<string, T>(k, val);
                table[index] = temp;

                items++;
                hasCollision = false;
            }
            probe++;
        }
    } 
    return probe;   
}

template <typename T>
const T& Hashtable<T>::lookup(string k){
    int index = hash(k);

    if(table[index] != nullptr && table[index] -> first == k) return table[index] -> second;
    else if(table[index] != nullptr && table[index] -> first != k){
        int probe = 0;

        while(1){
            if(table[(long long)(index + pow(probe + 1, 2)) % size] -> first == k){
                return table[(long long)(index + pow(probe + 1, 2)) % size] -> second;
            }
            probe++;
        }
    }
    else return size;
}

template <typename T>
void Hashtable<T>::reportAll(ostream &outputStream) const{
    for(int i = 0; i < size; i++){
        if(table[i] != nullptr) cout << table[i] -> first << " " << table[i] -> second << endl;
    }
}

template <typename T>
void Hashtable<T>::resize(){
    int oldItem = items;
    int oldSize = size;

    if(size < 823117 && size >= 411527){
        size = 823117;
    }
    else if(size < 411527 && size >= 205759){
        size = 411527;
    }
    else if(size < 205759 && size >= 102877){
        size = 205759;
    }
    else if(size < 102877 && size >= 51437){
        size = 102877;
    }
    else if(size < 51437 && size >= 25717){
        size = 51437;
    }
    else if(size < 25717 && size >= 12853){
        size = 25717;
    }
    else if(size < 12853 && size >= 6421){
        size = 12853;
    }
    else if(size < 6421 && size >= 3203){
        size = 6421;
    }
    else if(size < 3203 && size >= 1597){
        size = 3203;
    }
    else if(size < 1597 && size >= 797){
        size = 1597;
    }
    else if(size < 797 && size >= 397){
        size = 797;
    }
    else if(size < 397 && size >= 197){
        size = 397;
    }
    else if(size < 197 && size >= 97){
        size = 197;
    }
    else if(size < 97 && size >= 47){
        size = 97;
    }
    else if(size < 47 && size >= 23){
        size = 47;
    }
    else if(size < 23 && size >= 11){
        size = 23;
    }

    pair<string, T>** temp = new pair<string, T> *[size]();
    pair<string, T>** oldCopy = new pair<string, T> *[oldSize]();

    //making new random values if debug is off
    if(!debug){
        for(int i = 0; i < 5; i++){
            rVal[i] = rand() % size;
        }
    }

    //deep copy
    for(int i = 0; i < oldSize; i++){
        if(table[i] != nullptr){
            oldCopy[i] = new pair<string, T> (table[i] -> first, table[i] -> second);
        }
    }

    //free up table
    for(int i = 0; i < oldSize; i++){
        if(table[i] != nullptr){
            delete table[i];
        }
    }
    delete[] table;

    table = temp; //table is now expanded with more indices

    //rehash from oldCopy to table
    for(int i = 0; i < oldSize; i++){
        if(oldCopy[i] != nullptr){
            int garbage = add(oldCopy[i] -> first, oldCopy[i] -> second);
        }
    }
    items = oldItem;
}

template <typename T>
int Hashtable<T>::hash(string k) const{
    long long wVal[5];
    
    for(int i = 5 - 1; i >= 0; i--){
        wVal[i] = 0;
    }

    if(k.size() <= 6){
        int emptyCount = 6 - k.size(); // # of empty slots

        //gets wValue
        for(int i = 0; i < 6 - emptyCount; i++){
            if(i == 0){
                wVal[4] += (long long) ((long long) k[k.size() - 1.0 - i] - 96.0);
            }
            else{
                wVal[4] += pow(27.0, i) * ((long long) ((long long) k[k.size() - 1.0 - i] - 96.0));
            }
        }
    }
    else{
        int counter = 4;
        string key = k; //last 6 letters of k

        while(key.size() != 0){
            if(key.size() <= 6){
                int emptyCount = 6 - key.size(); // # of empty slots

                for(int i = 0; i < 6 - emptyCount; i++){
                    if(i == 0){
                        wVal[counter] += (long long) ((long long) key[key.size() - 1.0 - i] - 96.0);
                    }
                    else{
                        wVal[counter] += pow(27.0, i) * ((long long) ((long long) key[key.size() - 1.0 - i] - 96.0));
                    }
                }
                key = ""; //terminates loop
            }
            else{
                string temp = key.substr(key.size() - 6, key.size()); //last 6 letters

                for(int i = 0; i < 6; i++){
                    if(i == 0){
                        wVal[counter] += (long long) ((long long) key[key.size() - 1.0 - i] - 96.0);
                    }
                    else{
                        wVal[counter] += pow(27, i) * ((long long) ((long long) key[key.size() - 1.0 - i] - 96.0));
                    }
                }
                key = key.substr(0, key.size() - 6); //key updates

            }
            counter--;
        }
    }

    return (((long long) ((long long) rVal[0] * wVal[0]) + 
        (long long) ((long long) rVal[1] * wVal[1]) + 
        (long long) ((long long) rVal[2] * wVal[2]) + 
        (long long) ((long long) rVal[3] * wVal[3]) + 
        (long long) ((long long)rVal[4] * wVal[4])) % size);
}