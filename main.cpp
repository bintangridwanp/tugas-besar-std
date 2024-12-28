#include "graph.h"

int main() {
    // Tambahkan jalur antarstadion
    tambahJalur("Old_Trafford", "Etihad_Stadium", 10);
    tambahJalur("Etihad_Stadium", "Anfield", 20);
    tambahJalur("Anfield", "Goodison_Park", 30);
    tambahJalur("Goodison_Park", "Molineux_Stadium", 40);
    tambahJalur("Goodison_Park", "St_James_Park", 70);
    tambahJalur("Molineux_Stadium", "Villa_Park", 50);
    tambahJalur("St_James_Park", "City_Ground", 80);
    tambahJalur("Villa_Park", "King_Power_Stadium", 60);
    tambahJalur("City_Ground", "King_Power_Stadium", 90);
    tambahJalur("King_Power_Stadium", "London_Stadium", 100);
    tambahJalur("London_Stadium", "Emirates_Stadium", 110);
    tambahJalur("Emirates_Stadium", "Stamford_Bridge", 120);
    tambahJalur("Stamford_Bridge", "Tottenham_Hotspurs_Stadium", 130);
    tambahJalur("Tottenham_Hotspurs_Stadium", "Gtech_Community_Stadium", 140);
    tambahJalur("Gtech_Community_Stadium", "Sellhurst_Park", 150);
    tambahJalur("Sellhurst_Park", "Portman_Road", 160);
    tambahJalur("Portman_Road", "Vitality_Stadium", 160);
    tambahJalur("Vitality_Stadium", "Stadium_St_Marys", 170);
    tambahJalur("Stadium_St_Marys", "Stadium_Falmer", 180);
    tambahJalur("Stadium_Falmer", "Bramall_Lane", 190);
    tambahJalur("Bramall_Lane", "Old_Trafford", 200);

    // Untuk tes
    tambahJalur("Bandung", "Solo", 220);

    int pilihan;
    string stadion1, stadion2;
    int jarak, threshold;

    do {
        cout<< "\n";
        cout << "|==================== Menu Utama ====================|\n";
        cout << "|1. Tambah jalur antarstadion                        |\n";
        cout << "|2. Tampilkan graf stadion                           |\n";
        cout << "|3. Cari jalur tercepat                              |\n";
        cout << "|4. Cari stadion dengan jalur terpanjang             |\n";
        cout << "|5. Cari jalur dengan bobot lebih dari Batas (km)    |\n";
        cout << "|6. Keluar                                           |\n";
        cout << "|----------------------------------------------------|\n";
        cout << "|Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            // Menambahkan jalur antarstadion
            cout << "Masukkan nama stadion asal: ";
            cin >> stadion1;
            cout << "Masukkan nama stadion tujuan: ";
            cin >> stadion2;
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            tambahJalur(stadion1, stadion2, jarak);
        } else if (pilihan == 2) {
            // Menampilkan graf stadion
            cout << "Graf stadion:\n";
            tampilkanGraf();
        } else if (pilihan == 3) {
            // Mencari jalur tercepat antara dua stadion
            cout << "Masukkan nama stadion asal: ";
            cin >> stadion1;
            cout << "Masukkan nama stadion tujuan: ";
            cin >> stadion2;
            jalurTercepat(stadion1, stadion2);
        } else if (pilihan == 4) {
            // Mencari stadion dengan jalur terpanjang
            stadionJarakTerpanjang();
        } else if (pilihan == 5) {
            // Mencari jalur dengan bobot lebih dari threshold
            cout << "Masukkan Batas jarak (km): ";
            cin >> threshold;
            jalurBerat(threshold);
        } else if (pilihan == 6) {
            // Membersihkan memori graf dan keluar dari program
            cleanupGraf();
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}
