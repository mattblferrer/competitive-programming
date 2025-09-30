#include <bits/stdc++.h>

void problem1999D() {
    std::string s, t;
    std::cin >> s >> t;
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '?') {
            if (j == t.size()) {
                s[i] = 'a';
            }
            else {
                s[i] = t[j];
                j++;
            }
        }
        else if (s[i] == t[j]) j++;
        
    }
    if (j == t.size()) {
        std::cout << "YES\n" << s << "\n";
        return;
    }
    std::cout << "NO\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1999D();
    }
    return 0;
}