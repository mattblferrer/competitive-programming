#include <bits/stdc++.h>

int n, m, q;
std::vector<int> a, b, c, d;

int search(int l, std::vector<int> A) {
    int low, score = 0;
    if (l == n) {
        for (int i = 0; i < q; i++) {
            if (A[b[i]] - A[a[i]] == c[i]) score += d[i];
        }
        return score;
    }
    if (A.size() == 0) low = 1;
    else low = A[A.size() - 1];
    for (int i = low; i <= m; i++) {
        A.push_back(i);
        score = std::max(score, search(l + 1, A));
        A.pop_back();
    }
    return score;
}

void ABC165C() {
    std::cin >> n >> m >> q;
    int a_i, b_i, c_i, d_i;
    for (int i = 0; i < q; i++) {
        std::cin >> a_i >> b_i >> c_i >> d_i;
        a.push_back(a_i - 1);
        b.push_back(b_i - 1);
        c.push_back(c_i);
        d.push_back(d_i);
    }
    std::vector<int> A;
    std::cout << search(0, A);
}

int main() {
    ABC165C();
    return 0;
}