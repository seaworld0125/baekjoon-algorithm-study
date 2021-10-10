#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N, K, w, v, dp[100001] = {0}; 
    cin >> N >> K;
    for(int i = 1; i <= N; i++){
        cin >> w >> v;
        for(int j = K; j >= 1; j--)
            if(j >= w) dp[j] = max(dp[j], dp[j-w] + v);
    }
    cout << dp[K];
}