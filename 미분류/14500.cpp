#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> map;
                                        
int tet01[1][4] = {}
                                    
int main() {
    cin >> N >> M;

    vector<vector<int>>(N, vector<int>(M)).swap(map);
    
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < M; j++) 
            cin >> map[i][j];

    tetromino[0].emplace_back(0, 0)
}