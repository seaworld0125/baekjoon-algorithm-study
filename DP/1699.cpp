#include <iostream>
#include <algorithm>
using namespace std;

#define INF 1e9

int dp[1000001];

int main() {
    fill(dp, dp+1000001, INF);
    dp[1] = 1;
    
    int num;
    cin >> num;

    // 바텀업
    for(int i = 2; i <= num; i++) {
        for(int j = 1; j*j <= i; j++) {
            int remain = i - (j*j);

            if(!remain) dp[i] = 1;
            else dp[i] = min(dp[i], dp[j*j] + dp[remain]);
        }
    }
    cout << dp[num];
}