#include <iostream>
#include "src/myList.hpp"
#include "src/myArray.hpp"
using namespace std;

int main() {
	Array<int>a = {2, 3, 4, 5, 6};
	List<int>b;

	for (auto &x: a) {
		b.insert(x);
	}
	for (int i = 0;i < b.length();i ++) {
		cout << b[-i] << " ";
	}
	cout << "\n";
	return 0;
}