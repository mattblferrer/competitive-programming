#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;
const string rank_map = "3456789TJQKA2";
const string suit_map = "CSHD";

ll char_to_rank(char c) {
    for (ll i = 0; i < rank_map.length(); i++) {
        if (rank_map[i] == c) return i;
    }
    return -1;
}

ll char_to_suit(char c) {
    for (ll i = 0; i < suit_map.length(); i++) {
        if (suit_map[i] == c) return i;
    }
    return -1;
}

void print_cards(vector<pll> cards) {
    for (ll i = 0; i < cards.size(); i++) {
        cout << rank_map[cards[i].first] << suit_map[cards[i].second] << " ";
    }
}

vector<ll> generate_bitmasks(ll a, ll b) {
    vector<ll> ans;
    for (ll i = 0; i < (1 << b); i++) {
        if (__builtin_popcountll(i) == a) ans.push_back(i);
    }
    return ans;
}

vector<pll> find_straight_flush(vector<pll> cards) {
    map<ll, vector<ll>> suits;
    for (ll i = 0; i < 7; i++) {
        suits[cards[i].second].push_back(cards[i].first);
    }
    for (const auto& pair: suits) {
        if (pair.second.size() >= 5) {
            vector<ll> ranks = pair.second;
            sort(ranks.begin(), ranks.end());
            for (ll start = ranks.size() - 5; start >= 0; start--) {
                bool straight = true;
                for (ll i = start; i < start + 4; i++) {
                    if (ranks[i] != ranks[i + 1] - 1) { 
                        straight = false; 
                        break; 
                    }
                }
                if (straight) {
                    vector<pll> out;
                    for (ll i = start; i < start + 5; i++) {
                        out.push_back({ranks[i], pair.first});
                    }
                    sort(out.begin(), out.end(),[](pll a, pll b) {
                        if (a.first == b.first) return a.second < b.second;
                        else return a.first < b.first;
                    });
                    return out;
                }
            }
        }
    }
    return {};
}

vector<pll> find_four_kind(vector<pll> cards) {
    map<ll, ll> ranks;
    for (ll i = 0; i < 7; i++) {
        ranks[cards[i].first]++;
    }
    vector<pll> out;
    for (const auto& pair: ranks) {
        if (pair.second == 4) {
            for (ll i = 0; i < 4; i++) {
                out.push_back({pair.first, i});
            }
            for (ll i = 6; i >= 0; i--) {
                if (cards[i].first != pair.first) {
                    out.push_back(cards[i]);
                }
                if (out.size() == 5) {
                    sort(out.begin(), out.end(),[](pll a, pll b) {
                        if (a.first == b.first) return a.second < b.second;
                        else return a.first < b.first;
                    });
                    return out;
                }
            }
        }
    }
    return {};
}

vector<pll> find_full_house(vector<pll> cards) {
    map<ll, vector<ll>> ranks;
    vector<ll> three, two;
    for (ll i = 0; i < 7; i++) {
        ranks[cards[i].first].push_back(cards[i].second);
    }
    for (const auto& pair: ranks) {
        if (pair.second.size() == 3) three.push_back(pair.first);
        if (pair.second.size() == 2) two.push_back(pair.first);
    }
    if (three.size() < 1) return {};
    sort(three.begin(), three.end());
    sort(two.begin(), two.end());
    vector<pll> out;
    if (three.size() == 2) {
        for (ll i = 0; i < 3; i++) {
            out.push_back({three[1], ranks[three[1]][i]});
        }
        for (ll i = 0; i < 2; i++) {
            out.push_back({three[0], ranks[three[0]][i]});
        }
    }
    if (three.size() == 1) {
        if (two.size() < 1) return {};
        for (ll i = 0; i < 3; i++) {
            out.push_back({three[0], ranks[three[0]][i]});
        }
        for (ll i = 0; i < 2; i++) {
            out.push_back({two.back(), ranks[two.back()][i]});
        }
    }
    sort(out.begin(), out.end(),[](pll a, pll b) {
        if (a.first == b.first) return a.second < b.second;
        else return a.first < b.first;
    });
    return out;
}

