/*
在接受输入的同时统计陆地的数量cnt。并记录一个任意的陆地地块作为dfs的起点start point (i, j) -> si, sj
深搜搜索到的陆地数量为_cnt，cnt==_cnt等价于该状态连通

对于无解的情况：
如果所有未知地块全部被看作陆地后，从(si, sj)开始dfs，记录下搜索经过的陆地数量_cnt
如果cnt!=_cnt，则可以充分断定无解(以最可能连通的方式去检测仍然不能连通)
反之如果cnt==_cnt则可以确定至少有一解，从而达成对无解的判定

对于多解的情况：
先把所有未知地块看作陆地，如果多解，则必定存在未知地块x，当x被设置回湖泊时，仍然从(si, sj)开始dfs
只需要遍历全图->
遇到未知地块，设为湖泊->
dfs一次记录_cnt->
判断_cnt==cnt是否成立即可

如果存在一个地块x，设回湖泊时陆地仍然连通，则说明该地块是多余的，因而该图有多解，此时直接输出并return即可

对于单解的情况：
到此处应该注意到visited1[][]这个数组
该数组在初次dfs时标识了所有途径的点，并且在后续dfs中没有改变过(后边的dfs搜到的范围是从初次dfs中移除部分元素的，因为将未知区域设为湖泊后搜到的地块只会变少)
它只会在非无解的情况发挥作用(因为无解直接return了，后续没有再用到visited1[][]）
一是在判断多解的时候排除**孤立的**由未知区域组成的地区：
假设在陆地之外存在一个独立的未知地块，如果我们尝试把这个地块设置为湖泊，这时再深搜是会出问题的！
例如下图的测试案例，如果不跳过**孤立的**由未知区域组成的地区，则会得到多解的结果，但是实际上这个图是唯一解
#####
#...#
#####
##?##
#####
解决这个问题的方法就是初次深搜时标定visited1[][]，在设未知区域为湖泊时跳过没有被初次深搜标定的地块，即可避免
二是用于输出单解的图
首先，单解的图内只有'.'和'#'
到这里应该能够理解，只需要把visited1[][]中1当作'.', 0当作'#'输出就是单解的答案
多解的搜索过程中，看作湖泊的都是visited1[][]标记过的未知地块，这些地块都会导致cnt!=_cnt，也就是说这些地块对于陆地的连通都是必要的
同时，初次深搜未标记过的未知区域肯定不会设为陆地
*/

#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, cnt=0, _cnt=0, N=0, si, sj;
int M[60][60], visited[60][60], visited1[60][60];
int di[]={1, 0, -1, 0}, dj[]={0, 1, 0, -1};
void dfs(int i, int j) {
    if (visited[i][j] || M[i][j]==0) return;
    visited[i][j]=visited1[i][j]=1;
    if (M[i][j]==1) _cnt++;
    for(int t=0; t<4; t++) {
        int fi=i+di[t], fj=j+dj[t];
        if (!(fi>=0 && fj>=0 && fi<n && fj<m)) continue;
        dfs(fi, fj);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; i++) {
        char s[100];
        scanf("%s", s);
        for(int j=0; j<m; j++) {
            if (s[j]=='#') M[i][j]=0;
            else if (s[j]=='.') {
                M[i][j]=1;
                cnt++;
                si=i, sj=j; // 此处si, sj用于标识深搜的起点
            }
            else M[i][j]=2;
        }
    }
    dfs(si, sj);
    if (_cnt!=cnt) {
        printf("Impossible");
        return 0;
    } // 判断无解结束
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (M[i][j]!=2 || visited1[i][j]==0) continue;
            _cnt=0;
            memset(visited, 0, sizeof(visited));
            M[i][j]=0;
            dfs(si, sj);
            if (_cnt==cnt) {
                printf("Ambiguous");
                return 0;
            }
            M[i][j]=2;
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
            printf(visited1[i][j]?".":"#");
        printf("\n");
    }
    return 0;
}
