#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//��ͷ� Ž��
//�����ϰ� dfs ���
//�迭 ����� Ž��
//������ �������� dfs ����

int M, N, K, _size, ct = 0; //ct = count
vector<int> answer;
char arr[101][101] = {0};
int moveX[4] = {-1, 0, 1, 0}; //��������
int moveY[4] = {0, 1, 0, -1};

void makeArr(int x1, int y1, int x2, int y2){ // �ϴ� �迭 �����
    for(int i = 0; i < M; i++)
        if(i >= y1 && i < y2)
            for(int j = 0; j < N; j++)
                if(j >= x1 && j < x2)
                    if(arr[i][j] == 0) arr[i][j] = '1';
}
void dfs(int y, int x){ // ��� �̿��ϱ����� dfs
    int nodeX, nodeY;
    for(int i = 0; i < 4; i++){
        nodeX = x + moveX[i];   //Ž�� ������ ���ʳ�����
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
    for(int i = 0; i < K; i++){ //�迭 ���� - ��ǥ �κ��� �ٳ�°����� ǥ��
        cin >> x1 >> y1 >> x2 >> y2;
        makeArr(x1, y1, x2, y2);
    }
    for(int i = 0; i < M; i++){ //�迭 �ȱ� - �ٳ���� ���� �κ������� dfs ����
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
    sort(answer.begin(), answer.end()); //�迭 sort
    cout << ct << endl;
    for(int i = 0; i < ct; i++){
        cout << answer[i] << ' '; 
    }
    return 0;
}