#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> cnt(10);
    for (int i = 0; i < n; i++) cnt[a[i] % 10]++;
    for (int i = 0; i <= 9; i++) {
        cnt[i]--;
        for (int j = 0; j <= 9; j++) {
            cnt[j]--;
            for (int k = 0; k <= 9; k++) {
                cnt[k]--;
                if ((i + j + k) % 10 == 3 && cnt[i] >= 0 && cnt[j] >= 0 && cnt[k] >= 0) {
                    cout << "YES\n";
                    return;
                } 
                cnt[k]++;
            }
            cnt[j]++;
        }
        cnt[i]++;
    }
    cout << "NO\n";
    return;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}