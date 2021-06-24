#include <iostream>
using namespace std;

int * arr;
int narr[8] = {0}; // 계산용 배열
int N, answer = 0, p = 0; // p 재귀 깊이

void calcans(){ // 계산용
    int temp, tanswer = 0;
    for(int i = 0; i < N-1; i++){
        temp = narr[i] - narr[i+1];
        if(temp < 0) temp *= -1;
        tanswer += temp;
    }if(tanswer > answer) answer = tanswer;
}
void recursive(){ // 재귀 탐색
    static bool sarr[8] = {false}; // static state arr
    static int p = 0;
    if(p == N){ // 종료 조건 : 재귀 깊이가 N 만큼일때
        calcans(); p--;
        return ;
    }
    int n = -1;
    bool varr[8] = {false}; // 멤버 bool 배열 : 선택 가능한 수 중에서 써본 적이 있는지 기록
    for(int i = 0; i < N; i++){
        if(!varr[i] && !sarr[i]) {  // arr[i] 가 써본 적이 없고 사용중이지 않은 수라면
            if(n != -1) sarr[n] = false; // 만약 이전에 선택한 수가 있다면 상태 false 로 돌려놓기
            narr[p++] = arr[i];
            sarr[i] = true; // 상태 true 로 변경
            varr[i] = true; // 기록
            recursive(); n = i;
        }
    }
    sarr[n] = false; // 상태 false 로 돌려놓기
    p--;
    return ; // 종료 조건 : 선택 가능한 수가 없을 때
}
int main(){
    cin >> N;
    arr = new int[N];
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    recursive();
    cout << answer;
}