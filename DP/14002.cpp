#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int A, answer;
vector<int> arr;
vector<int> lis;
int dp[1000] = {0,};

void input(){
    cin >> A;
    for(int i = 0; i < A; i++){
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    answer = 0;
}
void solve(){
    input();
    for(int i = 0; i < A; i++){
        int tmp = 0;
        for(int j = 0; j < i; j++){
            if(arr[j] < arr[i]){
                tmp = max(tmp, dp[j]);
            }   
        }
        dp[i] = tmp+1;
        answer = max(answer, dp[i]);
    }
    cout << answer << endl;

    int tmp = answer;
    for(int i = A-1 ; i >= 0; i--){
        if(tmp == dp[i]){
            lis.push_back(arr[i]);
            tmp--;
            if(tmp == 0) break;
        }
    }
    for(int i = lis.size()-1; i >= 0; i--){
        if(i == 0) {cout << lis[i]; break;}
        else cout << lis[i] << ' ';
    }
}
int main(){
    solve();
}