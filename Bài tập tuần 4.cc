#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;

class RC4 {
private:
    vector<int> S;
    vector<int> K;
    int N;

public:
    RC4(vector<int> key, int n_size) : K(key), N(n_size) {
        S.resize(N);
    }

    void ksa() {
        for (int i = 0; i < N; i++) S[i] = i;
        int j = 0;
        int key_len = K.size();
        for (int i = 0; i < N; i++) {
            j = (j + S[i] + K[i % key_len]) % N;
            swap(S[i], S[j]);
        }
        
        cout << "Mang S sau buoc KSA: ";
        for (int x : S) cout << x << " ";
        cout << "\n" << endl;
    }

    void encrypt(string plaintext) {
        int i = 0, j = 0;

        cout << left << setw(5)  << "m(t)" 
             << setw(4)  << "i" 
             << setw(4)  << "j" 
             << setw(6)  << "S[i]" 
             << setw(6)  << "S[j]" 
             << setw(12) << "t=(Si+Sj)%N"
             << setw(10) << "k = S[t]" 
             << setw(10) << "C (Dec)" 
             << "C (ASCII)" << endl;
        
        cout << string(75, '-') << endl;

        for (char &m : plaintext) {
            //Tim khoa k
            i = (i + 1) % N;
            j = (j + S[i]) % N;
            swap(S[i], S[j]);
            int t = (S[i] + S[j]) % N;
            int k = S[t]; 

            //Ma hoa XOR
            unsigned char m_val = (unsigned char)m;
            unsigned char c_val = m_val ^ k;
            char c_char = (char)c_val;

            cout << left << setw(5)  << m 
                 << setw(4)  << i 
                 << setw(4)  << j 
                 << setw(6)  << S[i] 
                 << setw(6)  << S[j] 
                 << setw(12) << t
                 << setw(10) << k 
                 << setw(10) << (int)c_val;
            
            if (c_val >= 32 && c_val <= 126) {
                cout << c_char << endl;
            } else {
                cout << "[non-print]" << endl;
            }
        }
    }
};

int main() {
    vector<int> seed_K = {2, 4, 1, 7};
    int N_size = 10; 
    string text = "cybersecurity";

    RC4 rc4(seed_K, N_size);
    rc4.ksa();
    rc4.encrypt(text);

    return 0;
}