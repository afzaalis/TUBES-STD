#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
using namespace std;


#define info(p) (p)->info
#define next(p) (p)->next
#define prev(p) (p)->prev
#define nextR(p) (p)->nextR
#define first(L) (L).first
#define last(L) (L).last

//DATA PEKERJAAN FREELANCE DLL MULTI LINK LIST
//terdiri dari 2 ADT



//ADT STRUCT FREELANCER (DLL)
//induk freelancer
struct Freelancer {
    string nama;
    string keahlian;
    int rating;
};

struct JobName {
    string namaKlien;
    string deskripsi;
    int fee;
};

typedef JobName InfotypeJob;
typedef Freelancer InfotypeFreelancer;

typedef struct ElmInduk *AdrInduk;
typedef struct ElmAnak *AdrAnak;
typedef struct ElmRelasi *AdrRelasi;

struct ElmRelasi {
    AdrRelasi nextR;
    AdrAnak next;
};

struct ElmAnak {
    InfotypeJob info;
    AdrAnak next;
};

struct ElmInduk {
    InfotypeFreelancer info;
    AdrInduk next;
    AdrInduk prev;
    AdrRelasi nextR;
};

struct ListAnak {
    AdrAnak first;
};

struct ListInduk {
    AdrInduk first;
    AdrInduk last;
};


AdrInduk createElementInd(InfotypeFreelancer x);
AdrAnak createElementAnak(InfotypeJob x);
AdrRelasi createElementR(AdrAnak p);
void showAllParent(ListInduk L);
void deleteParentWithRelations(ListInduk& L, AdrInduk parentToDelete);
AdrInduk findParent(ListInduk L, string namaFreelancer);
AdrAnak findChild(AdrInduk parent, string namaKlien);
void addChild(AdrInduk parent, InfotypeJob childData);
void connectParentToChild(AdrInduk parent, AdrAnak child);
void showAllData(ListInduk L);
AdrAnak findChildOnParent(AdrInduk parent);
void deleteChildOnParent(AdrInduk parent);
int countChildOfParent(AdrInduk freelancer);
void deleteRelasi(ListInduk &f,string nama,string namaKlien);
void findRelasi(ListInduk &f, string nama,string namaKlien);
void showAllChild(AdrInduk parent);
void deleteParent(ListInduk& L, AdrInduk parentToDelete);
void deleteChild(AdrInduk parent, string namaKlien);
void showHighestContract(ListInduk L);
void displayMenu();
#endif // HEADER_H_INCLUDED
