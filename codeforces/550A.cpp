#include <bits/stdc++.h>

std::string problem550A() {
    std::string s;
    std::cin >> s;
    int ab_left, ba_left, ab_right, ba_right;
    bool ab_found = false, ba_found = false;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == 'A' && s[i + 1] == 'B') {
            if (ab_found == false) {
                ab_left = i;
                ab_found = true;
            }
            ab_right = i;
        }
        if (s[i] == 'B' && s[i + 1] == 'A') {
            if (ba_found == false) {
                ba_left = i;
                ba_found = true;
            }
            ba_right = i;
        }
    }
    if (ab_found && ba_found && ba_right - ab_left > 1) return "YES";
    if (ab_found && ba_found && ab_right - ba_left > 1) return "YES";
    return "NO";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem550A() << "\n";
    return 0;
}