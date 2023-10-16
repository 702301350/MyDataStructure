#include <iostream>
#include "src/myList.hpp"
#include "src/myArray.hpp"
#include "src/myQueue.hpp"
#include "src/myQueue.hpp"
#include "src/myStack.hpp"
using namespace std;

int main() {
	Queue<int>a;
	a.push(1);
	Queue<int>b = a;
	cout << b.front();
	return 0;
}
