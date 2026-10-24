#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
struct trip
{
    int start;
    int end;
    int idx;
    int person;
    int value;
};

struct fragment
{
    int idx;
    bool is_start;
    int value;
};

bool operator<(const trip &lhs, const trip &rhs)
{
    return lhs.start < rhs.start;
}
bool operator<(const fragment &lhs, const fragment &rhs)
{
    return lhs.value < rhs.value;
}
void solve()
{
    int n, k, q; cin >> n >> k >> q;
    vector<trip> trips;
    for (int i = 0; i < q; i++)
    {
        int p, l, r; cin >> p >> l >> r; p--;
        trip cur_trip = {l, r, i, p, 0};
        trips.push_back(cur_trip);
    }

    vector<fragment> compressor;
    for (trip t : trips)
    {
        auto [l, r, i, person, value] = t;
        compressor.push_back({i, true, l});
        compressor.push_back({i, false, r});
    }

    sort(compressor.begin(), compressor.end());
    int rep = compressor.front().value;
    int cur_idx = 0;
    for (int i = 0; i < compressor.size(); i++)
    {
        auto [idx, is_start, value] = compressor[i];
        if (value != rep)
        {
            cur_idx++; rep = value;
        }

        if (is_start) trips[idx].start = cur_idx;
        else trips[idx].end = cur_idx;
    }

    vector<int> difference_array(cur_idx + 5, 0);
    difference_array[0] = n;
    for (trip t : trips)
    {
        auto [l, r, i, person, value] = t;
        difference_array[l] += -1;
        difference_array[r + 1] += 1;
    }

    for (int i = 1; i < difference_array.size(); i++) difference_array[i] += difference_array[i - 1];

    vector<int> supposed_ans(q, 0);
    for (int i = 0; i < q; i++)
    {
        if (difference_array[trips[i].end] > 0) supposed_ans[i] = 0;
        else supposed_ans[i] = 1;
    }

    vector<int> key_da(cur_idx + 5, 0);
    for (int i = 0; i < q; i++)
    {
        if (supposed_ans[i] == 1)
        {
            key_da[trips[i].start] += 1;
            key_da[trips[i].end + 1] += -1;
        }
    }

    for (int i = 1; i < key_da.size(); i++) key_da[i] += key_da[i - 1];
    for (int i = 0; i < key_da.size(); i++)
    {
        if (key_da[i] > k)
        {
            cout << "impossible";
            return;
        }
    }

    for (int i : supposed_ans) cout << i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}