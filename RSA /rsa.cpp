#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h> 
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//counts # of digits
long getDigits(long num){
    long temp = num;
    int counter = 0;

    while(temp != 0){
        temp = temp/10;
        counter++;
    }
    return counter;
}

//original GCD function
long gcd(long a, long b){
    long x = a;
    long y = b;

    while(y != 0){
        int r  = x % y;
        x = y;
        y = r;
    }
    return x;
}

//extended euclidean algorithm
void extendedGCD(long p, long q, long L, long& gcd, long& d){
    int e = 65537;
    long s = 0;
    long old_s = 1;
    long t = 1;
    long old_t = 0;
    long r = e;
    long old_r = L;

    while(r != 0){
        long quotient = floor(old_r / r);
        long temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    gcd = old_r;

    if(old_t >= 0){
        d = old_t;
    }
    else{
        d = old_t + (p-1)*(q-1);
    }    
}

//converts numbers to binary
string toBinary(long num){
    string val;
    long temp = num;

    while(temp > 0){
        val += to_string(temp % 2);
        temp = temp / 2;
    }
    return val;
}

//performs modular exponentiation
long modExp(long b, string e, long m){
    long x = 1;
    long long power = b % m;

    for(int i = 0; i < e.size(); i++){
        if(e[i] == '1'){
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }
    return x;
}

//encryption
void encrypt(string fileName, long n, string message){
    ofstream myfile;
    myfile.open(fileName);

    int e = 65537;
    int x = 1+log10(n/27)/log10(100);

    int pos = 0;
    int counter = 0;

    string arr[27] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "20", "21", "22", "23", "24", "25", "26"};

    while(counter < ceil((message.size()*1.0)/x)){
        string M;
        for(int i = pos; i < x * (counter + 1); i++){
            if((int) (message[i]) == 32){
                M += arr[0];
            }
            else{
                M += arr[(int) (message[i]) - 96];
            }
        }
        if(M.size() != x * 2){
            int size = (x * 2 - M.size())/2;
            for(int i = 0; i < size; i++){
                M += arr[0];
            }
        }

        long C = modExp(stol(M), toBinary(e), n);
        
        myfile << C;
        myfile << " ";

        pos = x + pos;
        counter++;
    }
}

//gets decryption key
void getDecryptKey(long p, long q, long& d, long& gcdEL, bool& status){
    int L = ((p - 1) * (q - 1))/gcd(p - 1, q - 1);
    int e = 65537;

    if(L <= e){
        cout << "Numbers too small" << endl;
        status = false;
        return;
    }

    extendedGCD(p, q, L, gcdEL, d);

    if(gcdEL != 1){
        cout << "Poor choice of P & Q" << endl;
        status = false;
        return;
    }
}

void decrypt(string inputFile, string outputFile, long p, long q, bool& status){
    long d = 0;
    long gcdEL = 0;
    string arr[27] = {" ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
        "t", "u", "v", "w", "x", "y", "z"};
    string message;

    getDecryptKey(p, q, d, gcdEL, status);

    if(!status) return;

    long C = 0;
    ifstream file;
    file.open(inputFile); //will it always open?

    while(file >> C){
        string M;
        long mNum = modExp(C, toBinary(d), p * q);
        
        if(getDigits(mNum) % 2 == 1){
            M = "0";
            M += to_string(mNum);
        }
        else{
            M += to_string(mNum);
        }
        cout << M << " ";
        
        for(int i = 0; i < M.size(); i += 2){
            int temp = stoi(M.substr(i, 2));
            message += arr[temp];
        }
    }
    ofstream ofile;
    ofile.open(outputFile);
    ofile << message;
}

int main(int argc, char** argv){
    if(argc != 3){
        cout << "Invalid parameters" << endl;
        return 0;
    }

    long p = stol(argv[1]);
    long q = stol(argv[2]);
    bool status = true;

    if((p * (q-1)) * (p * (q-1)) > 9 * pow(10, 15)){
        cout << "P and Q too large" << endl;
        return 0;
    }

    cout << "Enter a command: ";

    string command;
    cin >> command;

    if(command.compare("EXIT") != 0 && command.compare("DECRYPT") != 0 && command.compare("ENCRYPT") != 0){
        cout << "Invalid command" << endl;
        return 0;
    }

    if(command.compare("DECRYPT") == 0){
        string input;
        string output;

        cin >> input;
        cin >> output;

        decrypt(input, output, p, q, status);
        if(!status) return 0;
    }
    else if(command.compare("ENCRYPT") == 0){
        string fileName;
        string message;
        int n;

        cin >> fileName;
        cin >> n;
        getline(cin >> std::ws, message);

        if(n < 27){
            cout << "Integer too small" << endl;
            return 0;
        }
        encrypt(fileName, n, message);
    }
    else if(command.compare("EXIT") == 0){
        return 0;
    }
    return 1;
}