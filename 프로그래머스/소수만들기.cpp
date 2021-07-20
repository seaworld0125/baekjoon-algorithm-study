#include <vector>
#include <iostream>
using namespace std;

bool prime[3001];
bool check[1001];    //방문 여부
vector<int> comb_;       //조합의 합 저장

//comb func : 중복을 허용하지 않는 조합을 구하고 합을 저장함
void comb(vector<int> & nums, int index, int depth = 1, int sum_ = 0){    //index는 nums의 index임 
    check[nums[index]] = true;
    sum_ += nums[index];
    if(depth == 3)  //3개 뽑아야함
    {
        comb_.push_back(sum_);
    }
    for(int i = index+1; i < nums.size(); i++)
    {
        if(!check[nums[i]])
        {   
            check[nums[i]] = true;
            comb(nums, i, depth+1, sum_);
            check[nums[i]] = false;
        }
    }
}
//단순한 3중 for문 조합 구하기
void comb2(vector<int> & nums){
    for(int i = 0; i <= nums.size()-3; i++){
        for(int j = i+1; j < nums.size(); j++){
            for(int k = j+1; k < nums.size(); k++){
                comb_.push_back(nums[i]+nums[j]+nums[k]);
            }
        }
    }
}
//소수 판별
bool isPrime(){
    for(int i = 1; i <= 3000; i++)
    {
        prime[i] = true;
    }
    for(int i = 2; i*i <= 3000; i++)
    {
        if(prime[i]){
            for(int j = i*i; j <= 3000; j+=i)
            {
                prime[j] = false;
            }
        }
    }
    return true;
}
int solution(vector<int> nums) 
{
    int answer = 0;
    isPrime();

    // for(int i = 0; i < nums.size(); i++)
    // {
    //     comb(nums, i);
    // }
    comb2(nums);
    for(int i = 0; i < comb_.size(); i++){
        if(prime[comb_[i]])
        {
            answer++;
        }
    }
    return answer;
}

int main(){
    vector<int> nums = {1,2,7,6,4};
    cout << endl << solution(nums);
}