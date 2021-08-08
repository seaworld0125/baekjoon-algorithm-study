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
        for(int i = 0; i < home.size(); i++)
        {
            // 집 치킨거리
            int d = INF;
            for(int j = 0; j < sub_v.size(); j++)
            {
                if(sub_v[j])
                    d = min(manhattan(home[i].first, home[i].second, chicken[j].first, chicken[j].second), d);
            }
            tmp += d;
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