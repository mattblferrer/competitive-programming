#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
    tree_order_statistics_node_update> indexed_set;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<indexed_set> letters(26);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        letters[c - 'A'].insert(i);
    }
    for (int i = 0; i < q; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "SWAP") {
            int l, r;
            cin >> l >> r;
            l--; r--;
            if (s[l] == s[r]) continue;
            letters[s[l] - 'A'].erase(l);
            letters[s[l] - 'A'].insert(r);
            letters[s[r] - 'A'].erase(r);
            letters[s[r] - 'A'].insert(l);
            char temp = s[l];
            s[l] = s[r];
            s[r] = temp;
        }
        else if (cmd == "COUNT") {
            char x;
            int l, r;
            cin >> x >> l >> r;
            l--; r--;
            cout << letters[x - 'A'].order_of_key(r + 1) - letters[x - 'A'].order_of_key(l) << " ";
        }
    }
    cout << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}