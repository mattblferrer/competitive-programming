#include <bits/stdc++.h>
using namespace std;
using ll = long long;
enum type
{
    AB,
    A,
    B,
    O
};

struct plate
{
    ll start;
    ll type;
    ll pieces;
    ll cost;
    int mark;
};

bool operator<(const plate &lhs, const plate &rhs)
{
    return lhs.cost < rhs.cost;
}

type flags_to_type(bool can_a, bool can_b)
{
    if (can_a && can_b) return type::AB;
    if (can_a && !can_b) return type::A;
    if (!can_a && can_b) return type::B;
    return O;
}
void solve()
{
    int n, m, k, pa, pb;
    cin >> n >> m >> k >> pa >> pb; pa--; pb--;
    vector<ll> a_need(m), b_need(m), total_exist(m);
    for (int i = 0; i < m; i++) cin >> a_need[i];
    for (int i = 0; i < m; i++) cin >> b_need[i];
    vector<vector<plate>> plates(m);
    for (int i = 0; i < k; i++)
    {
        ll s, t, x, c; cin >> s >> t >> x >> c;
        s--; t--;
        plates[t].push_back({s, t, x, c});
        total_exist[t] += x;
    }

    for (int i = 0; i < m; i++) if (total_exist[i] < a_need[i] + b_need[i])
    {
        cout << "impossible";
        return;
    }
    for (int i = 0; i < m; i++) sort(plates[i].begin(), plates[i].end());

    auto check = [&](int time) -> pair<bool, ll>
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < plates[i].size(); j++)
                {
                    bool can_a = false;
                    bool can_b = false;
                    int raw_a_dist = pa - plates[i][j].start;
                    int raw_b_dist = pb - plates[i][j].start;
                    if (raw_a_dist < 0) raw_a_dist += n;
                    if (raw_b_dist < 0) raw_b_dist += n;
                    if (raw_a_dist <= time) can_a = true;
                    if (raw_b_dist <= time) can_b = true;
                    plates[i][j].mark = flags_to_type(can_a, can_b);
                }
            }


            for (int i = 0; i < m; i++)
            {
                ll forced_a, forced_b;
                forced_a = forced_b = 0;
                ll fluids = 0;
                for (int j = 0; j < plates[i].size(); j++)
                {
                    if (plates[i][j].mark == A) forced_a += plates[i][j].pieces;
                    else if (plates[i][j].mark == B) forced_b += plates[i][j].pieces;
                    else if (plates[i][j].mark == AB) fluids += plates[i][j].pieces;
                }
                ll free_spaces = max(0ll, a_need[i] - forced_a) + max(0ll, b_need[i] - forced_b);
                if (free_spaces > fluids) return {false, -1};
            }

            ll total_cost = 0;
            for (int i = 0; i < m; i++)
            {
                ll forced_a, forced_b;
                forced_a = forced_b = 0;
                ll fluids = 0;
                ll cur_cost = 0;
                for (int j = 0; j < plates[i].size(); j++)
                {
                    ll max_a_holes = a_need[i] - forced_a;
                    ll max_b_holes = b_need[i] - forced_b;
                    ll cur_holes = max_a_holes + max_b_holes - fluids;
                    ll cur_add = plates[i][j].pieces;
                    ll cur_plate_cost = plates[i][j].cost;
                    ll newly_added = 0;
                    if (plates[i][j].mark == A)
                    {
                        ll holes_to_be_filled = min(max_a_holes, cur_holes);
                        newly_added = min(cur_add, holes_to_be_filled);
                        forced_a += newly_added;
                    }
                    else if (plates[i][j].mark == B)
                    {
                        ll holes_to_be_filled = min(max_b_holes, cur_holes);
                        newly_added = min(cur_add, holes_to_be_filled);
                        forced_b += newly_added;
                    }
                    else if (plates[i][j].mark == AB)
                    {
                        newly_added = min(cur_add, cur_holes);
                        fluids += newly_added;
                    }
                    cur_cost += newly_added * cur_plate_cost;
                    if (fluids + forced_a + forced_b == a_need[i] + b_need[i]) break;
                }
                total_cost += cur_cost;
            }
            return {true, total_cost};
        };


    int l = -1;
    int r = n - 1;
    while (l + 1 < r)
    {
        int m = l + (r - l) / 2;
        auto [is_possible, _] = check(m);
        if (is_possible) r = m;
        else l = m;
    }

    auto [_, ans] = check(r);
    cout << r << " " << ans << "\n";

}
int main(void)
{
    solve();
    return 0;
}