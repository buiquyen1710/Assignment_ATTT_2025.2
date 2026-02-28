#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Playfair {
    char matrix[5][5];
public:
    Playfair(string key) {
        string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        string combined = "";
        for(char c : key) if(c == 'J') combined += 'I'; else combined += toupper(c);
        combined += alphabet;

        string finalKey = "";
        bool used[26] = {false};
        for(char c : combined) {
            if(!used[c - 'A'] && c != 'J') {
                finalKey += c;
                used[c - 'A'] = true;
            }
        }

        for(int i = 0; i < 25; i++) matrix[i/5][i%5] = finalKey[i];
    }

    void findPos(char c, int &r, int &c_out) {
        if(c == 'J') c = 'I';
        for(int i=0; i<5; i++)
            for(int j=0; j<5; j++)
                if(matrix[i][j] == c) { r = i; c_out = j; return; }
    }

    string preparePlaintext(string text) {
        string result = "";
        for(char c : text) {
            if(isalpha(c)) {
                c = toupper(c);
                if(c == 'J') c = 'I';
                result += c;
            }
        }
        
        // Chia cặp và thêm X nếu cần
        string pairs = "";
        for(int i = 0; i < result.length(); i += 2) {
            if(i + 1 < result.length()) {
                if(result[i] == result[i+1]) {
                    pairs += result[i];
                    pairs += 'X';
                    i--; // xử lý lại ký tự thứ i+1
                } else {
                    pairs += result[i];
                    pairs += result[i+1];
                }
            } else {
                pairs += result[i];
                pairs += 'X'; // thêm X nếu số ký tự lẻ
            }
        }
        return pairs;
    }

    string encrypt(string text) {
        string pairs = preparePlaintext(text);
        string result = "";
        
        for(int i = 0; i < pairs.length(); i += 2) {
            char c1 = pairs[i];
            char c2 = pairs[i+1];
            
            int r1, col1, r2, col2;
            findPos(c1, r1, col1);
            findPos(c2, r2, col2);
            
            // Quy tắc 1: Cùng hàng → thay bằng ký tự bên phải
            if(r1 == r2) {
                result += matrix[r1][(col1 + 1) % 5];
                result += matrix[r2][(col2 + 1) % 5];
            }
            // Quy tắc 2: Cùng cột → thay bằng ký tự bên dưới
            else if(col1 == col2) {
                result += matrix[(r1 + 1) % 5][col1];
                result += matrix[(r2 + 1) % 5][col2];
            }
            // Quy tắc 3 & 4: Khác hàng khác cột → hoán đổi cột
            else {
                result += matrix[r1][col2];
                result += matrix[r2][col1];
            }
        }
        
        return result;
    }
};

int main() {
    string key = "MONARCHY";
    Playfair cipher(key);
    
    cout << "========== PLAYFAIR CIPHER ==========" << endl;
    cout << "Key: " << key << endl << endl;
    
    string plaintext = "Do you like to study a cryptography course";
    cout << "Plaintext:  " << plaintext << endl;
    
    string encrypted = cipher.encrypt(plaintext);
    cout << "Encrypted:  " << encrypted << endl;
    
    return 0;
}