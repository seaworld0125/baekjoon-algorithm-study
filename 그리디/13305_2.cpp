#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 1e9

long long N, answer;
long long weight[100001];
long long cost[100001];

void input(){
    cin >> N;
    int i, j, k;
    for(i = 0; i < N-1; i++){
        cin >> weight[i];     
    }
    for(i = 0; i < N; i++){
        cin >> cost[i];
    }
    
    long long cheap = INF;
    for(i = 0; i < N-1; i++){
        cheap = min(cheap, cost[i]);
        answer += cheap * weight[i];
    }
    cout << answer;
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    input();
}