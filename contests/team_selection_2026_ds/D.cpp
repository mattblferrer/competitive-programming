#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using ll = long long;
using ld = long double;

using namespace __gnu_pbds;
template <typename T>
using index_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    index_set<pair<int, int>> cookies;
    map<int, int> curr_i;
    string c;
    while (cin >> c) {
        if (c == "#") {
            int idx;
            if (cookies.size() % 2 == 0) idx = (cookies.size() + 1) / 2 - 1;
            else idx = (cookies.size() / 2);

            pair<int, int> p = *cookies.find_by_order(idx);
            cout << p.first << "\n";
            cookies.erase(p);
        }
        else {
            int cn = stoi(c);
            cookies.insert({cn, curr_i[cn]});
            curr_i[cn]++;
        }
    }

    return 0;
}