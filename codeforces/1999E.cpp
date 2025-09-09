#include <bits/stdc++.h>

std::vector<long long> pref(200001);

void comp() {
    long long test;
    for (int i = 1; i < 200001; i++) {
        test = i;
        pref[i] = pref[i - 1];
        while (test > 0) {
            test /= 3;
            pref[i]++;
        }
    }
}

long long problem1999E() {
    long long l, r;
    std::cin >> l >> r;

    long long ans = pref[r] + pref[l] - 2 * pref[l - 1];
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    comp();
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1999E() << "\n";
    }
    return 0;
}