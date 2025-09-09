#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct crane {
    ll x;
    ll y;
    ll h;
    ll i;
    ll j;
};

long double distance(ll x1, ll y1, ll x2, ll y2) {
    return sqrtl(abs(x2 - x1) * abs(x2 - x1) + abs(y2 - y1) * abs(y2 - y1));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, x, y, h;
    cin >> n;
    vector<crane> cranes(n);
    for (ll i = 0; i < n; i++) {
        cin >> x >> y >> h;
        cranes[i] = {x, y, h, i, h};
    }
    sort(cranes.begin(), cranes.end(), [](crane a, crane b) {
        return a.h > b.h;
    });
    for (ll i = 0; i < n; i++) {
        crane curr = cranes[i];
        ll jib = curr.h;
        for (ll j = 0; j < i; j++) {
            crane prev = cranes[j];
            jib = min((ll)floor(distance(curr.x, curr.y, prev.x, prev.y)), jib);
        }
        cranes[i].j = jib;
    }
    sort(cranes.begin(), cranes.end(), [](crane a, crane b) {
        return a.i < b.i;
    });
    for (ll i = 0; i < n; i++) {
        cout << cranes[i].j << "\n";
    }

    return 0;
}