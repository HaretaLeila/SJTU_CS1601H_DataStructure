// 本题主要卡时间，只需要想到二分查找降复杂度就可以AC
#include <stdio.h>
using namespace std;
int main() {
    int prev = 0, cur = 0;
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    int* preSum = new int[n+5];
    preSum[0]=0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cur);
        prev += cur;
        preSum[i] = prev;
    }

    int target = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &target);
        int left=0, right=n; // binary search [left, right];
        int mid;
        while(left<=right) {
            if (preSum[right]<target) {
                mid=right+1;
                break;
            }
            mid=(left+right)/2;
            if (preSum[mid]>=target) right=mid-1;
            else left=mid+1;
        }
        printf("%d %d\n", mid, target-preSum[mid-1]);
    }
    return 0;
}
