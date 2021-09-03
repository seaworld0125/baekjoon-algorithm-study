#include <iostream>
#include <string>
#include <stack>
using namespace std;

string str = "";
int answer = 0;

stack<char> s;

// (()[[]]) ([])

// == (()) + ([[]]) + ([])

int main(){
    cin >> str;
    if(str.length() % 2){
        cout << 0;
    }
    else{
        int standard;
        int tmp;
        bool flag = false;

        for(int i = 0; i < str.length(); i++){
            if(str[i] == '('){
                if(s.empty()) {
                    standard = 1;
                }
                standard *= 2;
                s.push('(');
                flag = false;
            }
            else if(str[i] == '['){
                if(s.empty()) {
                    standard = 1;
                }
                standard *= 3;
                s.push('[');
                flag = false;
            }
            else if(str[i] == ')'){
                if(s.empty() || s.top() != '('){
                    answer = 0;
                    break;
                }
                tmp = 2;
                s.pop();
                if(!flag){
                    answer += standard;
                    flag = true;
                }
                standard /= tmp;
            }
            else if(str[i] == ']'){
                if(s.empty() || s.top() != '['){
                    answer = 0;
                    break;
                }
                tmp = 3;
                s.pop();
                if(!flag){
                    answer += standard;
                    flag = true;
                }
                standard /= tmp;
            }
        }
        cout << answer;
    }
    return 0;
}