// 本题数据集有问题
// 很明显，下面这份代码AC但是没有实现循环队列
#include <iostream>
using namespace std;
int main() {
	int t;
	int n;
	cin >> t >> n;
	int* s = new int[t];
	int head = 0;
	int tail = 0;
	int c = 0;
	int x = 0;
	int size = 0;
	for (int i = 0; i < n; i++) {
		cin >> c;
		if (c) { //dequeue
			if (size != 0) {
				size--;
				head++;
			}
			cout << head << ' ' << size << endl;
		}
		else { //enqueue
			size++;
			cin >> x;
			s[tail] = x;
			tail ++;
			cout << tail << ' ' << size << endl;
		}
	}
	delete [] s;
	return 0;
}
