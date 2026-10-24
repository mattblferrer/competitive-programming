#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n), temp(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<pair<int, int>> record;
    auto move = [&](int from, int to)
        {
            if (from + 3 > n || to + 3 > n) return;
            for (int i = 0; i < n; i++) temp[i] = -1;
            for (int i = 0; i < 3; i++)
            {
                temp[to + i] = a[from + i];
                a[from + i] = -1;
            }

            int a_idx = 0;
            for (int i = 0; i < n; i++)
            {
                if (temp[i] != -1) continue;
                while (a[a_idx] == -1) a_idx++;
                if (a_idx == n) break;
                temp[i] = a[a_idx]; a_idx++;
            }
            for (int i = 0; i < n; i++) a[i] = temp[i];
            record.push_back({from, to});
        };

    int check_region_end = n;
    int target = n;
    for (int i = 0; i < n; i++)
    {
        if (check_region_end < 5) break;
        int target_idx;
        for (int j = 0; j < check_region_end; j++)
        {
            if (a[j] == target)
            {
                target_idx = j;
                break;
            }
        }

        if (target_idx == 0)
        {
            move(0, 2);
            move(0, check_region_end - 3);
        }
        else if (target_idx == 1)
        {
            move(1, 2);
            move(0, check_region_end - 3);
        }
        else if (target_idx == check_region_end - 1)
        {

        }
        else
        {
            move(target_idx - 2, check_region_end - 3);
        }
        check_region_end--;
        target--;
    }

    // handle 4
    int four_loc = 0;
    for (int i = 0; i < 4; i++)
    {
        if (a[i] == 4) four_loc = i;
    }
    for (int i = 0; i < 4 - 1 - four_loc; i++)
    {
        move(0, 1);
    }

    auto flip = [&]()
        {
            move(0, 2);
            move(0, 1);
            move(0, 2);
        };

    auto left_shift = [&]()
        {
            move(1, 2);
            move(1, 2);
            move(0, 2);
        };

    // last stretch
    if (a[0] == 1 && a[1] == 2 && a[2] == 3)
    {

    }
    if (a[0] == 1 && a[1] == 3 && a[2] == 2)
    {
        flip();
    }
    if (a[0] == 2 && a[1] == 1 && a[2] == 3)
    {
        flip();
        left_shift();
        left_shift();
    }
    if (a[0] == 2 && a[1] == 3 && a[2] == 1)
    {
        left_shift();
        left_shift();
    }
    if (a[0] == 3 && a[1] == 1 && a[2] == 2)
    {
        left_shift();
    }
    if (a[0] == 3 && a[1] == 2 && a[2] == 1)
    {
        flip();
        left_shift();
    }

    cout << record.size() << "\n";
    for (pair<int, int> move : record) cout << move.first + 1 << " " << move.second + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}