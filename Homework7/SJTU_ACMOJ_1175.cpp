// 本题与前面的排队那题一样，只需排序即可
// 这里用了优先队列，和排序是一样的效果，可能会慢一点不过不会慢太多

#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
#define ull unsigned long long
inline ull max(ull a, ull b){return a>b?a:b;};
inline ull min(ull a, ull b){return a<b?a:b;};
inline int read() {
	int x=0, f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
    return x*f;
}
int main() {
    int N=read();
    int li[N+5];
    for(int i=0; i<N; i++) li[i]=read();
    int M=read();
    int sex=0;
    priority_queue<int, vector<int>, greater<int>> q0, q1;
    for(int i=0; i<M; i++) {
        sex=read();
        if (sex==1) q0.push(read());
        else q1.push(read());
    }
    int male_cnt=q0.size();
    int female_cnt=q1.size();
    queue<int> Q0, Q1;
    int time=0;
    ull male_total_wait_time=0;
    ull female_total_wait_time=0;
    for(int i=0; i<N; i++) {
        while(!q0.empty() && q0.top()<=time) {
            int a=q0.top();
            q0.pop();
            Q0.push(a);
        }
        while(!q1.empty() && q1.top()<=time) {
            int a=q1.top();
            q1.pop();
            Q1.push(a);
        }
        while(!Q0.empty() && !Q1.empty()) {
            int a=Q0.front();
            Q0.pop();
            int b=Q1.front();
            Q1.pop();
            male_total_wait_time+=time-a;
            female_total_wait_time+=time-b;
        }
        time+=li[i];
    }
    time-=li[N-1];
    while(!q0.empty()) {
        male_total_wait_time+=time-q0.top();
        q0.pop();
    }
    while(!q1.empty()) {
        female_total_wait_time+=time-q1.top();
        q1.pop();
    }
    while(!Q0.empty()) {
        male_total_wait_time+=time-Q0.front();
        Q0.pop();
    }
    while(!Q1.empty()) {
        female_total_wait_time+=time-Q1.front();
        Q1.pop();
    }
    printf("%.2f %.2f", double(male_total_wait_time)/double(male_cnt), double(female_total_wait_time)/double(female_cnt));
    return 0;
}
