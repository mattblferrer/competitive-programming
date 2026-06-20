class Solution {
public:
    vector<vector<long long>> adj;
    vector<long long> time;
    vector<bool> seen;

    void helper(long long n, vector<vector<int>> &edges, vector<int> &baseTime) {
        seen[n] = true;
        long long earliest = LLONG_MAX, latest = -1, ownDuration = 0;
        for (int i = 0; i < adj[n].size(); i++) {
            long long v = adj[n][i];
            if (!seen[v]) {
                helper(v, edges, baseTime);
                earliest = min(earliest, time[v]);
                latest = max(latest, time[v]);
            }
        }
        if (latest == -1) time[n] = baseTime[n];
        else {
            ownDuration = (latest - earliest) + baseTime[n];
            time[n] = latest + ownDuration;
        }
    }

    long long finishTime(int n, vector<vector<int>> &edges, vector<int> &baseTime) {
        adj.resize(n);
        time.resize(n);
        seen.resize(n);
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        helper(0, edges, baseTime);
        return time[0];
    }
}