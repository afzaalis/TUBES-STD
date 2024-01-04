#include <iostream>
#include "header.h"
using namespace std;

int main() {
    ListInduk L;
    ListAnak K;
    L.first = nullptr;
    L.last = nullptr;

    int choice = -1;
    while (choice != 0) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "===================================" << endl;
            cout << "Masukkan Data Freelancer" << endl;

            InfotypeFreelancer dataFreelancer;
            cout << "Nama: ";
            cin.ignore();
            getline(cin, dataFreelancer.nama);

            cout << "Keahlian: ";
            getline(cin, dataFreelancer.keahlian);

            cout << "Rating: ";
            cin >> dataFreelancer.rating;

            AdrInduk newFreelancer = createElementInd(dataFreelancer);
            if (L.first == nullptr) {
                L.first = newFreelancer;
                L.last = newFreelancer;
            } else {
                L.last->next = newFreelancer;
                L.last = newFreelancer;
            }
            cout << "Data Freelancer berhasil dimasukkan." << endl;
            cout << "===================================" << endl;

        } else if (choice == 2) {

            cout << "===================================" << endl;
            cout << "Masukkan Data Kontrak" << endl;

            InfotypeJob kontrak;
            cout << "Nama Klien: ";
            cin.ignore();
            getline(cin, kontrak.namaKlien);

            cout << "Deskripsi: ";
            getline(cin, kontrak.deskripsi);

            cout << "fee: ";
            cin >> kontrak.fee;
            /*
            AdrAnak newKontrak = createElementAnak(kontrak);
            if (L.first == nullptr) {
                L.first = kontrak;
            } else {
                L.first->next = kontrak;
            }
            */
            cout << "Data Kontrak berhasil dimasukkan." << endl;
            cout << "===================================" << endl;

        }else if (choice == 3) {
            cout << "===================================" << endl;
            cout << "Tampilkan Seluruh Data Freelancer" << endl;
            showAllParent(L);
            cout << "===================================" << endl;

        } else if (choice == 4) {
            cout << "===================================" << endl;
cout << "Menghubungkan Data Freelancer dengan Kontrak" << endl;

    string namaFreelancer, namaKlien;
    AdrInduk parent = nullptr;
    int N;
    cout << "Nama freelancer yang ingin dihubungkan dengan kontrak pekerjaan: ";
    cin.ignore();
    getline(cin, namaFreelancer);

    parent = findParent(L, namaFreelancer);

    if (parent != nullptr) {
        cout << "Berapa pekerjaan yang ingin dihubungkan: ";
        cin >> N;
        cin.ignore();

        for (int i = 0; i < N; i++) {
            cout << "Nama klien untuk kontrak " << i + 1 << ": ";
            getline(cin, namaKlien);

            InfotypeJob kontrak;
            cout << "Deskripsi pekerjaan untuk kontrak " << i + 1 << ": ";
            getline(cin, kontrak.deskripsi);
            cout << "Fee untuk kontrak " << i + 1 << ": ";
            cin >> kontrak.fee;
            cin.ignore();
            kontrak.namaKlien = namaKlien;

            addChild(parent, kontrak);
        }

        cout << "Data Kontrak berhasil dihubungkan dengan Freelancer " << parent->info.nama << endl;
    } else {
        cout << "Freelancer tidak ditemukan." << endl;
    }
    cout << "===================================" << endl;

        } else if (choice == 5) {
            cout << "===================================" << endl;
            cout << "Cari Data Freelancer" << endl;

            cout << "Masukkan nama Freelancer yang ingin dicari: ";
            string namaFreelancer;
            cin.ignore();
            getline(cin, namaFreelancer);

            AdrInduk freelancer = findParent(L, namaFreelancer);

        if (freelancer != nullptr) {
            cout << "Data Freelancer ditemukan:" << endl;
            cout << "Nama: " << freelancer->info.nama << endl;
            } else {
                cout << "Data Freelancer tidak ditemukan." << endl;
                }
                cout << "===================================" << endl;
        } else if (choice == 6) {
            // Mencari data Kontrak
           cout << "===================================" << endl;
           cout << "Cari Data Kontrak" << endl;

           cout << "Masukkan nama klien yang ingin dicari: ";
            string klien;
            cin.ignore();
        getline(cin, klien);

        showAllParent(L);
        string namaFreelancer;
        cout << "Masukkan Nama Freelancer: ";
        getline(cin, namaFreelancer);

        AdrInduk parent = findParent(L, namaFreelancer);

        if (parent != nullptr) {
            // Mencari data kontrak pada freelancer yang dipilih
            AdrAnak kontrak = findChild(parent, klien);

            if (kontrak != nullptr) {
            cout << "Data Kontrak ditemukan pada Freelancer " << parent->info.nama << ":" << endl;
            cout << "Nama Klien: " << kontrak->info.namaKlien << endl;

                } else {
                cout << "Data Kontrak tidak ditemukan pada Freelancer " << parent->info.nama << endl;
                }
                } else {
                cout << "Freelancer tidak ditemukan. Tidak dapat mencari data kontrak." << endl;
                    }
                    cout << "===================================" << endl;
        } else if (choice == 7) {
              cout << "===================================" << endl;
            cout << "Masukkan Data Pekerjaan" << endl;

            string namaFreelancer;
            cout << "Masukkan Nama Freelancer: ";
            cin.ignore();
            getline(cin, namaFreelancer);

            AdrInduk parent = findParent(L, namaFreelancer);

            if (parent != nullptr) {
                InfotypeJob dataJob;
                cout << "Nama Klien: ";
                getline(cin, dataJob.namaKlien);

                cout << "Deskripsi Job: ";
                getline(cin, dataJob.deskripsi);

                cout << "Fee: ";
                cin >> dataJob.fee;
                cin.ignore();
                addChild(parent, dataJob);

                cout << "Data Pekerjaan berhasil dimasukkan ke Freelancer " << parent->info.nama << endl;
            } else {
                cout << "Freelancer tidak ditemukan. Tidak dapat menambahkan data pekerjaan." << endl;
                    }
                cout << "===================================" << endl;

        } else if (choice == 8) {
            cout << "===================================" << endl;
            cout << "Tampilkan seluruh data Freelancer beserta Kontraknya!" << endl;
            showAllData(L);
            cout << "===================================" << endl;




        } else if (choice == 9) {
     cout << "===================================" << endl;
        cout << "Mencari data Pekerjaan pada Freelancer tertentu" << endl;

        string namaFreelancer;
        cout << "Masukkan nama Freelancer: ";
        cin.ignore();
        getline(cin, namaFreelancer);

        AdrInduk freelancer = findParent(L, namaFreelancer);

        if (freelancer != nullptr) {
        cout << "Data Pekerjaan dari Freelancer " << freelancer->info.nama << ":" << endl;
        showAllChild(freelancer); // Panggil fungsi untuk menampilkan semua data Pekerjaan pada Freelancer
        } else {
        cout << "Freelancer tidak ditemukan." << endl;
        }
        cout << "===================================" << endl;

        } else if (choice == 10) {
            cout << "===================================" << endl;
    cout << "Menghapuskan pekerjaan pada freelancer tertentu" << endl;

    string namaFreelancer;
    cout << "Masukkan nama Freelancer yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaFreelancer);

    AdrInduk freelancerToDelete = findParent(L, namaFreelancer);

    if (freelancerToDelete != nullptr) {
        deleteParent(L, freelancerToDelete);
        cout << "Data Freelancer beserta Pekerjaannya berhasil dihapus." << endl;
    } else {
        cout << "Freelancer tidak ditemukan." << endl;
    }
    cout << "==================================="<<endl;
        } else if (choice == 11) {
            cout << "===================================" << endl;
    cout << "Hapus Data Pekerjaan pada Freelancer Tertentu beserta relasinya" << endl;

    string namaFreelancer;
    cout << "Masukkan nama Freelancer: ";
    cin.ignore();
    getline(cin, namaFreelancer);

    string namaKlien;
    cout << "Masukkan nama Klien: ";
    getline(cin, namaKlien);

    AdrInduk freelancer = findParent(L, namaFreelancer);

    if (freelancer != nullptr) {
        deleteChild(freelancer, namaKlien); // Panggil fungsi untuk menghapus data Pekerjaan pada Freelancer Tertentu beserta relasinya
        cout << "Data Pekerjaan pada Freelancer " << namaFreelancer << " dengan Klien " << namaKlien << " berhasil dihapus." << endl;
    } else {
        cout << "Freelancer tidak ditemukan." << endl;
    }
    cout << "===================================" << endl;
        } else if (choice == 12) {
    cout << "===================================" << endl;
    cout << "Menghitung jumlah data child dari parent tertentu" << endl;

    string namaFreelancer;
    cout << "Masukkan nama Freelancer: ";
    cin.ignore();
    getline(cin, namaFreelancer);

    AdrInduk freelancer = findParent(L, namaFreelancer);

    if (freelancer != nullptr) {
        int jumlahChild = countChildOfParent(freelancer);
        cout << "Jumlah data Pekerjaan pada Freelancer " << freelancer->info.nama << " adalah: " << jumlahChild << endl;
    } else {
        cout << "Freelancer tidak ditemukan." << endl;
    }
    cout << "===================================" << endl;

        } else if (choice == 13) {
         cout << "===================================" << endl;
    cout << "Menampilkan Kontrak dengan Nilai Tertinggi untuk Setiap Freelancer" << endl;

    showHighestContract(L);

    cout << "===================================" << endl;
            }else if (choice == 0) {
            cout << "Terima kasih! Program berakhir." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}

