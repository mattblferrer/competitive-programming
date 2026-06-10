class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int left = -1, right = n;
        while (right - left > 1) {
            int mid = midpoint(left, right);
            if (citations[mid] >= n - mid) right = mid;
            else left = mid;
        }
        return n - right;
    }
};