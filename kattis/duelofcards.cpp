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
    vector<int> a(2*n);
    for (int i = 0; i < n; i++) {
        int card;
        cin >> card;
        card--;
        a[card] = 1;
    }
    int minp = n, maxp = 0;
    vector<bool> smin(2*n), smax(2*n);
    for (int i = 0; i < 2*n; i++) {
        if (a[i] == 1) {
            smin[i] = smax[i] = true;
            for (int j = i + 1; j < 2*n; j++) {
                if ((!a[j]) && (!smin[j])) {
                    smin[j] = true;
                    minp--;
                    break;
                }
            }
            for (int j = i - 1; j >= 0; j--) {
                if ((!a[j]) && (!smax[j])) {
                    smax[j] = true;
                    maxp++;
                    break;
                }
            }
        }
    }
    cout << minp << " " << maxp;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}