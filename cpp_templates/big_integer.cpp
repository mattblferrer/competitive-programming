#include <bits/stdc++.h>

class BigInt {
    public:
    std::string digits;
    bool sign = false;

    BigInt(long long a = 0) {
        if (a < 0) {
            sign = true;
            a = -a;
        }
        while (a > 0) {
            digits.push_back('0' + a % 10);
            a /= 10;
        }
    }
    BigInt(std::string& s) {
        digits = "";
        int n = s.size();
        for (int i = n - 1; i >= 0; i--) digits.push_back(s[i]);    
    }   
    BigInt(const char* s) {
        digits = "";
        int n = strlen(s);
        for (int i = n - 1; i >= 0; i--) digits.push_back(s[i]);    
    }   
    
    // TODO: addition and subtraction
    friend BigInt &operator+=(BigInt& a, const BigInt& b) {
        
    }
    friend BigInt &operator-=(BigInt& a, const BigInt& b) {
        
    }
    char &operator[](const int idx) {
        return digits[digits.size() - idx - 1];
    }
    friend std::istream &operator>>(std::istream& in, BigInt& a) {
        std::string s;
        in >> s;
        int n = s.size();
        if (s[0] == '-') {
            a.sign = true;
            s.erase(s.begin());
        }
        for (int i = n - 1; i >= 0; i--) a.digits.push_back(s[i]);
        return std::cin;
    }
    friend std::ostream &operator<<(std::ostream& out, const BigInt& a) {
        if (a.sign) std::cout << '-';
        int n = a.digits.size();
        for (int i = n - 1; i >= 0; i--) {
            std::cout << a.digits[i];
        }
        return std::cout;
    }
};

int main() {
    BigInt a(-32159120512);
    std::cout << a;
}