// 本写法为模拟方法，使用单循环链表进行模拟
// 本题另有数学解法，参考知乎专栏https://www.zhihu.com/tardis/zm/art/121159246?source_id=1005
#include <iostream>
using namespace std;
struct node {
	int val;
	node* next;
};
int main() {
	int M;
	cin >> M;
	node* head = new node;
	head->val = 1;
	node* ptr = head;
	int size = M;
	for (int i = 2; i <= M; i++) {
		ptr->next = new node;
		ptr = ptr->next;
		ptr->val = i;
	}
	ptr->next = head;
	for (int i = 0; i < M - 1; i++) {
		int k;
		cin >> k;
		k %= size;
		if (k == 0) k = size;
		for (int i = 0; i < k - 1; i++) {
			head = head->next;
			ptr = ptr->next;
		}
		ptr->next = head->next;
		delete head;
		head = ptr->next;
		size--;
	}
	cout << (ptr->val);
	delete ptr;
	return 0;
}
