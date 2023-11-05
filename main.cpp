#include "src/myBBinTree.hpp"
#include <iostream>
using namespace std;

int main() {
	BBinTree<int>tree(greater<int>{});
	BBinTree<int>tree2(less<int>{});
	Array<int>arr = { 2, 4, 1, 3, 5, 6, 5, 6, 1 };
	for (int x : arr) {
		tree.insert(x);
	}

	tree.merge(tree2);
	Array<int>res = tree.traverse(PRECO);
	for (int x : res) {
		cout << x << " ";
	}
	cout << "\n";
	cout << tree.has(6) << "\n";

	res = tree.traverse(PRECO);
	for (int x : res) {
		cout << x << " ";
	}

	return 0;
}