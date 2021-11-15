#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int N;
map<char, int> m;
char board[50][50];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

void lengthCheck(int y, int x) {
    for(int i = 0; i < N; i++) {
        char prev_c = board[i][0];
        int count = 0;

        for(int j = 0; j < N; j++) {
            if(prev_c == board[i][j]) count++;
            else {
                m[prev_c] = max(m[prev_c], count);
                count = 1;
                prev_c = board[i][j];
            }
        }
        m[prev_c] = max(m[prev_c], count);

        prev_c = board[0][i];
        count = 0;

        for(int j = 0; j < N; j++) {
            if(prev_c == board[j][i]) count++;
            else {
                m[prev_c] = max(m[prev_c], count);
                count = 1;
                prev_c = board[j][i];
            }
        }
        m[prev_c] = max(m[prev_c], count);
    }
}

void check(int y, int x) {
    for(int i = 0; i < 4; i++) {
        if(y+dy[i] >= 0 && y+dy[i] < N && x+dx[i] >= 0 && x+dx[i] < N) {
            if(board[y][x] != board[y+dy[i]][x+dx[i]]) {
                char prev01 = board[y][x];
                char prev02 = board[y+dy[i]][x+dx[i]];

                board[y][x] = prev02;
                board[y+dy[i]][x+dx[i]] = prev01;

                lengthCheck(y, x);

                board[y][x] = prev01;
                board[y+dy[i]][x+dx[i]] = prev02;
            }  
        }
    }
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++) 
            cin >> board[i][j];

    m['C'] = 0;
    m['P'] = 0;
    m['Z'] = 0;
    m['Y'] = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            check(i, j);

    cout << max(m['C'], max(m['P'], max(m['Z'], m['Y'])));
}