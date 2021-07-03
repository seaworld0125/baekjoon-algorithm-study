#include <iostream>
using namespace std;

int arr[10000] = {0};   //수열
int check[10000] = {0}; //탐색여부
int N, tmp;
int stnd = 1001;    //기준
int length = 0;     //부분 수열 길이
int answer = 1;     //답

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    // 앞에 작은 숫자가 있는데 뒤에 있는 큰 숫자부터 시작하는 부분수열은 의미가 없다.
    // 탐색된 구간은 부분수열 탐색할 필요가 없다.
    for(int i = 0; i < N; i++){
        if(arr[i] <= stnd && !check[i]){
            stnd = arr[i];  tmp = 0;
            bool out = true;
            while(out){
                for(int j = i+1; j < N; j++){
                    if(arr[j] > tmp && !check[j]){
                        tmp = arr[j];
                        length++;
                        check[j] = 1;
                    }
                }
            }
        }
    }cout << answer;
}