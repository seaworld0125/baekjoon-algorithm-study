#include <iostream>
#define endl '\n'
using namespace std;

int T;
int arr0[41];   //0이 호출되는 횟수 저장
int arr1[41];   //1이 호출되는 횟수 저장

int fibo0(int num){
    if(arr0[num] != -1){
        return arr0[num]; 
    }else{
        arr0[num] = fibo0(num-1) + fibo0(num-2);
    }
    return arr0[num];
}
int fibo1(int num){
    if(arr1[num] != -1){
        return arr1[num]; 
    }else{
        arr1[num] = fibo1(num-1) + fibo1(num-2);
    }
    return arr1[num];
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> T;
    int num, i;

    for(i = 0; i < 41; i++){
        arr1[i] = arr0[i] = -1;
    }
    arr1[0] = arr0[1] = 0;
    arr1[1] = arr0[0] = 1;

    for(i = 0; i < T; i++){
        cin >> num;
        cout << fibo0(num) << ' ' << fibo1(num) << endl;
    }
}