#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <climits>
#include <stack>
#include <queue>
#define int long long
using namespace std;

struct node{
    int cost, chosen;
};

bool comp(pair<int, int>&a, pair<int, int>&b){
    return a.first < b.first;
}

void solve(){
    int n, m; cin >> n >> m;
    int sum = 0;
    vector<node> delivery(n, {1, 1});
    for (auto &x: delivery) {
        cin >> x.cost;
        sum += x.cost;
    }
    vector<vector<node>> tmp(n, vector<node> (m));
    for (int j = 0; j < m; ++j){
        int minimal = INT_MAX;
        int id = 0;
        for (int i = 0; i < n; ++i){
            cin >> tmp[i][j].cost;
            if (tmp[i][j].cost < minimal){
                minimal = tmp[i][j].cost;
                id = i;
            }
        }
        sum += tmp[id][j].cost;
        tmp[id][j].chosen = true;
    }
    for (int q = 0; q <= 1000; ++q){
        vector<pair<int, int>> canditates;
        for (int i = 0; i < n; ++i){
            if (!delivery[i].chosen) continue;
            int nSum = sum;
            nSum -= delivery[i].cost;
            bool impossible = false;
            for (int j = 0; j < m; ++j){
                if (!tmp[i][j].chosen) continue;
                int id = 0;
                int minimal = INT_MAX;
                for (int ni = 0; ni < n; ++ni){
                    if (ni == i || !delivery[ni].chosen) continue;
                    if (tmp[ni][j].cost < minimal){
                        minimal = tmp[ni][j].cost;
                        id = ni;
                    }
                }
                if (minimal == INT_MAX) impossible = true;
                nSum -= tmp[i][j].cost;
                nSum += tmp[id][j].cost;
            }
            if (nSum >= sum || impossible) continue;
            canditates.push_back({nSum, i});
        }
        if (canditates.empty()) break;
        sort(canditates.begin(), canditates.end(), comp);
        int i = canditates[0].second;
        sum -= delivery[i].cost;
        delivery[i].chosen = false;
        for (int j = 0; j < m; ++j){
            if (!tmp[i][j].chosen) continue;
            int id = 0;
            int minimal = INT_MAX;
            for (int ni = 0; ni < n; ++ni){
                if (ni == i || !delivery[ni].chosen) continue;
                if (tmp[ni][j].cost < minimal){
                    minimal = tmp[ni][j].cost;
                    id = ni;
                }
            }
            sum -= tmp[i][j].cost;
            sum += tmp[id][j].cost;
            tmp[i][j].chosen = false;
            tmp[id][j].chosen = true;
        }
    }
    cout << sum << "\n";
    for (int j = 0; j < m; ++j){
        for (int i = 0; i < n; ++i){
            if (tmp[i][j].chosen) cout << i + 1 << " ";
        }
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
