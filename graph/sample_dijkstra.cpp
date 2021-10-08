#include<iostream>
#include<vector>
using namespace std;
#define INF 1e9 // 무한을 의미하는 값으로 10억을 설정

// 노드의 개수(N), 간선의 개수(M), 시작 노드 번호(Start)
// 노드의 개수는 최대 100,000개라고 가정
int n, m, start;

vector<pair<int, int>> graph[100001]; // 각 노드에 연결되어 있는 노드에 대한 정보를 담는 배열

bool visited[100001]; // 방문한 적이 있는지 체크하는 목적의 배열 만들기

int d[100001]; // 최단 거리 테이블 만들기

int getSmallestNode() // 방문하지 않은 노드 중에서, 가장 최단 거리가 짧은 노드의 번호를 반환.
{
    int min_value=INF;
    int index = 0; // 가장 최단 거리가 짧은 노드(인덱스)
    
    for(int i=1; i<=n; i++)
    {
        if(d[i] < min_value && !visited[i])
        {
            min_value = d[i];
            index = i;
        }
    }
    cout << "index :" << index << ", d[index] :" << d[index] << endl;
    return index;
}

void dijkstra(int start)
{
    d[start]=0;
    visited[start]= true;
    
    for(int j=0; j<graph[start].size(); j++)
    {
        int adjindex = graph[start][j].first;
        d[adjindex] = graph[start][j].second; // 최단거리 테이블에 초기값 세팅
        cout << "d :" << d[adjindex] << endl;
    }
    
    for(int i=0; i<n-1; i++)
    {
        int now = getSmallestNode();
        visited[now]=true;
        
        for(int j=0; j<graph[now].size(); j++)
        {
            int cost = d[now] + graph[now][j].second;
            if(cost<d[graph[now][j].first])
            {
                d[graph[now][j].first]=cost;
            }
        }
    }
}

int main()
{
    cin >> n >> m >> start;
    // 모든 간선 정보를 입력받기
    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;  // a번 노드에서 b번 노드로 가는 비용이 c라는 의미
        graph[a].push_back({b, c});
    }
    
    // 최단 거리 테이블을 모두 무한으로 초기화
    fill_n(d, 100001, INF);
    
    dijkstra(start);
    
    // 모든 노드로 가기 위한 최단 거리를 출력
    for (int i = 1; i <= n; i++)
    {
        // 도달할 수 없는 경우, 무한(INFINITY)이라고 출력
        if (d[i] == INF)
        {
            cout << "INFINITY" << '\n';
        }
        // 도달할 수 있는 경우 거리를 출력
        else
        {
            cout << d[i] << '\n';
        }
    }
    return 0;
}