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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) make_set(i);
        for (int i = 0; i < n; i++) {
            int a_i = edges[i][0] - 1, b_i = edges[i][1] - 1;
            bool valid = union_sets(a_i, b_i);
            if (!valid) return {a_i + 1, b_i + 1};
        }
        return {0};
    }
};