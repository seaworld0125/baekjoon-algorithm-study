#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    int basicHour = fees[0];
    int basicFee = fees[1];
    int unitTime = fees[2];
    int unitFee = fees[3];
    
    // 차량번호, 출입시간, 누적시간
    map< int, pair<int, int> > recordMap;

    for(int i = 0; i < records.size(); i++) {
        int hour, min, carNum;
        string str = records[i];
        istringstream ss(str);
        string tmp;
        ss >> tmp;
        hour = stoi(tmp.substr(0, 2));
        min = stoi(tmp.substr(3, 2));
        
        ss >> tmp;
        carNum = stoi(tmp);
        
        ss >> tmp;
        if(tmp == "IN") {
            int time = (hour * 60) + min;
            // 출입시간 갱신
            if(recordMap.count(carNum)) {
                int tmp = recordMap[carNum].second;
                recordMap[carNum] = {time, tmp};
            }
            else{
                recordMap[carNum] = {time, 0};
            }
        }
        else if(tmp == "OUT") {
            int time = (hour * 60) + min;
            // 누적시간 갱신
            if(recordMap.count(carNum)) {
                int tmp = recordMap[carNum].second + (time - recordMap[carNum].first);
                recordMap[carNum] = {0, tmp};
            }
        }
    }

    vector<int> answer;
    
    int endTime = (23 * 60) + 59;
    map< int, pair<int, int> > ::iterator itr;
    for(itr = recordMap.begin(); itr != recordMap.end(); itr++) {
        // 출차처리 되지 않은 차량 처리
        if(itr->second.first != 0 || itr->second.second == 0){
            // 누적시간 갱신
            int tmp = itr->second.second + (endTime - itr->second.first);
            itr->second.first = 0;
            itr->second.second = tmp;
        }
        // 누적 시간
        int accumTime = itr->second.second;
        // cout << "accumTime :" << accumTime << endl;

        // 기본 시간 > 누적 시간 : 기본 요금만 부과
        if(basicHour >= accumTime) {
            answer.emplace_back(basicFee);
        }
        else {
            // cout << "ceil : " << ceil(((double)accumTime - basicHour) / unitTime) << endl;;
            answer.emplace_back(basicFee + (ceil(((double)accumTime - basicHour) / unitTime) * unitFee));
        }
    }
    return answer;
}










int main(){
    vector<int> fees = {1, 461, 1, 10};
    vector<string> records = {"00:00 1234 IN"};
    vector<int> answer = solution(fees, records);
    for(int i = 0; i < answer.size(); i++){
        cout << answer[i] << ", " << endl;
    }
}