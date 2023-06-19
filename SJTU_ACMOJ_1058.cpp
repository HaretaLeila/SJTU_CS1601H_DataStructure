#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE {
        int val;
        NODE* next;
    };
    NODE* head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        return;
    }

    NODE* move(int i) { //移动i次后的节点，head为移动0次，tail为移动len-1次，LIST[i]移动[i]次
        NODE* ptr = head;
        for (int k = 0; k < i; k++) {
            ptr = ptr->next;
        }
        return ptr;
    }

    void insert(int i, int x) {
        if (len == 0) {
            init();
            head = new NODE;
            head->val = x;
            head->next = head;
            len = 1;
            return;
        }
        if (i == 0) {
            NODE* tail = move(len - 1);
            NODE* tmp = new NODE;
            tmp->val = x;
            tmp->next = head;
            head = tmp;
            tail->next = head;
            len++;
            return;
        }
        NODE* tmp = move(i - 1);
        NODE* a = new NODE;
        a->val = x;
        a->next = tmp->next;
        tmp->next = a;
        len++;
        return;
    }

    void remove(int i) {
        if (i == 0) {
            if (len == 0) return;
            NODE* tail = move(len - 1);
            NODE* tmp = head;
            head = head->next;
            tail->next = head;
            len--;
            if (len == 0) init();
            delete tmp;
            return;
        }
        NODE* tmp = move(i - 1);
        NODE* tmpNext = tmp->next;
        tmp->next = tmp->next->next;
        len--;
        delete tmpNext;
        if (len == 0) init();
        return;
    }

    void remove_insert(int i) {
        if (len == 0) return;
        if (i == 0) {
            head = head->next;
            return;
        }
        if (i == len - 1) return;
        NODE* target = move(i);
        NODE* pre = move(i - 1);
        NODE* tail = move(len - 1);
        NODE* back = target->next;
        pre->next = back;
        tail->next = target;
        target->next = head;
        return;
    }

    void get_length() {
        cout << len << endl;
        return;
    }

    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << endl;
            return;
        }
        cout << move(i)->val << endl;
        return;
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << endl;
            return;
        }
        int m = -1;
        NODE* ptr = head;
        for (int k = 0; k < len; k++) {
            ptr = ptr->next;
            m = max(m, ptr->val);
        }
        cout << m << endl;
        return;
    }

    void clear() {
        if (len == 0) return;
        if (len == 1) {
            delete head;
            return;
        }
        if (len == 2) {
            delete head->next;
            delete head;
        }
        NODE* tmp = head->next;
        delete head;
        for (int i = 0; i < len - 2; i++) {
            head = tmp;
            tmp = tmp->next;
            delete head;
        }
        delete tmp;
    }
}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch (op) {
        case 0:
            LIST::get_length();
            break;
        case 1:
            cin >> p >> x;
            LIST::insert(p, x);
            break;
        case 2:
            cin >> p;
            LIST::query(p);
            break;
        case 3:
            cin >> p;
            LIST::remove(p);
            break;
        case 4:
            cin >> p;
            LIST::remove_insert(p);
            break;
        case 5:
            LIST::get_max();
            break;
        }
    }
    LIST::clear();
    return 0;
}
