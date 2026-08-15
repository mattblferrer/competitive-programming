#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve()
{
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    int t_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'T') t_cnt++;
    }

    deque<int> dead_tree_array;
    vector<bool> good_w(n, false);
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == 'T')
        {
            dead_tree_array.push_back(i);
        }
        else if (s[i] == 'W' && !dead_tree_array.empty())
        {
            good_w[i] = true;
            dead_tree_array.pop_back();
        }

        if (dead_tree_array.size() > m)
        {
            cout << -1;
            return;
        }
    }

    if (dead_tree_array.size() > 0)
    {
        cout << -1;
        return;
    }

    vector<int> needed_space(n, 0);
    deque<int> water_array;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'W' && good_w[i])
        {
            water_array.push_back('W');
        }
        else if (s[i] == 'T')
        {
            water_array.pop_back();
        }

        needed_space[i] = water_array.size();
    }

    for (int i = n - 2; i >= 0; i--)
    {
        needed_space[i] = max(needed_space[i], needed_space[i + 1]);
    }

    deque<int> true_array;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'O' && true_array.size() + 1 <= m - needed_space[i]) true_array.push_back(i);
    }
    cout << true_array.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}