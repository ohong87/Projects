#include "company.hpp"

#include <iostream>

using namespace std;

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];

    for (int i = 0; i < numCompanies; i++) {
        companies[i] = new Company();
    }
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    for (int i = 0; i < numCompanies; i++) {
        while (bigger(i)->merge1 != NULL) {
            split(i);
        }
        delete companies[i];
    }
    delete[] companies;
}

void CompanyTracker::merge(int i, int j) {
    // edge cases
    if ((i < 0 || j < 0) || (i > (numCompanies - 1) || j > (numCompanies - 1))) {
        // out of bounds
        return;
    } else if (bigger(i) == bigger(j)) {
        // if they are in the same company
        return;
    } else {
        Company* c = new Company(bigger(i), bigger(j));  // creates new merged company
        bigger(i)->parent = c;                           // updates parent for i
        bigger(j)->parent = c;                           // updates parent for j
    }
}

void CompanyTracker::split(int i) {
    // edge cases
    if (i < 0 || i > numCompanies - 1) {
        cout << "out of bounds" << endl;
        return;
    } else if (bigger(i) == companies[i]) {
        cout << "1 person company" << endl;
        return;
    } else {
        // updates subcompany parent pointers
        Company* temp = bigger(i);

        temp->merge1->parent = NULL;
        temp->merge2->parent = NULL;

        delete temp;
    }
}

bool CompanyTracker::inSameCompany(int i, int j) {
    // edge
    if ((i < 0 || j < 0) || (i > (numCompanies - 1) || j > (numCompanies - 1))) {
        // out of bounds
        return false;
    } else if (bigger(i) == bigger(j)) {
        return true;
    } else {
        return false;
    }
}

// returns biggest subcompany
Company* CompanyTracker::bigger(int a) {
    int counter = 0;
    Company* temp = companies[a];  // creates temp company

    while ((*temp).parent != NULL) {  // while the company above temp isn't the biggest
        temp = temp->parent;
        counter++;
    }
    return temp;  // return biggest subcompany
}
