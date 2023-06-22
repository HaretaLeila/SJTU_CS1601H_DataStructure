// 本题因为未知原因必须增加一个find函数才可以通过
// 直接删除会导致wa
// 大概率为出题问题

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int val[100005], rc[100005], lc[100005];
// rc: right child, lc:left child
int cnt=1;
int ptr=0;
char output[100005];
bool search(int x, int cur) {
    if (cur==0) {
        return 0;
    }
    else if (x==val[cur]) {
        output[ptr]='\n';
        return 1;
    }
    else if(x>val[cur]) {
        output[ptr++]='r';
        return search(x, rc[cur]);
    }
    else {
        output[ptr++]='l';
        return search(x, lc[cur]);
    }
}
void insert(int x, int& cur) {
    if (cur==0) {
        cur=cnt;
        return;
    }
    if (x==val[cur]) return;
    else if(x>val[cur]) insert(x, rc[cur]);
    else insert(x, lc[cur]);
}
void find(int x, int& cur) {
    if (val[cur]>x) find(x, lc[cur]);
    if (val[cur]<x) find(x, rc[cur]);
    if (x==val[cur]) cur=rc[cur];
}
void erase(int x, int& cur) {
    if (cur==0) return;
    if (x<val[cur]) erase(x, lc[cur]);
    else if(x>val[cur]) erase(x, rc[cur]);
    else {
        if (rc[cur]==0 && lc[cur]==0) cur=0;
        else if (rc[cur]==0) {
            cur=lc[cur];
        }
        else {
            int tmp=rc[cur];
            while(lc[tmp]!=0) tmp=lc[tmp];
            val[cur]=val[tmp];
            find(val[cur], rc[cur]);
        }
    }
}
int main() {
    int n=0;
    int root=0;
    scanf("%d\n", &n);
    while(n--) {
        char op, s[10];
        scanf("%s", s);
        op=s[0];
        int x=0;
        scanf("%d", &x);
        if (op=='+') {
            val[++cnt]=x;
            insert(x, root);
        }
        else if (op=='-') {
            erase(x, root);
        }
        else {
            output[0]='*';
            ptr=1;
            if (search(x, root)) {
                for(int i=0; i<=ptr; i++) printf("%c", output[i]);
            }
            else printf("Nothing.\n");
        }
    }
    return 0;
}
