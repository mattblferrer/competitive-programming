#include <bits/stdc++.h>

const long long INF = 2e18;
long long fs;  // flow size
std::vector<std::set<long long>> adj;  // adjacency of every vertex i
std::vector<std::vector<long long>> capacity;  // residual capacity
std::vector<std::vector<long long>> fg;  // flow graph (actual)

long long bfs(long long s, long long t, std::vector<long long>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    std::queue<std::pair<long long, long long>> q;
    q.push({s, INF});

    while (!q.empty()) { 
        long long curr = q.front().first, flow = q.front().second;
        q.pop();
        for (long long next: adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next]) {
                parent[next] = curr;
                long long new_flow = std::min(flow, capacity[curr][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

long long max_flow(long long s, long long t) {
    long long flow = 0, new_flow;
    std::vector<long long> parent(fs);

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        long long curr = t;
        while (curr != s) {
            long long prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            fg[prev][curr] += new_flow;
            fg[curr][prev] -= new_flow;
            curr = prev;
        }
    }
    return flow;
}

int main() {
    adj.resize(fs);
    capacity.resize(fs, std::vector<long long>(fs));
    fg.resize(fs, std::vector<long long>(fs));

    return 0;
}
