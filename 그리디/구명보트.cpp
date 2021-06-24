#include <iostream>
#include <vector>
using namespace std;

int weightArr[241]={0};
int solution(vector<int> people, int limit) {
    int i, j, rWeight, answer = 0;
    for(i = 0; i < people.size(); i++){ //배열에 몸무게 별로 사람수 저장
        weightArr[people[i]]++;
    }
    for(i = 240; i > 39;){  //무거운사람부터
        if(weightArr[i] > 0){   //사람있으면 태우고 보트 추가
            rWeight = limit - i;    //한명태움 //남은 무게 계산
            weightArr[i]--;         //한명빼기
            answer++;               //보트++
            for(j = rWeight; j > 39;){
                if(weightArr[j] > 0){   //사람있으면 태움
                    weightArr[j]--;
                    break;  //태우고 종료
                }else j--;      //남은 무게보다 무거우면 다음 몸무게
            }
        }else i--;        
    }
    return answer;
}