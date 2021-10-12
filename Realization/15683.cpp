#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 세로 N, 가로 M
int N, M, blindSpot = 100;
int map[8][8];
class CAMERA {
public:
    int type, y, x;
};

// CAMERA List
vector<CAMERA> list;

// direction
enum Direction {
    Left = 0,
    Right = 1,
    Top = 2,
    Bottom = 3
};
int dy[4] = {0, 0, -1, 1};
int dx[4] = {-1, 1, 0, 0};

// y, x
vector<pair<int, int>> direct = {
    {dy[Left], dx[Left]}, {dy[Right], dx[Right]}, {dy[Top], dx[Top]}, {dy[Bottom], dx[Bottom]}
};
vector<vector<vector<pair<int, int>>>> direction = { 
    {}, 
    // vector[1]
    { 
        // vector[1][0]
        {
            direct[Left]
        }, 
        {direct[Right]}, 
        {direct[Top]}, 
        {direct[Bottom]}, 
    }, 
    { 
        {direct[Left], direct[Right]}, 
        {direct[Top], direct[Bottom]} 
    }, 
    { 
        {direct[Left], direct[Top]}, 
        {direct[Top], direct[Right]}, 
        {direct[Right], direct[Bottom]}, 
        {direct[Bottom], direct[Left]} 
    }, 
    { 
        {direct[Left], direct[Top], direct[Right]}, 
        {direct[Top], direct[Right], direct[Bottom]}, 
        {direct[Right], direct[Bottom], direct[Left]}, 
        {direct[Bottom], direct[Left], direct[Top]} 
    }, 
    { 
        {direct[Left], direct[Top], direct[Right], direct[Bottom]} 
    } 
};


bool compare(CAMERA a, CAMERA b) {
    if(a.type >= b.type) return true;
    else return false;
}

void mapCopy(int ** tmp) {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            tmp[i][j] = map[i][j];
}

void updateMap(int ** tmp) {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            map[i][j] = tmp[i][j];
}

int checkBlindSpot(int ** tmp) {
    int cnt = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(tmp[i][j] == 0) cnt++;

    return cnt;
}

int ** fillSpot(vector<pair<int, int>> & direction_, const int & y, const int & x, int & spotCount) {
    int ** tmp = new int * [8];
    for(int i = 0; i < 8; i++) tmp[i] = new int[8];
    mapCopy(tmp);

    for(int i = 0; i < direction_.size(); i++) {
        int move_y = y, move_x = x;
        while(move_y >= 0 && move_y < N && move_x >= 0 && move_x < M) {
            move_y += direction_[i].first, move_x += direction_[i].second;

            if(tmp[move_y][move_x] == 0) tmp[move_y][move_x] = 7;
            else if(tmp[move_y][move_x] == 6) break;
        }
    }
    int cnt;
    if(spotCount >= (cnt = checkBlindSpot(tmp))) {
        spotCount = cnt;
        return tmp;
    } 
    else
        delete tmp; 
    return NULL;
}

void checkBestDirection(const int & type, const int & y, const int & x) {
    int ** fixed;
    int ** tmp;
    int spotCount = blindSpot;
    if(type == 1) {
        if(tmp = fillSpot(direction[type][0], y, x, spotCount)) fixed = tmp;
        if(tmp = fillSpot(direction[type][1], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][2], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][3], y, x, spotCount)) delete fixed, fixed = tmp;
    }
    else if(type == 2) {
        if(tmp = fillSpot(direction[type][0], y, x, spotCount)) fixed = tmp;
        if(tmp = fillSpot(direction[type][1], y, x, spotCount)) delete fixed, fixed = tmp;
    }
    else if(type == 3) {
        if(tmp = fillSpot(direction[type][0], y, x, spotCount)) fixed = tmp;
        if(tmp = fillSpot(direction[type][1], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][2], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][3], y, x, spotCount)) delete fixed, fixed = tmp;
    }
    else if(type == 4) {
        if(tmp = fillSpot(direction[type][0], y, x, spotCount)) fixed = tmp;
        if(tmp = fillSpot(direction[type][1], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][2], y, x, spotCount)) delete fixed, fixed = tmp;
        if(tmp = fillSpot(direction[type][3], y, x, spotCount)) delete fixed, fixed = tmp;
    }
    else if(type == 5) {
        if(tmp = fillSpot(direction[type][0], y, x, spotCount)) fixed = tmp;
    }
    updateMap(fixed);
    blindSpot = spotCount;
    delete fixed;
}

void printMap() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cout << map[i][j] << ' ';
        }cout << endl;
    }
}

void checkCameraList() {
    int type, y, x;
    for(int i = 0; i < list.size(); i++) {
        type = list[i].type;
        y = list[i].y;
        x = list[i].x;
        checkBestDirection(type, y, x);
    }
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int tmp;
            cin >> tmp;
            map[i][j] = tmp;
            if(tmp >= 1 && tmp <= 5) list.push_back(new CAMERA(tmp, i, j));
            sort(list.begin(), list.end(), compare);
            checkCameraList();
        }
    }
    cout << blindSpot;
}