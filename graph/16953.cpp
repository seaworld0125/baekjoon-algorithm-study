#include <iostream>
#include <queue>
using namespace std;

queue<int> q;       //�湮����
int tLevel = 0;     //Ʈ�� ���� == ���� Ƚ��
int nfirst = 0;     //Ʈ�� �������� ù Ž�� ��� = ������ ���
int target = 0;
int node = 0;
bool clear = false;

void recursive(){
    if(node == nfirst){
        cout << "lvup " << node << endl;   
        tLevel++;  //ù��� ������ level ����
        nfirst = node*2; //������ ��� ����
    }if(node == target){ 
        clear = true;
        return;  //target ã���� ����
    }if(!q.empty()){
        node = q.front(); q.pop();
        if(node < target){  //target ���� ���� node �� �ڽ� ��� �߰� ����
            if(node*2 <= 1000000000) q.push(node*2);    //node �ڽ� ��� �߰�           
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