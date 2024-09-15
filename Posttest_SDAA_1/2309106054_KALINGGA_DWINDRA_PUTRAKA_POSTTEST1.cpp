#include <iostream>
using namespace std;

int pascal(int baris, int indeks) {
    if (indeks==0 or indeks==baris) {
        return 1;
    }
    return pascal(baris-1, indeks-1)+pascal(baris-1, indeks);
}

int main() {
    for (int i=0; i<4; i++) {
        for (int j=0; j<=i; j++){
            cout<<pascal(i, j)<<" ";
        }
        cout<<endl;
    }
    return 0;
}