#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 201
#define INF 1e8

int map[MAX][MAX];

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            if(j==i) map[i][j] = 0;
            else map[i][j] = INF;
        }
    }
    
    for(int i = 0; i < fares.size(); i++){
        map[fares[i][0]][fares[i][1]] = fares[i][2];
        map[fares[i][1]][fares[i][0]] = fares[i][2];
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                map[j][k] =  min(map[j][k], map[j][i] + map[i][k]);
            }
        }
    }
    
    int answer = INF;
    for(int i = 0; i <= n; i++){
        answer = min(answer, map[s][i] + map[i][a] + map[i][b]);
    }
    return answer;
}