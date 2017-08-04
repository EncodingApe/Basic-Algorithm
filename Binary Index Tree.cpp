#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#define MAX 100001

using namespace std;


int stack[MAX],c[MAX];

int lowbit(int x) {     // 树状数组中的重要操作， 操作结果是保留x对应二进制数的最后一个1而将其他高位的1置0
    return x & (-x);
}

int sum(int n) {    // 返回普通数组前n个数的和
    int sum = 0;
    int k = n;
    while(k > 0) {      // 对于c[k]，其等于从k开始以及前lowbit(k)个普通数组元素的和，即一个c[k]管理其前面lowbit(k)个元素
        sum += c[k];    // 因此求和就是把k前面的c[k]相加    时间复杂度为 O(logn)
        k -= lowbit(k);
    }
    return sum;
}

void add(int pos, int i) {      // 在普通数组的第pos个元素上 加i
    while(pos < MAX) {      // 因为第pos个元素又多个树状数组管辖 所以要递归改变多个树状数组元素的值
        c[pos] += i;
        pos += lowbit(pos);
    }
}

int binary_search(int tar) {
    int l=0,r=MAX-1,median,res;
    while(l<r-1) {
        median = (r+l) / 2;
        res=sum(median);
        if(res<tar)
            l=median;
        else
            r=median;
    }
    return l+1;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    char str[11];
    int tmp, N, left=1, right=1;
    for(int i=0; i<n; i++) {
        scanf("%s", str);
        if(str[1] == 'o') {
            if(right == left) {
                printf("Invalid\n");
            } else {
                right--;
                printf("%d\n", stack[right]);
                add(stack[right], -1);
            }
        } else if(str[1] == 'e') {
            N = right - left;
            if(! N) {
                printf("Invalid\n");
            } else {
                if(N % 2 == 0) {
                    tmp = binary_search(N/2);
                } else if (N % 2 == 1) {
                    tmp = binary_search((N+1)/2);
                }
                printf("%d\n", tmp);
            }
        } else if(str[1] == 'u') {
            scanf("%d", &tmp);
            stack[right++] = tmp;
            add(tmp, 1);
        }
    }
    return 0;
}
