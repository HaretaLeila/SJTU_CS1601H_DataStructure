// 典中典的下象棋问马能到哪的问题
// 使用bfs，每次向外延展一层，只需要记录搜的层数，搜到目标点直接输出并返回即可
#include <iostream>
#include <queue>
using namespace std;
int mp[40][40];
int vis[40][40];
struct p {
    int x, y;
    p(int _x, int _y):x(_x), y(_y){};
};
int main() {
    int n, m;
    cin >> m >> n;
    int m1, m2;
    cin >> m1 >> m2;
    int dx[]={-m1, -m1, -m2, -m2, m2, m2, m1, m1};
    int dy[]={m2, -m2, m1, -m1, m1, -m1, m2, -m2};
    int si, sj, ei, ej;
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            int a;
            cin >> a;
            if (a==1 || a==3 || a==4) mp[i][j]=1;
            if (a==3) si=i, sj=j;
            if (a==4) ei=i, ej=j;
        }
    }
    vis[si][sj]=1;
    queue<p> q;
    int ans=0;
    q.push(p(si, sj));
    auto isLegal=[&](int x, int y)->bool {
        return x>=0 && x<m && y>=0 && y<n;
    };
    while(!q.empty()) {
        ans++;
        int N=q.size();
        while(N--) {
            auto p1=q.front();
            q.pop();
            int x=p1.x, y=p1.y;
            for(int i=0; i<8; i++) {
                int xx=x+dx[i], yy=y+dy[i];
                if (!isLegal(xx, yy) || vis[xx][yy]==1 || mp[xx][yy]!=1) continue;
                if (xx==ei && yy==ej) {
                    cout << ans;
                    return 0;
                }
                q.push(p(xx, yy));
                vis[xx][yy]=1;
            }
        }
    }
    return 0;
}
