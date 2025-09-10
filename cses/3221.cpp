#include <bits/stdc++.h>

long long CSES3221() {
    long long n, k, x, a, b, c, ans;
    std::cin >> n >> k >> x >> a >> b >> c;
    long long x_i = x, x_prev;
    std::deque<long long> window;
    window.push_back(x_i);
    for (int i = 2; i <= k; i++) {
        x_i = (a * x_i + b) % c;
        if (window.empty() || window.back() < x_i) {
            window.push_back(x_i);
            continue;
        }
        while (!window.empty() && window.back() > x_i) {
            window.pop_back();
        }
        window.push_back(x_i);
    }
    ans = window.front();
    x_prev = x;
    for (int i = k + 1; i <= n; i++) {
        x_i = (a * x_i + b) % c;
        if (window.front() == x_prev) window.pop_front();
        x_prev = (a * x_prev + b) % c;
        if (window.empty() || window.back() < x_i) {
            window.push_back(x_i);
            ans ^= window.front();
            continue;
        }
        while (!window.empty() && window.back() > x_i) {
            window.pop_back();
        }
        window.push_back(x_i);
        ans ^= window.front();
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES3221() << "\n";
    return 0;
}