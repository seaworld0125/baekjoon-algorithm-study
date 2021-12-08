#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define F first
#define S second

pair<int, int> queen;
pair<int, int> rock;

int N;

bool ifSafe(int y, int x) {
    return (y >= 0 && y < 8 && x >= 0 && x < 8 ? true : false);
}

pair<int, int> getMoveIdx(string & dir) {
    if(dir == "R") return {0, 1};
    if(dir == "L") return {0, -1};
    if(dir == "B") return {1, 0};
    if(dir == "T") return {-1, 0};
    if(dir == "RT") return {-1, 1};
    if(dir == "LT") return {-1, -1};
    if(dir == "RB") return {1, 1};
    if(dir == "LB") return {1, -1};
}

int main() {
    string pos01, pos02, dir;
    cin >> pos01 >> pos02 >> N;

    queen.S = pos01[0] - 'A';
    rock.S = pos02[0] - 'A';
    queen.F = abs(pos01[1] - 56);
    rock.F = abs(pos02[1] - 56);

    for(int i = 0; i < N; i++) {
        cin >> dir;
        auto move = getMoveIdx(dir);

        int queeny = queen.F + move.F, 
            queenx = queen.S + move.S;

        if(queeny == rock.F && queenx == rock.S) { // 경로에 돌이 있으면
            int rocky = rock.F + move.F,
                rockx = rock.S + move.S;
            
            if(ifSafe(rocky, rockx)) { // 돌이 움직일 수 있으면 퀸의 이동도 보장됨..
                queen.F = queeny;
                queen.S = queenx;
                rock.F = rocky;
                rock.S = rockx;
            }
        } 
        else {
            if(ifSafe(queeny, queenx)) { // 퀸이 움직일 수 있으면
                queen.F = queeny;
                queen.S = queenx;
            }
        }
    }

    cout << (char)(queen.S + 'A') << abs(queen.F - 8) << '\n';
    cout << (char)(rock.S + 'A') << abs(rock.F - 8);
}