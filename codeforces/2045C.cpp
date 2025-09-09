#include <bits/stdc++.h>

std::string problem2045C() {
    int INF = 9999999;
    std::string s, t;
    std::cin >> s >> t;
    std::vector<int> s_idx(26, -1), t_idx(26, -1);
    for (int i = 1; i < s.size(); i++) {  // leftmost s[i]
        if (s_idx[s[i] - 'a'] == -1) s_idx[s[i] - 'a'] = i;
    }
    for (int i = 0; i < t.size() - 1; i++) {  // rightmost t[i]
        t_idx[t[i] - 'a'] = i;
    }
    int min_st = INF, min_i = INF, min_j = INF;
    for (int i = 1; i < s.size(); i++) {
        int s_pos = s_idx[s[i] - 'a'];
        int t_pos = t_idx[s[i] - 'a'];
        if (min_st > s_pos - t_pos && t_pos != -1) {
            min_i = s_pos;
            min_j = t_pos;
            min_st = s_pos - t_pos;
        }
    }
    if (min_st == INF) return "-1";
    return s.substr(0, min_i) + t.substr(min_j, t.size() - min_j);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem2045C() << "\n";
    return 0;
}