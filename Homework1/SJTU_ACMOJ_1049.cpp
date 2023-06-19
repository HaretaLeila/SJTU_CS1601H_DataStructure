// 简单想法，按照递归恢复二叉树并层序遍历即可，注意处理输出状态，需要从后向前寻找最后一个需要输出的元素
// 此题也有直接映射进入数组的做法
#include <iostream>
#include <cstring>
using namespace std;

struct node {
	char val;
	node* left;
	node* right;
	node(char v) {
		val = v;
		left = nullptr;
		right = nullptr;
	}
};
node* root = nullptr;
node* build(char pre[], int pl, int pr, char mid[], int ml, int mr) {
	if (pl > pr) return nullptr;
	node* p = new node(pre[pl]);
	if (!root) root = p;
	int pos = 0;
	int i = 0;
	int num = 0;
	for (i = ml; i <= mr; i++) {
		if (mid[i] == pre[pl]) break;
	}
	pos = i;
	num = pos - ml;
	p->left = build(pre, pl + 1, pl + num, mid, ml, pos - 1);
	p->right = build(pre, pl + num + 1, pr, mid, pos + 1, mr);
	return p;
}
int main() {
	char pre[30];
	char mid[30];
	cin >> pre >> mid;
	int size = strlen(pre);
	build(pre, 0, size-1, mid, 0, size-1);
	node* res[5000]{ nullptr };
	res[0] = root;
	int fast = 0;
	int slow = 0;
	bool flag = 1;
	while (flag && fast < 2000) {
		fast = fast * 2 + 1;
		flag = 0;
		for (int i = slow; i < fast; i++) {
			if (res[i] == nullptr) continue;
			flag = 1;
			node* tmp = res[i];
			if (tmp->left != nullptr) res[i * 2 + 1] = tmp->left;
			if (tmp->right != nullptr) res[i * 2 + 2] = tmp->right;
		}
		slow = fast;
	}
	int lim = 1500;
	while (res[lim] == nullptr) lim--;
	for (int i = 0; i <= lim; i++) {
		if (res[i] == nullptr) cout << "NULL" << ' ';
		else cout << res[i]->val << ' ';
	}
	return 0;
}
