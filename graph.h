// graph.h
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
using namespace std;

struct Edge {
    string destStadion;
    int jarak;
    Edge* next;
};

struct Vertex {
    string namaStadion;
    Edge* firstEdge;
    Vertex* next;
};

// Global variable untuk menyimpan head dari linked list
extern Vertex* first;

// Function declarations
Vertex* findVertex(string stadion);
Vertex* createNewVertex(string stadion);
Edge* createNewEdge(string dest, int jarak);
void insertVertex(string stadion);
void tambahJalur(string from, string to, int jarak);
void tampilkanGraf();
void jalurTercepat(string from, string to);
void stadionJarakTerpanjang();
void jalurBerat(int threshold);
void cleanupGraf();

#endif

