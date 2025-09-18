#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n % 3 == 0) cout << "Fizz";
    if (n % 5 == 0) cout << "Buzz";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}