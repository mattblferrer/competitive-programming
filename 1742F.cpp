#include <iostream>
#include <string>

void problem1742F() {
    long long q, d, k;
    std::string x;
    std::cin >> q;
    long long* s = new long long[26];
    long long* t = new long long[26]; 
    for (int i = 0; i < 26; i++) {
        s[i] = 0;
        t[i] = 0;
    }
    s[0] = t[0] = 1;

    for (long long i = 0; i < q; i++) {
        long long s_chars = 0;
        long long t_chars = 0;
        std::cin >> d >> k >> x;
        if (d == 1) {  // add to string s
            for (long long j = 0; j < x.length(); j++) {
                s[x[j] - 'a'] += k;
            }
        }
        if (d == 2) {  // add to string t
            for (long long j = 0; j < x.length(); j++) {
                t[x[j] - 'a'] += k;
            }
        }
        for (long long j = 0; j < 26; j++) {
            if (s[j]) {
                s_chars++;
            }
            if (t[j]) {
                t_chars++;
            }
        }
        if (t_chars != 1) {
            std::cout << "YES\n";
        }
        else if (s_chars != 1) {
            std::cout << "NO\n";
        }
        else if (s[0] >= t[0]) {
            std::cout << "NO\n";
        }
        else {
            std::cout << "YES\n";
        }
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1742F();
    }
    return 0;
}