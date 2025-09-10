#include <bits/stdc++.h>

std::string ABC211B() {
    std::string s_i;
    std::set<std::string> s;
    for (int i = 0; i < 4; i++) {
        std::cin >> s_i;
        s.insert(s_i);
    }
    if (s.size() == 4) return "Yes";
    return "No";
}

int main() { 
    std::cout << ABC211B();
    return 0;
}