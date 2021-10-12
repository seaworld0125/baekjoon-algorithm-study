#include <iostream>
#include <vector>
using namespace std;

// 1. 벨트 회전
// 2. 로봇 이동
// 3. 1번 칸에 로봇을 올림(올릴 수 있다면)
// 4. 전체 벨트의 내구도 검사

int N, K;
vector<int> belt;
vector<bool> robot;
int pointer1;   //올리는 위치
int pointer2;   //내리는 위치

int checkRange(int num){
    if(num < 0) return (2 * N) - 1;
    else if(num == 2 * N) return 0;
    else return num;
}

void rotateBelt(){
    pointer1--;
    pointer2--;
    pointer1 = checkRange(pointer1);
    pointer2 = checkRange(pointer2);
    if(robot[pointer2]) robot[pointer2] = false;
}

void moveRobot(){
    int pointer3 = pointer2;
    pointer3 = checkRange(pointer3);
    // 로봇이 이동할 수 있는지 먼저 검사
    while(pointer1 != pointer3){
        bool move_ = false;

        int tmp = checkRange(pointer3 - 1);
        if(belt[pointer3] > 0){
            if(robot[pointer3] == false && robot[tmp]){
                move_ = true;
            }
        }
        if(move_){
            robot[tmp] = false;
            robot[pointer3] = true;

            belt[pointer3]--;
        }
        pointer3 = tmp;
    }
    if(robot[pointer2]) robot[pointer2] = false;
}

void getRobot(){
    if(belt[pointer1] > 0){
        robot[pointer1] = true;
        belt[pointer1]--;
    }
}

bool checkDurability(){
    int check = 0;
    for(int i = 0; i < 2*N; i++){
        if(belt[i] < 1){
            check++;
        }
    }   

    if(check >= K){
        return true;
    }
    return false;
}

void solve(){
    int answer = 0;
    while(1){
        answer++;
        rotateBelt();
        moveRobot();
        getRobot();
        if(checkDurability()) break;
    }
    cout << answer;
}

void input(){
    cin >> N >> K;
    for(int i = 0, k; i < 2*N; i++){
        cin >> k;
        belt.push_back(k);
        robot.push_back(false);
    }
    pointer1 = 0;
    pointer2 = N-1;  
}

int main(){
    input();
    solve();
}