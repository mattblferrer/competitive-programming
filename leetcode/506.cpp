class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> answer(n);
        map<int, int> ranks;
        for (int i = 0; i < n; i++) {
            ranks[score[i]] = i;
        }
        sort(score.begin(), score.end(), greater<int>());
        for (int i = 0; i < n; i++) {
            if (i == 0) answer[ranks[score[i]]] = "Gold Medal";
            else if (i == 1) answer[ranks[score[i]]] = "Silver Medal";
            else if (i == 2) answer[ranks[score[i]]] = "Bronze Medal";
            else answer[ranks[score[i]]] = to_string(i + 1);
        }
        return answer;
    }
};