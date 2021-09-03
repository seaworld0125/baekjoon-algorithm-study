#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define INF 1e9
using namespace std;

vector<pair<int, int>> nodes[201];
int d[2][201];
int path_[201];

void betterDijkstra(int start, int layer){
    priority_queue<pair<int, int>> pq; 
    pq.emplace(0, start);
    d[layer][start] = 0;
    while(!pq.empty()){
        int dist = -pq.top().first;
        int visit = pq.top().second;
        pq.pop();

        if(dist > d[layer][visit])
            continue;

        for(int i = 0; i < nodes[visit].size(); i++){
            int cost = nodes[visit][i].second + dist;
            if(cost < d[layer][nodes[visit][i].first]){
                d[layer][nodes[visit][i].first] = cost;
                pq.emplace(-cost, nodes[visit][i].first);
                if(layer == 0)
                    path_[nodes[visit][i].first] = visit;
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    // d 초기화
    fill(d[0], d[0]+402, INF);

    // 노드 긴선 정보 담기
    for(int i = 0; i < fares.size(); i++){
        nodes[fares[i][0]].emplace_back(fares[i][1], fares[i][2]);
        nodes[fares[i][1]].emplace_back(fares[i][0], fares[i][2]);
    }



    betterDijkstra(s, 1);
    int dist = INF;
    int c;
    for(int i = 1; i <= n; i++){
        if(dist > d[1][i]){
            dist = d[1][i];
            c = i;
        }
    }
    cout << "s-> :" << dist << endl;
    // int c = path_[b];
    // int dist = INF;
    // while(c != a){
    //     cout << "c :" << c << endl;
    //     if(dist > d[1][c]){
    //         dist = d[1][c];
    //     }
    //     c = path_[c];
    // }
    // if(dist > d[1][a]){
    //     dist = d[1][a];
    //     c = a;
    // }
    // if(dist > d[1][b]){
    //     dist = d[1][b];
    // }
    betterDijkstra(c, 0);
    cout << "C->A :" << d[0][a] << endl;
    cout << "C->B :" << d[0][b] << endl;

    // 

    int answer = d[0][a] + d[0][b] + dist;
    return answer;
}

int main(){
    vector<vector<int>> tmp = {{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};
    cout << solution(6,4,6,2,tmp);
    // solution(6,4,6,2,tmp);
}