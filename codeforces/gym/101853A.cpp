#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> a;
    set<int> unique;
    vector<int> a_arr(n);
    for (int i = 0; i < n; i++) {
        int a_i;
        cin >> a_i;
        if (a.count(a_i) == 0) unique.insert(a_i); 
        a[a_i]++;
        a_arr[i] = a_i;
    }
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) { 
            int p, v;
            cin >> p >> v;
            p--;
            a[a_arr[p]]--;
            a[v]++;
            if (a[a_arr[p]] == 0) unique.erase(a_arr[p]);
            unique.insert(v);
            a_arr[p] = v;
        }
        else {
            cout << unique.size() - unique.count(0) << "\n";
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}