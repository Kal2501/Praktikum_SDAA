#include <iostream>
#include <bits/stdc++.h>
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

sablon* top = nullptr;

akun admin[1]={
    {"Kalingga", "6054"}
};
akun* user = admin;

void pushKatalog(string nama, string jenis, int stok) {
    sablon* newKatalog = new sablon;
    newKatalog->nama = nama;
    newKatalog->jenis = jenis;
    newKatalog->stok = stok;
    newKatalog->next = top;
    top = newKatalog;
}

void dequeueKatalog() {
    if (top == nullptr){
        cout << "Katalog kosong" << endl;
    }
    else{
        sablon* temp = top;
        top = top->next;
        delete temp;
    }
}

sablon* merge(sablon* left, sablon* right, bool ascending) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    sablon* result = nullptr;
    if ((ascending && left->stok <= right->stok) || (!ascending && left->stok >= right->stok)){
        result = left;
        result->next = merge(left->next, right, ascending);
    } 
    else{
        result = right;
        result->next = merge(left, right->next, ascending);
    }
    return result;
}

sablon* mergeSort(sablon* head, bool ascending) {
    if (head == nullptr || head->next == nullptr){
        return head;
    }
    sablon* slow = head;
    sablon* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    sablon* mid = slow->next;
    slow->next = nullptr;
    sablon* left = mergeSort(head, ascending);
    sablon* right = mergeSort(mid, ascending);
    sablon* result = merge(left, right, ascending);
    sablon* temp = result;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". Nama: " << temp->nama << endl;
        cout << "   Jenis: " << temp->jenis << endl;
        cout << "   Stok: " << temp->stok << endl;
        temp = temp->next;
        index++;
    }
    return result;
}

sablon* partition(sablon* start, sablon* end, sablon** newStart, sablon** newEnd) {
    sablon* pivot = end;
    sablon* prev = nullptr;
    sablon* curr = start;
    sablon* tail = pivot;
    while (curr != pivot) {
        if (curr->stok < pivot->stok){
            if ((*newStart) == nullptr) {
                (*newStart) = curr;
            }
            prev = curr;
            curr = curr->next;
        } 
        else{
            if (prev){
                prev->next = curr->next;
            }
            sablon* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }
    if ((*newStart) == nullptr) {
        (*newStart) = pivot;
    }
    (*newEnd) = tail;
    return pivot;
}

sablon* quickSortRec(sablon* start, sablon* end) {
    if (!start || start == end) {
        return start;
    }
    sablon* newStart = nullptr;
    sablon* newEnd = nullptr;
    sablon* pivot = partition(start, end, &newStart, &newEnd);
    if (newStart != pivot) {
        sablon* temp = newStart;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;
        newStart = quickSortRec(newStart, temp);
        temp = newStart;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = pivot;
    }
    pivot->next = quickSortRec(pivot->next, newEnd);
    return newStart;
}

void quickSort() {
    if (top == nullptr || top->next == nullptr) {
        return;
    }
    sablon* end = top;
    while (end->next != nullptr) {
        end = end->next;
    }
    top = quickSortRec(top, end);

    sablon* temp = top;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". Nama: " << temp->nama << endl;
        cout << "   Jenis: " << temp->jenis << endl;
        cout << "   Stok: " << temp->stok << endl;
        temp = temp->next;
        index++;
    }
}

int length(sablon* head){
    int count = 0;
    sablon* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int min(int x, int y) {return (x <= y) ? x : y;}

int fibMonaccianSearch(sablon *head, int x, int n) {
    sablon *temp = head;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        temp = head;
        for (int j = 0; j < i; j++) {
            if (temp != nullptr) {
                temp = temp->next;
            } 
            else{
                break;
            }
        }
        if (temp == nullptr) {
            break;
        }
        if (temp->stok < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->stok > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            return i;
        }
    }
    temp = head;
    for (int j = 0; j < offset + 1; j++) {
        if (temp != nullptr) {
            temp = temp->next;
        } else {
            break;
        }
    }
    if (fibMMm1 && temp != nullptr && temp->stok == x) {
        return offset + 1;
    }
    return -1;
}

sablon* findNode(sablon* head, int idx) {
    sablon* current = head;
    for (int i = 0; i < idx && current != nullptr; i++){
        current = current->next;
    }
    return current;
}

int jumpSearch(sablon* head, int x, int n) {
    int step = sqrt(n);
    int prev = 0;
    sablon* current = head;
    sablon* prevNode = nullptr;

    while (current != nullptr && current->stok < x) {
        prevNode = current;
        prev += step;
        current = findNode(head, prev);
        if (prevNode == nullptr || current == nullptr) {
            return -1;
        }
    }

    current = prevNode;
    int index = prev - step;
    while (current != nullptr && index < n && current->stok < x){
        current = current->next;
        index++;
    }

    if (current != nullptr && current->stok == x){
        return index;
    }
    return -1;
}

