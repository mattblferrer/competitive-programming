class Solution {
public:
    vector<string> subdomainVisits(vector<string> &cpdomains) {
        map<string, int> rep_map;
        for (int i = 0; i < cpdomains.size(); i++) {
            vector<string> d(4);
            int curr = 0;
            for (char c : cpdomains[i]) {
                if (c == '.' || c == ' ') curr++;
                else d[curr] += c;
            }
            string curr_domain = "";
            int rep = stoi(d[0]);
            for (int j = curr; j > 0; j--) {
                curr_domain = d[j] + curr_domain;
                rep_map[curr_domain] += rep;
                curr_domain = "." + curr_domain;
            }
        }
        vector<string> ans;
        for (auto pair : rep_map) {
            ans.push_back(to_string(pair.second) + " " + pair.first);
        }
        return ans;
    }
};