#include <iostream>
#include <cmath>
using namespace std;

#define MAX 300001
int A, P;
int visited[MAX] = {0};

int getPow(int num){
    int tmp = 0;
    while(num > 0)
    {
        tmp += (int)pow(num%10, P);
        num /= 10;
    }
    return tmp;
}

void dfs(int num){
    visited[num]++;

    if(visited[num] == 3) return;

    dfs(getPow(num));
}

int getResult(){
    int result = 0;
    for(int i = 0; i < MAX; i++)
    {
        if(visited[i] == 1)
        {
            result++;
        }
    }
    return result;
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A >> P;
    dfs(A);
    cout << getResult();
}


