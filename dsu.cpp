#include <bits/stdc++.h>

std::vector<int> parent;
std::vector<int> size;

void make_set(int a) {
    parent[a] = a;
    size[a] = 1;
}

int find_set(int a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (size[a] < size[b]) std::swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
}

bool is_connected(int a, int b) {
    return find_set(a) == find_set(b);
}
