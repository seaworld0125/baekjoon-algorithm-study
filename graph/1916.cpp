#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define F first
#define S second

vector<pair<int, int>> graph[100001];
int d[1001];
int N, M;
int start, goal;

void dijkstra() {
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, start);
    d[start] = 0;

    while(!pq.empty()) {
        int dist = -pq.top().F;
        int now = pq.top().S;
        pq.pop();

        if(d[now] < dist) continue;

        for(int i = 0; i < graph[now].size(); i++) {
            int cost = graph[now][i].F + dist;
            if(cost < d[graph[now][i].S]) {
                d[graph[now][i].S] = cost;
                pq.emplace(-cost, graph[now][i].S);
            }
        }
    }
}

int main() {
    cin >> N >> M;  
    for(int i = 0; i < M; i++) {
        int bs, bg, bc;
        cin >> bs >> bg >> bc;
        graph[bs].emplace_back(bc, bg);
    }
    cin >> start >> goal;
    fill_n(d, 1001, (int)1e9);

    dijkstra();
    cout << d[goal];
}