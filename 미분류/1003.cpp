#include <stdio.h>
using namespace std;

int count1;
int count0;

int fibonacci(int n) {
    if (n == 0) {
        count0++;
        return 0;
    } else if (n == 1) {
        count1++;
        return 1;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}
int main(){
    int T, n;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        scanf("%d", &n);
        count0 = 0;
        count1 = 0;
        fibonacci(n);
        printf("%d %d\n", count0, count1);
    }
}