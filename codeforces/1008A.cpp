#include <iostream>
#include <string>

bool is_vowel(char c) {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    for (char v: vowels) {
        if (c == v) return true;
    }
    return false;
}

std::string problem1008A() {
    std::string s;
    std::cin >> s;
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'n') continue;
        if (!is_vowel(s[i])) {
            if (!is_vowel(s[i + 1])) {
                return "NO";
            }
        }
    }   
    return "YES";
}

int main() {
    std::cout << problem1008A();
    return 0;
}