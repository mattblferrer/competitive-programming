#include <bits/stdc++.h>

std::string problem2094D() {
    std::string p, s;
    std::cin >> p >> s;
    if (p[0] != s[0]) return "NO";
    std::vector<int> run_p, run_s;
    int run = 0;
    char curr = p[0];
    for (const char c: p) {
        if (c == curr) run++;
        else {
            run_p.push_back(run);
            run = 1;
            curr = c;
        }
    }
    run_p.push_back(run);
    run = 0;
    curr = s[0];
    for (const char c: s) {
        if (c == curr) run++;
        else {
            run_s.push_back(run);
            run = 1;
            curr = c;
        }
    }
    run_s.push_back(run);
    if (run_p.size() != run_s.size()) return "NO";
    for (int i = 0; i < run_p.size(); i++) {
        if (run_p[i] > run_s[i]) return "NO";
        if (run_p[i] * 2 < run_s[i]) return "NO";
    }
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2094D() << "\n";
    }
    return 0;
}