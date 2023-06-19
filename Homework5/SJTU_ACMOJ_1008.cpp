/*
本题有多种可AC写法
以下链接给出二维前缀和的解法，时间复杂度O(n^2 logn)
https://blog.csdn.net/weixin_51394621/article/details/118682664
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int n=0, m=0, ans=0;
    scanf("%d %d",&n,&m);
    int dp[2][m];
    char line[m];
    for(int i=0; i<n; i++) {
        scanf("%s",line);
        for(int j=0; j<m; j++) {
            if (j==0 || line[j-1]!='-' || line[j]!='-') dp[i%2][j]=0;
            else if (i<1 || j<2) dp[i%2][j]=1;
            else dp[i%2][j]=min(dp[i%2][j-2], min(dp[(i+1)%2][j], dp[(i+1)%2][j-2]))+1;
            ans=max(ans, dp[i%2][j]);
        }
    }
    printf("%d", ans*ans*2);
    return 0;
}
/*
动态规划解法，时间O(n^2) 空间O(n)
dp[i][j]表示以(i,j)为右下角的空白矩形的最大高度
转移方程dp[i][j]=min{dp[i-1][j], dp[i][j-2], dp[i-1][j-2]}+1
对于dp[i][j]本身不可放或i-1与j-2越界的情况特判
只用到当前行和前一行数据，所以可以滚动数组
*/
