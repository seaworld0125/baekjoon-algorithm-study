#include <iostream>
#include <algorithm>
using namespace std;

int N;
int P[10001] = {0};     //카드 팩 가격
int dp[10001] = {0};

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i < N+1; i++){
        cin >> P[i];
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= i; j++){
            dp[i] = max(dp[i], dp[i - j] + P[j]);
            // cout << i << ", " << j << endl;
            // for(int k = 0; k <= N; k++){
            //     cout << dp[k] << ' ';
            // }cout << "\n";
        }
    }
    cout << dp[N] << endl;
}