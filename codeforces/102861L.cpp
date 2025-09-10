#include <bits/stdc++.h>

int problem102861L() {
    int l, c, n;
    std::cin >> l >> c;
    std::vector<std::string> grid(l);
    for (int i = 0; i < l; i++) {
        std::cin >> grid[i];
    }
    std::cin >> n;
    std::vector<std::string> words(n);
    std::map<int, std::vector<std::map<char, int>>> charset;
    for (int i = 0; i < n; i++) {
        std::cin >> words[i];
        std::map<char, int> currcnt;
        for (char letter: words[i]) {
            currcnt[letter]++;
        }
        charset[words[i].size()].push_back(currcnt);
    }
    std::vector<std::vector<std::set<std::map<char, int>>>> valid(l, 
        std::vector<std::set<std::map<char, int>>>(c));

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            std::map<char, int> cnt;
            for (int k = 0; k <= l; k++) {  // vertical (downward)
                if (i + k >= l) break;
                cnt[grid[i + k][j]]++;
                for (std::map<char, int> currcnt: charset[k + 1]) {
                    int is_valid = 1;
                    for (const auto& pair: currcnt) {
                        if (cnt[pair.first] != pair.second) {
                            is_valid = 0;
                            break;
                        }
                    }
                    if (is_valid) {
                        for (int sq = 0; sq <= k; sq++) {
                            valid[i + sq][j].insert(currcnt);
                        }
                    }
                }
            }
            cnt.clear();
            for (int k = 0; k <= c; k++) {  // horizontal (rightward)
                if (j + k >= c) break;
                cnt[grid[i][j + k]]++;
                for (std::map<char, int> currcnt: charset[k + 1]) {
                    int is_valid = 1;
                    for (const auto& pair: currcnt) {
                        if (cnt[pair.first] != pair.second) {
                            is_valid = 0;
                            break;
                        }
                    }
                    if (is_valid) {
                        for (int sq = 0; sq <= k; sq++) {
                            valid[i][j + sq].insert(currcnt);
                        }
                    }
                }
            }
            cnt.clear();
            for (int k = 0; k <= std::max(l, c); k++) {  // diagonal (southeast)
                if (i + k >= l || j + k >= c) break;
                cnt[grid[i + k][j + k]]++;
                for (std::map<char, int> currcnt: charset[k + 1]) {
                    int is_valid = 1;
                    for (const auto& pair: currcnt) {
                        if (cnt[pair.first] != pair.second) {
                            is_valid = 0;
                            break;
                        }
                    }
                    if (is_valid) {
                        for (int sq = 0; sq <= k; sq++) {
                            valid[i + sq][j + sq].insert(currcnt);
                        }
                    }
                }
            }
            cnt.clear();
            for (int k = 0; k <= std::max(l, c); k++) {  // diagonal (southwest)
                if (i + k >= l || j - k < 0) break;
                cnt[grid[i + k][j - k]]++;
                for (std::map<char, int> currcnt: charset[k + 1]) {
                    int is_valid = 1;
                    for (const auto& pair: currcnt) {
                        if (cnt[pair.first] != pair.second) {
                            is_valid = 0;
                            break;
                        }
                    }
                    if (is_valid) {
                        for (int sq = 0; sq <= k; sq++) {
                            valid[i + sq][j - sq].insert(currcnt);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (valid[i][j].size() > 1) ans++;
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem102861L();
    return 0;
}