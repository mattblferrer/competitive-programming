#include <bits/stdc++.h>

std::vector<long long> parent;
std::vector<long long> size;

void make_set(long long a) {
    parent[a] = a;
    size[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (size[a] < size[b]) std::swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}
