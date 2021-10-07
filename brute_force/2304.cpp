#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, L, H, ans = 0;
bool compare(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}
vector<pair<int, int>> v;

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> L >> H;
        v.emplace_back(L, H);
    } 
    sort(v.begin(), v.end(), compare);

    int left_l = v[0].first;
    int left_h = v[0].second;
    for(auto & info : v) {
        if(left_h <= info.second) {
            ans += (info.first - left_l) * left_h;
            left_l = info.first;
            left_h = info.second;
        }
    }
    int right_l = v.back().first;
    int right_h = v.back().second;
    for(int i = v.size()-1; i > -1; i--) {
        if(right_h < v[i].second) {
            ans += (right_l - v[i].first) * right_h;
            right_l = v[i].first;
            right_h = v[i].second;
        }
    }
    cout << ans + left_h;
}