#include <iostream>
#include <vector>
using namespace std;

int weightArr[241]={0};
int solution(vector<int> people, int limit) {
    int i, j, rWeight, answer = 0;
    for(i = 0; i < people.size(); i++){ //�迭�� ������ ���� ����� ����
        weightArr[people[i]]++;
    }
    for(i = 240; i > 39;){  //���ſ�������
        if(weightArr[i] > 0){   //��������� �¿�� ��Ʈ �߰�
            rWeight = limit - i;    //�Ѹ��¿� //���� ���� ���
            weightArr[i]--;         //�Ѹ���
            answer++;               //��Ʈ++
            for(j = rWeight; j > 39;){
                if(weightArr[j] > 0){   //��������� �¿�
                    weightArr[j]--;
                    break;  //�¿�� ����
                }else j--;      //���� ���Ժ��� ���ſ�� ���� ������
            }
        }else i--;        
    }
    return answer;
}