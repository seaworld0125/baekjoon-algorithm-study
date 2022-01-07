#include <stdio.h>
#include <stack>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    int i = 0;
    int j = 0;
    stack<int> s;
    vector<char> v;

    scanf("%d", &n);
    int arr[n];

    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for(i = 1, j = 0; i < n+1; i++){
        s.push(i);
        v.push_back('+');
        while(!s.empty() && s.top() == arr[j]){
            s.pop();
            v.push_back('-');
            j++;
        }
    }
    if(!s.empty()){
        printf("NO\n");
    }else{
        for(i = 0; i < v.size(); i++){
            printf("%c\n", v[i]);
        }
    }
}