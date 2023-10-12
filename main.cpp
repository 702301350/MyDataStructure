#include <iostream>
#include "myArray.hpp"
#include "myList.hpp"
#include "myStack.hpp"
#include "myQueue.hpp"
#include "myString.hpp"
// #include "myGList.hpp"

#include "myString.cpp"
using namespace std;

int main() {
	Array<int>a = {1, 2, 3, 4, 5};
	for (auto &x : a) {
		cout << x << " ";
	}
	return 0;
}
