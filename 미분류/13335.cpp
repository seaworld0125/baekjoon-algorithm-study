#include <iostream>
#include <queue>
using namespace std;
typedef struct TINFO{ // 트럭 구조체
    int tw; int tot;
}tinfo;
int main(){
    int n, w, l;
    int tarr[1000] = {0};
    cin >> n >> w >> l;
    int i, j;
    for(i = 0; i < n; i++){ // 트럭무게 입력
        cin >> tarr[i];
    }queue<tinfo> q1; int qw = 0; // 다리 큐, 큐 무게
    cout <<"test : "<<q1.front().tot<<endl;
    for(i = 1, j = 0;; i++){
        if(!q1.empty() && i == q1.front().tot){ // 트럭이 나갈시간(tot)이 되면 내보냄
            qw -= q1.front().tw; // 트럭 무게 빼고 트럭제거 
            q1.pop();
            if(j >= n && q1.empty()) break;
        }if(qw+tarr[j] <= l && j < n){ // 트럭 무게 + 큐 무게 <= 다리 하중
            tinfo truck{tarr[j], i+w};
            q1.push(truck);
            qw += tarr[j++];
        }
    }cout << i << endl;
}