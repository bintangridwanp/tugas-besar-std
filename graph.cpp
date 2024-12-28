// graph.cpp
#include "graph.h"

// Inisialisasi variabel global
Vertex* first = nullptr;

// Membuat vertex baru
Vertex* createNewVertex(string stadion) {
    Vertex* newVertex = new Vertex;
    newVertex->namaStadion = stadion;
    newVertex->firstEdge = nullptr;
    newVertex->next = nullptr;
    return newVertex;
}

// Membuat edge baru
Edge* createNewEdge(string dest, int jarak) {
    Edge* newEdge = new Edge;
    newEdge->destStadion = dest;
    newEdge->jarak = jarak;
    newEdge->next = nullptr;
    return newEdge;
}

// Mencari vertex berdasarkan nama stadion
Vertex* findVertex(string stadion) {
    Vertex* current = first;
    while (current != nullptr && current->namaStadion != stadion) {
        current = current->next;
    }
    return current;
}

// Menambahkan vertex baru ke dalam graf
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

// Menambahkan edge antara dua vertex
void tambahJalur(string from, string to, int jarak) {
    // Pastikan kedua vertex ada
    insertVertex(from);
    insertVertex(to);

    // Tambah edge dari from ke to
    Vertex* fromVertex = findVertex(from);
    Edge* newEdge = createNewEdge(to, jarak);
    if (fromVertex->firstEdge == nullptr) {
        fromVertex->firstEdge = newEdge;
    } else {
        newEdge->next = fromVertex->firstEdge;
        fromVertex->firstEdge = newEdge;
    }

    // Tambah edge dari to ke from (graf tidak berarah)
    Vertex* toVertex = findVertex(to);
    Edge* newEdgeReverse = createNewEdge(from, jarak);
    if (toVertex->firstEdge == nullptr) {
        toVertex->firstEdge = newEdgeReverse;
    } else {
        newEdgeReverse->next = toVertex->firstEdge;
        toVertex->firstEdge = newEdgeReverse;
    }
}

// Menampilkan graf
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

// Menemukan jalur tercepat menggunakan algoritma Dijkstra
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

// Menemukan stadion dengan jalur terpanjang
void stadionJarakTerpanjang() {
    Vertex* currentVertex = first;
    string stadionTerpanjang = "";
    int jarakTerpanjang = 0;

    cout << "\nMencari stadion dengan jalur terpanjang...\n";

    // Periksa setiap stadion
    while (currentVertex != nullptr) {
        Edge* currentEdge = currentVertex->firstEdge;

        while (currentEdge != nullptr) {
            if (currentEdge->jarak > jarakTerpanjang) {
                jarakTerpanjang = currentEdge->jarak;
                stadionTerpanjang = currentVertex->namaStadion + " -> " + currentEdge->destStadion;
            }
            currentEdge = currentEdge->next;
        }

        currentVertex = currentVertex->next;
    }

    if (stadionTerpanjang != "") {
        cout << "Jalur terpanjang adalah: " << stadionTerpanjang
             << " dengan jarak " << jarakTerpanjang << " km.\n";
    } else {
        cout << "Tidak ada jalur dalam graf.\n";
    }
}

// Menampilkan jalur dengan bobot lebih dari threshold
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

// Membersihkan memori graf
void cleanupGraf() {
    Vertex* currentVertex = first;
    while (currentVertex != nullptr) {
        Edge* currentEdge = currentVertex->firstEdge;
        while (currentEdge != nullptr) {
            Edge* tempEdge = currentEdge;
            currentEdge = currentEdge->next;
            delete tempEdge;
        }
        Vertex* tempVertex = currentVertex;
        currentVertex = currentVertex->next;
        delete tempVertex;
    }
    first = nullptr;
}
