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
    sablon* next;
};

sablon* head = nullptr;

akun admin[1]={
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
    cout<<"Ingin menambahkan katalog baru? (y/n): ";
    cin>>konfirmasi;
    if(konfirmasi == "y" || konfirmasi == "Y"){
        sablon* NodeBaru = new sablon;
        NodeBaru->nama = nama;
        NodeBaru->jenis = jenis;
        NodeBaru->stok = stok;
        NodeBaru->next = nullptr;
        if (head == nullptr){
            head = NodeBaru;
        } 
        else{
            sablon* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = NodeBaru;
        }
        cout<<"Katalog berhasil ditambahkan!"<<endl;
    } 
    else if (konfirmasi == "n" || konfirmasi == "N"){
        cout<<"Katalog tidak ditambahkan."<<endl;
    } 
    else{
        cout<<"Input tidak valid."<<endl;
    }
}

void lihatKatalog(){
    cout<<"Lihat Data Katalog"<<endl;
    if (head == nullptr){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        sablon* temp = head;
        int index = 1;
        while (temp != nullptr){
            cout<< index << ".\tNama: " <<temp->nama<<endl;
            cout<< "\tJenis: " <<temp->jenis<<endl;
            cout<< "\tStok: " << temp->stok<<endl;
            temp = temp->next;
            index++;
        }
    }
}

void ubahKatalog(){
    system("cls");
    cout<<"Ubah Data Katalog"<<endl;
    if (head == nullptr){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        int pilihan;
        cout<<"Pilih nomor katalog yang ingin diubah: ";
        cin>>pilihan;
        sablon* temp = head;
        int index = 1;
        while (temp != nullptr && index < pilihan){
            temp = temp->next;
            index++;
        }
        if (temp != nullptr){
            string nama, jenis;
            int stok;
            cout<<"Masukkan nama baru: ";
            cin.ignore();
            getline(cin, nama);
            cout<<"Masukkan jenis baru: ";
            getline(cin, jenis);
            cout<<"Masukkan stok baru: ";
            cin>>stok;
            temp->nama = nama;
            temp->jenis = jenis;
            temp->stok = stok;

            cout<<"Katalog berhasil diubah!"<<endl;
        } 
        else{
            cout<<"Input tidak valid."<<endl;
        }
    }
}

void hapusKatalog(){
    system("cls");
    cout<<"Hapus Data Katalog" << endl;
    if (head == nullptr){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        int pilihan;
        cout<<"Pilih nomor katalog yang ingin dihapus: ";
        cin>>pilihan;
        if(pilihan == 1){
            sablon* temp = head;
            head = head->next;
            delete temp;
            cout<<"Katalog berhasil dihapus!"<<endl;
        } 
        else{
            sablon* temp = head;
            sablon* prev = nullptr;
            int index = 1;

            while(temp != nullptr && index < pilihan){
                prev = temp;
                temp = temp->next;
                index++;
            }
            if(temp != nullptr){
                prev->next = temp->next;
                delete temp;
                cout<<"Katalog berhasil dihapus!"<<endl;
            } 
            else{
                cout<<"Input tidak valid."<<endl;
            }
        }
    }
}

void menuUtama(){
    int pilih;
    cout<<"Menu Utama"<<endl;
    cout<<"1. Tambah Data Katalog"<<endl;
    cout<<"2. Lihat Data Katalog"<<endl;
    cout<<"3. Ubah Data Katalog"<<endl;
    cout<<"4. Hapus Data Katalog"<<endl;
    cout<<"0. Keluar"<<endl;
    cout<<"Pilih menu: ";
    cin>>pilih;

    if(pilih == 1){
        tambahKatalog();
        system("cls");
        menuUtama();
    } 
    else if(pilih == 2){
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
    else if(pilih == 0){
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
    if(user[0].username == uname && user[0].password == pass){
        system("cls");
        menuUtama();
    } 
    else{
        system("cls");
        cout<<"Username atau password salah, silahkan coba lagi."<<endl;
        login();
    }
}

int main(){
    system("cls");
    cout<<"Sistem Manajemen Data Katalog SablonYuk"<<endl;
    login();
    return 0;
}
