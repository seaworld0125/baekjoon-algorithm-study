#include <iostream>
#include <queue>
using namespace std;
typedef struct TINFO{ // Ʈ�� ����ü
    int tw; int tot;
}tinfo;
int main(){
    int n, w, l;
    int tarr[1000] = {0};
    cin >> n >> w >> l;
    int i, j;
    for(i = 0; i < n; i++){ // Ʈ������ �Է�
        cin >> tarr[i];
    }queue<tinfo> q1; int qw = 0; // �ٸ� ť, ť ����
    cout <<"test : "<<q1.front().tot<<endl;
    for(i = 1, j = 0;; i++){
        if(!q1.empty() && i == q1.front().tot){ // Ʈ���� �����ð�(tot)�� �Ǹ� ������
            qw -= q1.front().tw; // Ʈ�� ���� ���� Ʈ������ 
            q1.pop();
            if(j >= n && q1.empty()) break;
        }if(qw+tarr[j] <= l && j < n){ // Ʈ�� ���� + ť ���� <= �ٸ� ����
            tinfo truck{tarr[j], i+w};
            q1.push(truck);
            qw += tarr[j++];
        }
    }cout << i << endl;
}