#include <bits/stdc++.h>

std::string problem43B() {
    std::string s_1, s_2;
    std::getline(std::cin, s_1);
    std::getline(std::cin, s_2);
    int* c_1 = new int[256];
    int* c_2 = new int[256];
    for (int i = 0; i < 256; i++) {
        c_1[i] = 0;
        c_2[i] = 0;
    }
    for (char c: s_1) {
        c_1[c]++;
    }
    for (char c: s_2) {
        c_2[c]++;
    }
    for (char i = 'A'; i <= 'Z'; i++) {
        if (c_1[i] < c_2[i]) return "NO";
    }
    for (char i = 'a'; i <= 'z'; i++) {
        if (c_1[i] < c_2[i]) return "NO";
    }
    return "YES";
}

int main() {
    std::cout << problem43B();
    return 0;
}