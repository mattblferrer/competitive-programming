#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::vector<long long> parent;
std::vector<long long> size;
std::vector<long long> amt;

void make_set(long long a) {
    parent[a] = a;
    size[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (parent[a] < parent[b]) std::swap(a, b);
    parent[b] = a;
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

struct thing
{
    ll val;
    ll idx;
};

void problem105562F() {
    // input + make components of size 1
    ll n, q;
    std::cin >> n >> q;
    parent.resize(n + 1);
    size.resize(n + 1);
    amt.resize(n + 1);
    for (ll i = 1; i <= n; i++) {
        make_set(i);
    }
    std::vector<ll> c(n + 1);
    for (ll i = 1; i <= n; i++) {
        std::cin >> c[i];
    }

     // find index of nearest larger value
    std::vector<int> l_idx(n + 1);
    std::deque<thing> things;
    for (ll i = n; i > 0; i--)
    {
        while (!things.empty() && c[i] > things.front().val) things.pop_front();
        if (!things.empty() && things.front().val > l_idx[i]) 
            l_idx[i] = things.front().idx;
        else l_idx[i] = -1;
        things.push_front({c[i], i});
    }
    for (ll i = 1; i <= q; i++) {
        char t;
        ll l, x;
        std::cin >> t;
        if (t == '+') {
            std::cin >> l >> x;
            l = find_set(l);
            amt[l] += x;
            while (amt[l] > c[l]) {
                ll over = amt[l] - c[l];
                amt[l] = c[l];
                if (l_idx[l] == -1) continue;
                union_sets(l, l_idx[l]);
                l = find_set(l);
                amt[l] += over;
            }
        } 
        else if (t == '?') {
            std::cin >> l;
            std::cout << amt[l] << "\n"; 
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem105562F();
    return 0;
}