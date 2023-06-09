#include "MinHeap.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>

using namespace std;

//finds word that differs by 1 letter and adds it to graph
void findWord(map<string, vector<string>>& a, string word, vector<string> wordList, map<string, bool> test){
    char alpha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};

    for(int i = 0; i < word.size(); i++){
        for(int j = 0; j < 26; j++){
            string temp = word;
            temp[i] = alpha[j]; 
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

            if(temp != word && test[temp] == true){ 
                //add the edge to the tree
                a[word].push_back(temp);
            }
        }
    }
}

//returns the number of different letters between 2 strings
int getH(string a, string b){
    int counter = 0;

    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            counter++;
        }
    }
    return counter;
}

//A* search
void findPath(map<string, vector<string>> graph, string start, string end, int& exp, int& step){ 
    map<string, int> g; //distance from start

    MinHeap<string> heap(2);

    int h = getH(start, end);

    g.emplace(start, 0);

    //adds start node to heap
    heap.add(start, (h + g[start]) * (start.size() + 1) + h);

    while(!heap.isEmpty()){
        string v = heap.peek();
        
        if(v == end){
            break;
        }
        if(heap.getPriority() != (g[v] +  getH(v, end)) * (start.size() + 1) + getH(v, end)){
            heap.remove();
            continue;
        }
        heap.remove();

        exp++;

        for(int i = 0; i < graph[v].size(); i++){
            vector<string> temp = graph[v];

            if(g.find(temp[i]) == g.end() || g[v] + 1 < g[temp[i]]){
                g[temp[i]] = g[v] + 1;
                heap.add(temp[i], (g[temp[i]] + getH(temp[i], end)) * (start.size() + 1) + getH(temp[i], end));
            }
        }
    }
    
    if(getH(start, end) != 0 && g[end] == 0){
        step = -1;
    }
    else{
        step = g[end];
    }
}

int main(int argc, char** argv){
    //edge cases
    if(argc != 4){
        cout << "Invalid parameters" << endl;
        return 1;
    }
    
    string start = argv[1];
    string end = argv[2];

    transform(start.begin(), start.end(), start.begin(), ::toupper);
    transform(end.begin(), end.end(), end.begin(), ::toupper);


    string filename = argv[3];
    ifstream infile(filename);

    if(!infile){
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }

    int wordCount;
    vector<string> words;
    map<string, bool> test;
    infile >> wordCount;

    //reads in words and puts them in vector
    for(unsigned int i = 0; i < wordCount; i++){
        string temp;
        infile >> temp;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper); //capitalizes words
        words.push_back(temp);
        test[temp] = true;
    }
    
    map<string, vector<string>> graph;
    int expansion = 0;
    int step = 0;

    //creates graph without edges
    for(unsigned int i = 0; i < wordCount; i++){
        vector<string> temp;
        graph[words[i]] = temp;
    }

    //adds edges to graph
    for(unsigned int i = 0; i < wordCount; i++){
        findWord(graph, words[i], words, test);
    }

    findPath(graph, start, end, expansion, step);

    if(step == -1){
        cout << "No transformation" << endl << expansion << endl;
    }
    else{
        cout << step << endl << expansion << endl;
    }

    return 0;
}