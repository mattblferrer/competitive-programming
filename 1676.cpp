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

void CSES1676() {
    int n, m, a, b;
    std::cin >> n >> m;
    parent.resize(n + 1);
    size.resize(n + 1);
    int max_size = 1;
    int components = n;
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b;
        if (union_sets(a, b)) components--;
        max_size = std::max({max_size, size[find_set(a)], size[find_set(b)]});
        std::cout << components << " " << max_size << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1676();
    return 0;
}