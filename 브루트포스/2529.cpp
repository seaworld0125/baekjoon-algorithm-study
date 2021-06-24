#include <iostream>
using namespace std;

int K;
char * carr;
int arr[10] = {0};
int Barr[10] = {0};
int Sarr[10] = {9};
bool safe(){
    for(int i = 0; i < K; i++){
        switch (carr[i]){
        case '<':
            if(arr[i] >= arr[i+1]) return false;
            break;
        case '>':
            if(arr[i] <= arr[i+1]) return false;
        default:
            break;
        }
    }return true;
}
void compare(){
    bool b = false; int i;
    for(i = 0; i < K+1; i++){
        if(arr[i] == Barr[i]);
        else if(arr[i] > Barr[i]){
            b = true;
            break;
        }else if(arr[i] < Barr[i]) break;
    }
    if(b){
        for(i = 0; i < K+1; i++){
            Barr[i] = arr[i];
        }
    }
    b = false;
    for(i = 0; i < K+1; i++){
        if(arr[i] == Sarr[i]);
        else if(arr[i] < Sarr[i]){
            b = true;
            break;
        }else if(arr[i] > Sarr[i]) break;
    }
    if(b){
        for(i = 0; i < K+1; i++){
            Sarr[i] = arr[i];
        }
    }
}
void recursive(){
    static bool sarr[10] = {false};
    static int p = 0;
    if(p == K+1){
        if(safe()) compare(); 
        p--;
        return ;
    }
    int n = -1;
    bool varr[10] = {false};
    for(int i = 0; i < 10; i++){
        if(!varr[i] && !sarr[i]) {
            if(n != -1) sarr[n] = false;
            arr[p++] = i;
            sarr[i] = true;
            varr[i] = true;                 
            recursive(); n = i;
        }
    }
    sarr[n] = false;
    p--;
    return ;
}
int main(){
    cin >> K;
    carr = new char[K];
    for(int i = 0; i < K; i++){
        cin >> carr[i];
    }
    recursive();
    for(int i = 0; i < K+1; i++){
        cout << Barr[i];
    }cout << endl;
    for(int i = 0; i < K+1; i++){
        cout << Sarr[i];
    }
}
