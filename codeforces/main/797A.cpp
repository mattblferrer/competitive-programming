#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> factors;
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    int size = factors.size();
    if (size < k) {
        cout << "-1\n";
        return;
    }
    while (size > k) {
        int last = factors[size - 1];
        int sec = factors[size - 2];
        factors.pop_back();
        factors[size - 2] = last * sec;
        size--;
    }
    for (int f: factors) {
        cout << f << " ";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}