#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<string, int> & a, pair<string, int> & b){
    if(a.second > b.second) return true;
    else return false;
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for(int i = 0; i < orders.size(); i++){
        sort(orders[i].begin(), orders[i].end());
    }
    for(int i = 0; i < course.size(); i++){
        vector<pair<string, int>> comb;
        bool jump = true;
        for(int j = 0; j < orders.size(); j++){
            if(course[i] > orders[j].length()){
                continue;
            }
            jump = false;
            // 보조수열 이용 //
            vector<int> sub_;
            for(int k = 0; k < orders[j].size() - course[i]; k++) sub_.push_back(0);
            for(int k = 0; k < course[i]; k++) sub_.push_back(1);
            do
            {
                string tmp = "";
                for(int k = 0; k < sub_.size(); k++){
                    if(sub_[k]) tmp += orders[j][k];
                }
                bool find = false;
                for(int k = 0; k < comb.size(); k++){
                    if(comb[k].first == tmp){
                        comb[k].second++;
                        find = true;
                    }
                }
                if(!find) {
                    comb.push_back({tmp, 1});
                }
            } while (next_permutation(sub_.begin(), sub_.end()));
            vector<int>().swap(sub_);
        }
        if(!jump){
            sort(comb.begin(), comb.end(), cmp);
            int max = comb[0].second;
            if(max >= 2){
                answer.push_back(comb[0].first);
                for(int i = 1; i < comb.size(); i++){
                    if(max == comb[i].second) answer.push_back(comb[i].first);
                    else break;
                }
            }
            vector<pair<string, int>>().swap(comb);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}

int main(){
    // vector<string> answer;
    // vector<string> orders = {"XYZ", "XWY", "WXA"};
    // vector<int> course = {2,3,4};
    // answer = solution(orders, course);
    // for(int i = 0; i < answer.size(); i++){
    //     cout << answer[i] << ' ';
    // }cout << endl;
}
