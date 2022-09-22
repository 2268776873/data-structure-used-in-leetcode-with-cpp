#pragma once

#include <vector>

using namespace std;

class trie2 {
public:
    trie2(int _n) :n(_n) {
        tree.resize(4 * _n, 0);
        lazy.resize(4 * _n, 0);
    }

    void add(int l, int r) {
        add(l, r, 0, n - 1, 0);
    }

    vector<vector<int>> serach(int m) {
        vector<vector<int>> tmp;
        search(m, 0, n - 1, 0, tmp);
        vector<vector<int>> ans;
        for (auto& v : tmp) {
            if (ans.empty() || ans.back()[1] != v[0] - 1) {
                ans.emplace_back(v);
            }
            else
                ans.back()[1] = v[1];
        }
        return ans;
    }

private:
    void add(int l, int r, int cl, int cr, int i) {
        if (cl > r || cr < l)
            return;
        if (cl >= l && cr <= r) {
            ++tree[i];
            ++lazy[i];
            return;
        }
        int mid = (cl + cr) / 2;
        add(l, r, cl, mid, i * 2 + 1);
        add(l, r, mid + 1, cr, i * 2 + 2);
    }

    void search(int m, int cl, int cr, int i, vector<vector<int>>& ret) {
        if (tree[i] >= m) {
            ret.push_back({ cl,cr });
            return;
        }
        if (cl == cr)
            return;
        pushdown(i);
        int mid = (cl + cr) / 2;
        search(m, cl, mid, i * 2 + 1, ret);
        search(m, mid + 1, cr, i * 2 + 2, ret);
    }

    void pushdown(int i) {
        tree[2 * i + 1] += lazy[i];
        tree[2 * i + 2] += lazy[i];
        lazy[2 * i + 1] += lazy[i];
        lazy[2 * i + 2] += lazy[i];
        lazy[i] = 0;
    }

    vector<int>tree;
    vector<int>lazy;
    int n;
};