#include <bits/stdc++.h>

void problemE() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    long long ans = 0;
    std::vector<std::vector<int>> pairs(26, std::vector<int>(26));  // all pairs of letters (i, j)
    std::vector<int> cnt(26);
    
    // iterate through all pairs of unique letters and see how many are present in s
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (i == j) continue;

            bool first = true;
            for (int k = 0; k < n; k++) {
                if (first && s[k] - 'a' == i) {
                    first = false;
                }
                else if (!first && s[k] - 'a' == j){
                    pairs[i][j]++;
                    first = true;
                }
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (pairs[i][j]) ans += pairs[i][j];
        }
    }
    std::cout << ans;
}

int main() {
    problemE();
    return 0;
}