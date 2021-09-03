#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool checkStr(string u){
    bool check = true;
    stack<char> st;
    for(char & c : u){
        if(c == '(')
            st.push('(');
        else{
            if(st.empty()){
                check = false;
                break;
            }
            else
                st.pop();
        }
    }
    return check;
}
string recursive(string p){
    if(p == "") return p;
    string u = "", v = "";
    int gradient = 0, i;
    for(i = 0; i < p.size(); i++){
        if(p[i] == '('){
            gradient--;
            u += p[i];
        }
        else{
            gradient++;
            u += p[i];
        }
        if(gradient == 0){
            i++;
            break;
        }
    }
    for(; i < p.size(); i++)
        v += p[i];
    
    //u가 올바른 문자열인 경우
    if(checkStr(u)){
        v = recursive(v);
        u += v;
        return u;
    }
    else{
        string tmp = '(' + recursive(v) + ')';
        //u 처리
        for(i = 1; i < u.size()-1; i++){
            if(u[i] == '(') tmp += ')';
            else tmp += '(';
        }
        return tmp;
    }
}
string solution(string p) {
    //빈 문자열 처리
    if(p == "") return p;
    //else
    string answer = recursive(p);
    return answer;
}





int main(){
    string p = "(()())()";
    cout << solution(p) << endl;
    p = ")(";
    cout << solution(p) << endl;
    p = "()))((()";
    cout << solution(p) << endl;
}