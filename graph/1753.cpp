#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define F first
#define S second

int V, E, K;
vector<pair<int, int>> edge[20002];

int D[20002];

void dijkstra() {
    // -비용, 정점
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, K);
    D[K] = 0;

    while(!pq.empty()) {
        int dist = -pq.top().F;
        int now = pq.top().S;
        pq.pop();

        if(D[now] < dist) continue; // 이미 체크한 경우 패스

        for(int i = 0; i < edge[now].size(); i++) {
            int cost = dist + edge[now][i].F;

            if(cost < D[edge[now][i].S]) {
                D[edge[now][i].S] = cost;
                pq.emplace(-cost, edge[now][i].S);
            }
        }
    } 
}

int main() {ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E >> K;
    fill(D, D + (V + 1), 1e9);

    int p1, p2, weight;
    for(int i = 0; i < E; i++) {
        cin >> p1 >> p2 >> weight;
        edge[p1].emplace_back(weight, p2);
    }

    dijkstra();
    
    for(int i = 1; i <= V; i++) {
        if(D[i] >= 1e9) cout << "INF\n";
        else cout << D[i] << "\n";
    }
}