vector<pll> find_flush(vector<pll> cards) {
    map<ll, ll> suits;
    for (ll i = 0; i < 7; i++) {
        suits[cards[i].second]++;
    }
    vector<pll> out;
    for (const auto& pair: suits) {
        if (pair.second >= 5) {
            for (ll i = 6; i >= 0; i--) {
                if (cards[i].second == pair.first) {
                    out.push_back(cards[i]);
                }
                if (out.size() == 5) {
                    sort(out.begin(), out.end(),[](pll a, pll b) {
                        if (a.first == b.first) return a.second < b.second;
                        else return a.first < b.first;
                    });
                    return out;
                }
            }
        }
    }
    return {};
}

vector<pll> find_straight(vector<pll> cards) {
    set<ll> ranks;
    for (ll i = 0; i < 7; i++) {
        ranks.insert(cards[i].first);
    }
    vector<ll> ranks_vec;
    for (ll rank: ranks) {
        ranks_vec.push_back(rank);
    }
    if (ranks_vec.size() < 5) return {};
    for (ll start = ranks_vec.size() - 5; start >= 0; start--) {
        bool straight = true;
        for (ll i = start; i < start + 4; i++) {
            if (ranks_vec[i] != ranks_vec[i + 1] - 1) straight = false;
        }
        if (straight) { 
            vector<pll> out;
            for (ll i = start; i < start + 5; i++) {
                for (ll k = 6; k >= 0; k--) {
                    if (cards[k].first == ranks_vec[i]) {
                        out.push_back(cards[k]);
                        break;
                    }
                }
            }
            sort(out.begin(), out.end(),[](pll a, pll b) {
                if (a.first == b.first) return a.second < b.second;
                else return a.first < b.first;
            });
            return out;
        }
    } 
    return {};
}

vector<pll> find_three_kind(vector<pll> cards) { 
    map<ll, vector<ll>> ranks;
    vector<ll> threes;
    for (ll i = 0; i < 7; i++) {
        ranks[cards[i].first].push_back(cards[i].second);
    }
    for (const auto& pair: ranks) {
        if (pair.second.size() == 3) threes.push_back(pair.first);
    }
    if (threes.size() < 1) return {};

    vector<pll> out;
    for (const auto& pair: ranks) {
        if (pair.second.size() == 3) {
            for (ll i = 0; i < 3; i++) {
                out.push_back({pair.first, ranks[pair.first][i]});
            }
            for (ll i = 6; i >= 0; i--) {
                if (cards[i].first != pair.first) out.push_back(cards[i]);
                if (out.size() == 5) {
                    sort(out.begin(), out.end(),[](pll a, pll b) {
                        if (a.first == b.first) return a.second < b.second;
                        else return a.first < b.first;
                    });
                    return out;
                }
            }
        }
    }
    return {};
}

vector<pll> find_two_pair(vector<pll> cards) { 
    map<ll, vector<ll>> ranks;
    vector<ll> pairs;
    for (ll i = 0; i < 7; i++) {
        ranks[cards[i].first].push_back(cards[i].second);
    }
    for (const auto& pair: ranks) {
        if (pair.second.size() == 2) pairs.push_back(pair.first);
    }
    if (pairs.size() < 2) return {};

    sort(pairs.begin(), pairs.end(), greater<ll>());
    vector<pll> out;
    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j < 2; j++) {
            out.push_back({pairs[i], ranks[pairs[i]][j]});
        }
    }
    for (ll i = 6; i >= 0; i--) {
        if (count(out.begin(), out.end(), cards[i]) == 0) {
            out.push_back(cards[i]);
        }
        if (out.size() == 5) {
            sort(out.begin(), out.end(),[](pll a, pll b) {
                if (a.first == b.first) return a.second < b.second;
                else return a.first < b.first;
            });
            return out;
        }
    }
    return {};
}

vector<pll> find_one_pair(vector<pll> cards) { 
    map<ll, vector<ll>> ranks;
    vector<ll> pairs;
    for (ll i = 0; i < 7; i++) {
        ranks[cards[i].first].push_back(cards[i].second);
    }
    for (const auto& pair: ranks) {
        if (pair.second.size() == 2) pairs.push_back(pair.first);
    }
    if (pairs.size() < 1) return {};

    sort(pairs.begin(), pairs.end(), greater<ll>());
    vector<pll> out;
    for (ll i = 0; i < 1; i++) {
        for (ll j = 0; j < 2; j++) {
            out.push_back({pairs[i], ranks[pairs[i]][j]});
        }
    }

    ll ctr = 0;
    for (ll i = 6; i >= 0; i--) {
        if (count(out.begin(), out.end(), cards[i]) == 0) {
            out.push_back(cards[i]);
            ctr++;
        }
        if (ctr == 3) {
            sort(out.begin(), out.end(),[](pll a, pll b) {
                if (a.first == b.first) return a.second < b.second;
                else return a.first < b.first;
            });
            return out;
        }
    }
    return {};
}

