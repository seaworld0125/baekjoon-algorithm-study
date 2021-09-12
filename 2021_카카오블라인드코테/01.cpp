#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    map< string, int > countMap;
    map< string, int > mailCount;
    map< string, vector<string> > recordMap; 
    for(int i = 0; i < id_list.size(); i++) {
        countMap[id_list[i]] = 0;
        mailCount[id_list[i]] = 0;
        recordMap[id_list[i]] = vector<string>();
    }
    vector<string> v;
    vector<int> answer;  

    for(int i = 0; i < report.size(); i++) {
        string str = report[i];
        istringstream ss(str);
        string name, target;
        ss >> name;
        ss >> target;
        v = recordMap[target];

        bool alreadyReport = false;
        for(int i = 0; i < v.size(); i++) {
            if(v[i] == name) alreadyReport = true;
        }

        if(!alreadyReport) {
            countMap[target] += 1;
            recordMap[target].emplace_back(name);
        }
    }

    for(int i = 0; i < id_list.size(); i++){
        string target = id_list[i];
        if(countMap[target] >= k) {
            v = recordMap[target];

            for(int i = 0; i < v.size(); i++) {
                mailCount[v[i]] += 1;
            }
        }
    } 

    for(int i = 0; i < id_list.size(); i++){
        answer.emplace_back(mailCount[id_list[i]]);
    } 

    return answer;
}


int main(){
    vector<string> id_list = {"muzi", "frodo", "apeach", "neo"};
    vector<string> report = {"muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi"};
    int k = 2;
    vector<int> answer = solution(id_list, report, k);
    for(int i = 0; i < answer.size(); i++)
        cout << answer[i] << ", ";
}