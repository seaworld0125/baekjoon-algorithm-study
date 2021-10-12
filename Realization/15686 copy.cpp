#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define endl '\n'
#define INF 1e9

int N, M, answer = INF;
int MAP[51][51];
vector<pair<int, int>> home;
vector<pair<int, int>> chicken;

// int DX[4] = {-1, 0, 1, 0};//왼위오아
// int DY[4] = {0, -1, 0, 1};

// void BFS(int y, int x, int & tmp){
//     queue<pair<int, int>> dst;
//     dst.push({y, x});

//     bool visited[51][51];
//     memset(visited, false, sizeof(visited));

//     int len = 1;
//     while(!dst.empty())
//     {
//         int size = dst.size();

//         for(int l = 0; l < size; l++)
//         {
//             int dy = dst.front().first;
//             int dx = dst.front().second;
//             visited[dy][dx] = true;
//             dst.pop();

//             for(int i = 0; i < 4; i++)
//             {
//                 int dy_ = dy+DY[i];
//                 int dx_ = dx+DX[i];
                
//                 if(dy_ > 0 && dx_ > 0 && dy_ <= N && dx_ <= N)
//                 {
//                     if(MAP[dy_][dx_] == 2)
//                     {   
//                         tmp += len;
//                         return;
//                     }
//                     //방문한 적 없다면
//                     if(!visited[dy_][dx_]){
//                         dst.push({dy_, dx_});
//                     }
//                 }
//             }
//         }
//         len++;
//     }
// }

int manhattan(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

void solution(){
    vector<int> sub_v;
    int j = 0;
    for(; j < chicken.size()-M; j++)
        sub_v.push_back(0);
    for(; j < chicken.size(); j++)
        sub_v.push_back(1);
    
    do
    {
        // 임시변수 //도시 치킨거리
        int tmp = 0;
        // for(int i = 0; i < chicken.size(); i++)
        // {
        //     if(sub_v[i])
        //     {
        //         MAP[chicken[i].first][chicken[i].second] = 2;
        //     }
        //     else
        //     {
        //         MAP[chicken[i].first][chicken[i].second] = 0;
        //     }   
        // }

        for(int i = 0; i < home.size(); i++)
        {
            int d = INF;
            for(int j = 0; j < sub_v.size(); j++)
            {
                if(sub_v[j])
                    d = min(manhattan(home[i].first, home[i].second, chicken[j].first, chicken[j].second), d);
            }
            tmp += d;
            // BFS(home[i].first, home[i].second, );
        }
        answer = min(answer, tmp);

    } while(next_permutation(sub_v.begin(), sub_v.end()));

    cout << answer;
}

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            if(MAP[i][j] == 1)
                home.push_back({i, j});
            if(MAP[i][j] == 2)
                chicken.push_back({i, j});
        }
    }
    solution();
}