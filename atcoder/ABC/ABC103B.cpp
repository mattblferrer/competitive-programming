#include <iostream>
#include <string>

std::string ABC103B() {
    std::string s, t;
    std::cin >> s >> t;
    s = s + s;
    for (int i = 0; i < t.length(); i++) {
        if (s.substr(i, t.length()) == t) {
            return "Yes";
        }
    }
    return "No";
}

int main() { 
    std::cout << ABC103B();
    return 0;
}