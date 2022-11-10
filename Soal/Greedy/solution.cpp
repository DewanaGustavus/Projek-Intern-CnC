#include <bits/stdc++.h>
using namespace std;

int main() {
    std::string inp;
    int i, sum, currentx, currentxgroup;
    long long stepsum;
    int mod = 10000003;
    cin >> inp;

    int length = inp.size(); // panjang string
    
    // KAMUS
    sum = 0; // jumlah orang
    currentx = 0; // jumlahx yang bersebelahan
    stepsum = 0;
    
    // ALGORITMA
    for (i = 0; i < length; i++) {
        if (inp[i] == 'x') {
            sum++;
        }
    }
    
    // secara intuisi kita menggeser X mendekati yang paling banyak untuk meminimasi langkah yang harus diambil
    for (i = 0; i < length; i++) {
        if (inp[i] == 'x') { // jika pada index i adalah x maka jumlahx yang bersebelahan + 1
            currentx++;
        } else {
            // menentukan x mana yang harus digrupkan, tentukan grup yang lebih kecil untuk meminimasi langkah yang diambil
            if (currentx > sum - currentx) {
                currentxgroup = sum - currentx;
            } else {
                currentxgroup = currentx;
            }
            
            // setiap x pada grup di geser sebanyak 1 langkah
            stepsum = stepsum + currentxgroup;
        }
    }
    
    cout << stepsum;

    return 0;  
}