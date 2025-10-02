#include <bits/stdc++.h>
using namespace std;

std::vector<long long> parent;
std::vector<long long> sz;

void make_set(long long a) {
    parent[a] = a;
    sz[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) std::swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) make_set(i);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isConnected[i][j]) union_sets(i, j);
            }
        }
        set<int> provinces;
        for (int i = 0; i < n; i++) {
            provinces.insert(find_set(i));
        }
        return provinces.size();
    }
};