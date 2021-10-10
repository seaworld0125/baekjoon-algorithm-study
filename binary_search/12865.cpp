#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<pair<int, int>> itemList;
int dp[105] = {0};

void printDp() {
    cout << "\n\nDP" << endl;
    for(int i = 0; i < N; i++) cout << dp[i] << "\t "; 
}

int main() {
    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        itemList.emplace_back(w, v);
    }
    // 아이템 가치 내림차순
    sort(itemList.begin(), itemList.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    for(int i = 0; i < N; i++) {
        int weight = itemList[i].first, value = itemList[i].second;
        for(int j = i+1; j < N; j++) {
            if(weight + itemList[j].first <= K) {
                weight += itemList[j].first;
                value += itemList[j].second;    
                if(value > dp[j]) dp[j] = value;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++) ans = max(ans, dp[i]);

    cout << ans;
    // printDp();
}