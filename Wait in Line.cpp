#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct client{
    int start;
    int cno;
    int need;
    int leave;
    client(int start,int cno,int need) {
        this->start = start;
        this->cno = cno;
        this->need = need;
        this->leave = need + start;
    }
};

void tohour(int min,char times[]) {
    int h = min / 60 + 8;
    times[0] = (h / 10) + '0';
    times[1] = (h % 10) + '0';
    int m = min % 60;
    times[3] = (m / 10) + '0';
    times[4] = (m % 10) + '0';
    return;
}

int main(int argc, char const *argv[]) {
    int N,M,K,Q,j=0;
    int need,start=0;
    int earliest_leave;
    scanf("%d%d%d%d", &N,&M,&K,&Q);
    vector<deque<client> > queue_lst(N,deque<client>());
    int* fin_time = (int*)malloc(K * sizeof(int));
    for(int i=0;i<min(N*M,K);i++) {
        scanf("%d", &need);
        if(j>=N) start = queue_lst[j%N].back().leave;
        queue_lst[(j++)%N].push_back(client(start,i,need));
    }
    for(int i=N*M;i<K;i++) {
        scanf("%d", &need);
        earliest_leave = queue_lst[0].front().leave;
        j = 0;
        for(int k=1;k<N;k++) {
            if(queue_lst[k].front().leave < earliest_leave){
                j = k;
                earliest_leave = queue_lst[k].front().leave;
            }
        }
        if(queue_lst[j].front().start < 540 ) fin_time[queue_lst[j].front().cno] = queue_lst[j].front().leave;
        start = queue_lst[j].back().leave;
        queue_lst[j].pop_front();
        queue_lst[j].push_back(client(start,i,need));
    }
    for(deque<client> q : queue_lst) {
        while(! q.empty()) {
            if(q.front().start < 540) fin_time[q.front().cno] = q.front().leave;
            q.pop_front();
        }
    }
    int query;
    for(int i=0;i<Q;i++) {
        scanf("%d", &query);
        if(fin_time[query-1] > 0 ) {
            char times[6] = {'0','0',':','0','0','\0'};
            tohour(fin_time[query-1],times);
            printf("%s\n", times);
        }
        else printf("%s\n", "Sorry");
    }
    return 0;
}
