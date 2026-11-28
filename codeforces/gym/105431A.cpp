#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve()
{
    ll xs, ys, xt, yt, xp, yp;
    cin >> xs >> ys >> xt >> yt >> xp >> yp;
    vector<pair<ll, ll>> points;
    bool up_s = false;
    bool up_t = false;
    if (yp <= ys) up_s = true;
    if (yp <= yt) up_t = true;

    if (up_s && up_t)
    {
        points.push_back({xs, 1e9});
        points.push_back({xt, 1e9});
    }
    else if (!up_s && up_t)
    {
        points.push_back({xs, -1e9});
        points.push_back({-1e9, -1e9});
        points.push_back({-1e9, 1e9});
        points.push_back({xt, 1e9});
    }
    else if (up_s && !up_t)
    {
        points.push_back({xs, 1e9});
        points.push_back({1e9, 1e9});
        points.push_back({1e9, -1e9});
        points.push_back({xt, -1e9});
    }
    else
    {
        points.push_back({xs, -1e9});
        points.push_back({xt, -1e9});
    }

    cout << points.size() << "\n";
    for (auto [x, y] : points)
    {
        cout << x << " " << y << "\n";
    }

}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}