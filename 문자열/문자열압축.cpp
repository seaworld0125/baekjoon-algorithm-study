#include <iostream>
#include <string>
#define endl '\n'
#define INF 1e9
using namespace std;

int solution(string s) {
    int size = s.size();
    int ans_size = INF;
    if(size == 1) return 1;//문자열 길이 1일 때. 리턴 1.

    for(int i = size/2; i > 0; i--)//절반 이상으로 나누는건 의미가 없음. 절반 이하까지만 탐색
    {
        string tmp = "";    //
        string cmp1 = "";   //비교 기준 문자열
        string cmp2 = "";   //비교 대상 문자열 
        int j = 0, count = 1;

        for(; j < i; j++)
        {
            cmp1 += s[j]; //비교할 문자열 저장
        }
        
        while(j < size)
        {
            int c = i+j; //j에서 i만큼 문자를 탐색하기 위함
            for(; j < c && j < size; j++)
            {
                cmp2 += s[j];
            }
            if(cmp1 == cmp2) count++;   //비교 문자열 같으면 count 증가
            else{                       //비교 문자열 다르면 cmp1에 cmp2 문자열 넘겨주고 count 초기화
                if(count != 1)  //count == 1은 버린다
                    tmp += (to_string(count) + cmp1);
                else
                    tmp += cmp1;

                count = 1;
                cmp1 = cmp2;
            }
            cmp2 = "";
        }

        if(count != 1)
            tmp += (to_string(count) + cmp1);
        else
            tmp += cmp1;

        if(tmp.size() < ans_size)//답 최신화
        {
            ans_size = tmp.size();
        }
    }
    return ans_size;
}

int main(){
    cout << solution("aabbaccc") << endl;
    cout << solution("ababcdcdababcdcd") << endl;
    cout << solution("abcabcdede") << endl;
    cout << solution("abcabcabcabcdededededede") << endl;
    cout << solution("xababcdcdababcdcd") << endl;
    return 0;
}