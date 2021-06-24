#include <iostream>
using namespace std;

int main(){
    int N, M, result=0, K=0;
    cin >> N >> M;
    if(2*N+1 > M) cout << 0;
    else{    
        char str[M];
        cin >> str;
        for(int i = 0; i < M; i++){
            while(1){
                if(str[i]=='I' && str[i+1]=='O' && str[i+2]=='I') {
                    i+=2;
                    K+=1; 
                }else break;
            } 
            if(K >= N){
                result += (K-N+1);
            } K=0;
        }
    }cout << result;
}