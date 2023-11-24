#ifndef MYHUFFMTREE_IMPL_HPP_
#define MYHUFFMTREE_IMPL_HPP_

#include "myHuffmTree_decl.hpp"

//
// 构造函数
//
// @param data 被构造的数组
//
template<typename T>
HuffmTree<T>::HuffmTree(Array<T> data) {
	for (const auto &x: data) {
		huffFrqc[x] ++;
	}
	buildHuffmTree();
}


//
// 构造函数
//
// @param frqc 出现的频率集合
//
template<typename T>
HuffmTree<T>::HuffmTree(std::unordered_map<T, size_t> frqc) {
	huffFrqc = frqc;
	buildHuffmTree();
}

//
// 导出哈夫曼编码
//
template<typename T>
String HuffmTree<T>::exportHuff(Array<T> data) {
	String res = "";
	for (const auto &x : data) {
		res += huffCode[x];
	}
	return res;
}

//
// 导出哈夫曼编码表
//
template<typename T>
std::unordered_map<T, String> HuffmTree<T>::exportTable() const {
	return huffCode;
}

//
// 解析哈夫曼编码
//
// @param code 待解析的哈夫曼编码
//
template<typename T>
Array<T> HuffmTree<T>::explain(String code) {
	Array<T> res;
	Node* root = heap.top();
	for (const auto &x : code) {
		if ( x == '0' ) {
			root = root -> left;
		}
		else {
			root = root -> right;
		}

		if ( !root -> flag ) {
			res.push_back(root -> data);
			root = heap.top();
		}
	}

	return res;
}

//
// generateCode 生成哈夫曼编码函数
//
// @param root 根结点  code 编码
//
template<typename T>
void HuffmTree<T>::generateCode(typename HuffmTree<T>::Node* root, String code) {
	if ( root != nullptr ) {
		if ( !root -> flag ) {
			huffCode[root -> data] = code;
		}

		generateCode(root -> left, code + "0");
		generateCode(root -> right, code + "1");
	}
}

//
// buildHuffmTree 生成哈夫曼树 
//
template<typename T>
void HuffmTree<T>::buildHuffmTree() {
	for (const auto &x : huffFrqc) {
		heap.insert(new Node(x.first, x.second));
	}

	while ( heap.size() > 1 ) {
		Node* l = heap.top();
		heap.pop();

		Node* r = heap.top();
		heap.pop();

		Node* tmp = new Node(T(), l -> frq + r -> frq);
		tmp -> flag = true;
		tmp -> left = l;
		tmp -> right = r;

		heap.insert(tmp);
	}

	generateCode(heap.top(), "");
}

#endif