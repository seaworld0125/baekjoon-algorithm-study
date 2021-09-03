#include <iostream>
#include <string>
#include <queue>
using namespace std;

string solution(string new_id) {
    queue<char> q;
    bool dot_ = true;

    for(char & elem : new_id){
        if(elem >= 'A' && elem <= 'Z')  elem = tolower(elem);
        if((elem >= 'a' && elem <= 'z') || (elem >= '0' && elem <= '9') || elem == '-' || elem == '_'){
            q.push(elem);
            dot_ = true;
        }
        else if(elem == '.' && dot_){
            q.push('.');
            dot_ = false;
        }
    }

    string answer = "";
    int size = q.size();
    for(int i = 0; i < size && answer.size() < 15; i++){
        if(i == 0 && q.front() == '.') q.pop();
        else{
            answer += q.front();
            q.pop();
        }
    }

    if(answer.size() == 0)  answer = "aaa";
    else if(answer[answer.size()-1] == '.'){
        answer.pop_back();
    }
    size = answer.size();
    if(size <= 2){
        for(int i = 0; i < 3-size; i++)
            answer += answer[size-1];
    }
    return answer;
}

int main(){
    // cout << solution("...!@BaT#*..y.abcdefghijklm") << endl;
    // cout << solution("z-+.^.") << endl;
    // cout << solution("=.=") << endl;
    // cout << solution("123_.def") << endl;
    // cout << solution("abcdefghijklmn.p") << endl;
    // cout << solution("b.") << endl;
    // cout << solution("cc.") << endl;
    // cout << solution("......................") << endl;
    // cout << solution(".") << endl;
    // cout << solution("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB") << endl;
    cout << solution("..a..b..c..d..") << endl;
}