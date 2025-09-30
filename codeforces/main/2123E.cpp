#include <bits/stdc++.h>

void problem2123E() {
    int n, mex;
    std::cin >> n;
    std::vector<int> a(n), cnt(n + 1);
    std::map<int, std::vector<int>> cnt_map;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = n; i >= 0; i--) {
        if (cnt[i] == 0) {
            mex = i;
        }
        else cnt_map[cnt[i]].push_back(i);
    }
    std::set<int> valid;
    valid.insert(mex);
    std::cout << valid.size() << " ";

    for (int k = 1; k <= n; k++) {
        auto it = valid.find(n - (k - 1));
        if (it != valid.end()) valid.erase(it);
        for (int e: cnt_map[k]) {
            if (e <= std::min(mex, n - k)) valid.insert(e);
        }
        std::cout << valid.size() << " ";
    }

    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2123E();
    }
    return 0;
}