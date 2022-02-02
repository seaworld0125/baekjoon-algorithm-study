#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Student {
public:
    int friendList[4];
};

class Entity {
public:
    int studentNum = -1;
    bool hasStudent = false;
    int satisfaction = 0;
};

class Preference {
public:
    int friendCount;
    int blankCount;
    int y;
    int x;

    Preference(int y, int x) : y(y), x(x), friendCount(0), blankCount(0) {}
};

int dy[] = {0,0,1,-1};
int dx[] = {-1,1,0,0};
int N;

bool checkRange(int y, int x, int n) {
    return y < 0 || x < 0 || y >= n || x >= n;
}

bool checkFriend(int * friendList, int number) {
    for(int i = 0; i < 4; i++) {
        if(friendList[i] == number) return true;
    }
    return false;
} 

int main() {
    cin >> N;

    int size = N * N;

    vector<Student> studentList(size + 1);
    vector<int> order(size);
    Entity map[20][20];

    for(int i = 0; i < size; i++) { // input
        cin >> order[i];

        for(int j = 0; j < 4; j++) {
            cin >> studentList[order[i]].friendList[j];
        }
    }

    for(int i = 0; i < size; i++) {
        int nowStudentNumber = order[i];

        vector<Preference> vp;
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                if(map[j][k].hasStudent) continue; // 빈 자리가 아니면 패스

                Preference pref(j, k);

                for(int l = 0; l < 4; l++) { // 주변에 친한 친구가 몇 있는지 확인
                    int y = j + dy[l];
                    int x = k + dx[l];

                    if(checkRange(y, x, N)) continue; // 범위를 벗어난 칸이면 패스

                    if(!map[y][x].hasStudent) { // 주변 칸이 빈 칸이면 blankCount++;
                        pref.blankCount++;
                        continue;
                    }

                    if(checkFriend(studentList[nowStudentNumber].friendList, map[y][x].studentNum)) {
                        pref.friendCount++; // 주변 칸에 친구가 있으면 friendCount++;
                    }
                }

                vp.push_back(pref);
            }
        }
        sort(vp.begin(), vp.end(), [](Preference a, Preference b) { // 후보 칸들을 세 가지 조건에 맞게 정렬
            if(a.friendCount == b.friendCount) {
                if(a.blankCount == b.blankCount) {
                    if(a.y == b.y) {
                        return a.x < b.x;
                    }
                    return a.y < b.y;
                }
                return a.blankCount > b.blankCount;
            }
            return a.friendCount > b.friendCount;
        });

        int bestY = vp[0].y;
        int bestX = vp[0].x;

        map[bestY][bestX].hasStudent = true;
        map[bestY][bestX].studentNum = nowStudentNumber;
        map[bestY][bestX].satisfaction = vp[0].friendCount;

        for(int l = 0; l < 4; l++) { // 주변 친구 만족도 업데이트
            int y = bestY + dy[l];
            int x = bestX + dx[l];

            if(checkRange(y, x, N) || !map[y][x].hasStudent) continue; // 범위를 벗어난 칸, 빈 칸이면 패스

            if(checkFriend(studentList[map[y][x].studentNum].friendList, nowStudentNumber)) { // 주변 친구의 친한 친구 목록에 내가 있으면
                map[y][x].satisfaction++; // 만족도 증가시키기
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++) 
            if(map[i][j].satisfaction > 0) 
                ans += pow(10, map[i][j].satisfaction - 1);
            
    cout << ans;
}