#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
#define INF 1e9
#define MAX 101
using namespace std;

int n, m, r, answer=0;
int dis[MAX];
int item[MAX] = {0};
bool visited[MAX];
vector<pair<int, int>> v[MAX];

int getShortway(){
    int min_d = INF;
    int index = 0;
    for(int i = 1; i <= n; i++){
        if(dis[i] < min_d && !visited[i]){
            min_d = dis[i];
            index = i;
        }
    }
    return index;
}
int dijkstra(int start){
    fill_n(dis, MAX, INF);      //INF값으로 초기화
    fill_n(visited, MAX, false);//false값으로 초기화
    visited[start] = true;
    dis[start] = 0;

    for(int i = 0; i < v[start].size(); i++){
        dis[v[start][i].first] = v[start][i].second;    //dis[연결 노드 번호] = 간선 길이
    }
    for(int i = 0; i < n-1; i++){//시작 점을 제외한 모든 노드를 꺼내어 한번 씩 탐색
        int now = getShortway();
        visited[now] = true;
        for(int j = 0; j < v[now].size(); j++){
            int cost = v[now][j].second + dis[now];
            if(cost < dis[v[now][j].first]){
                dis[v[now][j].first] = cost;
            }
        }
    }
    int answer = 0;
    for(int i = 1; i <= n; i++){
        if(dis[i] <= m){
            answer += item[i];
        }
    }   
    return answer;
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> r;
    for(int i = 1; i <= n; i++){
        cin >> item[i];
    }
    for(int i = 1; i <= r; i++){
        int a, b, l;
        cin >> a >> b >> l;
        v[a].push_back(make_pair(b, l));//(연결 노드 번호, 간선 길이)
        v[b].push_back(make_pair(a, l));//
    }
    for(int i = 1; i <= n; i++){
        answer = max(dijkstra(i), answer);
    }
    cout << answer;
    return 0;
}