#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) {
    int m,n,k,tmp;
    scanf("%d %d %d",&m,&n,&k);

    int* ans = (int*)malloc(k * sizeof(int));
    memset(ans,0,k * sizeof(int));

    vector<int> v;

    for(int i=0; i<k; i++) {
        scanf("%d", &tmp);
        v.clear();
        v.push_back(tmp);
        for(int j=1; j<n; j++) {
            scanf("%d", &tmp);
            if(tmp < v.front()) {
                if(tmp > v.back()) {
                    ans[i] = 1;
                } else {
                    v.push_back(tmp);
                }
            } else if(tmp > v.front()) {
                v.clear();
                v.push_back(tmp);
            }
            if(v.size() > m) {
                ans[i] = 1;
            }
        }
    }

    for(int i=0; i<k; i++) {
        if(ans[i]) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}
