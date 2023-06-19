/*
括号栈，但与普通括号匹配不同，额外要求删除功能
所以本题的难点就落在如何实现删除的同时做到括号栈的匹配查询
首先，需要一个栈s来如实记录所有push与pop操作
朴素的想法是每次查询是否匹配时将栈中所有元素进行一次普通括号匹配的检查，时间复杂度为O(n^2)
但是本题数据集过大，这样的做法会导致超时，需要转换思路
额外增添一个栈check来时刻维护括号是否匹配，check空等价于当前状态的所有括号为匹配状态
思考push的过程中做了什么操作：在右括号匹配左括号时将左括号弹出
在删除时，就有两种操作：
如实记录的栈s顶为左括号时，如实弹出check
如实记录的栈s顶为右括号时，此时如果这个右括号 *被匹配成功并且没有进入过check* 则需要向check补充左括号，反之说明右括号没有正确匹配，只需直接弹出check栈顶即可
有关如何确定右括号状态，可以通过在链式结构栈的节点结构体内增加一个bool类型的flag用于判断，在push时决定flag的取值
这种做法的时间复杂度为O(n)
*/
#include <cstdio>
using namespace std;
struct node {
	char val;
	bool flag;
	node* next;
};
class Stack {
private:
	node* head;
public:
	Stack() {
		head = nullptr;
	}
	void push(char c) {
		node* tmp = new node;
		tmp->val = c;
		tmp->flag = 0;
		tmp->next = head;
		head = tmp;
		return;
	}
	void pop() {
		if (head == nullptr) return;
		node* tmp = head->next;
		delete head;
		head = tmp;
		return;
	}
	node* top() {
		if (head == nullptr) return 0;
		return head;
	}
	bool empty() {
		return head == nullptr;
	}
	void clear() {
		while (head != nullptr) {
			pop();
		}
		return;
	}
};

int main() {
	Stack s;
	Stack check;
	int n = 0;
	scanf("%d", &n);
	char C = 'a';
	bool f = 0;
	int op = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &op);
		switch (op) {
		case 1:
			char c;
			char tool[10];
			scanf("%s", tool);
			c = tool[0];
			s.push(c);
			if (check.empty()) {
				check.push(c);
				break;
			}
			if (c == '[' || c == '{' || c == '(') {
				check.push(c);
				s.top()->flag = 0;
				break;
			}
			switch (c) {
			case ')':
				if (check.top()->val == '(') {
					check.pop();
					s.top()->flag = 1;
				}
				else {
					check.push(c);
					s.top()->flag = 0;
				}
				break;
			case ']':
				if (check.top()->val == '[') {
					check.pop();
					s.top()->flag = 1;
				}
				else {
					check.push(c);
					s.top()->flag = 0;
				}
				break;
			case '}':
				if (check.top()->val == '{') {
					check.pop();
					s.top()->flag = 1;
				}
				else {
					check.push(c);
					s.top()->flag = 0;
				}
				break;
			}
			break;
		case 2:
			if (s.empty()) break;
			C = s.top()->val;
			f = s.top()->flag;
			s.pop();
			switch (C) {
			case '{':
			case '[':
			case '(':
				check.pop();
				break;
			default:
				if (f) {
					if (C == ')') check.push('(');
					if (C == ']') check.push('[');
					if (C == '}') check.push('{');
				}
				else check.pop();
			}
			break;
		case 3:
			if (s.empty()) break;
			printf("%c\n", s.top()->val);
			break;
		case 4:
			if (check.empty()) printf("YES\n");
			else printf("NO\n");
			break;
		}
	}
	s.clear();
	return 0;
}
