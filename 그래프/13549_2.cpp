#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 1e9

int N; //누나
int K; //동생

// 최단 거리 테이블
int d[100001];

bool safe(int n){
    return (0 <= n && n <= 100000);
}

void betterDijkstra(){
    priority_queue<pair<int, int>> pq;
    pq.push({0, N});
    d[N] = 0;

    while(!pq.empty()){
        // 오름차순 정렬을 위해서 저장할 때 - 를 붙임..
        // 뺄때도 - 붙여줘야함
        int dist = -pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if(d[now] < dist) continue;

        // now * 2 인 경우
        int cost = dist;
        if(safe(now*2) && cost < d[now*2]){
            d[now*2] = cost;
            pq.push({-cost, now*2});
        }
        // now + 1 인 경우
        cost = dist + 1;
        if(safe(now+1) && cost < d[now+1]){
            d[now+1] = cost;
            pq.push({-cost, now+1});
        }
        // now - 1 인 경우
        cost = dist + 1;
        if(safe(now-1) && cost < d[now-1]){
            d[now-1] = cost;
            pq.push({-cost, now-1});
        }
    }
}

void solve(){
    // 초기화
    fill(d, d + 100001, INF);
    betterDijkstra();
    cout << d[K];
}

int main(){
    cin >> N >> K;
    solve();
    return 0;
}