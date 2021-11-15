#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, M, R;
int map[300][300];
vector<deque<int>> v;

int main() {
    cin >> N >> M >> R;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> map[i][j];

    int x1 = 0, x2 = M-1, y1 = 0, y2 = N-1;

    while(x1 <= x2 && y1 <= y2) {
        deque<int> v_;

        for(int i = y1; i < y2; i++)
            v_.emplace_back(map[i][x1]);
        
        for(int i = x1; i < x2; i++)
            v_.emplace_back(map[y2][i]);
        
        for(int i = y2; i > y1; i--)
            v_.emplace_back(map[i][x2]);
        
        for(int i = x2; i > x1; i--)
            v_.emplace_back(map[y1][i]);

        v.emplace_back(v_);

        x1++;  y1++; 
        x2--;  y2--;
    }

    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < R; j++) {
            int back = v[i].back();
            v[i].pop_back();
            v[i].emplace_front(back);
        }

    x1 = 0, x2 = M-1, y1 = 0, y2 = N-1;

    int count = 0;
    int i = 0;
    while(x1 <= x2 && y1 <= y2 && i < v.size() && count < v[i].size()) {

        for(int j = y1; j < y2; j++)
            map[j][x1] = v[i][count++];

        for(int j = x1; j < x2; j++)
            map[y2][j] = v[i][count++];

        for(int j = y2; j > y1; j--)
            map[j][x2] = v[i][count++];
        
        for(int j = x2; j > x1; j--)
            map[y1][j] = v[i][count++];

        x1++;  y1++; 
        x2--;  y2--;

        count = 0;
        i++;
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++)
            cout << map[i][j] << ' ';
        
        cout << endl;
    }
}