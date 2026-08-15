#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;
struct point
{
    int x;
    int y;
};

bool operator==(const point &lhs, const point &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
};

bool operator<(const point &lhs, const point &rhs)
{
    return lhs.x < rhs.x;
}

void solve()
{
    int point_count;
    cin >> point_count;

    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ll area = (abs(x2 - x1) + 1) * (abs(y1 - y2) + 1);
    vector<point> points_temp(point_count);
    for (int i = 0; i < point_count; i++)
    {
        cin >> points_temp[i].x >> points_temp[i].y;
    }

    sort(points_temp.begin(), points_temp.end());
    vector<point> points;
    for (int i = 0; i < points_temp.size(); i++)
    {
        if (points.empty() || !(points.back() == points_temp[i]))
        {
            points.push_back(points_temp[i]);
        }
    }

    ll points_within = 0;
    for (int i = 0; i < points.size(); i++)
    {
        if (x1 <= points[i].x && points[i].x <= x2 && y2 <= points[i].y && points[i].y <= y1)
        {
            points_within++;
        }
    }

    if (points_within > 0)
    {
        cout << area - points_within;
        return;
    }

    // review
    ll min_take = y2 - 1;
    for (int i = 0; i < points.size(); i++)
    {
        point cur_point = points[i];
        if (cur_point.x <= x1 && cur_point.y <= y2)
        {
            min_take = min(min_take, abs(x1 - cur_point.x) + abs(y2 - cur_point.y) - 1);
        }
        else if (cur_point.x >= x2 && cur_point.y <= y2)
        {
            min_take = min(min_take, abs(x2 - cur_point.x) + abs(y2 - cur_point.y) - 1);
        }
        else if (cur_point.x >= x2 && cur_point.y >= y1)
        {
            min_take = min(min_take, abs(x2 - cur_point.x) + abs(y1 - cur_point.y) - 1);
        }
        else if (cur_point.x <= x1 && cur_point.y >= y1)
        {
            min_take = min(min_take, abs(x1 - cur_point.x) + abs(y1 - cur_point.y) - 1);
        }
        else
        {
            if (x1 <= cur_point.x && cur_point.x <= x2)
            {
                min_take = min({min_take, abs(cur_point.y - y1), abs(cur_point.y - y2) - 1});
            }
            else
            {
                min_take = min({min_take, abs(cur_point.x - x1), abs(cur_point.y - y2) - 1});
            }
        }
    }
    cout << min_take + area;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}