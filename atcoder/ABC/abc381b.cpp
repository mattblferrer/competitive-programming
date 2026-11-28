#include <iostream>
#include <map>
#include <string>

std::string ABC381B() {
    std::string s;
    std::cin >> s;
    std::map<char, int> chars;
    
    if (s.length() % 2 != 0) {
        return "No";
    }
    for (int i = 0; i < s.length(); i++) {
        if (chars.count(s[i])) {
            chars[s[i]] += 1; 
        }
        else {
            chars[s[i]] = 1;
        }
        if (i % 2 == 1 && s[i] != s[i - 1]) {
            return "No";
        }
    }

    for (const auto& pair: chars) {
        if (pair.second != 2) {
            return "No";
        }
    }
    
    return "Yes";
}

int main() { 
    std::cout << ABC381B();
    return 0;
}