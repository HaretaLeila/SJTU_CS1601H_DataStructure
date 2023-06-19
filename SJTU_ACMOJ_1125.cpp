// 本题只需要维护一个优先队列即可，建议自己写，不过使用stl queue中的priority_queue也没有扣分
// 不过数据集相当弱，优先队列用插入排序O(n^2)都能过(from 舍友)
#include <iostream>
#include <stdio.h>
#define init 20
using namespace std;
class Vector {
public:
	int* storage;
	int size = 0;
	int maxsize = 20;
	void doubleSpace() {
		maxsize *= 2;
		int* tmp = new int[maxsize];
		for (int i = 0; i < size; i++) {
			tmp[i] = storage[i];
		}
		delete[] storage;
		storage = tmp;
		return;
	}
	Vector(int s = 20) {
		size = 0;
		maxsize = s;
		storage = new int[maxsize];
	}
	int Size() {
		return size;
	}
	bool empty() {
		return size == 0;
	}
	void push_back(int elem) {
		if (size == maxsize) doubleSpace();
		storage[size] = elem;
		size++;
	}
	void pop_back() {
		if (empty()) {
			return;
		}
		size--;
		return;
	}
	int& operator [] (int index) {
		return storage[index];
	}
	void goDown() {
		int index = 0;
		swap(storage[size - 1], storage[0]);
		pop_back();
		while (index * 2 + 1 < size) {
			int tmp = index * 2 + 1;
			if (tmp + 1 < size && storage[tmp + 1] < storage[tmp]) tmp++;
			if (storage[tmp] >= storage[index]) break;
			swap(storage[tmp], storage[index]);
			index = tmp;
		}
		return;
	}
	void goUp(int val) {
		push_back(val);
		int index = size - 1;
		int father = (index - 1) / 2;
		while (index > 0) {
			if (storage[index] < storage[father]) {
				swap(storage[index], storage[father]);
				index = father;
				father = (father - 1) / 2;
			}
			else break;
		}
	}
};
int main() {
	int n = 0;
	int m = 0;
	scanf("%d %d", &n, &m);
	Vector** v = new Vector*[n];
	int val;
	for (int i = 0; i < n; i++) {
		scanf("%d", &val);
		v[i] = new Vector();
		v[i]->push_back(val);
	}
	int op = 0;
	while (m--) {
		cin >> op;
		switch (op) {
		case 0: {
			int a;
			int b;
			bool flag = 0;
			scanf("%d %d", &a, &b);// merge b into a
			if (v[a]->Size() < v[b]->Size()) {
				swap(v[a], v[b]);
				flag = 1;
			}
			for (int i = 0; i < v[b]->Size(); i++) {
				v[a]->goUp((*v[b])[i]);
			}
			break;
		}
		case 1: {
			int a;
			scanf("%d", &a);
			if (v[a]->empty()) {
				printf("-1\n");
				break;
			}
			printf("%d\n", (*v[a])[0]);
			v[a]->goDown();
			break;
		}
		case 2: {
			int a;
			int b;
			scanf("%d %d", &a, &b);
			v[a]->goUp(b);
			break;
		}
		}
	}
	return 0;
}
