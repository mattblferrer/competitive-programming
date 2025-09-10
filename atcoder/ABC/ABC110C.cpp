#include <bits/stdc++.h>

std::string ABC110C() {
    std::string s, t;
    std::cin >> s >> t;
    std::map<int, int> s_char, t_char;
    std::vector<int> s_count, t_count;
    for (char c: s) s_char[c]++;
    for (char c: t) t_char[c]++;
    for (const auto& pair: s_char) s_count.push_back(pair.second);
    for (const auto& pair: t_char) t_count.push_back(pair.second);
    std::sort(s_count.begin(), s_count.end());
    std::sort(t_count.begin(), t_count.end());
    for (int i = 0; i < s_count.size(); i++) {
        if (s_count[i] != t_count[i]) return "No";
    }
    return "Yes";
}   

int main() {
    std::cout << ABC110C();
    return 0;
}