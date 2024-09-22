#include <iostream>
using namespace std;

struct akun{
    string username;
    string password;
};
struct sablon{
    string nama;
    string jenis;
    int stok;
};

sablon katalog[100];

int jmlkatalog = 0;

akun admin[1] = {
    {"Kalingga", "6054"}
};
akun* user = admin;

void tambahKatalog(){
    string nama;
    string jenis;
    int stok;
    string konfirmasi;
    system("cls");
    cout<<"Tambah Data Katalog"<<endl;
    cout<<"Masukkan nama: ";
    cin.ignore();
    getline(cin, nama);
    cout<<"Masukkan jenis: ";
    getline(cin, jenis);
    cout<<"Masukkan stok: ";
    cin>>stok;
    cout<<"Ingin menambahkan katalog baru?(y/n)";
    cin>>konfirmasi;
    if (konfirmasi == "y" || konfirmasi == "Y") {
        katalog[jmlkatalog].nama = nama;
        katalog[jmlkatalog].jenis = jenis;
        katalog[jmlkatalog].stok = stok;
        jmlkatalog++;
        cout<<"Katalog berhasil ditambahkan!"<<endl;
    }
    else if(konfirmasi=="n" || konfirmasi=="N"){
        cout<<"Katalog tidak ditambahkan."<<endl;
    }
    else{
        cout<<"Input tidak valid."<<endl;
    }
}

void lihatKatalog(){
    cout<<"Lihat Data Katalog"<<endl;
    if (jmlkatalog == 0){
        cout<<"Katalog belum ditambahkan"<<endl;
    }
    else{
        for (int i =0; i< jmlkatalog;i++){
            cout<<i+1 << ".\tNama : "<<katalog[i].nama<<endl;
            cout<<"\tJenis : "<<katalog[i].jenis<<endl;
            cout<<"\tStok : "<<katalog[i].stok<<endl;
        }
    }
}

void ubahKatalog(){
    system("cls");
    cout<<"Ubah Data Katalog"<<endl;
    int pilihan;
    if (jmlkatalog == 0){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        cout<<"Pilih nomor katalog yang ingin diubah: ";
        cin>>pilihan;
        if (pilihan > 0 && pilihan <= jmlkatalog){
            string nama, jenis;
            int stok;
            cout<<"Masukkan nama baru: ";
            cin.ignore();
            getline(cin, nama);
            cout<<"Masukkan jenis baru: ";
            getline(cin, jenis);
            cout<<"Masukkan stok baru: ";
            cin>>stok;
            katalog[pilihan-1].nama = nama;
            katalog[pilihan-1].jenis = jenis;
            katalog[pilihan-1].stok = stok;
            cout<<"Katalog berhasil diubah!"<<endl;
        } 
        else{
            cout<<"Input tidak valid."<<endl;
        }
    }
}

void hapusKatalog(){
    system("cls");
    cout<<"Hapus Data Katalog"<<endl;
    int pilihan;
    if (jmlkatalog == 0) {
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        cout<<"Pilih nomor katalog yang ingin dihapus: ";
        cin>>pilihan;
        if (pilihan > 0 && pilihan <= jmlkatalog){
            for (int i = pilihan-1; i < jmlkatalog-1; i++) {
                katalog[i] = katalog[i + 1];
            }
            jmlkatalog--;
            cout<<"Katalog berhasil dihapus!"<<endl;
        } 
        else{
            cout<<"Input tidak valid."<<endl;
        }
    }
}

void menuUtama(){
    int pilih;
    cout<<"Menu Utama"<<endl;
    cout<<"1.Tambah Data Katalog"<<endl;
    cout<<"2.Lihat Data Katalog"<<endl;
    cout<<"3.Ubah Data Katalog"<<endl;
    cout<<"4.Hapus Data Katalog"<<endl;
    cout<<"0.Keluar"<<endl;
    cout<<"Pilih menu: ";
    cin>>pilih;
    if (pilih == 1){
        tambahKatalog();
        system("cls");
        menuUtama();
    }
    else if (pilih == 2){
        system("cls");
        lihatKatalog();
        menuUtama();
    }
    else if (pilih == 3){
        ubahKatalog();
        system("cls");
        menuUtama();
    } 
    else if (pilih == 4){
        hapusKatalog();
        system("cls");
        menuUtama();
    }
    else if (pilih == 0){
        return;
    }
    else{
        cout<<"Input tidak valid."<<endl;
        menuUtama();
    }
}

void login(){
    string uname;
    string pass;
    cout<<"Username: ";
    cin>>uname;
    cout<<"Password: ";
    cin>>pass;
    for (int i = 0; i < 100; i++) {
    if (user[i].username != uname || user[i].password != pass){
        system("cls");
        cout<<"Username atau password salah, silahkan coba lagi."<<endl;
        login();
    }
    else{
        system("cls");
        menuUtama();
        break;
    }
    }
}

int main(){
    system("cls");
    cout<<"Sistem Manajemen Data Katalog SablonYuk"<<endl;
    login();
    return 0;
}