void cariStokJump(){
    if (top == nullptr){
        cout << "Katalog belum ditambahkan!" << endl;
        return;
    }
    int stokDicari;
    cout << "Masukkan stok yang ingin dicari: ";
    cin >> stokDicari;
    int n = 0;
    sablon* temp = top;
    while (temp != nullptr){
        n++;
        temp = temp->next;
    }
    top = mergeSort(top, true);
    int hasil = jumpSearch(top, stokDicari, n);
    if (hasil != -1){
        sablon* ditemukan = findNode(top, hasil);
        cout << "Stok ditemukan pada katalog " << hasil + 1 << endl;
        cout << "Nama: " << ditemukan->nama << endl;
        cout << "Jenis: " << ditemukan->jenis << endl;
        cout << "Stok: " << ditemukan->stok << endl;
    } 
    else{
        cout << "Stok tidak ditemukan!" << endl;
    }
}

void cariStokFibonacci(){
    if (top == nullptr){
        cout << "Katalog belum ditambahkan!" << endl;
        return;
    }
    int stokDicari;
    cout << "Masukkan stok yang ingin dicari: ";
    cin >> stokDicari;
    int n = 0;
    sablon* temp = top;
    while (temp != nullptr){
        n++;
        temp = temp->next;
    }
    top = mergeSort(top, true);
    int hasil = fibMonaccianSearch(top, stokDicari, n);
    if (hasil != -1){
        sablon* ditemukan = findNode(top, hasil);
        cout << "Stok ditemukan pada katalog " << hasil + 1 << endl;
        cout << "Nama: " << ditemukan->nama << endl;
        cout << "Jenis: " << ditemukan->jenis << endl;
        cout << "Stok: " << ditemukan->stok << endl;
    } 
    else{
        cout << "Stok tidak ditemukan!" << endl;
    }
}

const int NO_OF_CHARS = 256;

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]){
    for (int i = 0; i < NO_OF_CHARS; i++){
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++){
        badChar[(int) str[i]] = i;
    }
}

void boyerMooreSearch(sablon* head, string pattern){
    int m = pattern.size();
    sablon* temp = head;
    bool found = false;
    while (temp != nullptr) {
        int n = temp->nama.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pattern, m, badChar);
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == temp->nama[s + j]){
                j--;
            }
            if (j < 0){
                cout << "Nama katalog ditemukan: " << temp->nama << endl;
                cout << "   Jenis: " << temp->jenis << endl;
                cout << "   Stok: " << temp->stok << endl;
                found = true;
                break;
            } 
            else{
                s += max(1, j - badChar[temp->nama[s + j]]);
            }
        }
        temp = temp->next;
    }
    if (!found){
        cout << "Nama katalog tidak ditemukan!" << endl;
    }
}

void lihatKatalog(){
    cout << "Lihat Data Katalog" << endl;
    if (top == nullptr){
        cout << "Katalog belum ditambahkan" << endl;
    } 
    else{
        int pilihan;
        cout << "Pilih metode pengurutan:" << endl;
        cout << "1. Merge Sort Descending (Stok)" << endl;
        cout << "2. Quick Sort Ascending (Stok)" << endl;
        cout << "3. Cari Stok dengan Jump Search" << endl;
        cout << "4. Cari Stok dengan Fibonacci Search" << endl;
        cout << "5. Cari Nama Katalog dengan Boyer Moore Search" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
            top = mergeSort(top, false);
        } 
        else if (pilihan == 2) {
            quickSort();
        } 
        else if (pilihan == 3) {
            cariStokJump();
        } 
        else if (pilihan == 4) {
            cariStokFibonacci();
        }
        else if (pilihan == 5) {
            string pattern;
            cout << "Masukkan nama katalog yang ingin dicari: ";
            cin.ignore();
            getline(cin, pattern);
            boyerMooreSearch(top, pattern);
        }
        else {
            cout << "Input tidak valid." << endl;
            return;
        }
    }
}

void tambahKatalog() {
    string nama;
    string jenis;
    int stok;
    string konfirmasi;
    system("cls");
    cout << "Tambah Data Katalog" << endl;
    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan jenis: ";
    getline(cin, jenis);
    cout << "Masukkan stok: ";
    cin >> stok;
    cout << "Ingin menambahkan katalog baru? (y/n): ";
    cin >> konfirmasi;
    if (konfirmasi == "y" || konfirmasi == "Y"){
        pushKatalog(nama, jenis, stok);
        cout << "Katalog berhasil ditambahkan!" << endl;
    } 
    else if (konfirmasi == "n" || konfirmasi == "N"){
        cout << "Katalog tidak ditambahkan." << endl;
    } 
    else {
        cout << "Input tidak valid." << endl;
    }
}

void ubahKatalog(){
    system("cls");
    cout<<"Ubah Data Katalog"<<endl;
    if (top == nullptr){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        int pilihan;
        cout<<"Pilih nomor katalog yang ingin diubah: ";
        cin>>pilihan;
        sablon* temp = top;
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
    if (top == nullptr){
        cout<<"Katalog belum ditambahkan"<<endl;
    } 
    else{
        lihatKatalog();
        int pilihan;
        cout<<"Pilih nomor katalog yang ingin dihapus: ";
        cin>>pilihan;
        if(pilihan == 1){
            dequeueKatalog();
            cout<<"Katalog berhasil dihapus!"<<endl;
        } 
        else{
            sablon* temp = top;
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
