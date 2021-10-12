#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 보드의 크기
int N;
// 사과의 개수
int K;
// 방향 변환 횟수
int L;
// 시간
int time = 0;

// 방향 :오 아 왼 위
int dx[] = {1, 0, -1, 0}; 
int dy[] = {0, 1, 0, -1};

// 0:오    1:아   2:왼   3:위
int dir = 0;

class Snake{
public:
    int y;
    int x;
    Snake(int y_, int x_):y(y_), x(x_) {}
};

vector<Snake> snake;
vector<pair<int, int>> apple;
queue<pair<int, char>> rotate_v;

bool safeCheck(int ty, int tx){
    // head sy, sx
    int sy = snake[0].y;
    int sx = snake[0].x;
    // 꼬리 부딪힘 체크
    if(ty == sy && tx == sx) return false;
    // 맵 범위 체크
    if(sy >= 0 && sy < N && sx >= 0 && sx < N){
        // 몸통과 충돌 체크
        for(int i = 1; i < snake.size(); i++){
            if(snake[i].y == sy && snake[i].x == sx){
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}
bool appleCheck(){
    for(int i = 0; i < apple.size(); i++){
        if(snake[0].y == apple[i].first && snake[0].x == apple[i].second){
            apple[i].first = -1;
            apple[i].second = -1;
            return true;
        }
    }return false;
}
void rotation(char C){
    if(dir == 0){
        if(C == 'L')
            dir = 3;
        else
            dir = 1;
    }
    else if(dir == 1){
        if(C == 'L')
            dir = 0;
        else
            dir = 2;
    }
    else if(dir == 2){
        if(C == 'L')
            dir = 1;
        else
            dir = 3;    
    }
    else{
        if(C == 'L')
            dir = 2;
        else
            dir = 0;   
    }
}
bool move(){
    // 꼬리 위치 기록
    int ty, tx;
    ty = snake[snake.size()-1].y;
    tx = snake[snake.size()-1].x;
    // 몸통 이동
    for(int i = snake.size()-1; i > 0; i--){
        snake[i].y = snake[i-1].y;
        snake[i].x = snake[i-1].x;
    }
    //대가리 회전 
    if(rotate_v.front().first == time){
        rotation(rotate_v.front().second);
        rotate_v.pop();
    }
    //대가리 직진
    snake[0].y += dy[dir];
    snake[0].x += dx[dir];
    //대가리 위치에 사과있으면
    if(appleCheck()){
        snake.push_back(Snake(ty, tx));
    }
    time++;
    if(safeCheck(ty, tx)) return true;
    else return false;
}
void input(){
    cin >> N;
    cin >> K;
    int apple_y, apple_x;
    for(int i = 0; i < K; i++){
        cin >> apple_y >> apple_x;
        apple.push_back(make_pair(apple_y-1, apple_x-1));
    }
    cin >> L;
    int x;
    char c;
    for(int i = 0; i < L; i++){
        cin >> x >> c;
        rotate_v.push(make_pair(x, c));
    }
    snake.push_back(Snake(0, 0));
}
void solve(){
    input();
    while(move()){}
    cout << time;
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
}