// 所谓镜像一个树再后序遍历，实际上直接右->左->中深搜即可，注意建树方式，v[i][0,1,2]表示节点i的值，左子节点和右子节点
#include <iostream>
int v[10005][2];
void dfs(int node) {
	if (node <= 0) return;
	dfs(v[node][1]);
	dfs(v[node][0]);
	std::cout << node << ' ';
}
int main() {
	int n, a, root = 114514;
	std::cin >> n;
	while(n--) {
		std::cin >> a >> v[a][0] >> v[a][1];
		if (root == 114514) root = a;
	}
	dfs(root);
	return 0;
}
