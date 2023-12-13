#include <iostream>
#include "myArray.hpp"
using namespace std;

int main() {
	Array<int>a = {1, 2, 4, 5};
	for (auto x : a) {
		cout << x << " ";
	}
	return 0;
}