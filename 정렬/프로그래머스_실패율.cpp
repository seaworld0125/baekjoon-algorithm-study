#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<int, double> a, pair<int, double> b){
    if(a.second > b.second) 
        return true;
    if(a.second == b.second)   
        return a.first < b.first;

    return false;
};

vector<int> solution(int N, vector<int> stages) {
    // 실패율 => 현재 스테이지 실패 인원 / 현재 스테이지 도달 인원
    // 현재 스테이지 도달 인원 = 이전 스테이지 도달 인원(처음에는 stages.size()) - 이전 스테이지 실패 인원

    // failer_count : 스테이지 실패 인원 저장
    vector<int> failer_count(N+1, 0);
    for (int num : stages)
        if(num < N+1)
            failer_count[num]++;

    // failer_rate : 실패율 저장
    // stage_count : 현재 스테이지 도달 인원
    vector<pair<int, double>> failer_rate;
    int stage_count = stages.size();
    for (int i = 1; i < failer_count.size(); i++) {
        if(stage_count != 0)
            failer_rate.emplace_back(i, (double)failer_count[i] / stage_count);
        else
            failer_rate.emplace_back(i, 0);
        stage_count -= failer_count[i];
    }

    // 정렬
    sort(failer_rate.begin(), failer_rate.end(), compare);
    vector<int> answer;
    for (auto rate : failer_rate) {
        answer.emplace_back(rate.first);
    }
    return answer;
}





int main() {
    vector<int> answer = solution(5, {2, 1, 2, 6, 2, 4, 3, 3});
    
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << ", "; 
}