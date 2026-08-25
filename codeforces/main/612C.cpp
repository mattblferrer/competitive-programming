#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

bool is_open(char c) {
    string open = "<{[(", close = ">}])";
    for (char c2 : open) {
        if (c == c2) return true;
    }
    return false;
}

bool is_eq_bracket(char c1, char c2) {
    if (is_open(c2)) swap(c1, c2);
    return ((c1 == '<') && (c2 == '>')) || ((c1 == '{') && (c2 == '}'))
        || ((c1 == '[') && (c2 == ']')) || ((c1 == '(') && (c2 == ')'));
}

void solve() {
    string s;
    cin >> s;
    stack<char> st;

    ll ans = 0;
    for (char c : s) {
        if (st.empty()) {
            if (is_open(c)) st.push(c);
            else { cout << "Impossible\n"; return; }
        }
        else if (is_open(c)) {
            st.push(c);
        }
        else {
            if (!is_eq_bracket(c, st.top())) ans++;
            st.pop();
        }
    }
    if (!st.empty()) { cout << "Impossible\n"; return; }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}