#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

bool is_perfect(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum == 10;
}

void solve() {
    int k;
    cin >> k;
    int curr = 1, perf = 0;
    while (perf < k) {
        curr++;
        if (is_perfect(curr)) perf++;
    }
    cout << curr;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}