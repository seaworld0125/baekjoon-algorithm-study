#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 1e9

int N;
vector<int> weight;
vector<int> cost;
vector<pair<int, int>> cheapest; //cost, idx
/*
뒤에서부터 싼 주유소 탐색
*/

void solution(){
    long long int answer = 0;

    int prev_st = N-1;
    for(int i = 0; i < cheapest.size(); i++){
        int station = cheapest[i].second;
        long long int weight_ = 0;
        for(int j = station; j < prev_st; j++){
            weight_ += weight[j];
        }
        prev_st = station;
        answer += (cheapest[i].first * weight_);
    }
    cout << answer;
}

void input(){
    cin >> N;
    int i, j, k;
    for(i = 0; i < N-1; i++){
        cin >> k;
        weight.push_back(k);      
    }
    for(i = 0; i < N; i++){
        cin >> k;
        cost.push_back(k);
    }
    for(i = N-1; i > 0;){
        int cheap = INF;
        int cheap_idx = 0;        
        for(k = 0; k < i; k++){
            if(cheap >= cost[k]){
                cheap = cost[k];
                cheap_idx = k;
            }
        }
        cheapest.push_back({cheap, cheap_idx});
        i = cheap_idx;
    }
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    input();
    solution();
}