bool tie_np_s_sf(pair<ll, vector<pll>> pair_a, pair<ll, vector<pll>> pair_b) {
    vector<pll> cards_a = pair_a.second, cards_b = pair_b.second;
    for (ll i = 4; i >= 0; i--) {
        ll val_a = cards_a[i].first * 4 + cards_a[i].second;
        ll val_b = cards_b[i].first * 4 + cards_b[i].second;
        if (val_a != val_b) return val_a < val_b;
    }
    return true;
}

bool tie_3_4_kind(pair<ll, vector<pll>> pair_a, pair<ll, vector<pll>> pair_b) {
    vector<pll> cards_a = pair_a.second, cards_b = pair_b.second;
    return cards_a[2].first < cards_b[2].first;
}

bool tie_flush(pair<ll, vector<pll>> pair_a, pair<ll, vector<pll>> pair_b) {
    vector<pll> cards_a = pair_a.second, cards_b = pair_b.second;
    if (cards_a[0].second != cards_b[0].second) return cards_a[0].second < cards_b[0].second;
    for (ll i = 4; i >= 0; i--) {
        if (cards_a[i].first != cards_b[i].first) return cards_a[i].first < cards_b[i].first;
    }
    return true;
}

bool tie_fh(pair<ll, vector<pll>> pair_a, pair<ll, vector<pll>> pair_b) {
    vector<pll> cards_a = pair_a.second, cards_b = pair_b.second;
    map<ll, vector<ll>> suits_a, suits_b;
    for (ll i = 0; i < 5; i++) {
        suits_a[cards_a[i].first].push_back(cards_a[i].second);
        suits_b[cards_b[i].first].push_back(cards_b[i].second);
    }
    ll three_a, two_a, three_b, two_b;
    for (const auto& pair: suits_a) {
        if (pair.second.size() == 3) three_a = pair.first;
        else two_a = pair.first;
    }
    for (const auto& pair: suits_b) {
        if (pair.second.size() == 3) three_b = pair.first;
        else two_b = pair.first;
    }
    if (three_a != three_b) return three_a < three_b;
    if (two_a != two_b) return two_a < two_b;
    for (ll i = 2; i >= 0; i--) {
        if (suits_a[three_a][i] != suits_b[three_b][i]) return suits_a[three_a][i] < suits_b[three_b][i];
    }
    for (ll i = 1; i >= 0; i--) {
        if (suits_a[two_a][i] != suits_b[two_b][i]) return suits_a[two_a][i] < suits_b[two_b][i];
    }
    return true;
}

pair<ll, vector<pll>> get_card_type(vector<pll> cards) {
    // check the type of hand for each card set
    ll type = 0;
    vector<pll> cards_temp, cards_top;
    for (ll i = 2; i < 7; i++) {
        cards_top.push_back(cards[i]);
    }
    cards_temp = find_one_pair(cards);
    if (cards_temp.size() > 0) {
        type = 1;
        cards_top = cards_temp;
    }
    cards_temp = find_two_pair(cards);
    if (cards_temp.size() > 0) {
        type = 2;
        cards_top = cards_temp;
    }
    cards_temp = find_three_kind(cards);
    if (cards_temp.size() > 0) {
        type = 3;
        cards_top = cards_temp;
    }
    cards_temp = find_straight(cards);
    if (cards_temp.size() > 0) {
        type = 4;
        cards_top = cards_temp;
    }
    cards_temp = find_flush(cards);
    if (cards_temp.size() > 0) {
        type = 5;
        cards_top = cards_temp;
    }
    cards_temp = find_full_house(cards);
    if (cards_temp.size() > 0) {
        type = 6;
        cards_top = cards_temp;
    }
    cards_temp = find_four_kind(cards);
    if (cards_temp.size() > 0) {
        type = 7;
        cards_top = cards_temp;
    }
    cards_temp = find_straight_flush(cards);
    if (cards_temp.size() > 0) {
        type = 8;
        cards_top = cards_temp;
    }
    return {type, cards_top};
}

