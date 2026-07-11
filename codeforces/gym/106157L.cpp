#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int R = 100;
const int K = 300;
ll dp[K][R];
ll dist[K][K];
void floyd_warshall(int V)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void solve() {
    // your solution here
    // code
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < R; r++)
        {
            dp[k][r] = LLONG_MAX;
        }
    }
    for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) dist[i][j] = LLONG_MAX;

    int pint_count;
    cin >> pint_count;
    vector<ll> pints(pint_count);
    for (int i = 0; i < pint_count; i++)
    {
        cin >> pints[i];
    }

    int pub_count;
    cin >> pub_count;
    vector<int> closing(pub_count);
    for (int i = 0; i < pub_count; i++)
    {
        cin >> closing[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int l, r; ll w;
        cin >> l >> r >> w;
        l--; r--;
        dist[l][r] = min(dist[l][r], w);
        dist[r][l] = min(dist[r][l], w);
    }

    floyd_warshall(pub_count);

    if (pints[0] <= closing[0]) dp[0][0] = pints[0];
    for (int cur_pub = 1; cur_pub < pub_count; cur_pub++)
    {
        if (dist[0][cur_pub] == LLONG_MAX) continue;
        ll second_glass = pints[0] + dist[0][cur_pub];
        if (second_glass <= closing[cur_pub]) dp[cur_pub][0] = pints[0] + dist[0][cur_pub];
    }

    for (int cur_pint = 0; cur_pint < pint_count - 1; cur_pint++)
    {
        for (int cur_pub = 0; cur_pub < pub_count; cur_pub++)
        {
            if (dp[cur_pub][cur_pint] == LLONG_MAX) continue;
            for (int next_pub = 0; next_pub < pub_count; next_pub++)
            {
                if (cur_pub == next_pub) continue;
                ll travel_time = dist[cur_pub][next_pub];
                if (dist[cur_pub][next_pub] == LLONG_MAX) continue;

                int next_pint = cur_pint + 1;
                ll second_glass = pints[next_pint] + travel_time + dp[cur_pub][cur_pint];
                if (second_glass <= closing[next_pub])
                {
                    dp[next_pub][next_pint] = min(dp[next_pub][next_pint], second_glass);
                }
            }
        }
    }

    ll ans = 0;
    for (ll pub = 0; pub < pub_count; pub++)
    {
        for (ll pint = 0; pint < pint_count; pint++)
        {
            if (dp[pub][pint] != LLONG_MAX) ans = max(pint, ans);
        }
    }
    cout << ans + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}