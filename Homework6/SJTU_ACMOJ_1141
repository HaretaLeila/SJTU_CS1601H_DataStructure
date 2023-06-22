// 双哈希并且懒得做冲突处理

#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
int hash_table_1[2000300];
int hash_table_2[2000300];
char c[2000];
#define i64 unsigned long long
int main() {
    int res=0;
    int n=0;
    scanf("%d\n", &n);
    for(int i=0; i<n; i++) {
        cin.getline(c, 2000, '\n');
        i64 hash1=0, hash2=0;
        int n=strlen(c);
        for(int i=0; i<n; i++) hash1=(hash1*13331)%(2000003)+c[i];
        for(int i=0; i<n; i++) hash2=(hash2*131)%(2000083)+c[i];
        if (hash_table_1[hash1]!=0 && hash_table_2[hash2]!=0) continue;
        hash_table_1[hash1]=1, hash_table_2[hash2]=1;
        res++;
    }
    cout << res;
}
