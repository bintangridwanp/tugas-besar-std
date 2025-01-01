#include "graph.h"

// Inisialisasi variabel global
Vertex* first = nullptr;

Vertex* createNewVertex(string stadion) {
    Vertex* newVertex = new Vertex;
    newVertex->namaStadion = stadion;
    newVertex->firstEdge = nullptr;
    newVertex->next = nullptr;
    return newVertex;
}

Edge* createNewEdge(string dest, int jarak) {
    Edge* newEdge = new Edge;
    newEdge->destStadion = dest;
    newEdge->jarak = jarak;
    newEdge->next = nullptr;
    return newEdge;
}

Vertex* findVertex(string stadion) {
    Vertex* current = first;
    while (current != nullptr && current->namaStadion != stadion) {
        current = current->next;
    }
    return current;
}

void insertVertex(string stadion) {
    if (findVertex(stadion) == nullptr) {
        Vertex* newVertex = createNewVertex(stadion);

        if (first == nullptr) {
            first = newVertex;
        } else {
            newVertex->next = first;
            first = newVertex;
        }
    }
}

void tambahJalur(string from, string to, int jarak) {
    insertVertex(from);
    insertVertex(to);

    //insert first
    Vertex* fromVertex = findVertex(from);
    Edge* newEdge = createNewEdge(to, jarak);
    if (fromVertex->firstEdge == nullptr) {
        fromVertex->firstEdge = newEdge;
    } else {
        newEdge->next = fromVertex->firstEdge;
        fromVertex->firstEdge = newEdge;
    }

    Vertex* toVertex = findVertex(to);
    Edge* newEdgeReverse = createNewEdge(from, jarak);
    if (toVertex->firstEdge == nullptr) {
        toVertex->firstEdge = newEdgeReverse;
    } else {
        newEdgeReverse->next = toVertex->firstEdge;
        toVertex->firstEdge = newEdgeReverse;
    }
}

void tampilkanGraf() {
    Vertex* currentVertex = first;
    while (currentVertex != nullptr) {
        cout << "Stadion: " << currentVertex->namaStadion << "\n";
        Edge* currentEdge = currentVertex->firstEdge;
        while (currentEdge != nullptr) {
            cout << "  -> " << currentEdge->destStadion
                 << " (" << currentEdge->jarak << " km)\n";
            currentEdge = currentEdge->next;
        }
        currentVertex = currentVertex->next;
    }
}

