#include <iostream>
#include "src/myHuffmTree.hpp"
#include "src/myString.cpp"
#include <unordered_map>
using namespace std;

unordered_map<char, size_t>hashMap = {
	{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
};

int main() {
	HuffmTree<char>huff(hashMap);

	unordered_map<char, String> table = huff.exportTable();
	for (auto &x : table) {
		cout << x.first << " " << x.second << "\n";
	}

	String s = huff.exportHuff({'a', 'b', 'c', 'd', 'e', 'f'});
	cout << s << "\n";

	Array<char> arr = huff.explain(s);

	for (auto x : arr) {
		cout << x;
	}
	return 0;
}