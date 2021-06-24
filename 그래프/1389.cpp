#include <stdio.h>
#include <queue>
using namespace std;

//bfs 이용 - 퍼져나가는 방식으로 탐색
//탐색 시 층? layer? 을 카운트해서 더해주기

char arr[101][101] = {0};  
int kbNum = 0;              //kbnum 계속 최신화됨
int answerKnum = 102;       //제일 작은 kbnum
int answer = 102;           //사람 번호
int layer;                  //bfs 층 정보

int N, M;

void bfs(int root){
    queue<int> q;                   //방문예정 노드
    char alreadyVisit[101] = {0};   //방문기록
    layer = 1; kbNum = 0;           //기본 layer 1

    int visit;
    q.push(root);
    alreadyVisit[root] = '1';       //루트노드 방문표시
    while (!q.empty()){             
        int size = q.size();
        for(int j = 0; j < size; j++){      //층 정보 알기위함 
            visit = q.front();
            q.pop();
            for(int i = 1; i < N+1; i++){   //방문예정 기록
                if(arr[visit][i] == '1' && alreadyVisit[i] == 0){
                    q.push(i);
                    alreadyVisit[i] = '1';
                    kbNum += layer;         //층 번호 만큼 kbnum 더하기
                }
            }
        }
        layer++;
        if(kbNum > answerKnum){         //kbnum 이 답보다 커지면 의미없으므로 탐색 중지
            break;
        }
    }
    if(answerKnum > kbNum){     //답 최신화
        answerKnum = kbNum;
        answer = root;
    }else if(answerKnum == kbNum){
        if(answer > root){
            answer = root;
        }
    }
}
int main(){
    scanf("%d %d", &N, &M);
    int a, b;
    for(int i = 0; i < M; i++){ 
        scanf("%d %d", &a, &b);
        arr[a][b] = '1'; 
        arr[b][a] = '1';
    }    
    for(int i = 1; i < N+1; i++){
        bfs(i);
    }
    printf("%d", answer);
}