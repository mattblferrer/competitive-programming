class Solution {
public:
    bool isRectangleCover(vector<vector<int>> &rectangles) {
        set<pair<int, int>> points;
        long long area = 0;
        long long minx = 1'000'000'000, maxx = -1'000'000'000;
        long long miny = 1'000'000'000, maxy = -1'000'000'000;

        for (int i = 0; i < rectangles.size(); i++) {
            vector<int> &rect = rectangles[i];
            vector<pair<int, int>> rect_pts(4);
            rect_pts[0] = {rect[0], rect[1]};
            rect_pts[1] = {rect[2], rect[1]};
            rect_pts[2] = {rect[0], rect[3]};
            rect_pts[3] = {rect[2], rect[3]};
            area += (long long)(rect[2] - rect[0]) * (rect[3] - rect[1]);
            minx = min(minx, (long long)rect[0]);
            miny = min(miny, (long long)rect[1]);
            maxx = max(maxx, (long long)rect[2]);
            maxy = max(maxy, (long long)rect[3]);

            for (auto pt : rect_pts) {
                if (points.count(pt)) points.erase(pt);
                else points.insert(pt);
            }
        }
        long long expected = (maxx - minx) * (maxy - miny);
        if (points.size() != 4) return false;
        if (area != expected) return false;

        vector<pair<int, int>> bounds = {{minx, miny}, {maxx, miny}, {minx, maxy}, {maxx, maxy}};
        for (pair<int, int> pt : bounds) {
            if (points.count(pt) == 0) return false;
        }
        return true;
    }
};