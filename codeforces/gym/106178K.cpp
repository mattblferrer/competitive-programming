#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct point
{
    ll x;
    ll y;
};

bool x_comp(const point &lhs, const point &rhs)
{
    return lhs.x < rhs.x;
}

bool y_comp(const point &lhs, const point &rhs)
{
    return lhs.y < rhs.y;
}
vector<pair<int, int>> directions = {{1, -1},{1, 1},{-1, -1},{-1, 1},{1, 0},{0, 1},{-1, 0},{0, -1}};

void solve() {
    int n, k; cin >> n >> k;
    vector<point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    if (n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    sort(points.begin(), points.end(), x_comp);
    ll min_x, max_x, min_y, max_y;
    min_x = points.front().x; max_x = points.back().x;
    sort(points.begin(), points.end(), y_comp);
    min_y = points.front().y; max_y = points.back().y;

    ll cur_height = (max_y - min_y + 1);
    ll cur_width = (max_x - min_x + 1);
    ll cur_area = cur_height * cur_width;
    ll ans = cur_area;
    for (int i = 0; i < n; i++)
    {
        for (auto [x_sign, y_sign] : directions)
        {
            ll cur_x = points[i].x;
            ll cur_y = points[i].y;
            cur_x += k * (x_sign);
            cur_y += k * (y_sign);

            ll temp_max_x, temp_max_y, temp_min_x, temp_min_y;
            temp_max_x = max(cur_x, max_x);
            temp_max_y = max(cur_y, max_y);
            temp_min_x = min(cur_x, min_x);
            temp_min_y = min(cur_y, min_y);
            ll temp_width = (temp_max_x - temp_min_x + 1);
            ll temp_height = (temp_max_y - temp_min_y + 1);
            ll temp_area = temp_width * temp_height;
            ans = max(ans, temp_area);
        }
    }

    for (int i = 0; i <= k; i++)
    {
        ll row_delta = i;
        ll column_delta = k - i;
        ll new_h = row_delta + cur_height;
        ll new_w = column_delta + cur_width;
        ll new_area = new_h * new_w;
        ans = max(ans, new_area);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}