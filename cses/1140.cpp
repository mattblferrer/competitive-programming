#include <bits/stdc++.h>

long long CSES1140() {
    int n, a_i, b_i, r_i;
    std::cin >> n;
    std::vector<std::vector<int>> proj(n + 1); 
    proj[0] = {0, 0, 0};
    for (int i = 1; i <= n; i++) {
        std::cin >> a_i >> b_i >> r_i;
        proj[i] = {a_i, b_i, r_i};
    }
    std::sort(proj.begin(), proj.end(), 
        [](std::vector<int> a, std::vector<int> b) {
            return a[1] < b[1];
        });
    std::vector<int> b_vec(n + 1);  // arr of finish times for binary search
    for (int i = 0; i <= n; i++) {
        b_vec[i] = proj[i][1];
    }
    std::vector<long long> p(n + 1);  // index of last non-overlapping interval with i
    for (int i = 1; i <= n; i++) {
        p[i] = std::distance(b_vec.begin(), 
            std::lower_bound(b_vec.begin(), b_vec.end(), proj[i][0])) - 1;
    }
    std::vector<long long> m(n + 1);  // optimal solution over interval 0 to n
    for (int i = 1; i <= n; i++) {
        m[i] = std::max(proj[i][2] + m[p[i]], m[i - 1]);
    }
    return m[n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1140() << "\n";
    return 0;
}