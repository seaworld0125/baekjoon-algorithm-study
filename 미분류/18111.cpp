#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, B, ansTime = 1e9, ansStand = -1e9;
vector<int> map;
int mapSize;

void solve() {
    for(int stand = 0; stand <= 256; stand++) {
        int time = 0;
        int block = B;

        for(int i = 0; i < mapSize; i++) {
            if(map[i] == stand) continue;
            else if(map[i] > stand) {
                block += (map[i] - stand);
                time += (2 * (map[i] - stand));
            }
            else {
                block -= (stand - map[i]);
                time += (stand - map[i]);
            }
        }
        if(block >= 0) {
            if(ansTime > time) {
                ansTime = time;
                ansStand = stand;
            }
            else if(ansTime == time) {
                ansStand = max(ansStand, stand);
            }
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

    solve();
    cout << ansTime << ' ' << ansStand;
}