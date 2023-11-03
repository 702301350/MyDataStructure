#include <iostream>
#include "src/myBinTree.hpp"
//#include "src/myString.hpp"
//#include "src/myString.cpp"
using namespace std;

bool func(int a, int b) {
	return true;
}

int main() {
	String str = "1234567";
	Array<int>num = {5, 2, 1, 3, 7};

	BinTree<int> bin( func );
	for (int i = 0;i < 5;i ++) {
		bin.insert(num[i], str.substr(0, i + 1));
	}

	bin.delSubTree("12");
	Array<int>a = bin.traverse(PRECO);
	for (auto &x : a) {
		cout << x << " ";
	}
	cout << "\n";

	cout << bin.isFull() << " " << bin.isComplete() << " " << bin.deepth() << " " << bin.size() << "\n";
	return 0;
}