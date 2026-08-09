class Solution {
public:
    long long weightedSum(vector<int> &parent, vector<int> &nums) {
        int n = parent.size();
        vector<int> d(n, -1);
        d[0] = 1;
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[i].push_back(parent[i]);
            adj[parent[i]].push_back(i);
        }

        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (d[v] != -1) continue;
                q.push(v);
                d[v] = d[u] + 1;
            }
        }
        int h = 0;
        for (int i = 0; i < n; i++) h = max(h, d[i]);
        long long ans = 0;
        for (int i = 0; i < n; i++) ans += (long long)nums[i] * (h - d[i] + 1);
        return ans;
    }
};