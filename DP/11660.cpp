#include <iostream>
using namespace std;

int N, M, x1, y1, x2, y2;
int arr[1025][1025] = {0};
int dp[1025][1025] = {0};

//       1   2   3
// 
//  1    1   3   6
//  2    6   14  24  
//  3    15  33  53

// (x, y) dp 구하는 식 : dp[x][y-1] + dp[x-1][y] - dp[x-1][y-1] + arr[x][y] 
// (x1, y1) ~ (x2, y2) 합 : dp[x2][y2] - dp[x2][y1-1] - dp[x1-1][y2] + dp[x1-1][y1-1]

int getDp(int x, int y){
    return dp[x][y-1] + dp[x-1][y] - dp[x-1][y-1] + arr[x][y];
}
int getSum(int x1, int y1, int x2, int y2){
    return dp[x2][y2] - dp[x2][y1-1] - dp[x1-1][y2] + dp[x1-1][y1-1];
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i < N+1; i++){
        for(int j = 1; j < N+1; j++){
            cin >> arr[i][j];
            dp[i][j] = getDp(i, j);
        }
    }
    for(int i = 0; i < M; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        cout << getSum(x1, y1, x2, y2) << '\n';
    }
    return 0;
}