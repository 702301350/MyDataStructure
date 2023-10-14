#include <iostream>
#include "myGList.hpp"
using namespace std;

int main() {
	GList<int>a = {1, 2, {2, 3, 4}, 8}, b = {2, 3, {3, {1, 2, 3}, 4}, 2};
	// b[2].modify(1, a);
	// cout << b;
	b[2] = a;
	cout << b;
	return 0;
}
