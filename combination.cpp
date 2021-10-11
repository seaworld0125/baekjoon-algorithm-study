#include <iostream>
#include <vector>
using namespace std;

vector<int> set = {1,2,3,4,5};

void byFor() 
{
    for(int i = 0; i < set.size(); i++)
        for(int j = i+1; j < set.size(); j++)
            for(int l = j+1; l < set.size(); l++)
                cout << set[i] << " " << set[j] << " " << set[l] << "\n"; 
}

void printPicked(vector<int> & picked) 
{
    for(int i = 0; i < picked.size(); i++)
        cout << set[picked[i]] << " ";

    cout << "\n";
}
void byRecursive(int n, vector<int> & picked, int toPick) 
{
    if(toPick == 0) {printPicked(picked); return;};

    int smallest = picked.empty() ? 0 : picked.back() + 1;

    for(int next = smallest; next < n; next++) {
        picked.push_back(next);
        byRecursive(n, picked, toPick - 1);
        picked.pop_back();
    }
}

int main() {
    cout << "byFor----------\n";
    byFor();

    cout << "byRecursive----\n";
    vector<int> picked; 
    byRecursive(set.size(), picked, 3);
}