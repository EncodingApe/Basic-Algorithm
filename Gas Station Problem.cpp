#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct station {
    float price;
    float dis;
}* sta;

bool cmp(const station* s1,const station* s2) {
    return s1->dis < s2->dis;
}

int main(int args,char* argv[]) {
    int max_cap,dis,aver_run,n; // 油箱容量 距离 每单位可走多远 加油站个数
    scanf("%d%d%d%d",&max_cap,&dis,&aver_run,&n);
    int max_run = max_cap * aver_run;
    vector<station*> v;
    for(int i=0;i<n;i++) {
        sta = new station();
        scanf("%f%f",&sta->price,&sta->dis);
        v.push_back(sta);
    }
    sort(v.begin(),v.end(),cmp);
    if(v[0]->dis!=0) { printf("The maximum travel distance = %.2f", 0.000); return 0;}
    float min_cost = 0.0,price,cur_tank=0,need_tank;
    int cur_sta = 0,flag,i;
    while(true) {
        flag = 0;
        price = v[cur_sta]->price;  // 调整当前价格
        for(i=cur_sta+1;i < n && v[i]->dis - v[cur_sta]->dis <= max_run;i++) {   // 先找规定范围内第一个比自己便宜的
            flag = 1;   // 代表存在一个站在范围之内
            if(v[i]->price < price) break;
        }
        if(i == n) {
            if(dis - v[cur_sta]->dis > max_run) { printf("The maximum travel distance = %.2f", v[cur_sta]->dis+max_run); return 0; };
            need_tank = (dis - v[cur_sta]->dis) / aver_run;
            min_cost += (need_tank - cur_tank) * price;
            break;
        }
        if(! flag) { printf("The maximum travel distance = %.2f", v[cur_sta]->dis+max_run); return 0; }; // 范围之内没有任何站 则无法继续前进
        if(v[i]->dis - v[cur_sta]->dis <= max_run) {   // 找到范围内第一个比自己便宜的 则加足够的油 !刚好! 到达那里
            need_tank = (v[i]->dis - v[cur_sta]->dis) / aver_run;
            if(cur_tank < need_tank) {
                min_cost += (need_tank - cur_tank) * price;
                cur_tank = need_tank;
            }
            cur_sta = i;
            cur_tank -= need_tank;
        }
        else {  // 未找到 比当前便宜的 则在当前地方加满油 开往下一个地方
            min_cost += (max_cap - cur_tank) * price;
            cur_tank = max_cap - (v[cur_sta+1]->dis - v[cur_sta]->dis) / aver_run;
            cur_sta++;
        }
    }
    printf("%.2f\n", min_cost);
    return 0;
}
