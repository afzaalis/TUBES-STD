#include <iostream>
using namespace std;
#include "header.h"

AdrInduk createElementInd(InfotypeFreelancer x) {
    AdrInduk newParent = new ElmInduk;
    newParent->info = x;
    newParent->next = NULL;
    newParent->prev = NULL;
    newParent->nextR = NULL;
    return newParent;
}


AdrAnak createElementAnak(InfotypeJob x) {
    AdrAnak newChild = new ElmAnak;
    newChild->info = x;
    newChild->next = NULL;
    return newChild;
}

// Fungsi untuk membuat relasi antara elemen-anak dan elemen-induk
AdrRelasi createElementR(AdrAnak p) {
    AdrRelasi newRelasi = new ElmRelasi;
    newRelasi->nextR = NULL;
    newRelasi->next = p;

    return new ElmRelasi;
}

// Fungsi untuk menampilkan semua elemen induk (Freelancer)
void showAllParent(ListInduk L) {
    AdrInduk current = L.first;
    while (current != NULL) {
        cout << "==========" << endl;
        cout << "Nama: " << current->info.nama << endl;
        cout << "Keahlian: " << current->info.keahlian << endl;
        cout << "Rating: " << current->info.rating << endl;
        current = current->next;
    }
}
void deleteParentWithRelations(ListInduk& L, AdrInduk parentToDelete) {
     // Menghapus relasi terlebih dahulu jika ada
    AdrRelasi relasiToDelete = parentToDelete->nextR;
    while (relasiToDelete != nullptr) {
        AdrRelasi temp = relasiToDelete;
        relasiToDelete = relasiToDelete->nextR;
        delete temp->next;
        delete temp;
         }

    // Menghapus elemen-induk
    if (parentToDelete == L.first) {
        L.first = parentToDelete->next;
        if (L.first != nullptr) {
            L.first->prev = nullptr;
        } else {
            L.last = nullptr;
        }
    } else if (parentToDelete == L.last) {
        L.last = parentToDelete->prev;
        L.last->next = nullptr;
    } else {
        parentToDelete->prev->next = parentToDelete->next;
        parentToDelete->next->prev = parentToDelete->prev;
    }

    delete parentToDelete;
}
AdrInduk findParent(ListInduk L, string namaFreelancer) {
       AdrInduk current = L.first;
    while (current != nullptr) {
        if (current->info.nama == namaFreelancer) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

AdrAnak findChild(AdrInduk parent, string namaKlien) {
AdrRelasi relasi = parent->nextR;
    while (relasi != nullptr) {
        AdrAnak current = relasi->next;
        while (current != nullptr) {
            if (current->info.namaKlien == namaKlien) {
                return current;
            }
            current = current->next;
        }
        relasi = relasi->nextR;
    }
    return nullptr;
}

void addChild(AdrInduk parent, InfotypeJob childData){
    AdrRelasi relasi = parent->nextR;
    bool found = false;

    // Mencari relasi yang sesuai dengan parent
    while (relasi != nullptr && !found) {
        AdrAnak current = relasi->next;
        if (current == nullptr) {
            // Tidak ada anak di relasi ini, tambahkan child baru
            current = createElementAnak(childData);
            relasi->next = current;
            found = true;
        } else {
            // Iterasi sampai ke elemen terakhir untuk menambahkan child baru
            while (current->next != nullptr) {
                current = current->next;
            }
            AdrAnak newChild = createElementAnak(childData);
            current->next = newChild;
            found = true;
        }
        relasi = relasi->nextR;
    }

    if (!found) {
        // Jika tidak ada relasi yang sesuai, buat relasi baru dan tambahkan child
        relasi = createElementR(NULL);
        AdrAnak newChild = createElementAnak(childData);
        relasi->next = newChild;
        parent->nextR = relasi;
    }
};

// Fungsi untuk menghubungkan data parent ke data child
void connectParentToChild(AdrInduk parent, AdrAnak child) {
    AdrRelasi relasi = parent->nextR;

    // Mencari relasi yang sesuai dengan parent
    while (relasi != nullptr) {
        if (relasi->next == nullptr) {
            // Tidak ada anak di relasi ini, tambahkan child baru
            relasi->next = child;
            return;
        }
        relasi = relasi->nextR;
    }

    // Jika tidak ada relasi yang sesuai, buat relasi baru dan tambahkan child
    relasi = createElementR(child);
    parent->nextR = relasi;
}

void showAllData(ListInduk L) {
     AdrInduk currentParent = first(L);

    if (currentParent == nullptr) {
        cout << "Tidak ada data." << endl;
        return;
    }

    while (currentParent != nullptr) {
        cout << "Nama Freelancer: " << currentParent->info.nama << endl;
        cout << "Keahlian: " << currentParent->info.keahlian << endl;
        cout << "Rating: " << currentParent->info.rating << endl;

        AdrRelasi relasi = currentParent->nextR;
        while (relasi != nullptr) {
            AdrAnak currentChild = relasi->next;
            while (currentChild != nullptr) {
                cout << "Nama Klien: " << currentChild->info.namaKlien << endl;
                cout << "Deskripsi Job: " << currentChild->info.deskripsi << endl;
                cout << "Fee: " << currentChild->info.fee << endl;
                cout << "-----------------------------------" << endl;

                currentChild = currentChild->next;
            }
            relasi = relasi->nextR;
        }

        currentParent = currentParent->next;
    }

}

AdrAnak findChildOnParent(AdrInduk parent) {
     if (parent == nullptr || parent->nextR == nullptr) {
        return nullptr; // Tidak ada anak pada parent atau relasi belum terbentuk
    }

    AdrRelasi relasi = parent->nextR;
    while (relasi != nullptr) {
        if (relasi->next != nullptr) {
            return relasi->next; // Mengembalikan anak pertama dari relasi saat ini
        }
        relasi = relasi->nextR;
    }

    return nullptr;
}

void deleteChildOnParent(AdrInduk parent) {
    if (parent == nullptr || parent->nextR == nullptr) {
        return; // Tidak ada anak pada parent atau relasi belum terbentuk
    }

    AdrRelasi relasi = parent->nextR;
    while (relasi != nullptr) {
        AdrAnak current = relasi->next;
        while (current != nullptr) {
            AdrAnak temp = current;
            current = current->next;
            delete temp; // Hapus anak
        }
        relasi->next = nullptr; // Set relasi anak menjadi null
        relasi = relasi->nextR;
    }
}
int countChildOfParent(AdrInduk parent) {
    int count = 0;
    AdrRelasi relasi = parent->nextR;

    while (relasi != nullptr) {
        AdrAnak currentChild = relasi->next;
        while (currentChild != nullptr) {
            count++;
            currentChild = currentChild->next;
        }
        relasi = relasi->nextR;
    }

    return count;
}
void findRelasi(ListInduk &f, string nama,string namaKlien){
   if (f.first == nullptr) {
        cout << "Tidak ada data Freelancer." << endl;
        return;
    }

    AdrInduk current = f.first;
    bool found = false;
    while (current != nullptr && !found) {
        if (current->info.nama == nama) {
            AdrRelasi relasi = current->nextR;
            while (relasi != nullptr) {
                AdrAnak currentAnak = relasi->next;
                while (currentAnak != nullptr) {
                    if (currentAnak->info.namaKlien == namaKlien) {
                        found = true;
                        cout << "Relasi ditemukan antara " << nama << " dan " << namaKlien << endl;
                        return;
                    }
                    currentAnak = currentAnak->next;
                }
                relasi = relasi->nextR;
            }
        }
        current = current->next;
    }

    if (!found) {
        cout << "Tidak ditemukan relasi antara " << nama << " dan " << namaKlien << endl;
    }
};

void deleteRelasi(ListInduk &f,string nama,string namaKlien){
if (f.first == nullptr) {
        cout << "Tidak ada data Freelancer." << endl;
        return;
    }

    AdrInduk current = f.first;
    bool found = false;
    while (current != nullptr && !found) {
        if (current->info.nama == nama) {
            AdrRelasi relasi = current->nextR;
            while (relasi != nullptr) {
                AdrAnak prevAnak = nullptr;
                AdrAnak currentAnak = relasi->next;
                while (currentAnak != nullptr) {
                    if (currentAnak->info.namaKlien == namaKlien) {
                        found = true;
                        if (prevAnak == nullptr) {
                            relasi->next = currentAnak->next;
                        } else {
                            prevAnak->next = currentAnak->next;
                        }
                        delete currentAnak;
                        cout << "Relasi antara " << nama << " dan " << namaKlien << " berhasil dihapus." << endl;
                        return;
                    }
                    prevAnak = currentAnak;
                    currentAnak = currentAnak->next;
                }
                relasi = relasi->nextR;
            }
        }
        current = current->next;
    }

    if (!found) {
        cout << "Tidak ditemukan relasi antara " << nama << " dan " << namaKlien << endl;
    }
};
void showAllChild(AdrInduk parent) {
 if (parent == nullptr) {
        cout << "Freelancer tidak ditemukan." << endl;
        return;
    }

    if (parent->nextR == nullptr) {
        cout << "Tidak ada data pekerjaan pada Freelancer " << parent->info.nama << endl;
        return;
    }

    AdrRelasi relasi = parent->nextR;
    while (relasi != nullptr) {
        AdrAnak currentChild = relasi->next;
        while (currentChild != nullptr) {
            cout << "Nama Klien: " << currentChild->info.namaKlien << endl;
            cout << "Deskripsi Job: " << currentChild->info.deskripsi << endl;
            cout << "Fee: " << currentChild->info.fee << endl;
            cout << "-----------------------------------" << endl;

            currentChild = currentChild->next;
        }
        relasi = relasi->nextR;
    }
}
void deleteParent(ListInduk& L, AdrInduk parentToDelete) {
    if (parentToDelete == nullptr) {
        return;
    }

    if (parentToDelete == first(L)) {
        if (next(parentToDelete) != nullptr) {
            first(L) = next(parentToDelete);
            prev(next(parentToDelete)) = nullptr;
        } else {
            first(L) = nullptr;
            last(L) = nullptr;
        }
    } else if (parentToDelete == last(L)) {
        last(L) = prev(parentToDelete);
        next(prev(parentToDelete)) = nullptr;
    } else {
        next(prev(parentToDelete)) = next(parentToDelete);
        prev(next(parentToDelete)) = prev(parentToDelete);
    }

    deleteChildOnParent(parentToDelete); // Hapus semua relasi data anak
    delete parentToDelete;
}
void deleteChild(AdrInduk parent, string namaKlien) {
    if (parent == nullptr) {
        cout << "Parent tidak valid." << endl;
        return;
    }

    AdrAnak child = findChild(parent, namaKlien);
    if (child == nullptr) {
        cout << "Data Pekerjaan tidak ditemukan pada Freelancer ini." << endl;
        return;
    }

    if (parent->nextR == nullptr) {
        cout << "Freelancer tidak memiliki relasi." << endl;
        return;
    }

    AdrRelasi relasi = parent->nextR;
    AdrRelasi prevRelasi = nullptr;

    while (relasi != nullptr) {
        AdrAnak currentChild = relasi->next;

        while (currentChild != nullptr) {
            if (currentChild == child) {
                if (prevRelasi == nullptr) {
                    relasi->next = currentChild->next;
                    delete currentChild;
                    cout << "Data Pekerjaan pada Freelancer berhasil dihapus." << endl;
                    return;
                } else {
                    prevRelasi->next = currentChild->next;
                    delete currentChild;
                    cout << "Data Pekerjaan pada Freelancer berhasil dihapus." << endl;
                    return;
                }
            }

            prevRelasi = relasi;
            currentChild = currentChild->next;
        }

        relasi = relasi->nextR;
    }

    cout << "Data Pekerjaan pada Freelancer tidak ditemukan." << endl;
}
void showHighestContract(ListInduk L) {
    AdrInduk freelancer = L.first;

    while (freelancer != nullptr) {
        cout << "===================================" << endl;
        cout << "Freelancer: " << freelancer->info.nama << endl;

        AdrAnak highestContract = nullptr;
        int highestFee = -1;

        AdrAnak contract = findChildOnParent(freelancer);

        while (contract != nullptr) {
            if (contract->info.fee > highestFee) {
                highestFee = contract->info.fee;
                highestContract = contract;
            }
            contract = contract->next;
        }

        if (highestContract != nullptr) {
            cout << "Kontrak dengan nilai tertinggi:" << endl;
            cout << "Nama Klien: " << highestContract->info.namaKlien << endl;
            cout << "Deskripsi: " << highestContract->info.deskripsi << endl;
            cout << "Fee: " << highestContract->info.fee << endl;
        } else {
            cout << "Freelancer ini belum memiliki kontrak." << endl;
        }

        freelancer = freelancer->next;
    }
}
void displayMenu() {
 cout << "===================================" << endl;
    cout << "MENU" << endl;
    cout << "1. Masukan Data Freelancer" << endl;
    cout << "2. Masukan Data Kontrak" << endl;
    cout << "3. Tampilkan Seluruh Data Freelancer" << endl;
    cout << "4. Menghubungkan data Freelancer dengan pekerjaan" << endl;
    cout << "5. Mencari data Freelancer" << endl;
    cout << "6. Mencari data Kontrak" << endl;
    cout << "7. Tambahkan data Pekerjaan" << endl;
    cout << "8. Tampilkan seluruh data Freelancer beserta Pekerjaannya" << endl;
    cout << "9. Mencari data Pekerjaan pada Freelancer tertentu" << endl;
    cout << "10. Menghapuskan pekerjaan pada freelancer tertentu " << endl;
    cout << "11. Hapus Data Pekerjaan pada Freelancer Tertentu beserta relasinya " << endl;
    cout << "12. Menghitung jumlah data child dari parent tertentu " << endl;
    cout << "13. Menampilkan nilai tertinggi(rating) di kontrak " << endl;
    cout << "0. Keluar" << endl;
    cout << "===================================" << endl;
    cout << "Pilihan Anda: ";
}

