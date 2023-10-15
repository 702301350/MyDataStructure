#include <iostream>
#include "myList.hpp"
#include "myArray.hpp"
#include "myGList.hpp"
using namespace std;

int main() {
	GList<int>a = {1, 2, {1, 2, 3}, 4, 5}, b = {2, 3, 4, 5};
	cout << a;
	return 0;
}
