#include <bits/stdc++.h>

class BigInt {
    public:
    std::vector<signed char> d;  // digits

    BigInt(long long a = 0) {
        while (a > 0) {
            d.push_back(a % 10);
            a /= 10;
        }
    }
    BigInt(std::string& s) {
        std::vector<signed char> d;
        int n = s.size();
        for (int i = n - 1; i >= 0; i--) d.push_back(s[i] - '0');    
    }   
    BigInt(const char* s) {
        std::vector<signed char> d;
        int n = strlen(s);
        for (int i = n - 1; i >= 0; i--) d.push_back(s[i] - '0');    
    }   
    int size() const {
        return d.size();
    }
    
    friend BigInt &operator+=(BigInt& a, const BigInt& b) {
        int n = std::max(a.size(), b.size());
        while (a.size() != n + 1) a.d.push_back(0);
        for (int i = 0; i < b.size(); i++) a.d[i] += b.d[i];
        for (int i = 0; i < n; i++) {
            if (a.d[i] > 9) {
                a.d[i] -= 10;
                a.d[i + 1]++;
            }
        }
        while (a.d.back() == 0) a.d.pop_back();
        return a;
    }
    friend BigInt &operator-=(BigInt& a, const BigInt& b) {
        int n = std::max(a.size(), b.size());
        for (int i = 0; i < b.size(); i++) a.d[i] -= b.d[i];
        for (int i = 0; i < n; i++) {
            if (a.d[i] < 0) {
                a.d[i] += 10;
                a.d[i + 1]--;
            }
        }
        while (a.d.back() == 0) a.d.pop_back();
        return a;
    }
    friend BigInt operator+(BigInt& a, const BigInt& b) {
        BigInt temp = a;
        temp += b;
        return temp;
    }
    friend BigInt operator-(BigInt& a, const BigInt& b) {
        BigInt temp = a;
        temp -= b;
        return temp;
    }
    char operator[](const int idx) const {
        return d[d.size() - idx - 1];
    }
    friend std::istream &operator>>(std::istream& in, BigInt& a) {
        std::string s;
        in >> s;
        int n = s.size();
        for (int i = n - 1; i >= 0; i--) a.d.push_back(s[i]);
        return std::cin;
    }
    friend std::ostream &operator<<(std::ostream& out, const BigInt& a) {
        int n = a.d.size();
        for (int i = n - 1; i >= 0; i--) {
            std::cout << (int)a.d[i];
        }
        return std::cout;
    }
};