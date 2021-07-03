#include <iostream>
#include <algorithm>
using namespace std;

int N;
int P[10001] = {0};     //카드 팩 가격
float arr[10001] = {0}; //카드 개당 가격

int getPrice(int N){
    float me = 0;   //제일 비싼 카드 개당 가격
    int me_p = 0;   //제일 비싼 카드팩 번호
    cout << "N : " << N << '\n';
    if(N == 0) return 0;
    for(int i = 1; i < N+1; i++){   //필요한 카드 개수만큼 살 수 있는 카드팩까지만 조사
        if(me < arr[i]){
            me = arr[i];
            me_p = i;
            cout << "me : " << me << ", me_p : " << me_p << '\n';
        }            
    }
    int price = P[me_p];
    int remain_N = N-me_p;
    return price + getPrice(remain_N);
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i < N+1; i++){
        cin >> P[i];
        arr[i] = (float)P[i]/i;    //개당 가격
        cout << "\narr[" << i << "] : " << arr[i] << ' '; 
    }cout << '\n';
    cout << getPrice(N);
}