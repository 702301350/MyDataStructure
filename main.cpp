#include <iostream>
#include "myArray.hpp"
#include "myGList.hpp"
using namespace std;

int main() {
	Array<int>arr[] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8}
	};
	
	GList<int>ggglist = {1, {1, {1, 2}, 2, 3}, 4, {2, 1, 3, 2, {22, 11}}};
//	cout << ggglist[3] << "\n";
	
	GList<int>gglist = {2, 1, 3, 5, 3};
	GList<int>glist;
	glist.push_back(arr[0]);
	glist.push_back(arr[1]);
	glist.push_back(11);
	glist.push_back(gglist);
	cout << glist << " ";
	return 0;
}
