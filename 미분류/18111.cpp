#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, B;
vector<int> map;
int mapSize;

pair<int, int> solve() {
    int standIdx = (mapSize / 2) - 1;
    if(B == 0) standIdx = mapSize - 1;

    while(standIdx < mapSize) {
        int stand = map[standIdx];
        int time = 0;
        int block = B;

        for(int i = 0; i < mapSize; i++) {
            if(map[i] > stand) time += 2 * (map[i] - stand);
            else if(map[i] < stand) {
                block -= 1;
                if(block < 0) {
                    standIdx++;
                    break;
                }
                time += stand - map[i];
            }
        }
        // cout << "stand : " << stand << ", standIdx : " << standIdx << ", time : " << time << ", block : " << block << endl; 
        if(block >= 0) {
            return {time, stand};    
        }
    }
}

int main() {
    cin >> N >> M >> B;
    mapSize = N * M;

    map.resize(mapSize);
    for(int i = 0; i < mapSize; i++)
        cin >> map[i];

    sort(map.begin(), map.end(), [](int a, int b) {
        return a > b;
    });

    auto ans = solve();

    cout << ans.first << ' ' << ans.second;
}