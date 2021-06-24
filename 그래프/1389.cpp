#include <stdio.h>
#include <queue>
using namespace std;

//bfs �̿� - ���������� ������� Ž��
//Ž�� �� ��? layer? �� ī��Ʈ�ؼ� �����ֱ�

char arr[101][101] = {0};  
int kbNum = 0;              //kbnum ��� �ֽ�ȭ��
int answerKnum = 102;       //���� ���� kbnum
int answer = 102;           //��� ��ȣ
int layer;                  //bfs �� ����

int N, M;

void bfs(int root){
    queue<int> q;                   //�湮���� ���
    char alreadyVisit[101] = {0};   //�湮���
    layer = 1; kbNum = 0;           //�⺻ layer 1

    int visit;
    q.push(root);
    alreadyVisit[root] = '1';       //��Ʈ��� �湮ǥ��
    while (!q.empty()){             
        int size = q.size();
        for(int j = 0; j < size; j++){      //�� ���� �˱����� 
            visit = q.front();
            q.pop();
            for(int i = 1; i < N+1; i++){   //�湮���� ���
                if(arr[visit][i] == '1' && alreadyVisit[i] == 0){
                    q.push(i);
                    alreadyVisit[i] = '1';
                    kbNum += layer;         //�� ��ȣ ��ŭ kbnum ���ϱ�
                }
            }
        }
        layer++;
        if(kbNum > answerKnum){         //kbnum �� �亸�� Ŀ���� �ǹ̾����Ƿ� Ž�� ����
            break;
        }
    }
    if(answerKnum > kbNum){     //�� �ֽ�ȭ
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