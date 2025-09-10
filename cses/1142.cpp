#include <bits/stdc++.h>

long long CSES1142() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n + 1), left(n + 1), right(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::stack<long long> s_l, pos_l, s_r, pos_r;
    long long ans = 0;
    s_l.push(0);
    pos_l.push(0);
    for (int i = 1; i <= n; i++) {
        while (s_l.top() >= a[i]) {
            s_l.pop();
            pos_l.pop();
        }
        left[i] = pos_l.top() + 1;
        s_l.push(a[i]);
        pos_l.push(i);
    }
    s_r.push(0);
    pos_r.push(n + 1);
    for (int i = n; i > 0; i--) {
        while (s_r.top() >= a[i]) {
            s_r.pop();
            pos_r.pop();
        }
        right[i] = pos_r.top() - 1;
        s_r.push(a[i]);
        pos_r.push(i);
    }
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, a[i] * (right[i] - left[i] + 1));
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1142() << "\n";
    return 0;
}