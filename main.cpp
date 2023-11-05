#include <iostream>
#include "src/myCBinTree.hpp"
#include "src/myString.cpp"
using namespace std	;

int main() {
	Array<int>a = {10, 25, 40, 50, 65, 75, 80}, b = {10, 40, 25, 65, 80, 75, 50};
	CBinTree<int>tree(a, MIDO, b, AFTERO);

	Array<int>c = tree.traverse(PRECO);
	for (auto &x : c) {
		cout << x << " ";
	} 
	return 0;
}