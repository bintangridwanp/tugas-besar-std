#include "graph.h"

int main() {
    // Tambahkan jalur antarstadion
    tambahJalur("Old Trafford", "Etihad Stadium", 7);
    tambahJalur("Etihad Stadium", "Anfield", 50);
    tambahJalur("Anfield", "Goodison Park", 1);
    tambahJalur("Goodison Park", "St James' Park", 1);
    tambahJalur("Goodison Park", "Molineux Stadium", 1);
    tambahJalur("Molineux Stadium", "Villa Park", 1);
    tambahJalur("Villa Park", "King Power Stadium", 1);
    tambahJalur("St James' Park", "St James' Park", 1);
    // ... tambahkan jalur lainnya ...

    cout << "Graf stadion:\n";
    tampilkanGraf();

    cout << "\nJalur tercepat:\n";
    jalurTercepat("Old Trafford", "Anfield");

    // Bersihkan memory sebelum program selesai
    cleanupGraf();

    return 0;
}
