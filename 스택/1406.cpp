#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main(){
    vector<char> str; //input str
    stack<char> s; //stack
    int N, j, i, cs;
    char cm;

    char str2[100001] = {0}; //temp str
    cin >> str2;
    for(j = 0; str2[j] != 0; j++){
        str.push_back(str2[j]);
    }
    cs = str.size();

    cin >> N;
    for(j = 0; j < N; j++){
        cin >> cm;
        if(cm == 'L'){
            if(!str.empty()){
                cs--;
                s.push(str[cs]);
                str.pop_back();
            }
        }else if(cm == 'D'){
            if(!s.empty()){
                str.push_back(s.top());
                s.pop();
                cs++;
            }
        }else if(cm == 'B'){
            if(!str.empty()){
                cs--;
                str.pop_back();
            }            
        }else if(cm == 'P'){
            cin >> cm;
            str.push_back(cm);
            cs++;
        }
    }    
    while(!s.empty()){
        str.push_back(s.top());
        s.pop();
    }
    for(j = 0; j < str.size(); j++){
        cout << str[j];
    }
}