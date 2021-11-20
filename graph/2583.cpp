#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//재귀로 탐색
//간단하게 dfs 사용
//배열 만들고 탐색
//나눠진 영역마다 dfs 수행

int M, N, K, _size, ct = 0; //ct = count
vector<int> answer;
char arr[101][101] = {0};
int moveX[4] = {-1, 0, 1, 0}; //왼위오아
int moveY[4] = {0, 1, 0, -1};

void makeArr(int x1, int y1, int x2, int y2){ // 일단 배열 만들기
    for(int i = 0; i < M; i++)
        if(i >= y1 && i < y2)
            for(int j = 0; j < N; j++)
                if(j >= x1 && j < x2)
                    if(arr[i][j] == 0) arr[i][j] = '1';
}
void dfs(int y, int x){ // 재귀 이용하기위해 dfs
    int nodeX, nodeY;
    for(int i = 0; i < 4; i++){
        nodeX = x + moveX[i];   //탐색 순서는 왼쪽노드부터
        nodeY = y + moveY[i];
        if(nodeY > -1 && nodeY < M && nodeX > -1 && nodeX < N){
            if(arr[nodeY][nodeX] == 0){
                arr[nodeY][nodeX] = '1';
                _size++;
                dfs(nodeY, nodeX);
            }
        }
    }
}
int main(){
    int x1, y1, x2, y2;
    cin >> M >> N >> K;
    for(int i = 0; i < K; i++){ //배열 생성 - 좌표 부분은 다녀온것으로 표현
        cin >> x1 >> y1 >> x2 >> y2;
        makeArr(x1, y1, x2, y2);
    }
    for(int i = 0; i < M; i++){ //배열 훑기 - 다녀오지 않은 부분있으면 dfs 수행
        for(int j = 0; j < N; j++){
            if(arr[i][j] == 0){
                arr[i][j] = '1';
                _size = 1;
                dfs(i, j);
                answer.push_back(_size);
                ct++;
            }
        }
    }
    sort(answer.begin(), answer.end()); //배열 sort
    cout << ct << endl;
    for(int i = 0; i < ct; i++){
        cout << answer[i] << ' '; 
    }
    return 0;
}