void jalurTercepat(string from, string to) {
    // Hitung jumlah vertex
    int jumlahVertex = 0;
    Vertex* temp = first;
    while (temp != nullptr) {
        jumlahVertex++;
        temp = temp->next;
    }

    // Struktur untuk menyimpan informasi jalur
    struct JalurInfo {
        string prevStadion;
        int jarak;
        bool visited;
    };

    // Alokasi array untuk jalur info dan daftar stadion
    JalurInfo* jalurInfo = new JalurInfo[jumlahVertex];
    string* stadionList = new string[jumlahVertex];

    // Inisialisasi array
    temp = first;
    for (int i = 0; i < jumlahVertex; i++) {
        stadionList[i] = temp->namaStadion;
        jalurInfo[i].jarak = INT_MAX;
        jalurInfo[i].prevStadion = "";
        jalurInfo[i].visited = false;
        temp = temp->next;
    }

    // Set jarak awal
    for (int i = 0; i < jumlahVertex; i++) {
        if (stadionList[i] == from) {
            jalurInfo[i].jarak = 0;
            break;
        }
    }

    // Algoritma Dijkstra
    for (int count = 0; count < jumlahVertex - 1; count++) {
        // Cari vertex dengan jarak minimum
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < jumlahVertex; i++) {
            if (!jalurInfo[i].visited && jalurInfo[i].jarak <= minDist) {
                minDist = jalurInfo[i].jarak;
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        // Tandai vertex sebagai visited
        jalurInfo[minIndex].visited = true;

        // Update jarak ke tetangga
        Vertex* currentVertex = findVertex(stadionList[minIndex]);
        Edge* currentEdge = currentVertex->firstEdge;

        while (currentEdge != nullptr) {
            int targetIndex = -1;
            for (int i = 0; i < jumlahVertex; i++) {
                if (stadionList[i] == currentEdge->destStadion) {
                    targetIndex = i;
                    break;
                }
            }

            if (!jalurInfo[targetIndex].visited &&
                jalurInfo[minIndex].jarak != INT_MAX &&
                jalurInfo[minIndex].jarak + currentEdge->jarak < jalurInfo[targetIndex].jarak) {
                jalurInfo[targetIndex].jarak = jalurInfo[minIndex].jarak + currentEdge->jarak;
                jalurInfo[targetIndex].prevStadion = stadionList[minIndex];
            }

            currentEdge = currentEdge->next;
        }
    }

    // Tampilkan hasil
    int targetIndex = -1;
    for (int i = 0; i < jumlahVertex; i++) {
        if (stadionList[i] == to) {
            targetIndex = i;
            break;
        }
    }

    if (jalurInfo[targetIndex].jarak == INT_MAX) {
        cout << "Tidak ada jalur dari " << from << " ke " << to << ".\n";
    } else {
        // Rekonstruksi jalur
        string currentStadion = to;
        string path = currentStadion;

        while (currentStadion != from) {
            for (int i = 0; i < jumlahVertex; i++) {
                if (stadionList[i] == currentStadion) {
                    currentStadion = jalurInfo[i].prevStadion;
                    path = currentStadion + " -> " + path;
                    break;
                }
            }
        }

        cout << "Jalur tercepat dari " << from << " ke " << to << ":\n";
        cout << path << "\n";
        cout << "Total jarak: " << jalurInfo[targetIndex].jarak << " km\n";
    }

    // Bersihkan memori
    delete[] jalurInfo;
    delete[] stadionList;
}

void stadionJarakTerpanjang() {
    string cariStadion;
    cout << "|Masukkan nama stadion: ";
    cin >> cariStadion;

    Vertex* currentVertex = findVertex(cariStadion);
    while (currentVertex == nullptr) {
        cout << "Stadion tidak ada, silakan masukkan nama stadion yang valid: ";
        cin >> cariStadion;
        currentVertex = findVertex(cariStadion);
    }

    string stadionTerpanjang = "";
    int jarakTerpanjang = 0;

    cout << "\nMencari jalur terpanjang dari stadion " << cariStadion << "...\n";

    Edge* currentEdge = currentVertex->firstEdge;
    while (currentEdge != nullptr) {
        if (currentEdge->jarak > jarakTerpanjang) {
            jarakTerpanjang = currentEdge->jarak;
            stadionTerpanjang = cariStadion + " -> " + currentEdge->destStadion;
        }
        currentEdge = currentEdge->next;
    }

    if (stadionTerpanjang != "") {
        cout << "Jalur terpanjang dari " << cariStadion << " adalah: "
             << stadionTerpanjang << " dengan jarak " << jarakTerpanjang << " km.\n";
    } else {
        cout << "Stadion " << cariStadion << " tidak memiliki jalur keluar.\n";
    }
}

void jalurBerat(int threshold) {
    cout << "\nJalur dengan bobot lebih dari " << threshold << " km:\n";
    bool ditemukan = false;

    Vertex* currentVertex = first;
    while (currentVertex != nullptr) {
        Edge* currentEdge = currentVertex->firstEdge;

        while (currentEdge != nullptr) {
            if (currentEdge->jarak > threshold) {
                cout << currentVertex->namaStadion << " -> " << currentEdge->destStadion
                     << " (" << currentEdge->jarak << " km)\n";
                ditemukan = true;
            }
            currentEdge = currentEdge->next;
        }

        currentVertex = currentVertex->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada jalur dengan bobot lebih dari " << threshold << " km.\n";
    }
}

