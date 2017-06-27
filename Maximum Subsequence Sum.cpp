#include <iostream>
#include <algorithm>

using namespace std;

// 若前k个为负数，则无论如何会拖累第k+1个，故前k个为负数则舍弃。

int main(int argc, char const *argv[]) {
    int k;
    cin >> k;
    int* arr = (int*)malloc(k * sizeof(int));
    for(int i=0;i<k;i++) cin >> arr[i];
    int max=-1,i=0,j=0;
    int temp_max=0,temp_i,temp_j;
    int flag = 1;
    for(int t=0;t<k;t++) {
        temp_max += arr[t];
        if(temp_max >= 0) {
            if(flag) {temp_i = t;temp_j = t;flag = 0;}
            else temp_j = t;
            if(temp_max > max) {
                max = temp_max;
                i = temp_i;
                j = temp_j;
            }
        }
        if(temp_max < 0) {flag = 1; temp_max = 0;}
    }
    if(max == -1) {max = 0; i = 0; j = k-1;}
    printf("%d %d %d\n", max,arr[i],arr[j]);
    return 0;
}
