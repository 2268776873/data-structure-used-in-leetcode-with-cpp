#include <iostream>


#include "trie.h"
#include "trie2.h"

using namespace std;


int main() {

    trie2 te(7);
    te.add(1, 2);
    te.add(0, 5);
    te.add(4, 4);

    vector<vector<int>> ans = te.serach(2);
    for (auto v : ans) {
        for (int i : v)
            cout << i << "\t";
        cout << endl;
    }



    return 0;
}
