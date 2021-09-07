#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

vector<string> solution(vector<string> record) {
    map<string, string> m;
    for(int i = 0; i < record.size(); i++){
        string tmp = record[i];
        istringstream st(tmp);
        string s[3];
        int c = 0;
        while(st >> s[c]){c++;}

        if(s[0][0] != 'L')
            m[s[1]] = s[2];
    }
    vector<string> answer;
    for(int i = 0; i < record.size(); i++){
        string tmp = record[i];
        istringstream st(tmp);
        string s[3];
        int c = 0;
        while(st >> s[c]){c++;}

        if(s[0][0] == 'E'){
            answer.emplace_back(m[s[1]] + "님이 들어왔습니다.");
        }
        else if(s[0][0] == 'L'){
            answer.emplace_back(m[s[1]] + "님이 나갔습니다.");
        }
    }
    return answer;
}


/*

00:00 ~ 12:28
28분

*/






int main(){
    vector<string> record = {"Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"};
    auto result = solution(record);
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << endl;
    }
    return 0;
}

