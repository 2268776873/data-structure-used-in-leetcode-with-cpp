#pragma once
#include <vector>
using namespace std;

class trie {
public:
    trie(const vector<int>& v) {
        n = v.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            add(i, i, v[i]);
        }
    }
    trie(int _n) :n(_n) {
        tree.resize(4 * _n, 0);
        lazy.resize(4 * _n, 0);
    }

    void add(int l, int r, int m) {
        add(l, r, m, 0, n - 1, 0);
    }

    int serach(int l, int r) {
        return serach(l, r, 0, n - 1, 0);
    }
private:
    void add(int l, int r, int m, int cl, int cr, int i) {
        if (cl > r || cr < l)
            return;
        if (cl >= l && cr <= r) {
            tree[i] += (cr - cl + 1) * m;
            lazy[i] += m;
            return;
        }
        int mid = (cl + cr) / 2;
        add(l, r, m, cl, mid, i * 2 + 1);
        add(l, r, m, mid + 1, cr, i * 2 + 2);
        tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
    }

    int serach(int l, int r, int cl, int cr, int i) {
        if (cl > r || cr < l)
            return 0;
        if (cl >= l && cr <= r) {
            return tree[i];
        }
        int mid = (cl + cr) / 2;
        pushdown(i, mid - cl + 1, cr - mid);
        int left = serach(l, r, cl, mid, i * 2 + 1);
        int right = serach(l, r, mid + 1, cr, i * 2 + 2);
        return left + right;
    }

    void pushdown(int i, int lenl, int lenr) {
        tree[2 * i + 1] += lazy[i] * (lenl);
        tree[2 * i + 2] += lazy[i] * (lenr);
        lazy[2 * i + 1] += lazy[i];
        lazy[2 * i + 2] += lazy[i];
        lazy[i] = 0;
    }

    vector<int>tree;
    vector<int>lazy;
    int n;
};