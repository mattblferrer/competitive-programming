#include <iostream>

long long problem1669E() {
    long long n;
    std::cin >> n;
    std::string* s = new std::string[n];
    long long pairs = 0;
    long long** c = new long long*[11];
    for (int i = 0; i < 11; i++) {
        c[i] = new long long[11];
        for (int j = 0; j < 11; j++) {
            c[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        int pos_1 = s[i][0] - 'a';
        int pos_2 = s[i][1] - 'a';
        c[pos_1][pos_2]++;
    }

    for (int i = 0; i < n; i++) {
        int pos_1 = s[i][0] - 'a';
        int pos_2 = s[i][1] - 'a';
        for (int j = 0; j < 11; j++) {
            if (pos_1 != j) {
                pairs += c[j][pos_2];
            }
            if (pos_2 != j) {
                pairs += c[pos_1][j];
            }
        }
    }

    return pairs / 2;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1669E() << "\n";	
    }
    

    return 0;
}