void solve() {
    // take input cards as 2 char string
    vector<string> cardstr(11);
    for (ll i = 0; i < 11; i++) cin >> cardstr[i];

    // convert cards to numeric rank, suit ordering
    vector<pll> card_rank(11);
    for (ll i = 0; i < 11; i++) {
        card_rank[i] = {char_to_rank(cardstr[i][0]), char_to_suit(cardstr[i][1])};
    }

    // get possible cards of Vince
    vector<pll> available;
    for (ll i = 0; i < 13; i++) {
        for (ll j = 0; j < 4; j++) {
            bool found = false;
            pll test = {i, j};
            for (ll k = 0; k < 11; k++) {
                if (card_rank[k] == test) {
                    found = true;
                    break;
                }
            }
            if (!found) available.push_back({i, j});
        }
    }

    // generate two card combinations for Vince
    vector<pair<pll, pll>> vince_pairs;
    for (ll i = 0; i < 41; i++) {
        for (ll j = i + 1; j < 41; j++) {
            vince_pairs.push_back({available[i], available[j]});
        }
    }
    
    // get 7 card set for players 1, 2, 3
    vector<pll> river;
    for (ll i = 6; i < 11; i++) river.push_back(card_rank[i]);
    vector<pll> cards_p1 = river, cards_p2 = river, cards_p3 = river;
    for (ll i = 0; i < 2; i++) cards_p1.push_back(card_rank[i]);
    for (ll i = 2; i < 4; i++) cards_p2.push_back(card_rank[i]);
    for (ll i = 4; i < 6; i++) cards_p3.push_back(card_rank[i]);

    // iterate through all 7 card sets for Vince
    vector<vector<pll>> cards_vince;
    for (ll i = 0; i < vince_pairs.size(); i++) {
        vector<pll> curr_cards = river;
        curr_cards.push_back(vince_pairs[i].first);
        curr_cards.push_back(vince_pairs[i].second);

        // sort cards in correct order ascending
        sort(curr_cards.begin(), curr_cards.end(),[](pll a, pll b) {
            if (a.first == b.first) return a.second < b.second;
            else return a.first < b.first;
        });
        cards_vince.push_back(curr_cards);
    }

    // classify each possible 7 card set by type 
    map<ll, set<pair<ll, vector<pll>>>> card_types;
    ll type;
    vector<pll> cards;
    pair<ll, vector<pll>> pair_ret;
    pair_ret = get_card_type(cards_p1);
    type = pair_ret.first;
    cards = pair_ret.second;
    if (type > 0) card_types[type].insert({1, cards});
    pair_ret = get_card_type(cards_p2);
    type = pair_ret.first;
    cards = pair_ret.second;
    if (type > 0) card_types[type].insert({2, cards});
    pair_ret = get_card_type(cards_p3);
    type = pair_ret.first;
    cards = pair_ret.second;
    if (type > 0) card_types[type].insert({3, cards});
    for (ll i = 0; i < cards_vince.size(); i++) {
        pair_ret = get_card_type(cards_vince[i]);
        type = pair_ret.first;
        cards = pair_ret.second;
        if (type > 0) card_types[type].insert({4, cards});
    }

    // tiebreaks, if needed
    ll highest_type = 0;
    for (ll i = 0; i < 9; i++) {
        if (card_types[i].size() > 0) highest_type = i;
    }
    vector<pair<ll, vector<pll>>> winners;
    for (const auto& pair: card_types[highest_type]) {
        winners.push_back(pair);
    }
    if ((highest_type == 8) || (highest_type == 4)) {
        sort(winners.begin(), winners.end(), tie_np_s_sf);
    }
    else if ((highest_type == 7) || (highest_type == 3)) {
        sort(winners.begin(), winners.end(), tie_3_4_kind);
    }
    else if (highest_type == 6) {
        sort(winners.begin(), winners.end(), tie_fh);
    }
    else if (highest_type == 5) {
        sort(winners.begin(), winners.end(), tie_flush);
    }
    ll winner = winners.back().first;
    vector<pll> winner_cards = winners.back().second;
    if (winner == 4) cout << "PASS\n";
    else cout << "ALL IN\n";
    print_cards(winner_cards);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    
    solve();
    return 0;
}
