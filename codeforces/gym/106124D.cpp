#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct point
{
    ll x;
    ll y;
};

void solve()
{
    srand(time(0));
    int n; cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    deque<pair<int, int>> intervals;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    intervals.push_back({0, n - 1});
    deque<int> left_block;
    deque<int> middle_block;
    deque<int> right_block;
    auto dist = [&](int lhs, int rhs) -> ll
        {
            ll dx = points[order[rhs]].x - points[order[lhs]].x;
            ll dy = points[order[rhs]].y - points[order[lhs]].y;
            return dx * dx + dy * dy;
        };

    while (!intervals.empty())
    {
        int l = intervals.front().first;
        int r = intervals.front().second;
        intervals.pop_front();
        int size = r - l + 1;

        if (size <= 1) continue;
        if (l < 0 || l >= n) continue;
        if (r < 0 || r >= n) continue;
        if (l == 0 && r == n - 1)
        {
            int lsep = 0;
            int rsep = n - 1;
            for (int i = l; i <= r; i++)
            {
                if (i == lsep || i == rsep) continue;
                ll x_lsep = dist(i, lsep);
                ll x_rsep = dist(i, rsep);
                ll lsep_rsep = dist(lsep, rsep);
                ll max_dist = max({x_lsep, x_rsep, lsep_rsep});
                if (x_lsep == max_dist)
                {
                    right_block.push_back(order[i]);
                }
                else if (x_rsep == max_dist)
                {
                    left_block.push_back(order[i]);
                }
                else if (lsep_rsep == max_dist)
                {
                    middle_block.push_back(order[i]);
                }
            }

            int cur_idx = 0, lsep_idx, rsep_idx;
            while (!left_block.empty())
            {
                order[cur_idx] = left_block.back();
                left_block.pop_back();
                cur_idx++;
            }
            order[cur_idx] = lsep; lsep_idx = cur_idx; cur_idx++;
            while (!middle_block.empty())
            {
                order[cur_idx] = middle_block.back(); middle_block.pop_back(); cur_idx++;
            }
            order[cur_idx] = rsep; rsep_idx = cur_idx; cur_idx++;
            while (!right_block.empty())
            {
                order[cur_idx] = right_block.back(); right_block.pop_back(); cur_idx++;
            }

            intervals.push_back({l, lsep_idx - 1});
            intervals.push_back({lsep_idx + 1, rsep_idx - 1});
            intervals.push_back({rsep_idx + 1, r});
        }
        else
        {
            int sep_idx = rand() % size + l;
            int sep = order[sep_idx];
            if (l == 0)
            {
                ll sep_r = dist(sep_idx, r + 1);
                for (int i = l; i < r + 1; i++)
                {
                    if (i == sep_idx) continue;
                    ll i_r = dist(i, r + 1);
                    if (sep_r > i_r) right_block.push_back(order[i]);
                    else left_block.push_back(order[i]);
                }
            }
            else if (r == n - 1)
            {
                ll sep_l = dist(sep_idx, l - 1);
                for (int i = l; i < r + 1; i++)
                {
                    if (i == sep_idx) continue;
                    ll i_l = dist(i, l - 1);
                    if (sep_l > i_l) left_block.push_back(order[i]);
                    else right_block.push_back(order[i]);
                }
            }
            else
            {
                ll sep_r = dist(sep_idx, r + 1);
                ll sep_l = dist(sep_idx, l - 1);
                for (int i = l; i < r + 1; i++)
                {
                    if (i == sep_idx) continue;
                    ll i_l = dist(i, l - 1);
                    ll i_r = dist(i, r + 1);
                    ll i_sep = dist(i, sep_idx);

                    if (sep_l > i_l && sep_l > i_sep)
                    {
                        left_block.push_back(order[i]);
                    }
                    else right_block.push_back(order[i]);
                }
            }

            int cur_idx = l, new_sep_idx;
            while (!left_block.empty())
            {
                order[cur_idx] = left_block.back(); left_block.pop_back(); cur_idx++;
            }
            order[cur_idx] = sep; new_sep_idx = cur_idx; cur_idx++;
            while (!right_block.empty())
            {
                order[cur_idx] = right_block.back(); right_block.pop_back(); cur_idx++;
            }

            intervals.push_back({l, new_sep_idx - 1});
            intervals.push_back({new_sep_idx + 1, r});
        }
    }

    long double ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        ans += sqrtl(dist(i, i + 1));
    }
    cout << setprecision(20) << ans << "\n";
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    solve();
    return 0;
}