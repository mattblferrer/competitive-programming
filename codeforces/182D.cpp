#include <bits/stdc++.h>

int problem182D() {
    std::string s_1, s_2;
    std::cin >> s_1 >> s_2;
    std::set<int> max_div;
    int max_l = std::max(s_1.size(), s_2.size());
    int min_l = std::min(s_1.size(), s_2.size());
    for (int i = 1; i <= (int)sqrt(max_l); i++) {
        if (max_l % i == 0) {
            max_div.insert(i);
            max_div.insert(max_l / i);
        }
    }
    std::set<int> both_div;
    for (int d: max_div) {
        if (min_l % d == 0) {
            both_div.insert(d);
        }
    }
    int fac = 0;
    for (int d: both_div) {
        bool is_factor = true;
        std::string sub = s_1.substr(0, d);
        for (int i = 0; i < s_1.size(); i += d) {
            if (s_1.substr(i, d) != sub) {
                is_factor = false;
                break;
            }
        }
        if (!is_factor) continue;
        for (int i = 0; i < s_2.size(); i += d) {
            if (s_2.substr(i, d) != sub) {
                is_factor = false;
                break;
            }
        }
        if (is_factor) {
            fac++;
        }
    }
    return fac;
}

int main() {
    std::cout << problem182D();
    return 0;
}