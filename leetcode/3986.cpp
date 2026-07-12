class Solution {
public:
    int secondsBetweenTimes(string startTime, string endTime) {
        int start_seconds = stoi(startTime.substr(0, 2)) * 3600 + stoi(startTime.substr(3, 2)) * 60 + stoi(startTime.substr(6, 2));
        int end_seconds = stoi(endTime.substr(0, 2)) * 3600 + stoi(endTime.substr(3, 2)) * 60 + stoi(endTime.substr(6, 2));
        return end_seconds - start_seconds;
    }
};