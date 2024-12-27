#include "graph.h"

int main() {
    Graph graf;

    // Tambahkan jalur antarstadion
    graf.tambahJalur("Old Trafford", "Etihad Stadium", 7);
    graf.tambahJalur("Etihad Stadium", "Anfield", 50);
    graf.tambahJalur("Anfield", "Goodison Park", 1);
    graf.tambahJalur("Anfield", "Villa Park", 25);
    graf.tambahJalur("Goodison Park", "Villa Park", 100);
    graf.tambahJalur("Villa Park", "King Power Stadium", 45);
    graf.tambahJalur("King Power Stadium", "Stamford Bridge", 120);
    graf.tambahJalur("Stamford Bridge", "Craven Cottage", 2);
    graf.tambahJalur("Craven Cottage", "Emirates Stadium", 10);
    graf.tambahJalur("Emirates Stadium", "Tottenham Hotspur Stadium", 5);
    graf.tambahJalur("Tottenham Hotspur Stadium", "London Stadium", 9);
    graf.tambahJalur("London Stadium", "Selhurst Park", 15);
    graf.tambahJalur("Selhurst Park", "Amex Stadium", 40);
    graf.tambahJalur("Amex Stadium", "Vitality Stadium", 90);
    graf.tambahJalur("Vitality Stadium", "St Mary's Stadium", 30);
    graf.tambahJalur("St Mary's Stadium", "Brentford Community Stadium", 65);
    graf.tambahJalur("Brentford Community Stadium", "Molineux Stadium", 140);
    graf.tambahJalur("Molineux Stadium", "Turf Moor", 85);
    graf.tambahJalur("Turf Moor", "Bramall Lane", 70);
    graf.tambahJalur("Bramall Lane", "St James' Park", 120);

    // Tampilkan graf
    cout << "Graf stadion:\n";
    graf.tampilkanGraf();



    // Cari jalur terpendek
    cout << "\nJalur tercepat:\n";
    graf.jalurTercepat("Old Trafford", "Vitality Stadium");
    // Cari jalur alternatif
    cout << "\nJalur alternatif:\n";
    graf.jalurAlternatif("Old Trafford", "Vitality Stadium");

    return 0;
}
