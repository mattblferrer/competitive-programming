#include <cmath>
#include <iostream>
#include <map>
#include <string>

long long factorial(long long n) {
    int x = 1;
    for (int i = 1; i <= n; i++) {
        x *= i;
    }
    return x;
}

std::string problem2047B() {
    long long n, p, min_p;
    std::string s, new_s, min_s;
    std::cin >> n >> s;
    min_p = 10000000000;

    for (int i = 0; i < n; i++) {
        new_s = s;
        for (int j = 0; j < n; j++) {
            p = factorial(n);
            std::map<char, int> chars;
            new_s[i] = s[j];
            for (int k = 0; k < n; k++) {
                chars[new_s[k]]++; 
            }
            for (const auto& pair: chars) {
                p /= factorial(pair.second);
            }
            if (min_p > p) {
                min_p = p;
                min_s = new_s;
            }
        }   
    }

    return min_s;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2047B() << std::endl;
    }

    return 0;
}