#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> adjacencyList;

public:
    void tambahJalur(string from, string to, int jarak);
    void tampilkanGraf();
    void jalurTercepat(string from, string to);
};

#endif
