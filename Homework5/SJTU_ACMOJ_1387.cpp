// 本题测试集有问题，第三个爆int，第四个爆long long，答案按照long long下给出，使用unsigned long long会wa
// 有关哈夫曼树权值和计算方法可以参考 https://zhuanlan.zhihu.com/p/515380547
// 可以直接算而不是真的去建树，一个节点每次被当作子树合并的时候相当于它底下的所有叶节点权重+1，就可以转换为答案加上该节点的值
#include <iostream>
#include <stdio.h>
#define ull long long
using namespace std;
// 简略实现优先队列
class priority_Queue {
public:
	ull* storage;
	int size = 0;
	int maxsize = 20;
	void doubleSpace() {
		maxsize *= 2;
		ull* tmp = new ull[maxsize];
		for (int i = 0; i < size; i++) {
			tmp[i] = storage[i];
		}
		delete[] storage;
		storage = tmp;
		return;
	}
	priority_Queue(int s = 20) {
		size = 0;
		maxsize = s;
		storage = new ull[maxsize];
	}
	bool empty() {
		return size == 0;
	}
    ull front() {
        return storage[0];
    }
	void push(ull elem) {
		if (size == maxsize) doubleSpace();
		storage[size] = elem;
		size++;
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
	void pop() {
		swap(storage[size - 1], storage[0]);
        size--;
        int index = 0;
		while (index * 2 + 1 < size) {
			int tmp = index * 2 + 1;
			if (tmp + 1 < size && storage[tmp + 1] < storage[tmp]) tmp++;
			if (storage[tmp] >= storage[index]) break;
			swap(storage[tmp], storage[index]);
			index = tmp;
		}
		return;
	}
};

int main() {
    int n=0;
    cin >> n;
    priority_Queue q;
    for(int i=0; i<n; i++) {
        ull val;
        cin >> val;
        q.push(val);
    }
    ull ans=0;
    for(int i=0; i<n-1; i++) {
        ull a=q.front();
        q.pop();
        ull b=q.front();
        q.pop();
        ull c=a+b;
        q.push(c);
        ans+=c;
    }
    cout << ans << endl;
    return 0;
}
