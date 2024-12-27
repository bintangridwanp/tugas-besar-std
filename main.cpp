#include "graph.h"

int main() {
    // Tambahkan jalur antarstadion
    tambahJalur("Old Trafford", "Etihad Stadium", 7);

    tambahJalur("Etihad Stadium", "Anfield", 20);

    tambahJalur("Anfield", "Goodison Park", 30);

    tambahJalur("Goodison Park", "Molineux Stadium", 40);
    tambahJalur("Goodison Park", "St James' Park", 70);

    tambahJalur("Molineux Stadium", "Villa Park", 50);

    tambahJalur("St James' Park", "City Ground", 80);

    tambahJalur("Villa Park", "King Power Stadium", 60);
    tambahJalur("City Ground", "King Power Stadium", 90);

    tambahJalur("King Power Stadium", "London Stadium", 100);

    tambahJalur("London Stadium", "Emirates Stadium", 110);

    tambahJalur("Emirates Stadium", "Stamford Bridge", 120);

    tambahJalur("Stamford Bridge", "Tottenham Hotspurs Stadium", 130);

    tambahJalur("Tottenham Hotspurs Stadium", "Gtech Community Stadium", 140);

    tambahJalur("Gtech Community Stadium", "Sellhurst Park", 150);

    tambahJalur("Sellhurst Park", "Portman Road", 160);

    tambahJalur("Portman Road", "Vitality Stadium", 160);

    tambahJalur("Vitality Stadium", "Stadium St Mary's", 170);

    tambahJalur("Stadium St Mary's", "Stadium Falmer", 180);

    tambahJalur("Stadium Falmer", "Bramall Lane", 190);

    tambahJalur("Bramall Lane", "Old Trafford", 200);

    // ... tambahkan jalur lainnya ...

    cout << "Graf stadion:\n";
    tampilkanGraf();

    cout << "\nJalur tercepat:\n";
    jalurTercepat("Old Trafford", "Anfield");

    // Bersihkan memory sebelum program selesai
    cleanupGraf();

    return 0;
}
