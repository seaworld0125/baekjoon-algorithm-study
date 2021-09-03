#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 1e9

vector<pair<int, int>> nodes[201];
int d[3][201];

void betterDijkstra(int start, int layer){
    priority_queue<pair<int, int>> pq; 
    pq.emplace(0, start);
    d[layer][start] = 0;
    while(!pq.empty()){
        int dist = -pq.top().first;
        int visit = pq.top().second;
        pq.pop();

        if(dist > d[layer][visit]) continue;

        for(int i = 0; i < nodes[visit].size(); i++){
            int cost = nodes[visit][i].second + dist;
            if(cost < d[layer][nodes[visit][i].first]){
                d[layer][nodes[visit][i].first] = cost;
                pq.emplace(-cost, nodes[visit][i].first);
            }
        }
    }
}
// ang.........
// void dij(int idx, int n, int start) {
//     res[idx][start] = 0;
//     priority_queue<pair<int, int>> pq;
//     pq.push({ -0, start });
//     for (int i = 1; i <= n; i++) res[idx][i] = inf;
//     while (!pq.empty()) {
//         auto cur = pq.top();
//         pq.pop();
//         if (res[idx][cur.second] != inf) continue;
//         int cost = -cur.first;
//         res[idx][cur.second] = cost;
//         for (int i = 0; i < node[cur.second].next.size(); i++) {
//             auto next = node[cur.second].next[i];
//             if (res[idx][next.second] != inf) continue;
//             pq.push({ -(cost + next.first), next.second});
//         }
//     }
// }
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    fill(d[0], d[0]+402, INF);

    for(int i = 0; i < fares.size(); i++){
        nodes[fares[i][0]].emplace_back(fares[i][1], fares[i][2]);
        nodes[fares[i][1]].emplace_back(fares[i][0], fares[i][2]);
    }
    betterDijkstra(a, 0);
    betterDijkstra(b, 1);
    betterDijkstra(s, 2);

    int answer = INF;
    for(int i = 0; i <= n; i++){
        answer = min(answer, d[2][i] + d[1][i] + d[0][i]);
    }
    return answer;
}

int main(){
    vector<vector<int>> tmp = {{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};
    cout << solution(6,4,6,2,tmp);
    solution(6,4,6,2,tmp);
}