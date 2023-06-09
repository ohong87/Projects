#include "company.cpp"
#include <iostream>

using namespace std;

int main() {
    CompanyTracker a(5);

    // testing merge out of bounds
    a.merge(0, -1);
    if (a.inSameCompany(0, -1)) {
        cout << "Merged company 0 and company -1" << endl;
    } else {
        cout << "Failed to merge company 0 and company -1" << endl;
    }

    // testing merge out of bounds
    a.merge(0, 5);
    if (a.inSameCompany(0, 5)) {
        cout << "Merged company 0 and company 5" << endl;
    } else {
        cout << "Failed to merge company 0 and company 5" << endl;
    }

    // testing merge of 0 and 1
    a.merge(0, 1);
    if (a.inSameCompany(0, 1)) {
        cout << "Merged company 0 and company 1" << endl;
    } else {
        cout << "Failed to merge company 0 and company 1" << endl;
    }

    // testing merge of 0 and 2
    a.merge(0, 2);
    if (a.inSameCompany(1, 2)) {
        cout << "Merged company {0,1} and company 2" << endl;
    } else {
        cout << "Failed to merge company {0,1} and company {2}" << endl;
    }

    // testing split out of bounds
    a.split(-1);  // should print "out of bounds"

    // testing split out of bounds
    a.split(11);  // should print "out of bounds"

    // testing split on 1 person company
    a.split(4);  // should print "1 person company

    // tests split on {{0, 1}, {2}}
    a.split(1);
    if (a.inSameCompany(1, 2)) {
        cout << "Failed to split {{0, 1}, {2}}" << endl;
    } else {
        cout << "Split {{0, 1}, {2}}" << endl;
    }

    // tests inSameCompany bounds
    if (a.inSameCompany(-1, 2)) {
        cout << "Out of bounds test FAILED" << endl;
    } else {
        cout << "Out of bounds test WORKED" << endl;
    }

    return 0;
}