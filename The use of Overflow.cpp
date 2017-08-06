#include <iostream>

using namespace std;

// 巧妙利用溢出判断来进行比较 因为溢出了 肯定大于c所能输入的最大值

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        long long a, b, c;
        long long sum;
        scanf("%lld%lld%lld", &a, &b, &c);
        sum = a+b;
        if(a > 0 && b > 0 && sum <= 0) {
            printf("Case #%d: true\n", i);
        } else if(a < 0 && b < 0 && sum >= 0) {
            printf("Case #%d: false\n", i);
        } else {
            if(sum > c)
                printf("Case #%d: true\n", i);
            else
                printf("Case #%d: false\n", i);
        }
    }
    return 0;
}
