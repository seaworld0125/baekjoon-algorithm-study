#include <iostream>
using namespace std;

int * arr;
int narr[8] = {0}; // ���� �迭
int N, answer = 0, p = 0; // p ��� ����

void calcans(){ // ����
    int temp, tanswer = 0;
    for(int i = 0; i < N-1; i++){
        temp = narr[i] - narr[i+1];
        if(temp < 0) temp *= -1;
        tanswer += temp;
    }if(tanswer > answer) answer = tanswer;
}
void recursive(){ // ��� Ž��
    static bool sarr[8] = {false}; // static state arr
    static int p = 0;
    if(p == N){ // ���� ���� : ��� ���̰� N ��ŭ�϶�
        calcans(); p--;
        return ;
    }
    int n = -1;
    bool varr[8] = {false}; // ��� bool �迭 : ���� ������ �� �߿��� �ẻ ���� �ִ��� ���
    for(int i = 0; i < N; i++){
        if(!varr[i] && !sarr[i]) {  // arr[i] �� �ẻ ���� ���� ��������� ���� �����
            if(n != -1) sarr[n] = false; // ���� ������ ������ ���� �ִٸ� ���� false �� ��������
            narr[p++] = arr[i];
            sarr[i] = true; // ���� true �� ����
            varr[i] = true; // ���
            recursive(); n = i;
        }
    }
    sarr[n] = false; // ���� false �� ��������
    p--;
    return ; // ���� ���� : ���� ������ ���� ���� ��
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