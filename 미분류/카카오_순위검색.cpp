#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> answer;
map<string, vector<int>> dev;

vector<int> solution(vector<string> info, vector<string> query) {
    //info 파싱하기   
    for(int i = 0; i < info.size(); i++){
        string tmp = info[i];
        istringstream st(tmp);
        string s[5];
        int count = 0;
        while(st >> s[count]){count++;}
        count --;
        //점수
        int score = stoi(s[count]);
        for (int i = 0; i < (1 << count); i++) { // 1<<n은 2^n 따라서 부분집합의 개수
            tmp.erase();
            for (int j = 0; j < count; j++){ //원소의 개수만큼 for문 돌아감 
                if (i&(1 << j)) //i&(1<<j) i의 j번째 bit가 1인지 아닌지를 확인함 
                    tmp += s[j]; 
                else   
                    tmp += '-';
            }
            dev[tmp].emplace_back(score);
            // cout << tmp << endl; 
        }
    }
    //모든 key에 있는 vector 정렬
    for(auto iter = dev.begin(); iter != dev.end(); iter++){
        sort(iter->second.begin(), iter->second.end());
    }
    //query 파싱하기     
    for(int i = 0; i < query.size(); i++){
        string tmp = query[i];
        istringstream st(tmp);
        string token, query_ = "";
        int score, count = 0;
        while(st >> token){
            if(token != "and"){
                if(count < 4){
                    query_ += token;
                    count++;
                }
                else
                    score = stoi(token);
            }
        }
        //lower_bound로 범위 구하기
        auto itr = lower_bound(dev[query_].begin(), dev[query_].end(), score);
        count = dev[query_].size() - (itr - dev[query_].begin());

        answer.emplace_back(count);
    }
    return answer;
}












int main(){
    vector<string> info = {"java backend junior pizza 150","python frontend senior chicken 210",
                            "python frontend senior chicken 150","cpp backend senior pizza 260",
                            "java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query = {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200",
                            "cpp and - and senior and pizza 250","- and backend and senior and - 150",
                            "- and - and - and chicken 100","- and - and - and - 150"};
    
    solution(info, query);
}