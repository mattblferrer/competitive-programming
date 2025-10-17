#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> perm = {3, 2, 2};
    int psum = 0, asum = 0;
    cout << "1 1 " << n << "\n" << flush;
    cin >> psum;
    cout << "2 1 " << n << "\n" << flush;
    cin >> asum;
    int length = asum - psum;

    int left = 0, right = n - length + 2;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        int psub, asub;
        cout << "1 " << mid << " " << n << "\n" << flush;
        cin >> psub;
        cout << "2 " << mid << " " << n << "\n" << flush;
        cin >> asub;
        int diff = asub - psub;

        if (diff < length) right = mid;
        else left = mid;
    }
    cout << "! " << left << " " << left + length - 1 << "\n" << flush;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}