#include <iostream>
#include <string>
using namespace std;

string solution(string new_id) {
// 1. 대문자 --> 소문자
// 2. 특수문자 공백문자로 치환
// 3. 연속되는 도트 한개로 줄이기 -- dot_count 사용
    int size = new_id.size();
    int dot_count = 0;
    for(int i = 0; i < size; i++){
        new_id[i] = tolower(new_id[i]);
        if(new_id[i] == '.'){
            dot_count += 1;
            if(dot_count >= 2){
                for(int j = i, c = 0; c < dot_count-1;){ 
                    if(new_id[j] != ' '){
                        new_id[j] = ' ';
                        c++; j--;
                    }
                }
                dot_count -= 1;
            }
        }
        else if((new_id[i] >= 'a' && new_id[i] <= 'z') 
            || (new_id[i] >= 'A' && new_id[i] <= 'Z') 
            || (new_id[i] >= '0' && new_id[i] <= '9') 
            || new_id[i] == '-' 
            || new_id[i] == '_'){
            dot_count = 0;
            continue;
        }
        else{
            // 모든 특수문자는 공백으로 치환
            new_id[i] = ' ';
        }
    }
// 특수문자, 도트 처리 완료, 문자열 정리
    string answer = "";
    int cc = 0;
    for(int i = 0; i < size && cc < 15; i++){
        if(new_id[i] != ' '){
            if(cc == 0 && new_id[i] == '.') continue;
            answer.push_back(new_id[i]);
            cc++;
        }
    }
    if(answer.size() == 0){
        answer = "aaa";
    }
    else if(answer[answer.size()-1] == '.'){
        answer.pop_back();
    }
// 2글자 이하 처리
    size = answer.size();
    if(size <= 2){
        for(int i = size; i < 3; i++)
            answer.push_back(answer[size-1]);
    }

    return answer;
}

int main(){
    cout << solution("...!@BaT#*..y.abcdefghijklm") << endl;
    cout << solution("z-+.^.") << endl;
    cout << solution("=.=") << endl;
    cout << solution("123_.def") << endl;
    cout << solution("abcdefghijklmn.p") << endl;
    cout << solution("b.") << endl;
}