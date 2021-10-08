#include <iostream>
#include <queue>
using namespace std;

queue<int> q;       //방문순서
int tLevel = 0;     //트리 레벨 == 연산 횟수
int nfirst = 0;     //트리 층에서의 첫 탐색 노드 = 맨좌측 노드
int target = 0;
int node = 0;
bool clear = false;

void recursive(){
    if(node == nfirst){
        cout << "lvup " << node << endl;   
        tLevel++;  //첫노드 만나면 level 증가
        nfirst = node*2; //맨좌측 노드 업뎃
    }if(node == target){ 
        clear = true;
        return;  //target 찾으면 종료
    }if(!q.empty()){
        node = q.front(); q.pop();
        if(node < target){  //target 보다 작은 node 만 자식 노드 추가 가능
            if(node*2 <= 1000000000) q.push(node*2);    //node 자식 노드 추가           
            if((node*10)+1 <= 1000000000) q.push((node*10)+1);
        }
        cout << "node: " << node << endl;   
        return recursive();
    }
}
int main(){
    int start;
    cin >> start >> target;
    q.push(start);
    nfirst = start*2;
    recursive();    
    if(clear) cout << tLevel + 1;
    else cout << -1;
}