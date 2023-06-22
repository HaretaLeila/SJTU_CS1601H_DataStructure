/*
主要难点在于corner cases和溢出
以高度排序增加水的容积，每次增加的容积是[已数的完全覆盖的地块数量]*[这个地块和上个地块的高度差]
当容积增加到大于水的体积，回退一步并计算小数点部分的值
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define ull unsigned long long
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
inline ull max(ull a, ull b){return a>b?a:b;};
inline ull min(ull a, ull b){return a<b?a:b;};
ull* num;
ull* tmp;

// 排序采用归并的板子，这里为了省事直接用了全局数组
void merge(int l, int m, int h) {
    int i=l, j=m+1, k=l;
    while(i<=m && j<=h) {
        if (num[i]<num[j]) tmp[k++]=num[i++];
        else tmp[k++]=num[j++];
    }
    while(i<=m) tmp[k++]=num[i++];
    while(j<=h) tmp[k++]=num[j++];
    for(int i=l; i<=h; i++) num[i]=tmp[i];
}
void merge_sort(int l, int r) { //merge_sort for array:[l, r]
    if (l>=r) return;
    int m=(l+r)/2;
    merge_sort(l, m);
    merge_sort(m+1, r);
    merge(l, m, r);
}

int main() {
    int m=read(), n=read();
    num=new ull[m*n+5];
    tmp=new ull[m*n+5];
    ull Min=INT64_MAX;
    for(int i=0; i<m*n; i++) {
        num[i]=read();
        Min=min(Min, num[i]);
    }
    ull v;
    cin >> v;
    if (v==0) {
        printf("%.2f\n", double(Min));
        printf("0.00");
        return 0;
    }
    merge_sort(0, m*n-1);
    int i=1; //完全覆盖了i个地块
    int curheight=Min;
    num[m*n]=num[m*n-1]+v;
    while(i<=m*n) {
        int layerVolume=(num[i]-num[i-1])*i;
        if (layerVolume>=v) break;
        v-=layerVolume;
        curheight=num[i];
        i++;
    }
    double h=double(curheight)+double(v)/double(i);
    double percent=100.0*double(i)/double(m*n);
    printf("%.2f\n%.2f", h, percent);
}
