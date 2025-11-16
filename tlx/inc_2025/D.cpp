#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

struct Dijkstra {
    int n;
    vector<bool> is_proc;
    vector<lng> dis;
    priority_queue<pair<lng,int>, vector<pair<lng,int>>, greater<pair<lng,int>>> unproc;

    Dijkstra(int n): n(n), is_proc(n+1, false) {
        dis.resize(n + 1, INF64);
    }

    void runDijkstra(const vector<int> &src, const vector<vector<int>> &adj) {
        fill(is_proc.begin(), is_proc.end(), false);
        fill(dis.begin(), dis.end(), INF64);
        priority_queue<pair<lng,int>, vector<pair<lng,int>>, greater<pair<lng,int>>> empty;
        unproc.swap(empty);

        for (int u : src) {
            dis[u] = 0;
            unproc.push({dis[u], u});
        }

        while (!unproc.empty()) {
            int cur = unproc.top().se;
            unproc.pop();

            if (is_proc[cur]) {
                continue;
            }
            is_proc[cur] = true;

            for (int nxt : adj[cur]) {
                if (dis[cur] + 1 < dis[nxt]) {
                    dis[nxt] = dis[cur] + 1;
                    unproc.push({dis[nxt], nxt});
                }
            }
        }
    }

    void runDijkstra(const vector<int> &src, const vector<vector<pair<int, lng>>> &adj) {
        fill(is_proc.begin(), is_proc.end(), false);
        fill(dis.begin(), dis.end(), INF64);
        priority_queue<pair<lng,int>, vector<pair<lng,int>>, greater<pair<lng,int>>> empty;
        unproc.swap(empty);

        for (int u : src) {
            dis[u] = 0;
            unproc.push({dis[u], u});
        }

        while (!unproc.empty()) {
            int cur = unproc.top().se;
            unproc.pop();

            if (is_proc[cur]) {
                continue;
            }
            is_proc[cur] = true;

            for (auto [nxt, w] : adj[cur]) {
                if (dis[cur] + w < dis[nxt]) {
                    dis[nxt] = dis[cur] + w;
                    unproc.push({dis[nxt], nxt});
                }
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, lng>>> adjl(n + 1), adjl_half(n + 1);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        adjl[u].pb({v, w});
        adjl[v].pb({u, w});
        adjl_half[u].pb({v, (w + 1) / 2});
        adjl_half[v].pb({u, (w + 1) / 2});
    }

    Dijkstra djk(n);

    vector<lng> from1, from2, from2_half, from3;
    djk.runDijkstra({1}, adjl);
    from1 = djk.dis;
    djk.runDijkstra({2}, adjl);
    from2 = djk.dis;
    djk.runDijkstra({2}, adjl_half);
    from2_half = djk.dis;
    djk.runDijkstra({3}, adjl);
    from3 = djk.dis;

    lng ans = INF64;
    for (int i = 1; i <= n; i++)
        ans = min(ans, from1[i] + from2[i] + from2_half[i] + from3[i]);

    cout << ans << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
