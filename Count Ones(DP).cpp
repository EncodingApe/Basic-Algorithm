#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char const *argv[]) {
    long long int n;
    scanf("%lld", &n);

    long long int thresh[10];    // 存储长度为i的数中最多有多少个1
    long long int dp[10];   // 存储所求数的i位最多有多少1 动态规划
    int num[11];
    int len = 0;

    dp[1] = n % 10 == 0 ? 0 : 1;

    thresh[1] = 1;
    for(int i=2; i<10; i++) {
        thresh[i] = pow(10, i-1) + 10 * thresh[i-1];
    }

    for(int i=1; i<=10; i++) {     // 将数存入一个数组 低位为1
        if(n) len++;
        num[i] = n % 10;
        n = n / 10;
    }

    for(int i=2; i<=len; i++) {
        if(num[i] == 0) {
            dp[i] = dp[i-1];
        } else if(num[i] == 1) {
            int tmp = 0;
            for(int j=1;j<i;j++) {
                tmp += num[j] * pow(10,j-1);
            }
            dp[i] = dp[i-1] + thresh[i-1] + tmp + 1;
        } else if(num[i] >= 2) {
            dp[i] = dp[i-1] + pow(10,i-1) + num[i] * thresh[i-1];
        }
    }

    printf("%lld",dp[len]);

    return 0;
}
